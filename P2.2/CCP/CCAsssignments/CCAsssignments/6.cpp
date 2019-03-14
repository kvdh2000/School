/*
#include <thread>
#include <mutex>
#include <iostream>
#include <vector>
#include <deque>
#include <atomic>

class ThreadPool;

std::condition_variable ready_cv;

class Worker {
public:
	Worker(ThreadPool &s) : pool(s) { }
	void operator()();
private:
	ThreadPool &pool;
};

class ThreadPool {
public:
	ThreadPool(size_t threads);
	template<class F> void enqueue(F f);
	~ThreadPool();
private:
	friend class Worker;

	std::vector<std::thread> workers;
	std::deque<std::function<void()>> tasks;

	std::mutex queue_mutex;
	bool stop;
};

void Worker::operator()()
{
	std::function<void()> task;

	while (true)
	{
		std::unique_lock<std::mutex> locker(pool.queue_mutex);
		ready_cv.wait(locker, [&] {return !pool.tasks.empty() || pool.stop; });

		if (pool.stop) return;
		if (!pool.tasks.empty())
		{
			task = pool.tasks.front();
			pool.tasks.pop_front();
			locker.unlock();
			task();
		}
	}
}

ThreadPool::ThreadPool(size_t threads) : stop(false)
{
	for (size_t i = 0; i < threads; ++i)
		workers.push_back(std::thread(Worker(*this)));
}

ThreadPool::~ThreadPool()
{
	stop = true; 
	ready_cv.notify_all();
	for (auto &thread : workers)
		thread.join();
}

template<class F>
void ThreadPool::enqueue(F f)
{
	std::unique_lock<std::mutex> lock(queue_mutex);
	tasks.push_back(std::function<void()>(f));
	ready_cv.notify_one();
}

int main()
{
	ThreadPool pool(4);

	for (int i = 0; i < 8; ++i) pool.enqueue([i]() { std::cout << "Text printed by worker " << i << std::endl; });
	
	std::cin.ignore();
	return 0;
}
*/