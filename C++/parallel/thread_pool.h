#include <condition_variable>
#include <thread>
#include <mutex>
#include <queue>
#include <atomic>
#include <exception>
#include <utility>
#include <future>
#include <vector>
#include <functional>

template <class Value, class Container = std::deque<Value>>
class thread_safe_queue {
	std::size_t capacity;
	std::mutex _mutex;
	std::condition_variable not_full;
	std::condition_variable not_empty;
	Container _queue;
	bool down;
public:
	explicit thread_safe_queue(size_t _capacity) : capacity(_capacity), down(false) {}
	void enqueue(Value&& v);
	bool pop(Value& v);
	bool shutdown();
};


template <class Value, class Container>
void thread_safe_queue<Value, Container>::enqueue(Value&& item) {
	std::unique_lock<std::mutex> mut(_mutex);

	if (down)
		throw std::exception();
	while (_queue.size() >= capacity) {
		not_full.wait(mut);
		if (down)
			throw std::exception();
	}

	_queue.push_back(std::move(item));
	not_empty.notify_one();
}

template <class Value, class Container>
bool thread_safe_queue<Value, Container>::pop(Value& item) {
	std::unique_lock<std::mutex> mut(_mutex);

	while (_queue.empty()) {
		if (!down)
			not_empty.wait(mut);
		else return false;
	}

	item = std::move(_queue.front());
	_queue.pop_front();
	not_full.notify_one();

	return true;
}

template <class Value, class Container>
bool thread_safe_queue<Value, Container>::shutdown() {
	if (down) return false;								  //change in thread_queue
	std::unique_lock<std::mutex> mut(_mutex);
	down = true;
	not_empty.notify_all();
	not_full.notify_all();
	return true;
}


// Pool2.cpp: определяет точку входа для консольного приложения.



template <class R> //Result type
class thread_pool {
	typedef std::pair<std::function<R()>, std::promise<R>> typeq;
	std::vector<std::thread> workers;
	thread_safe_queue<typeq> _queue;
	std::atomic<int> work_in;
	std::condition_variable not_empty;
	std::mutex mut;
	std::size_t num_workers;
	void work();
	//std::atomic<bool> sht_down;

public:
	explicit thread_pool(std::size_t _num_workers);
	std::future<R> submit(std::function<R()> func);
	void shutdown();
	~thread_pool();
};

template <class R>
thread_pool<R>::thread_pool(std::size_t _num_workers) : _queue(1024), num_workers(_num_workers)/*,
sht_down(false)*/
{
	work_in.store(0);

	for (std::size_t i = 0; i < num_workers; ++i) {
		workers.emplace_back(std::thread([&]() {
			work();
		}));
		//workers[i].detach();
	}
	
}

template <class R>
std::future<R> thread_pool<R>::submit(std::function<R()> func) {
	std::promise<R> prom = std::move(std::promise<R>());
	auto future = std::move(prom.get_future());
	_queue.enqueue(std::move(std::make_pair(func, std::move(prom))));

	return std::move(future);
}
//typedef std::pair<std::function<R()>, std::shared_ptr<std::promise<R>>> typeq;
template <class R>
void thread_pool<R>::work() {
	typeq el;
	work_in.fetch_add(1);

	while (true) {
		try {
			if (!(_queue.pop(el))) break;
			auto res = std::move(el.first());
			el.second.set_value(std::move(res));
		}
		catch (...) {
			std::exception_ptr err = std::current_exception();
			el.second.set_exception(err);
		}
	}
	work_in.fetch_add(-1);
	std::unique_lock<std::mutex> m(mut);
	if (work_in.load() == 0) {
		not_empty.notify_one();
	}
}

template <typename Value>
thread_pool<Value>::~thread_pool() {
	shutdown();
}

template <class R>
void thread_pool<R>::shutdown() {
	if (!_queue.shutdown())
		return;
	
	

	//sht_down = true;
	std::unique_lock<std::mutex> m(mut);
	while (work_in.load() != 0) {
		not_empty.wait(m);
	}

	for (auto& t : workers)
		t.join();
}