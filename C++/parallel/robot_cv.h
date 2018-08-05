#include <stdio.h>
#include <condition_variable>
#include <thread>
#include <mutex>
#include <iostream>
#include <atomic>
#include <string>

/*Left leg waits right leg*/
class robot {
	std::condition_variable cl, cr; //condition left, condition right
	std::mutex mut, m_l, m_r;
	std::size_t flag; //left step = 0, right step = 1
public:
	void step(const std::string& str) {
		if (str == "left") m_l.lock();
		if (str == "right") m_r.lock();

		std::unique_lock<std::mutex> m(mut);
		if (str == "left") {
			while (!flag) cl.wait(m);
			flag = !flag;
			cr.notify_one();
			m_l.unlock();
		}
		if (str == "right") {
			while (flag) cr.wait(m);
			flag = !flag;
			cl.notify_one();
			m_r.unlock();
		}
		std::cout << str << std::endl;
	}
};