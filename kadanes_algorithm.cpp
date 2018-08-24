/*
 * Competive Programming - UniPi.
 * Pietro Paolini - 2017
 * Complexity : O(n)
 * https://practice.geeksforgeeks.org/problems/kadanes-algorithm/0
 */
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int kadanes_algorithm(vector<int> input) {
  int accumulator, max, index;

  max = accumulator = input[0];

  for (index = 1;index < input.size(); index++) { // O(n)
    int element = input[index];

    if (accumulator < 0) {
      accumulator = element;
    }
    else {
      accumulator += element;
    }
    if (accumulator > max)
      max = accumulator;
  }
  return max;
}



int main() {

  std::ios_base::sync_with_stdio(false);

  int test_case;

  cin >> test_case;
  for (int i = 0; i < test_case; i++) {

    // Read array's size and window's size
    string input;
    int size;
    vector<int> array_input;
    
    cin >> size;
    for (int j = 0; j < size; j++) {
      int input;

      cin >> input;
      array_input.push_back(input);
    }

    // Print the result
    int result = kadanes_algorithm(array_input);
    cout << result << " " << endl;
  }

}
