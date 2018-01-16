/*
 * Competive Programming - UniPi.
 * Pietro Paolini - 2017
 * Complexity : O(nlgn)
 * Source: http://codeforces.com/problemset/problem/424/B?locale=en
 */
#include <iostream>
#include <map>
#include <math.h>
using namespace std;

double radius(multimap<double, int, less<double>>& input, int population) {
  double radius = 0; 
  for (auto it = input.begin(); it != input.end(); ++it) { // O(n)
    population += it->second;
    radius = it->first;
    if (population >= 1E6)
      return radius;
  }
  return -1;
}

int main() {
  cout.precision(10);
  std::ios_base::sync_with_stdio(false);
  multimap<double, int, less<double>> input;
  int locations, population;
  
  cin >> locations >> population;
  for (int i = 0; i < locations; i++) { // O(nlgn)

    int x, y, location_population;
    double distance;
    cin >> x >> y >> location_population;
#ifdef DEBUG
    cout << x << " "<< y << " " << location_population << endl;
#endif
    distance = sqrt(x*x + y*y);
    input.insert({distance, location_population});
  }
  double result = radius(input, population);
  cout << result << endl;
  return 0;
}
