/*
 * Competive Programming - UniPi.
 * Pietro Paolini - 2017
 * Complexity : O(n^2lgn)
 * Source: http://codeforces.com/problemset/problem/579/B
 * Given a certain preference and its strength the problem can be solved by
 * creating a map containing all preferences sorted by strength.
 * For example the output:
 * 2
 * 6
 * 1 2
 * 3 4 5
 * Will result in: 6(2,1), 5(4,3), 4(4,2), 3(4,1) ,2(3,2), 1(3,1).
 *
 * The problem is resolved by examining those preferences in order and assigning
 * the team members to each other in the tuple if they are both unpaired.
*/
#include <map>
#include <list>
#include <iostream>
#include <vector>
using namespace std;


class Preference {
  public:
      int first, second;
  Preference(int one, int two):first(one), second(two) { }
  
};

void find_team_member(map<int,Preference,greater<int>>& input, vector<int>& output) {
  for (auto it = input.begin(); it != input.end(); ++it) { // O(n)

    int peer_one = it->second.first;
    int peer_two = it->second.second;

    // Taken already
    if (output[peer_one - 1] != 0 || output[peer_two - 1] != 0)
      continue;

    output[peer_one - 1] = peer_two;
    output[peer_two - 1] = peer_one;
  }
  return;
}



int main() {

  std::ios_base::sync_with_stdio(false);
  int teams;

  cin >> teams;
  vector<int> output(teams * 2, 0);
  map<int, Preference, greater<int>> input;


  for (int i = 2; i <= teams * 2; i++) {          // O(n)
    
    for (int j = 1; j < i; j++) {                 // O(n)
      int strength;
      cin >> strength;
      input.insert({strength, Preference(i, j)}); // O(lgn) 
    }
  }
#ifdef DEBUG
  for (auto it = input.begin(); it != input.end(); ++it) {
    cout << it->first << "(" << it->second.first << "," << it->second.second << ")" << endl;
  }
#endif
  find_team_member(input, output);               // O(n)
  for (auto it = output.begin(); it != output.end(); ++it)
    cout << *it << " ";
  cout << endl;
}
