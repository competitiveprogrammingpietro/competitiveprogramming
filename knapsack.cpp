#include <iostream>
#include <vector>
using namespace std;

// Source: http://www.practice.geeksforgeeks.org/problem-page.php?pid=909
int K[101][101] = { {0} };

int test()
{
  int number, capacity;

  cin >> number >> capacity;

  vector<int> weights(number), values(number);

  for (int i = 0; i < number; i++) {
    cin >> values[i];
  }
  for (int i = 0; i < number; i++) {
    cin >> weights[i];
  }

  for (int i = 1; i < number + 1; i++) {
    for (int j = 1; j < capacity + 1; j++) {
      int value_one, value_two;
      value_one = K[i - 1][j];

      int idx = j - weights[i - 1];
      if (idx < 0) {
	K[i][j] = value_one;
      } else {
	value_two = K[i - 1][j - weights[i - 1]] + values[i - 1];
	K[i][j] = value_one > value_two ? value_one : value_two;
      }
    }
  }

  //  cout << endl;
  int max = 0;
  for (int i = 0; i < number + 1; i++) {
    for (int j = 0; j < capacity + 1; j++) {
      max = K[i][j] > max ? K[i][j] : max;
      //      cout << K[i][j] << " ";
    }
    //    cout << endl;
  }

  cout << max << endl;
  return 0;
}

int main()
{
  int tests;

  cin >> tests;

  for (int i = 0; i < tests; i++) {
    test();
  }
  return 0;
}
