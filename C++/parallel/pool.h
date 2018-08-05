#include <stdio.h>
#include <tchar.h>
#include <condition_variable>
#include <thread>
#include <mutex>
#include <queue>
#include <iostream>
#include <atomic>
#include <cmath>
#include <future>
#include <string>
#include "block_queue_unlim.h"

template <class R> //Result type
class thread_pool {
	typedef std::pair<std::function<R()>, std::shared_ptr<std::promise<R>>> typeq;
	std::thread* workers;
	thread_safe_queue<typeq> _queue;
	std::atomic<int> work_in;
	std::condition_variable empty;
	std::mutex mut;
public:
	static std::size_t default_num_workers() {
		return	std::max(1u, std::thread::hardware_concurrency());
	}

	thread_pool(std::size_t _capasity = default_num_workers());

	std::future<R> submit(std::function<R()> func);
	void shutdown();
};

template <class R>
thread_pool<R>::thread_pool(std::size_t _capasity = default_num_workers()) {
	work_in.store(0);
	workers = new std::thread[_capasity];

	for (std::size_t i = 0; i < _capasity; ++i) {
		workers[i] = std::thread([&]() {
			typeq el;
			work_in.fetch_add(1);
			while (true) {
				if (!_queue.pop(el)) break;
				el.second->set_value(el.first());
			}
			work_in.fetch_add(-1);
			std::unique_lock<std::mutex> m(mut);
			if (work_in == 0) empty.notify_one();

		});
		workers[i].detach();
	}

}

template <class R>
std::future<R> thread_pool<R>::submit(std::function<R()> func) {
	auto prom = std::make_shared<std::promise<R>>();
	if (!_queue.enqueue(std::make_pair(func, prom))) {
		std::cerr << "_queue.enqueue() ERROR";
		throw 1;
	}
	return prom->get_future();
}


template <class R>
void thread_pool<R>::shutdown() {
	_queue.shutdown();
	std::unique_lock<std::mutex> m(mut);
	while (work_in != 0) {
		empty.wait(m);
	}
}