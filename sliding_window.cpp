/*
 * Competive Programming - UniPi.
 * Pietro Paolini - 2017
 */
#include <iostream>
#include <vector>
#include <deque>

using namespace std;
std::vector<int> SWM(std::vector<int> const& A, int k)
{
  deque<int> Q;
  vector<int> result;
  
  for (int i = 0; i < A.size(); i++) {

    // Remove elements outside of the window.
    while (!Q.empty() && Q.front() <= i-k ) {
      Q.pop_front();
    }

    // Remove elements from the back which are smaller than the one under
    // examination, add it at the back right after.
    while (!Q.empty() && A[Q.back()] <= A[i]) {
      Q.pop_back();
    }
    
    Q.push_back(i);

    // Insert result when a window of k-length
    if (i >= k-1)
      result.push_back(A[Q.front()]);
  }
  return result;
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
    cin >> k;

    for (int j = 0; j < size; j++) {
      int input;

      cin >> input;
      array_input.push_back(input);
    }

    // Print the result
    vector<int> result = SWM(array_input, k);
    for (vector<int>::iterator it = result.begin(); it != result.end(); ++it) {
      cout << *it << " ";
    }
    cout << endl;
  }
}
