
#include "ttt.h"
#include <iostream>
#include <algorithm>
#include <map>
#include <thread>
#include <condition_variable>
#include <atomic>
#include <stdint.h>
#include <queue>
#include <vector>
#include <memory>

using namespace std;

class ThreadPool;
class Worker;
condition_variable cv;

unsigned const n_trials = 1000;
array<int, 9> scores = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

enum class PlayerType
{
	Human,
	Computer
};

namespace natives
{
	typedef int16_t             int16;
	typedef int32_t             int32;
	typedef int64_t             int64;

	typedef std::atomic_bool    flag;
}

class ThreadPool
{
public:
	struct BaseTask
	{
		virtual void runTask() = 0;
	};

	template <class T> struct Task : public BaseTask
	{
		Task(T task)
			: m_Task(task)
		{}

		virtual void runTask()
		{
			m_Task();
		}

		T m_Task;
	};

	template <class T, class P1> struct ParameteredTask : public BaseTask
	{
		ParameteredTask(T task, const P1& p1)
			: m_Task(task), m_P1(p1)
		{}

		virtual void runTask()
		{
			m_Task(m_P1);
		}

		T  m_Task;
		P1 m_P1;
	};

	typedef std::queue<BaseTask*>                       TaskQueue;
	typedef std::vector <std::shared_ptr<std::thread> > WorkerGroup;
	typedef std::mutex                                  QueueLock;
	typedef std::unique_lock<std::mutex>                QueueGuard;
	typedef std::condition_variable                     WorkerSignal;

	static void thMain(TaskQueue* queue, QueueLock* qlock, WorkerSignal* signal, natives::flag* online)
	{
		while (*online)
		{
			BaseTask* task = nullptr;

			std::shared_ptr<ThreadPool::QueueGuard> qguard(std::make_shared<ThreadPool::QueueGuard>(*qlock));

			if (!queue->empty())
			{
				task = queue->front();
				queue->pop();

				qguard.reset();
			}
			else if (*online)
			{
				signal->wait(*qguard);
			}

			if (nullptr != task)
			{
				task->runTask();
				delete task;
			}
		}
	}

	ThreadPool(natives::int32 size)
		: m_Online(true)
	{
		for (natives::int32 counter = 0; size > counter; ++counter)
		{
			m_Workers.push_back(std::make_shared<std::thread>(thMain, &m_Queue, &m_QLock, &m_Signal, &m_Online));
		}
	}

	void addThread()
	{
		m_Workers.push_back(std::make_shared<std::thread>(thMain, &m_Queue, &m_QLock, &m_Signal, &m_Online));
	}

	~ThreadPool()
	{
		m_Online = false;

		m_Signal.notify_all();

		std::for_each(m_Workers.begin(), m_Workers.end(), [](std::shared_ptr<std::thread> thread)->void {thread->join(); });
	}

	void enqueue(BaseTask* task)
	{
		QueueGuard guard(m_QLock);
		m_Queue.push(task);

		m_Signal.notify_all();
	}

	template <class T> void enqueue(T task)
	{
		QueueGuard guard(m_QLock);
		m_Queue.push(new Task<T>(task));

		m_Signal.notify_all();
	}

	template <class T, class P1> void enqueue(T task, const P1& p1)
	{
		QueueGuard guard(m_QLock);
		m_Queue.push(new ParameteredTask<T, P1>(task, p1));

		m_Signal.notify_all();
	}

	natives::int32 getQueueSize()
	{
		QueueGuard guard(m_QLock);
		natives::int32 size = m_Queue.size();

		return size;
	}

	WorkerGroup   m_Workers;
	TaskQueue     m_Queue;
	QueueLock     m_QLock;
	WorkerSignal  m_Signal;
	natives::flag m_Online;
};

void mcUpdateScores(array<int, 9> &subscores, State &trialboard, Player &winner)
{
	for (int i = 0; i < 9; i++)
	{
		if (winner == Player::X)
		{
			if (trialboard[i] == Player::X)
			{
				subscores[i]++;
			}

			if (trialboard[i] == Player::O)
			{
				subscores[i]--;
			}
		}

		if (winner == Player::O)
		{
			if (trialboard[i] == Player::X)
			{
				subscores[i]--;
			}

			if (trialboard[i] == Player::O)
			{
				subscores[i]++;
			}
		}
	}

	for (int i = 0; i < 9; i++)
	{
		scores[i] = scores[i] + subscores[i];
	}
}

void mcTrial(State &board)
{
	State trialboard = board;
	array<int, 9> subscores = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	Player winner;

	vector<Move> moves = getMoves(trialboard);

	while (moves.size() != 0)
	{
		trialboard = doMove(trialboard, moves[(rand() % moves.size())]);
		moves = getMoves(trialboard);
	}

	winner = getWinner(trialboard);

	mcUpdateScores(subscores, trialboard, winner);
}

Move getBestMove(State &board)
{
	int highest = -9999;
	int index = -1;

	for (int i = 0; i < 9; i++)
	{
		if (scores[i] > highest && board[i] == Player::None)
		{
			highest = scores[i];
			index = i;
		}
	}

	return index;
}

Move mcMove(State &board, const Player &player)
{
	scores = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	ThreadPool pool(10);

	for (int i = 0; i < 10000; ++i)
	{
		pool.enqueue(mcTrial, ref(board));
	}
	
	return getBestMove(board);
}

int main()
{
	srand(time(0));

	map<Player, PlayerType> playerType;
	playerType[Player::X] = PlayerType::Human;
	playerType[Player::O] = PlayerType::Computer;

	State board =
	{
			Player::None, Player::None, Player::None,
			Player::None, Player::None, Player::None,
			Player::None, Player::None, Player::None };
	cout << board << endl;

	vector<Move> moves = getMoves(board);
	while (moves.size() > 0)
	{
		if (playerType[getCurrentPlayer(board)] == PlayerType::Human)
		{
			cout << "+-+-+-+" << endl
				<< "|0|1|2|" << endl
				<< "+-+-+-+" << endl
				<< "|3|4|5|" << endl
				<< "+-+-+-+" << endl
				<< "|6|7|8|" << endl
				<< "+-+-+-+" << endl
				<< endl;
			cout << "Enter a move ( ";
			for (Move m : moves)
				cout << m << " ";
			cout << "): ";
			Move m;
			cin >> m;
			board = doMove(board, m);
		}

		else
		{
			board = doMove(board, mcMove(board, getCurrentPlayer(board)));
		}
		cout << board << endl;
		moves = getMoves(board);
	}

	return 0;
}
