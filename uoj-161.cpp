#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
typedef double db;
const int N = 1e6 + 5;
const db inf = 1e50;
int n, h[N], t[N];
db ans[N], s[N], p[N];
vector<int> t0[N], t1[N];

char pbuf[100000001], *pp = pbuf;
void outint(ll x) {
  static int st[32];
  int t = 0;
  if(!x) st[++ t] = 0;
  while(x) st[++ t] = x % 10, x /= 10;
  while(t) *pp ++ = st[t --] ^ '0';
}
void outdb(db x) {
  outint(ll(x)); *pp ++ = '.';
  ll z = ll(x * 10000) % 10000;
  static int st[16];
  rep(i, 0, 3) st[i] = z % 10, z /= 10;
  per(i, 3, 0) *pp ++ = st[i] ^ '0';
}
int main() {
  scanf("%d", &n);
  rep(i, 1, n) scanf("%d", h + i);
  rep(i, 1, n) scanf("%d", t + i), (t[i] ? t1[h[i]] : t0[h[i]]).pb(i);
  int mx = *max_element(h + 1, h + n + 1);
  rep(i, 1, mx) {
    s[i] = t1[i].size() + t0[i].size() + s[i - 1];
    db dps = 0;
    for(int u : t1[i]) {
      ans[u] = s[i - t[u]] > 0 ? p[i - t[u]] / s[i - t[u]] + 1 : 1;
      dps += ans[u];
    }
    p[i] = dps + p[i - 1];
    if(!t0[i].size()) continue ;
    if(int(s[i]) == t0[i].size()) {
      p[i] = inf;
      for(int u : t0[i]) ans[u] = inf;
      continue ;
    }
    dps = (p[i] + s[i]) / (s[i] - t0[i].size());
    for(int u : t0[i]) {
      ans[u] = dps;
    }
    p[i] += dps * t0[i].size();
  }
  rep(i, 1, n) {
    if(ans[i] > 1e18) outint(0), *pp ++ = ' ';
    else outdb(ans[i]), *pp ++ = ' ';
  }
  *pp ++ = '\n';
  fwrite(pbuf, 1, pp - pbuf, stdout);
  return 0;
}
