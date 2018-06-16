#include <iostream>
#include <utility>
#include <list>
#include <vector>
#include <stack>
#include <set>
#include <cstring>
#include <algorithm>

using namespace std;

class F {
public:
  int node;
  int time;
  int cost;
  F(): node(0), time(0), cost(0) { };
};

bool order_by_time(F one, F two)
{
  return one.time > two.time;
}

bool order_by_cost(F one, F two)
{
  return one.cost < two.cost;
}

class graph {
public:
  int **            matrix;
  int               junctions_number, time, sccs_counter;
  int *             visited, * visited_t;
  F *               f;
  vector<vector<F>> sccs;
  graph(int junctions, vector<int>& junction_costs);
  void process_edge(int u, int v);
  void dfs(int node);
  void dfs_t(int node);
  pair<int, int> solution();
};


graph::graph(int junctions, vector<int>& junction_costs): sccs(junctions)
{
  this->junctions_number = junctions;
  this->visited = new int[junctions]();
  this->visited_t = new int[junctions]();
  this->matrix = new int*[junctions];
  this->f = new F[junctions]();
  for (auto i = 0; i < junctions; i++) {
    this->matrix[i] = new int[junctions]();
    this->f[i].cost = junction_costs[i];
  }
  
  this->time = this->sccs_counter = 0;
}

void graph::process_edge(int u, int v)
{
  this->matrix[u][v] = 1;
}


void graph::dfs(int node) {
  this->visited[node] = 1;
  this->time++;
  for (int i = 0; i < this->junctions_number; i++) {
    if (!matrix[node][i])
      continue;
    
    if (!this->visited[i]) // Don't visit it if it's been visited already
	dfs(i);
  }

  // Store exit node's time
  this->time++;
  this->f[node].node = node;
  this->f[node].time = time;
}

void graph::dfs_t(int node)
{
  if (this->visited_t[node])
    return;

  cout << __FUNCTION__ << node << " Adding at " << sccs_counter << endl;

  
  sccs[this->sccs_counter].push_back(f[node]);
  this->visited_t[node] = 1;

  vector<F> children;
  for (int i = 0; i < this->junctions_number; i++) {
    if (!matrix[i][node]) // Transpose
      continue;

    children.push_back(this->f[i]);
  }

  sort(children.begin(), children.end(), order_by_time);
  for (auto it = children.begin(); it != children.end(); ++it) {
    if (!this->visited_t[it->node])
      dfs_t(it->node);
  }
}
   
pair<int, int> graph::solution() {
  int cost, ways;

  cost = 0;
  ways = 1;
  for (auto it = this->sccs.begin(); it != this->sccs.end(); ++it) {
    if (it->empty())
      continue;

    sort(it->begin(), it->end(), order_by_cost);

    int count_min = 1;
    cost += it->begin()->cost;

    // Add all the ones having the same cost as the form a possible solution
    for (auto scc_item = it->begin() + 1; scc_item != it->end(); ++scc_item) {
      if (scc_item->cost != it->begin()->cost)
	break;
      count_min++;
    }
    ways *= count_min;
  }
  return pair<int, int>(cost, ways);
}

int main() {
  int junctions, edges;

  cin >> junctions;
  vector<int> costs(junctions, 0);

  for (auto i = 0; i < junctions; i++)
    cin >> costs[i];
  
  graph graph(junctions, costs);

  cin >> edges;
  for (int i = 0; i < edges; i++) {
    int u, v;
    cin >> u >> v;
    graph.process_edge(u - 1, v - 1);
  }
  
  for (int i = 0; i < junctions; i++) {
    if (!graph.visited[i])
      graph.dfs(i);
  }

  for (int i = 0; i < junctions; i++) {
    cout << "[" << i << "] =" << graph.f[i].time << endl;
  }
  for (int i = 0; i < junctions; i++, graph.sccs_counter++) {
    //    graph.sccs[graph.sccs_counter]; // TODO: how initalize
    //cout << endl << " { ";
    graph.dfs_t(i);
    //cout << " } " << endl;
  }

  //TODO: Order all scc by costs
  pair<int, int> solution = graph.solution();
  cout << solution.first << " " << solution.second << endl;
  return 0;
}

