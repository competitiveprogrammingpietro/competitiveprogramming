/*
 * Competive Programming - UniPi.
 * Pietro Paolini - 2017
 * Source: http://practice.geeksforgeeks.org/problems/missing-number-in-array/0
 * Complexity : O(n)
 */
#include <iostream>
#include <vector>
using namespace std;
int missing_number(std::vector<int> const& A)
{
  unsigned long long total_sum, actual_sum = 0;
  unsigned int size = A.size() + 1;
  
  // Compute the sum of the first n numbers
  total_sum = (size * (size + 1)) / 2;

  for (auto it = A.begin(); it != A.end(); ++it) {
    actual_sum += *it;
  }

  return total_sum - actual_sum;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int test_case;

  cin >> test_case;
  for (int i = 0; i < test_case; i++) {

    // Read array's size and window's size
    string input;
    int k;
    int size;
    vector<int> array_input;
    
    cin >> size;
    for (int j = 0; j < size - 1; j++) {
      int input;

      cin >> input;
      array_input.push_back(input);
    }

    // Print the result
    int result = missing_number(array_input);
    cout << result << endl;
  }
}
