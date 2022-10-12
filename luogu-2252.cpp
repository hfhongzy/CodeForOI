#include <bits/stdc++.h>
using namespace std;

int main() {
   int a, b; cin >> a >> b;
   if(a > b) swap(a, b);
   cout << ( (int)((sqrt(5) + 1) / 2.0 * (b - a)) == a ? 0 : 1) << "\n";
   return 0;
}