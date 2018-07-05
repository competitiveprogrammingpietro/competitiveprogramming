#include <iostream>
#include <vector>
#include <stdint.h>
using namespace std;
vector<uint64_t> MEMOIZE(10000, 0);


uint64_t compute(uint64_t n)
{
  if (MEMOIZE[n] != 0)
    return MEMOIZE[n];
  
  if (n == 0)
    return 1;
  if (n == 1)
    return 2;

  MEMOIZE[n] = compute(n - 1) + compute(n - 2);
  return MEMOIZE[n];
}

int main()
{
  uint64_t N;

  cin >> N;

  //printf("%I64d\n", compute(N));

  cout << compute(N) << endl;
  return 0;
}
