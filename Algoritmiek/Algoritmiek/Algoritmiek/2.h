
#ifndef h2
#define h2

#include <array>
#include <list>
#include <queue>
#include <vector>
#include <iostream>
#include <functional>
#include <stack>
#include <set>
#include <map>
#include <deque>

using Vertex = char;
using Path = std::vector<Vertex>;

class Graph
{
public:
    typename std::vector<Vertex>::const_iterator cbegin(Vertex v) const;
    typename std::vector<Vertex>::const_iterator cend() const;
private:
    mutable Vertex currentVertex;
    typedef std::map<Vertex,std::vector<Vertex>> GraphMap;
    static GraphMap adjacents;
};

Path dfs(const Graph &graph, const Vertex &start, std::function<bool(const Vertex &vertex)> goalTest);
Path bfs(const Graph &graph, const Vertex &start, std::function<bool(const Vertex &vertex)> goalTest);

#endif 
