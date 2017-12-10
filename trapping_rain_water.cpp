/*
 * Competive Programming - UniPi.
 * Pietro Paolini - 2017
 * Complexity : O(n)
 * Source: https://practice.geeksforgeeks.org/problems/trapping-rain-water/0
 */
#include <iostream>
#include <vector>
using namespace std;


int step(int& level, int ground) {
  if (ground > level)
    level = ground;
  return level - ground;
}

int trapping_rain(vector<int>& A)
{
  vector<int>::iterator start = A.begin();
  vector<int>::iterator end = A.end();
  int rain, level;

  level = rain = 0;
  while (start != end) {
    if (*start > *end) {
      rain += step(level, *end);
      end--;
    }
    else {
      rain += step(level, *start);
      start++;
    }
  }
  return rain;
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
    int result = trapping_rain(array_input);
    cout << result << endl;
  }
}
