#include <iostream>
#include <utility>
#include <list>
#include <vector>
#include <stack>
#include <set>
#include <cstring>
#include <algorithm>
#include <map>

using namespace std;
class SCC {
public:
  SCC(int n, int c): node(n), cost(c) { };
  int node;
  int cost;
};

bool order_by_cost(SCC one, SCC two)
{
  return one.cost < two.cost;
}

class graph {
public:
  vector<list<int>>     adjacent;
  vector<list<int>>     adjacent_transpose;
  int64_t               junctions_number, time, sccs_counter;
  vector<bool>          visited;
  vector<int64_t>       cost;
  map<int, int, greater<int>>         f;
  vector<vector<SCC>>   sccs;
  graph(int64_t junctions, vector<int64_t>& junction_costs);
  void process_edge(int64_t u, int64_t v);
  void dfs(int64_t node);
  void dfs_t(int64_t node);
  pair<int64_t, int64_t> solution();
};


graph::graph(int64_t junctions, vector<int64_t>& junction_costs): cost(junction_costs),
								  sccs(junctions),
								  visited(junctions),
								  adjacent(junctions),
								  adjacent_transpose(junctions)
{
  this->junctions_number = junctions;
  this->time = this->sccs_counter = 0;
}

void graph::process_edge(int64_t u, int64_t v)
{
  this->adjacent[u].push_back(v);
  this->adjacent_transpose[v].push_back(u);
}


void graph::dfs(int64_t node) {
  this->visited[node] = 1;
  this->time++;
  for (auto it = this->adjacent[node].begin(); it != this->adjacent[node].end(); ++it) {

    if (!this->visited[*it]) // Don't visit it if it's been visited already
	dfs(*it);
  }

  // Store exit node's time
  this->time++;
  this->f[time] = node;
  //  this->f[time] = node;
}

void graph::dfs_t(int64_t node)
{
  if (this->visited[node])
    return;

  //  cout << __FUNCTION__ << node << " Adding at " << sccs_counter << endl;

  
  sccs[this->sccs_counter].push_back(SCC(node, this->cost[node]));
  this->visited[node] = 1;

  for (auto it = this->adjacent_transpose[node].begin(); it != this->adjacent_transpose[node].end(); ++it) {
  
    if (this->visited[*it])
      continue;

    dfs_t(*it);
  }
}
   
pair<int64_t, int64_t> graph::solution() {
  int64_t cost, ways;

  cost = 0;
  ways = 1;
  for (auto it = this->sccs.begin(); it != this->sccs.end(); ++it) {
    if (it->empty())
      continue;

    // cout << "SCC ";
    // for (auto scc_item = it->begin(); scc_item != it->end(); ++scc_item) {
    //   cout << scc_item->node << ",";
    // }
    // cout << endl;
    
    sort(it->begin(), it->end(), order_by_cost);

    int64_t count_min = 1;
    cost += it->begin()->cost;
    //cout << "cost += " << it->begin()->cost << endl;

    // Add all the ones having the same cost as the form a possible solution
    for (auto scc_item = it->begin() + 1; scc_item != it->end(); ++scc_item) {
      if (scc_item->cost != it->begin()->cost)
	break;
      count_min++;
    }
    ways *= count_min;
  }
  return pair<int64_t, int64_t>(cost, ways);
}

int main() {
  int64_t junctions, edges;

  cin >> junctions;
  vector<int64_t> costs(junctions, 0);

  for (auto i = 0; i < junctions; i++)
    cin >> costs[i];
  
  graph graph(junctions, costs);

  cin >> edges;
  for (int64_t i = 0; i < edges; i++) {
    int64_t u, v;
    cin >> u >> v;
    graph.process_edge(u - 1, v - 1);
  }
  
  for (int64_t i = 0; i < junctions; i++) {
    if (!graph.visited[i])
      graph.dfs(i);
  }

  graph.visited.clear();
  graph.visited.resize(junctions, false);
  for (const auto& key : graph.f) {
    graph.dfs_t(key.second);
    graph.sccs_counter++;
  }
  
  // for (int i = junctions * 2 + 2 - 1; i >= 0; i--) {
  //   if (graph.f[i] == -1)
  //     continue;
  //   graph.dfs_t(graph.f[i]);
  //   graph.sccs_counter++;
  // }
  pair<int64_t, int64_t> solution = graph.solution();
  cout << solution.first << " " << solution.second % 1000000007 << endl;
  return 0;
}

