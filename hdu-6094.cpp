#include <bits/stdc++.h>
#define pb push_back
#define LOG(FMT...) fprintf(stderr, FMT);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
template<class T>
void chkmax(T &x, T y) { if(x < y) x = y; }
typedef long long ll;
const int N = 4e4 + 5;
const ll INF = 1ll << 60;
struct node {
  ll f; int g;
  bool operator < (const node &b) const { return f == b.f ? g > b.g : f > b.f; }
  node operator + (const node &b) const { return (node) {f + b.f, g + b.g}; }
} dp[64], la[64];
int n, m, k, vr[N][8], vd[N][8];
node calc(ll mid) { //match + 1 -> val-mid
  for(int i = 1; i < (1 << (m + 1)); i ++)
    dp[i] = {INF, 0};
  dp[0] = {0, 0};
  rep(i, 1, n) rep(j, 1, m) {
    if(j == 1) {
      rep(s, 0, (1 << (m + 1)) - 1) la[s] = {INF, 0};
      rep(s, 0, (1 << m) - 1) la[s << 1] = dp[s];
    } else {
      rep(s, 0, (1 << (m + 1)) - 1) la[s] = dp[s];
    }
    rep(s, 0, (1 << (m + 1)) - 1) dp[s] = {INF, 0};
    rep(s, 0, (1 << (m + 1)) - 1) {
      if(la[s].f == INF) continue ;
      int L = s >> (j - 1) & 1;
      int R = s >> j & 1;
      if(L && R) continue ;
      if(L) chkmax(dp[s ^ (1 << (j - 1))], la[s]);
      else if(R) chkmax(dp[s ^ (1 << j)], la[s]);
      else {
        chkmax(dp[s], la[s]);
        if(i < n) chkmax(dp[s ^ (1 << (j - 1))], la[s] + node{vd[i][j] - mid, 1});
        if(j < m) chkmax(dp[s ^ (1 << j)], la[s] + node{vr[i][j] - mid, 1});
      }
    }
  }
  return dp[0];
}
int main() {
  int test;
  scanf("%d", &test);
  rep(T, 1, test) {
    scanf("%d%d%d", &n, &m, &k);
    rep(i, 1, n - 1) rep(j, 1, m) scanf("%d", vd[i] + j);
    rep(i, 1, n) rep(j, 1, m - 1) scanf("%d", vr[i] + j);
    ll l = 0, r = (ll)n * m / 2 * ll(1e9);
    while(l <= r) {
      ll mid = (l + r) >> 1;
      if(calc(mid).g <= k) {
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    }
    printf("%lld\n", calc(l - 1).f + (l - 1ll) * k);
  }
  return 0;
}