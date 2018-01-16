/*
 * Competive Programming - UniPi.
 * Pietro Paolini - 2017
 * Complexity : O(NlgN)
 * Source: http://www.spoj.com/submit/INVCNT/
 */
#include <iostream>
#include <vector>
using namespace std;

long long fusione(vector<int>& input, int sx, int cx, int dx) {
  long long i,j, count, k;
  vector<int> clone(dx - sx + 1);
  
#ifdef DEBUG
  cout << __FUNCTION__ << " " << sx << " " << cx << " " << dx << endl;
#endif

  count = k = 0;
  i = sx;
  j = cx + 1;
  while ( (i <= cx) && (j <= dx)) {
    if (input[j] < input[i]) {
      clone[k] = input[j];
      j++;
      count += cx  - i + 1;
    } else {
      clone[k] = input[i];
      i++;
    }
    k++;
  }

  // Copy what's left into clone and the clone array in the original array thereafter
  while(i <= cx) {
    clone[k++] = input[i++];
  }
  while(j <= dx) {
    clone[k++] = input[j++];
  }
  copy(clone.begin(), clone.end(), input.begin()+sx);
  return count;
}


long long inversion_count(vector<int>& input, int sx, int dx) {
  long long count;
  
#ifdef DEBUG
  cout << __FUNCTION__ << " " << sx << " " << dx << endl;
#endif
  if (sx >= dx)
    return 0;

  int cx = (sx + dx) / 2;
  count =  inversion_count(input, sx, cx);
  count += inversion_count(input, cx + 1, dx);
  count += fusione(input, sx, cx, dx);
  return count;
}


int main() {
  std::ios_base::sync_with_stdio(false);

  int test_case;

  cin >> test_case;
  for (int i = 0; i < test_case; i++) {

    // Read array's size
    int size;
    vector<int> array_input;
    
    cin >> size;
    for (int j = 0; j < size; j++) {
      int input;
      cin >> input;
      array_input.push_back(input);
    }

    long long count = inversion_count(array_input, 0, array_input.size() - 1);
    cout << count << endl;
  }
}

