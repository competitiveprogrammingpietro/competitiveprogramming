#include <iostream>
#include <cmath>
#include <vector>

using namespace std;
int main()
{
  int size;
  unsigned long long result;

  cin >> size;
  
  vector<int> input(size);
  for (int i = 0; i < size; i++)
    cin >> input[i];

  result = (unsigned long long) abs(input[0]);
  for (int i = 1; i < size; i++) // O(n)
    result += (unsigned long long) abs(input[i] - input[i - 1]);

  cout << result << endl;
  
}
