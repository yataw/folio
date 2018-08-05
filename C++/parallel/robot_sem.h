#include <stdio.h>
#include <condition_variable>
#include <thread>
#include <mutex>
#include <iostream>
#include <atomic>
#include <string>


/*Right leg waits left leg*/
class semaphore {
	std::condition_variable cv;
	int counter;
	std::mutex mut;
public:
	semaphore(std::size_t count) :counter(count) {}
	void wait() {
		std::unique_lock<std::mutex> m(mut);
		while (counter < 0) cv.wait(m);
		--counter;
	}

	void signal() {
		std::unique_lock<std::mutex> m(mut);
		++counter;
		cv.notify_one();
	}
};

class robot {
	semaphore left, right;

public:
	robot() :left(0), right(-1) {}
	void step(const std::string& str) {

		if (str == "left") {
			left.wait();
			std::cout << str << std::endl;
			right.signal();
		}
		else {
			right.wait();
			std::cout << str << std::endl;
			left.signal();
		}
	}
};