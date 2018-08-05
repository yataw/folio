#include <stdio.h>
#include <atomic>
#include <thread>
#include <array>
#include <vector>
#include <iostream>


template <typename T>
struct atomwrapper //оболочка, чтобы можно было расширить vector<atomic <T>> (используя конструктор копирования)
{
	std::atomic<T> _a;

	atomwrapper()
		:_a()
	{}

	atomwrapper(const std::atomic<T> &a)
		:_a(a.load())
	{}

	atomwrapper(const atomwrapper &other)
		:_a(other._a.load())
	{}

	atomwrapper &operator=(const atomwrapper &other)
	{
		_a.store(other._a.load());
	}

	T load() {
		return _a.load();
	}

	void store(T val) {
		_a.store(val);
	}

};

struct atom_data {
	std::size_t offset;
	std::size_t lvl;
};


class peterson_mutex {
	std::array<atomwrapper<bool>, 2> want;
	atomwrapper<int> victim;

public:
	peterson_mutex() {
		want[0].store(false);
		want[1].store(false);
		victim.store(0);
	}

	void lock(int t) {
		want[t].store(true);
		victim.store(t);

		while (want[1 - t].load() && victim.load() == t) {
			std::this_thread::yield();
		}
	}

	void unlock(int t) {
		want[t].store(false);
	}
};


class tree_mutex {
	std::size_t N; //Кол-во вершин есть max (2^N - 1) : 2^N <= num_threads
	std::vector<peterson_mutex> tree;
	std::vector<std::size_t> en_po; //[enter_point] точка входа (направление) в м.Петерсона. (0 или 1)
	std::vector<std::size_t> pos; //[thread_position] номер мьютекса, в котором сейчас находится thread с номером thread_id
								  /*enter_point не атомарен, т.к. писать/читать туда(оттуда) единовременно может только один thread. (после lock'а соответствующего мьютекса*/
								  /*thread_position не атомарен, т.к. писать/читать из thread_pos [id] будет только поток с номером id (т.е. это ветор личных данных потока)*/
public:
	tree_mutex(std::size_t num_threads) {
		N = 2;

		while (N < num_threads) {
			N *= 2;
		}
		--N;

		tree.resize(N);
		en_po.resize(N, 0);
		pos.resize(num_threads);

		for (std::size_t i = 0; i < num_threads; ++i) {
			pos[i] = N + i;
		}
	}

	void lock(std::size_t thread_index);
	void unlock(std::size_t thread_index);
};


void tree_mutex::lock(std::size_t thread_index) {

	while (((pos[thread_index] - 1) / 2) > 0) {
		tree[(pos[thread_index] - 1) / 2].lock((pos[thread_index] + 1) % 2);
		en_po[(pos[thread_index] - 1) / 2] = (pos[thread_index] + 1) % 2;
		pos[thread_index] = (pos[thread_index] - 1) / 2;
	}

	tree[0].lock((pos[thread_index] + 1) % 2);
	en_po[0] = (pos[thread_index] + 1) % 2;
	pos[thread_index] = 0;
}

void tree_mutex::unlock(std::size_t thread_index) {
	while (pos[thread_index] != N + thread_index) {
		pos[thread_index] = 2 * (pos[thread_index]) + en_po[pos[thread_index]] + 1;
		tree[(pos[thread_index] - 1) / 2].unlock(en_po[(pos[thread_index] - 1) / 2]);
	}
}
