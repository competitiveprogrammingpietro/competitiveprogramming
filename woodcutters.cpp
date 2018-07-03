#include <iostream>
#include <vector>

using namespace std;

int main()
{
  int64_t size, result, last;

  cin >> size;
  vector<int64_t> coords(size), heights(size);

  for (int i = 0; i < size; i++)
    cin >> coords[i] >> heights[i];

  // We can always cull the first tree on the left
  result = 1;
  last = coords[0];
  for (int i = 1; i < size - 1; i++) {
    int64_t l, r;

    l = coords[i] - heights[i];
    r = coords[i] + heights[i];
    //    cout << "coords " << coords[i] << ", " << heights[i] <<  " l : " << l << " r: " << r << endl;
    if (l > last) {
      last = l;
      result++;
    }
    else if (r < coords[i + 1]) {
      last = r;
      result++;
    }
  }

  // We can always cull the last tree
  result++;
  printf("%I64d\n", result);
}
