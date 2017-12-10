/*
 * Competive Programming - UniPi.
 * Pietro Paolini - 2017
 * Complexity : O(NlgN)
 * Source: https://practice.geeksforgeeks.org/problems/next-larger-element/0
 */
#include <iostream>
#include <vector>
#include <map>
#include <iterator>

using namespace std;

void next_larger_element(std::vector<int>& A) {

  map<int, int> tree;
  int i;

  // Insert all element in a map whose key is the vector's value and whose value
  // is its index.
  for (i = 0; i < A.size(); i++) { // O(N)
    tree.insert(pair<int, int>(A[i], i)); // O(lgN)
  }

  // For each element looks its index up and search for the next greater element
  for (int item : A) {
    int result = -1;
    int index = (*tree.find(item)).second; // O(lgN)

    for (i = index + 1; i < A.size(); i++) { // O(N)
      if (A[i] <= item)
	continue;
      result = A[i];
      break;
    }
    cout << result << " ";
  }
  cout << endl;
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

    // Print the result
    next_larger_element(array_input);
  }
}
