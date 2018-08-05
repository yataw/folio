#include <stdio.h>
#include <tchar.h>
#include <condition_variable>
#include <thread>
#include <mutex>
#include <queue>
#include <iostream>
#include <atomic>

template <class T>
class thread_safe_queue {
	std::mutex _mutex;
	std::condition_variable full;
	std::condition_variable empty;
	std::queue<T> _queue;
	std::atomic<bool> down;
public:
	thread_safe_queue(): down(false) {}
	thread_safe_queue(const thread_safe_queue&) = delete;

	bool enqueue(T item);
	bool pop(T& item);
	void shutdown();
};

template <class T>
bool thread_safe_queue<T>::enqueue(T item) {
	std::unique_lock<std::mutex> mut(_mutex); 

	if (down.load()) return 0;
	_queue.push(item);
	empty.notify_one();
	return 1;
}

template <class T>
bool thread_safe_queue<T>::pop(T& item) {
	std::unique_lock<std::mutex> mut(_mutex);

	while (_queue.size() <= 0)
		empty.wait(mut);

	item = _queue.front(); 
	_queue.pop();
	full.notify_one();

	if (down.load()) return 0;
	return 1;
}

template <class T>
void thread_safe_queue<T>::shutdown() {
	std::unique_lock<std::mutex> mut(_mutex);
	down.store(true);
	empty.notify_all();
}