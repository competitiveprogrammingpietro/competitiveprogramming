#include <iostream>
#include <vector>
using namespace std;

int test(vector<int>& A) 
{
  int maxReach, step, jump;

  if (A[0] == 0)
    return -1;
  
  maxReach = step = A[0];
  jump = 1;
  for (int i = 1; i < A.size(); i++) {

    if (i >= A.size() - 1)
      return jump;

    //    cout << step << endl;
    maxReach = (maxReach > A[i] + i) ? maxReach : A[i] + i;
    step--;

    // Reached the end of the last jump
    if (step == 0) {
      jump++;

    // Impossible case
    if (i >= maxReach)
      return -1;
      
     step = maxReach - i; // Think about a zero 
    }
  }
  return -1;
}

int main()
{
  int tests;

  cin >> tests;

  int result = 0;
  for (int i = 0; i < tests; i++) {
    int size;

    cin >> size;
    vector<int> input(size);
    
    for (int u = 0; u < size;u++)
      cin >> input[u];
    result = test(input);
    cout << result << endl;
  }
  return result;
}
