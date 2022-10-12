#include <bits/stdc++.h>
#define eb emplace_back
using namespace std;
vector<pair<int, int>> v;
int main() {
  int n; scanf("%d", &n);
  if(!(n & (n - 1))) { puts("No"); return 0; }
  for(int i = 2; i < n; i += 2) {
    v.eb(1, i);
    v.eb(i, i + 1);
    v.eb(1, i + 1 + n);
    v.eb(i + 1 + n, i + n);
  }
  v.eb(3, n + 1);
  if(!(n & 1)) {
    int u = (n & (n - 1)) ^ 1;
    int w = n ^ 1 ^ u;
    v.eb(u + (u & 1) * n, n);
    v.eb(w + (w & 1) * n, n + n);
  }
  puts("Yes");
  for(auto p : v) {
    printf("%d %d\n", p.first, p.second);
  }
  return 0;
}