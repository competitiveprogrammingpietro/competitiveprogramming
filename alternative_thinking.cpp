#include <iostream>
#include <vector>

using namespace std;
int main()
{
  int size, index, counter;

  cin >> size;

  string input;
  cin >> input;

  counter = 1;
  for (index = 1; index < size; index++) {
    if (input[index] != input[index - 1])
      counter++;
      
  }

  if (counter + 2 < size)
    cout << counter + 2 << endl;
  else
    cout << size << endl;
}
  
