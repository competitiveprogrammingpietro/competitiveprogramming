#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cstdlib>    
using namespace std;
struct SET {
  int item;
  int r;
  struct SET * p;

  SET(int item): item(item), r(0), p(this) { }
  SET * UNION(SET * X, SET * Y);
  SET * LINK(SET * X, SET * Y);
  SET * FINDSET(SET * X);
};

SET * SET::UNION(SET * X, SET * Y) {
  return LINK(FINDSET(X), FINDSET(Y));
}

SET * SET::LINK(SET * X, SET * Y)
{
  if (X->r > Y->r) {
    Y->p = X;
    return X;
  } else {
    X->p = Y;
    if (X->r == Y->r)
      Y->r = Y->r + 1;
    return Y;
  }
}

SET * SET::FINDSET(SET * X)
{
  if (X != X->p)
    return FINDSET(X->p);
  return this;
}

#define A 0
#define B 1
#define C 2
set<int> SETS[3];

int find_item(int elem) {
  for (int i = A; i <= C; i++) {
    if (SETS[i].find(elem) != SETS[i].end())
      return i;
  }
  return -1;
}

int main() {
  int tests, n, k;

  cin >> tests;
  for (int i = 0; i < tests; i++) {
    cin >> n >> k;
    int result = 0;
    for (int j = 0; j < k; j++) {
      int type, x, y, xs, ys;
      
      cin >> type >> x >> y;

      if (x > n || y > n) {
	cout << "++" << endl;
	result++;
	continue;
      }


      xs = find_item(x);
      ys = find_item(y);
      cout << "find(" << x << ")=" << xs << endl;
      cout << "find(" << y << ")=" << ys << endl;
      switch (type) {
      case 1:

	// 1. They are already present and they are not into the same set
	if (xs != -1 && ys != -1 && xs != ys) {
	  result++;
	  cout << "++" << endl;
	}

	// 2. They are not present, put them into the same set
	else if (xs == -1 && ys == -1) {
	  SETS[A].insert(x);
	  SETS[A].insert(y);
	  continue;
	}

	// 2. One of them is present whereas the other isn't, put it into the same set
	else if (xs == -1 && ys != -1)
	  SETS[ys].insert(x);
	else
	  SETS[xs].insert(y);
	break;
      case 2:

	// 1. Wrong hint
	if (y == x) {
	  result++;
	}

	// 2. None of them exist, insert them
	else if (xs == -1 && ys == -1) {
	  SETS[A].insert(x);
	  SETS[B].insert(y);
	}

	// 3. The "eater" exists, put the other into the right set
	else if (xs != -1 && ys == -1) {
	  int destination = (xs + 1) % 3;
	  SETS[destination].insert(y);
	}

	// 4. The "eaten" exists, put the other into the right set
	else if (xs == -1 && ys != -1) {
	  int destination = (ys + 2) % 3;
	  SETS[destination].insert(x);
	}

	// 5. They both exist
	else {
	  if (ys != (xs + 1) % 3) {
	    cout << "++" << endl;
	    result++;
	  }
	}
	break;
      }
    }
    cout << result << endl;
  }
}
