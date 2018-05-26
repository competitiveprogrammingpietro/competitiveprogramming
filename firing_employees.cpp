/*
 * Competive Programming - UniPi.
 * Pietro Paolini - 2017
 * Complexity : O(nlgn)
 * Source: https://practice.geeksforgeeks.org/problems/firing-employees/0
 */
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

void compute_prime(vector<bool>& prime) {

  prime[0] = false;
  prime[1] = true;
  for (int i = 2; i < sqrt(prime.size()); ++i) {

    int factor = 2;
    while (factor * i < prime.size()) {
      prime[factor * i] = false;
      factor++;
    }
  }
}

void compute_seniority(vector<int>& input, vector<int>& senior, int employee) {
  if (input[employee] == 0) {
    senior[employee] = 0;
    return;
  }

  int senior_level = senior[input[employee] - 1];

  // Not computed yet, compute parents' seniority first
  // then add one to it.
  if (senior_level == -1)
    compute_seniority(input, senior, input[employee] - 1);
  
  senior[employee] = senior_level + 1;
  return;
}

int firing_employees(vector<int>& input) {

  // Initialize senior vector
  vector<int> senior(input.size(), -1);
  vector<bool> prime(input.size() * 2 + 1, true);
  int count = 0;
  
  cout << "Prime ";
  compute_prime(prime);
  for (int i = 0; i < prime.size(); ++i) {
    cout << "[" << i << "]:" << prime[i];
  }
  cout << endl;
  for (int i = 0; i < input.size(); ++i) {
    compute_seniority(input, senior, i);
  }

  cout << "Senior [";
  for (auto it = senior.begin(); it != senior.end(); ++it) {
    cout << *it << ",";
  }

  for (int i = 0; i < input.size(); i++) {

    if (input[i] == 0)
      continue;
    
    int sum = i + 1 + senior[i];
    if (prime[sum]) {
	count++;
    }
  }
  return count;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int test_case;

  cin >> test_case;
  for (int i = 0; i < test_case; i++) {

    // Read array's size
    int size;
    vector<int> array_input;
    
    cin >> size;
    for (int j = 0; j < size; j++) {
      int input;
      cin >> input;
      array_input.push_back(input);
    }
    int black_listed = firing_employees(array_input);
    cout << black_listed << endl;
  }
}
