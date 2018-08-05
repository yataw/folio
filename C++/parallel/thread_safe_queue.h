#include <condition_variable>
#include <thread>
#include <mutex>
#include <queue>
#include <atomic>
#include <exception>
#include <utility>

template <class Value, class Container = std::deque<Value>>
class thread_safe_queue {
	std::size_t capacity;
	std::mutex _mutex;
	std::condition_variable full;
	std::condition_variable empty;
	Container _queue;
	std::atomic<bool> down;
public:
	explicit thread_safe_queue(size_t _capacity) : capacity(_capacity), down(false) {}
	void enqueue(Value v);
	void pop(Value& v);
	void shutdown();
};


template <class Value, class Container>
void thread_safe_queue<Value, Container>::enqueue(Value item) {
	std::unique_lock<std::mutex> mut(_mutex);

	if (down.load())
		throw std::exception();

	while (_queue.size() >= capacity) {
		full.wait(mut);
		if (down.load())
			throw std::exception();
	}

	_queue.push_back(std::move(item));
	empty.notify_one();
}

template <class Value, class Container>
void thread_safe_queue<Value, Container>::pop(Value& item) {
	std::unique_lock<std::mutex> mut(_mutex);

	while (_queue.size() <= 0) {
		if (!down.load())
			 empty.wait(mut);
		else throw std::exception();
	}

	item = std::move(_queue.front());
	_queue.pop_front();
	full.notify_one();
}

template <class Value, class Container>
void thread_safe_queue<Value, Container>::shutdown() {
	std::unique_lock<std::mutex> mut(_mutex);
	down.store(true);
	empty.notify_all();
	full.notify_all();
}
