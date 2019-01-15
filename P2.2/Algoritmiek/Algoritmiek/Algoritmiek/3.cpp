/*
#include "3.h"

typename std::vector<Vertex>::const_iterator Graph::cbegin(Vertex v) const
{
	adjacents.clear();

	adjacents.push_back(doMove(v, Move::b, 0, 2));

	for (int r = 0; r < 3; r++) 
	{
		for (int c = 0; c < 3; c++) 
		{
			if (v[r][c] == 1) 
			{
				if (r == 0)
				{
					adjacents.push_back(doMove(v, Move::b, r, c));
					adjacents.push_back(doMove(v, Move::c, r, c));
				}

				if (r == 1)
				{
					adjacents.push_back(doMove(v, Move::a, r, c));
					adjacents.push_back(doMove(v, Move::c, r, c));
				}

				if (r == 2)
				{
					adjacents.push_back(doMove(v, Move::a, r, c));
					adjacents.push_back(doMove(v, Move::b, r, c));
				}
			}

			if (v[r][c] == 2)
			{
				if (!v[r][c + 1] == 1)
				{
					if (r == 0)
					{
						if (!v[1][2] == 1)
						{
							adjacents.push_back(doMove(v, Move::b, r, c));
						}

						if (!v[2][2] == 1)
						{
							adjacents.push_back(doMove(v, Move::c, r, c));
						}
					}

					if (r == 1)
					{
						if (!v[0][2] == 1)
						{
							adjacents.push_back(doMove(v, Move::a, r, c));
						}

						if (!v[2][2] == 1)
						{
							adjacents.push_back(doMove(v, Move::c, r, c));
						}
					}

					if (r == 2)
					{
						if (!v[0][2] == 1)
						{
							adjacents.push_back(doMove(v, Move::a, r, c));
						}

						if (!v[1][2] == 1)
						{
							adjacents.push_back(doMove(v, Move::b, r, c));
						}
					}
				}
			}

			if (v[r][c] == 3)
			{
				if (v[r][c + 1] == 0 && v[r][c + 2] == 0)
				{
					if (r == 0)
					{
						if (!v[1][2] == 1 || !v[1][1] == 2)
						{
							adjacents.push_back(doMove(v, Move::b, r, c));
						}

						if (!v[2][2] == 1 || !v[2][1] == 2)
						{
							adjacents.push_back(doMove(v, Move::c, r, c));
						}
					}

					if (r == 1)
					{
						if (!v[0][2] == 1 || !v[0][1] == 2)
						{
							adjacents.push_back(doMove(v, Move::a, r, c));
						}

						if (!v[2][2] == 1 || !v[2][1] == 2)
						{
							adjacents.push_back(doMove(v, Move::c, r, c));
						}
					}

					if (r == 2)
					{
						if (!v[0][2] == 1 || !v[0][1] == 2)
						{
							adjacents.push_back(doMove(v, Move::a, r, c));
						}

						if (!v[1][2] == 1 || !v[1][1] == 2)
						{
							adjacents.push_back(doMove(v, Move::b, r, c));
						}
					}
				}
			}
		}
	}

	return adjacents.cbegin();
}

typename std::vector<Vertex>::const_iterator Graph::cend() const
{
	return adjacents.cend();
}

Vertex doMove(const Vertex &v, const Move &m, int ro, int co)
{
	bool done=false;
	Vertex n = v;

	for (int r = 0; r < 3 && !done; r++) {
		for (int c = 0; c < 3 && !done; c++) {
				switch (m)
				{
				case Move::a: std::swap(n[ro][co], n[0][co]); done = true; break;
				case Move::b: std::swap(n[ro][co], n[1][co]); done = true; break;
				case Move::c: std::swap(n[ro][co], n[2][co]); done = true; break;
				}
		}
	}

	return n;
}

std::ostream &operator<<(std::ostream &os, const Vertex &state)
{
	for (int r = 0; r < 3; r++) 
	{
		for (int c = 0; c < 3; c++) 
		{
			os << state[r][c];
		}
		os << std::endl;
	}
	return os;
}

Path dfs(const Graph &graph, const Vertex &start, std::function<bool(const Vertex &vertex)> goalTest)
{
	std::stack<Path> queue;
	std::set<Vertex> visited;
	Path path;

	queue.push(path);
	while (!queue.empty()) 
	{
		path = queue.top();
		queue.pop();

		Vertex last;
		if (path.size() == 0) 
		{
			last = start;
		} 
		
		else
		{
			last = path.back();
		}

		if (goalTest(last))
		{
			return path; // path is a vector of Vertices
		}

		if (visited.find(last) == visited.end()) 
		{
			visited.insert(last);
			for (auto it = graph.cbegin(last); it != graph.cend(); it++) 
			{
				Path n = path;
				n.push_back(*it);
				queue.push(n);
			}
		}
	}
	return Path();
}

Path bfs(const Graph &graph, const Vertex &start, std::function<bool(const Vertex &vertex)> goalTest)
{
	std::deque<Path> queue;
	std::set<Vertex> visited;
	Path path;

	queue.push_back(path);

	while (!queue.empty())
	{
		path = queue.front();
		queue.pop_front();

		Vertex last;

		if (path.size() == 0)
		{
			last = start;
		}

		else
		{
			last = path.back();
		}

		if (goalTest(last))
			return path;

		for (auto it = graph.cbegin(last); it != graph.cend(); it++)
		{ // extend path with new Vertex
			Path n = path;
			if (visited.find(*it) == visited.end())
			{
				n.push_back(*it);
				queue.push_back(n);
			}

		}

		visited.insert(last);
	}
	return Path();
}

int main()
{
	Graph graph;

	Vertex start = {{
		{{3, 2, 1}},
		{{0, 0, 0}},
		{{0, 0, 0}},
	}};
	
	Vertex goal = {{
		{{0, 0, 0}},
		{{0, 0, 0}},
		{{3, 2, 1}}
	}};

	Path path = bfs(graph, start, [&](Vertex v) { return (v == goal); });

	std::cout << start << std::endl;
	for (auto it = path.cbegin(); it != path.cend(); it++)
	{
		std::cout << *it << std::endl;
	}

	return 0;
}
*/