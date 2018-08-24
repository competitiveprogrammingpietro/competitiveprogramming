#include <iostream>
#include <string>

using namespace std;
string a("1");
string b("14");
string c("144");

//  Source: http://codeforces.com/problemset/problem/320/A?locale=en
int main()
{
  string input;
  cin >> input;


  while (!input.empty()) {
    //    cout << input << endl;
    if (input.compare(0, 3, c) == 0) {
      input.erase(0, 3);
    }
    else if (input.compare(0, 2, b) == 0) {
      input.erase(0, 2);
    }
    else if (input.compare(0, 1, a) == 0) {
      input.erase(0, 1);
    }
    else {
      cout << "NO" << endl;
      return 0;
    }
  }

  cout << "YES" << endl;
}
