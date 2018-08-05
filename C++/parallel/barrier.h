#include <condition_variable>
#include <mutex>

class barrier {
	std::condition_variable cv;
	std::size_t first; //first gate counter
	std::size_t capacity;
	std::size_t btw; //between gates counter
	std::mutex _mutex;
public:
	barrier(size_t num_threads) : first(0), capacity(num_threads), btw(0) {}
	void enter();
};

void barrier::enter() {
	std::unique_lock<std::mutex> m(_mutex);
	++first;
	if (btw == 0 && first == capacity) {
		btw = capacity;
		first = 0;
		cv.notify_all();
	}
	else {
		cv.wait(m);
	}
	--btw;
}