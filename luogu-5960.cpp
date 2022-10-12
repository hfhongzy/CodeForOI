#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
using namespace std;
const int N = 2e5 + 10;
int n, m, eu[N], ev[N], ew[N], d[N];
int main() {
  scanf("%d%d", &n, &m);
  rep(i, 1, m) scanf("%d%d%d", ev + i, eu + i, ew + i);
  rep(i, 1, n) d[i] = 1e9;
  d[1] = 0;
  rep(i, 1, n - 1) rep(j, 1, m)
    d[ev[j]] = min(d[ev[j]], d[eu[j]] + ew[j]);
  rep(i, 1, m)
    if(d[ev[i]] > d[eu[i]] + ew[i])
      return puts("NO"), 0;
  rep(i, 1, n) printf("%d%c", d[i], " \n"[i == n]);
  return 0;
}