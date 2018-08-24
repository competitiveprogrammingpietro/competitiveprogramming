/*
 * Competive Programming - UniPi.
 * Pietro Paolini - 2017
 * Complexity : O(n)
 * https://practice.geeksforgeeks.org/problems/leaders-in-an-array/0
 */
#include <iostream>
#include <vector>
#include <deque>
#include <iterator>
using namespace std;

deque<int> leaders(vector<int> A)
{
  deque<int> Q;
  int i, max;

  Q.push_back(A.size() -1);
  i = A.size() - 2;
  max = A.size() - 1;
  for (i = A.size() - 2; i >=0 ; i--) { // O(n)

    // Skip left elements which aren't greater than the right most
    if (A[i] <= A[max])
      continue;

    /* 
     *  We have found an element greater than the current maximum therefore 
     *  a leader, store it and continue scanning
     */
    Q.push_back(i);
    max = i;
  }
  return Q;
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

    for (int j = 0; j < size; j++) {
      int input;
      cin >> input;
      array_input.push_back(input);
    }

    // Print the result
    typedef std::deque<int>::iterator iter_type;
    deque<int> result = leaders(array_input);

    deque<int>::reverse_iterator ret = result.rbegin();
    for (; ret != result.rend(); ++ret) {
      cout << array_input[*ret] << " ";
    }
    
    
    
    cout << endl;
  }
}
