#import <iostream>
#import <string>
#import <vector>

/**
 * https://practice.geeksforgeeks.org/problems/longest-prefix-suffix/0
 * Complexity: O(n)
 */

using namespace std;

// Implementation of KPM "Compute prefix function"
int test(string& input)
{
  vector<int> next(input.size() + 1, 0);
  int j = 0;
  
  next[1] = 0;
  for (int i = 2; i < input.size() + 1; i++) {
    int idx = i - 1;
    
    while (input[idx] != input[j] && j > 0) {
      j = next[j];
    }
    if (input[idx] == input[j])
      j = j + 1;
    next[i] = j;
  }
  
  // for (auto it = next.begin(); it != next.end(); it++) {
  //   cout << "next[" << next.size() - (next.end() - it) << "]=" << *it << endl;
  // }
  
  return next[next.size() - 1];
}

int main()
{
  int t;

  cin >> t;

  for (int i = 0; i < t; i++) {
    string a;
    
    cin >> a;
    cout << test(a) << endl;
  }
}
