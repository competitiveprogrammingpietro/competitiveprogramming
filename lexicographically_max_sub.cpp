#include <iostream>
#include <string>

using namespace std;
// Source: http://codeforces.com/problemset/problem/196/A?locale=en

int main()
{
  string input, output;
  int max;

  max = 0;
  cin >> input;
  for (int i = input.length() - 1; i >= 0; i--) { // O(N)
    if (input[i] >= max) {
      output = input[i] + output;
      max = input[i]; 
    }
  }

  cout << output << endl;
}
