/*
#include <thread>
#include <mutex>
#include <iostream>
#include <vector>
#include <deque>
#include <atomic>

class ThreadPool;

// forward declare
std::condition_variable ready_cv;
std::condition_variable processed_cv;
std::atomic<bool> ready(false);
std::atomic<bool> processed(false);

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

	// in real life you need a variable here like while(!quitProgram) or your
	// program will never return. Similarly, in real life always use `wait_for`
	// instead of `wait` so that periodically you check to see if you should
	// exit the program
	while (true)
	{
		std::unique_lock<std::mutex> locker(pool.queue_mutex);
		ready_cv.wait(locker, [] {return ready.load(); });

		if (pool.stop) return;
		if (!pool.tasks.empty())
		{
			task = pool.tasks.front();
			pool.tasks.pop_front();
			locker.unlock();
			task();
			processed = true;
			processed_cv.notify_one();
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
	stop = true; // stop all threads

	for (auto &thread : workers)
		thread.join();
}

template<class F>
void ThreadPool::enqueue(F f)
{
	std::unique_lock<std::mutex> lock(queue_mutex);
	tasks.push_back(std::function<void()>(f));
	processed = false;
	ready = true;
	ready_cv.notify_one();
	processed_cv.wait(lock, [] { return processed.load(); });
}

int main()
{
	ThreadPool pool(4);

	for (int i = 0; i < 8; ++i) pool.enqueue([i]() { std::cout << "Text printed by worker " << i << std::endl; });

	std::cin.ignore();
	return 0;
}
*/