#include <iostream>
#include <vector>
using namespace std;

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
      int previous_item = K[i - i][capacity];
      int add_item = K[i - 1][capacity - weights[i]] + values[i];
      K[i][j] = previous_item > add_item ? previous_item : add_item;
    }
  }

  cout << endl;
  int max = 0;
  for (int i = 1; i < number + 1; i++) {
    for (int j = 1; j < capacity + 1; j++) {
      max = K[i][j] > max ? K[i][j] : max;
      cout << K[i][j] << " ";
    }
    cout << endl;
  }

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
