// #include "paint.h"
#include <bits/stdc++.h>
#define pb push_back
using namespace std;
const int N = 4e5 + 10;
int f[N], g[N], tim[N];
vector<int> v, p[N];
int minimumInstructions(int n, int m, int k, vector<int> c, vector<int> a, vector<vector<int>> b) {
  for(int i = 0; i < m; i ++) for(int u : b[i]) p[u].pb(i);
  fill(tim, tim + m, N);
  for(int i = 0; i < n; i ++) {
    bool z = 0;
    for(int j : p[c[i]]) g[j] = 0;
    for(int j : p[c[i]]) {
      g[j] = max(g[j], 1 + (tim[!j ? m - 1 : j - 1] == i - 1 ? f[!j ? m - 1 : j - 1] : 0));
    }
    for(int j : p[c[i]]) f[j] = g[j], tim[j] = i, z |= f[j] >= m;
    if(z) v.pb(i);
  }
  int sz = v.size(), z = 0, r = -1, ans = 0;
  while(r < n - 1) {
    while(z < sz - 1 && v[z + 1] - m <= r) z ++;
    if(z >= sz || v[z] - m > r) { ans = -1; break ; }
    ans ++; r = v[z ++];
  }
  return ans;
}
