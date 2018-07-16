#include <iostream>
#include <vector>
#include <string>

using namespace std;
int largest_even_number(string input)
{
  vector<int> number(input.size());
  vector<int> count(11, 0);
  string result;

  for (auto i = 0; i < input.size(); i++) {
    int index = input[i] - '0';
    count[index]++;
  }

  char even = NULL;
  for (auto i = 2; i < 11; i += 2) {
    if (count[i] == 0)
      continue;

    // Make the number even
    count[i]--;
    even = i + '0';
    break;
  }
  
  for (auto i = 10; i >= 1; i--) {
    while (count[i] > 0) {
      result = result + (char) (i + '0');
      count[i]--;
    }
  }

  if (even)
    result = result + even;
  
  return stoi(result);
}

int main()
{
  int test;
  string input;

  cin >> test;
  for (int i = 0; i < test; i++) {
    cin >> input;
    cout << largest_even_number(input) << endl;
  }
  return 0;
}
