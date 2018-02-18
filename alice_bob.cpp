/* Pietro Paolini
 * Competitive programming Universita' degli studi di Pisa.
 * Source http://codeforces.com/problemset/problem/6/C?locale=en
 * Complexity O(n)
 */
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

pair<int, int> chocolet_bars(vector<int>& times) {
  int SUM[times.size() + 1], i, alice_i, bob_i, alice_t, bob_t, max_i;

  SUM[0] = 0;
  for (i = 1; i < times.size(); i++) {
    SUM[i] = times[i -1] + SUM[i -1];
  }
  SUM[times.size()] = SUM[times.size() - 1] + times[times.size() - 1];
  max_i = times.size();
  alice_i = bob_i = 0;
  alice_t = bob_t = 0;

  while (SUM[alice_i] + SUM[max_i] - SUM[max_i - bob_i] < SUM[max_i]) {
    alice_t = SUM[alice_i];
    bob_t = SUM[max_i] - SUM[max_i - bob_i];
    if (alice_t <= bob_t)
      alice_i++;
    else
      bob_i++;
  }
  return pair<int, int>(alice_i, bob_i);
}

int main() {
  int bars, i;
  vector<int> times;
  cin >> bars;
  for (i = 0; i < bars; i++) {
    int time;
    cin >> time;
    times.push_back(time);
  }
  pair<int, int> result = chocolet_bars(times);
  cout << result.first << " " << result.second << endl;
  return 0;
}

