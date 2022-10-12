#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
struct node {
  ll mxa, sumb;
  void operator += (node b) {
    mxa = max(mxa, b.mxa);
    sumb += b.sumb;
  }
} a[N], b[N];
int n, q, top, bom, f[N], st[N];
ll m, dp[N], s[N], g[N];
int find(int u) { return f[u] == u ? u : f[u] = find(f[u]); }
bool check(ll mid) {
  dp[0] = 0;
  int j = 0;
  multiset<ll> S, S2;
  st[bom = top = 1] = 0; S.insert(g[0] = b[1].mxa);
  rep(i, 1, q) {
    S2.insert(b[i].mxa);
    while(s[i] - s[j] > mid) S2.erase(S2.lower_bound(b[++ j].mxa));
    while(top >= bom && b[st[top]].mxa < b[i].mxa) {
      S.erase(S.lower_bound(g[st[top]])); top --;
    }
    if(top >= bom) {
      S.erase(S.lower_bound(g[st[top]]));
      S.insert(g[st[top]] = dp[st[top]] + b[i].mxa);
    }
    while(top >= bom && st[bom] < j) S.erase(S.lower_bound(g[st[bom ++]]));
    dp[i] = min(dp[j] + *--S2.end(), S.size() ? *S.begin() : 1ll << 62);
    if(i == q) break ;
    st[++ top] = i;
    S.insert(g[i] = dp[i] + b[i].mxa);
  }
  return dp[q] <= m;
}
int main() {
  freopen("sequence.in", "r", stdin);
  freopen("sequence.out", "w", stdout);
  scanf("%d%lld", &n, &m);
  ll sb = 0;
  rep(i, 1, n) {
    f[i] = i;
    scanf("%lld%lld", &a[i].mxa, &a[i].sumb);
    sb += a[i].sumb;
  }
  ll mx = 0;
  per(i, n, 1) {
    int p = lower_bound(st + 1, st + top + 1, a[i].sumb, [&](int x, ll y) { return a[x].mxa < y; }) - st;
    if(p <= top) {
      int u = i;
      while(u < st[p]) { u = f[u] = find(u + 1); }
    }
    if(mx < a[i].mxa) { st[++ top] = i; mx = a[i].mxa; }
  }
  rep(i, 1, n) if(find(i) != i) a[find(i)] += a[i];
  rep(i, 1, n) if(find(i) == i) b[++ q] = a[i];
  ll l = 0, r = sb, mid;
  rep(i, 1, q) l = max(l, b[i].sumb), s[i] = s[i - 1] + b[i].sumb;
  while(l <= r) {
    mid = (l + r) >> 1;
    if(check(mid)) r = mid - 1;
    else l = mid + 1;
  }
  printf("%lld\n", r + 1);
  return 0;
}