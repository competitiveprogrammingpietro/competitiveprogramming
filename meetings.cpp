#include <utility>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;


bool sort_pair(pair<int, int> a, pair<int, int> b)
{
  return a.second < b.second;
}

int main()
{
  int tests;

  cin >> tests;
  for (int i = 0; i < tests; i++) {
    int size;

    cin >> size;
    vector<int> S(size, 0);
    vector<pair<int, int>> F(size); // <position, value>

    for (int j = 0; j < size; j++)
      cin >> S[j];
    for (int j = 0; j < size; j++) {
      int value;
      cin >> value;
      pair<int, int> item(j, value);
      F[j] = item;
    }
	
    sort(F.begin(), F.end(), sort_pair); // O(NlgN)

    cout << F[0].first + 1 << " ";  // First always included
    int last = 0;
    for (int j = 1; j < size; j++) {    // O(n)
      if (F[last].second > S[F[j].first])
	continue;
      cout << F[j].first + 1 << " ";
      last = j;
    }
    cout << endl;
  }
}
