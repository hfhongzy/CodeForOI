#include <bits/stdc++.h>
using namespace std;

int main() {
  int t, a, b;
  cin >> t;
  here:
  if(!t) return 0;
  -- t;
  cin >> a >> b;
  if(a > b) swap(a, b);
  cout << ( (int)((sqrt(5) + 1) / 2.0 * (b - a)) != a ? 'A' : 'B') << "\n";
  goto here;
  return 0;
}