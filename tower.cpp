/*
 * Competive Programming - UniPi.
 * Pietro Paolini - 2017
 * Complexity : O(1)
 * Comment: it may be more performant to use a Map as the algorithm always
 * allocates 1000 positions, namely the maximum input's size
 * Source: https://practice.geeksforgeeks.org/problems/trapping-rain-water/0
 */
#include <iostream>
#include <vector>
using namespace std;

void tower(vector<int>& input, vector<int>& output) {
  for (int item : input) {
    output[item - 1]++;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  vector<int> array_input, result(1000, 0); // 1000 elements initialized to be zero
  int size, input;

  cin >> size;
  for (int i = 0; i < size; i++) {
    cin >> input;
    array_input.push_back(input);
  }

  tower(array_input, result);
  int num_towers, max;

  num_towers = max = 0;

  for (auto it = result.begin(); it != result.end(); it++) {
    if (*it == 0)
      continue;

    max = (*it > max) ? *it : max;
    num_towers++;
  }
  cout << max << " " << num_towers << endl;
}

