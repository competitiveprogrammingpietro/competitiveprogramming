#include <iostream>
#include <utility>
#include <list>
#include <vector>
#include <stack>
#include <set>
#include <cstring>

using namespace std;
/*
 * Source: http://codeforces.com/problemset/problem/277/A?locale=en
 */
class graph {
public:
  int **           matrix;
  int              *f, *visited, *visited_t, num;
  int              employees, languages, time, total_employees_languages;
  set<int>         *languages_set;
  graph(int employees, int languages);
  void dfs(int node);
  void dfs_t(int node);
};


graph::graph(int employees, int languages) {
  total_employees_languages = 0;
  time = 0;			
  this->employees = employees;
  this->languages = languages;
  f       = new int[2 * employees + 2]();
  visited = new int[employees]();
  visited_t = new int[employees]();
  matrix  = new int*[employees];
  languages_set = new set<int>[languages]();

  for (int i = 0; i < employees; i++) {
    matrix[i] = new int[languages]();
  }
  for (int i = 0; i < employees; i++) {
    int employee_languages;
    
    cin >> employee_languages;
    total_employees_languages += employee_languages;
    for (int j = 0; j < employee_languages; j++) {
      int language = 0;
      cin >> language;
      //cout << "i " << i << " Language " << language << endl;
      
      // The i-th employee speaks language - 1
      matrix[i][language - 1] = 1;
      //cout << "i " << i << " Language " << language << endl;

      // Add their to the set for the given language
      languages_set[language - 1].insert(i);
    }  
  }
}

void graph::dfs(int node) {
  this->visited[node] = 1;
  this->time++;
  for (int i = 0; i < this->languages; i++) {
    if (!matrix[node][i])
      continue;
    
    // Exiting star equals to set speaking that language
    set<int>& language = languages_set[i];
    for (auto it = language.begin(); it != language.end(); it++) {
      if (!this->visited[*it]) // Don't visit it if it's been visited already
	dfs(*it);
    }
  }
  
  // Store exit node's time
  this->time++;
  this->f[this->time] = node + 1;
}

void graph::dfs_t(int node)
{
  if (this->visited_t[node])
    return;
  
  //cout << node << ",";
  this->visited_t[node] = 1;
  this->num++;
  for (int i = 0; i < this->languages; i++) {
    if (!matrix[node][i])
      continue;
    
    // Exiting star equals to set speaking that language
    set<int>& language = languages_set[i];
    for (auto it = language.begin(); it != language.end(); it++) {
      if (!this->visited_t[*it]) // Don't visit it if it's been visited already
	dfs_t(*it);
    }
  }
}
   

int main() {
  int employees, languages;
  
  cin >> employees >> languages;
  graph graph(employees, languages);

  for (int i = 0; i < employees; i++) {
    if (!graph.visited[i])
      graph.dfs(i);
  }
  int scc = 0;
  for (int i = 0; i < employees; i++) {
    graph.num = 0;
    //cout << endl << " { ";
    graph.dfs_t(i);
    if (graph.num > 0) scc++;
    //cout << " } " << endl;
  }

  if (graph.total_employees_languages  == 0)
    cout << graph.employees << endl;
  else
    cout << scc - 1 << endl;
  
  // for (int j = 0; j < employees * 2 + 1; j++)
  //   cout << "time[" << j << "]=" << graph.f[j] << endl;

  return 0;
}

