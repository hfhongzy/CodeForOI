#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
using ll = long long;
using db = double;
char gc() {
  const int SZ = 1 << 20;
  static char buf[SZ], *S, *T;
  if(S == T) T = (S = buf) + fread(buf, 1, SZ, stdin);
  return S == T ? EOF : *S ++;
}
template<class T>
void read(T &x) {
  x = 0; char c = gc();
  for(; !isdigit(c); c = gc());
  for(; isdigit(c); c = gc()) x = x * 10 + (c & 15);
}
const int N = 1e6 + 10;
template<class T>
bool chkmax(T &x, T y) {
  if(x < y) return x = y, 1;
  return 0;
}
int n, q, k, a[N], f[N], g[N], m;
vector<int> vec[N];
vector<db> dp[N];
int cur;
db Log[N + N];
void solve(int l, int r, int ql, int qr) {
  if(l > r || ql > qr) return ;
  int mid = (l + r) >> 1, z = 0;
  int y = vec[cur][mid];
  rep(i, ql, qr) {
    int x = vec[cur-1][i];
    if(x < y && a[x] < a[y]) {
      chkmax(dp[cur][mid], dp[cur-1][i] + Log[a[y] - a[x] + k]) && (z = i);
    }
  }
  solve(l, mid - 1, ql, z);
  solve(mid + 1, r, z, qr);
}
int main() {
  read(n);
  rep(i, 1, n) read(a[i]);
  rep(i, 1, n) {
    int w = lower_bound(g + 1, g + m + 1, a[i]) - g;
    g[w] = a[i]; f[i] = w; vec[w].pb(i);
    if(g[m+1]) ++ m;
  }
  rep(i, 1, m) dp[i].resize(vec[i].size());
  printf("%d\n", m);
  read(q);
  rep(T, 1, q) {
    read(k);
    rep(i, 1, n + k) Log[i] = log(i);
    if(T > 1) {
      rep(i, 2, m) {
        dp[i].clear();
        dp[i].resize(vec[i].size());
      }
    }
    for(cur = 2; cur <= m; cur ++)
      solve(0, int(vec[cur].size()) - 1, 0, int(vec[cur - 1].size()) - 1);
    db ans = *max_element(dp[m].begin(), dp[m].end());
    printf("%.8f\n", ans);
  }
//  cerr << "time: " << clock() / (double) CLOCKS_PER_SEC << endl;
  return 0;
}