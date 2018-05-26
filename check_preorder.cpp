#include <iostream>
#include <vector>
#include <stack>
#include <climits>
/*
 * Competive Programming - UniPi.
 * Pietro Paolini - 2017
 * Complexity : n
 * Source: https://practice.geeksforgeeks.org/problems/check-for-bst/
 */

using namespace std;
int check_preorder(std::vector<int>& input) {
  int root = INT_MIN;

  stack<int> Q;

  for (auto it = input.begin(); it != input.end(); ++it) {

    if (*it < root)
      return 0;

    while (!Q.empty()) {
      if (Q.top() > *it) {
	Q.pop();
      } else {
	root = Q.top();
	break;
      }
    }
    Q.push(*it);
	  
  }
  return 1;
}


int main() {
    std::ios_base::sync_with_stdio(false);

    int num_test_cases = 0;
    std::cin >> num_test_cases;

    std::vector<int> vec;
    for (int i = 0; i < num_test_cases; ++i) {
        int n = 0;
        std::cin >> n;
        vec.reserve(n);
        for (int j = 0; j < n; ++j) {
            int x = 0;
            std::cin >> x;
            vec.push_back(x);
        }

        std::cout << check_preorder(vec) << std::endl;
        vec.clear();
    }

    return 0;
}
