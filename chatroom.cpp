#include <iostream>
#include <string>

using namespace std;
// Source: http://codeforces.com/problemset/problem/58/A?locale=en
string hello("hello");

int main()
{
  string input;
  int h, i;
  bool result;
  
  h = i = 0;
  cin >> input;
  
  //  cout << input;

  while (true) { // O(N)
    //    cout << "'" << hello[h] << "' = '" << input[i] << "'" << endl;  
    
    if (h == hello.length()) {
      result = true;
      break;
    }

    if (i == input.length()) {
      result = false;
      break;
    }

    if (hello[h] == input[i]) {
      h++;
      i++;
    } else {
      i++;
    }
  }

  if (result)
    cout << "YES" << endl;
  else
    cout << "NO" << endl;
  return 0;
}
