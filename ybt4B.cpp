#include <bits/stdc++.h>
#define LOG(FMT...) fprintf(stderr, FMT)
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int N = 1e6 + 10;

int n, x[N], y[N], l[N], r[N], f[N], u[N], v[N];
ll cross(int a, int b, int c) { //ab*ac
  int x1 = x[b] - x[a], y1 = y[b] - y[a];
  int x2 = x[c] - x[a], y2 = y[c] - y[a];
  return (ll)x1 * y2 - (ll)x2 * y1;
}
ll res[N];
vector<pii> G[N];
void dfs(int u, ll len = 0) {
  res[u] = len;
  for(auto &x : G[u]) {
    dfs(x.first, len + x.second);
  }
}
bool _less(int a, int b) {
  return y[a] < y[b] || (y[a] == y[b] && a < b);
}
int main() {
  freopen("mountain.in", "r", stdin);
  freopen("mountain.out", "w", stdout);
  scanf("%d", &n);
  int mx = 1;
  rep(i, 1, n) {
    scanf("%d%d", x + i, y + i);
    if(y[mx] <= y[i]) mx = i;
  }
  static int st[N];
  int top = 0;
  rep(i, 1, n) {
    while(top >= 2 && cross(st[top - 1], st[top], i) > 0) {
      top --;
    }
    l[i] = top ? st[top] : i;
    if(i == mx) l[i] = i;
    st[++ top] = i;
  }
  top = 0;
  per(i, n, 1) {
    while(top >= 2 && cross(st[top - 1], st[top], i) < 0) {
      top --;
    }
    r[i] = top ? st[top] : i;
    if(i == mx) r[i] = i;
    st[++ top] = i;
    f[i] = y[l[i]] > y[r[i]] ? l[i] : r[i];
    // LOG("f%d = %d, l, r = %d %d\n", i, f[i], l[i], r[i]);
  }
  top = 0;
  rep(i, 1, n) {
    while(top && _less(f[st[top]], f[i])) {
      top --;
    }
    u[i] = top ? st[top] : f[i];
    st[++ top] = i;
  }
  top = 0;
  per(i, n, 1) {
    while(top && _less(f[st[top]], f[i])) {
      top --;
    }
    v[i] = top ? st[top] : f[i];
    st[++ top] = i;
    // cerr << "for " << i << " : " << u[i] << ", " << v[i] << endl;
  }
  rep(i, 1, n) {
    if(i == mx) continue ;
    if(f[i] > i) {
      G[v[i]].pb({i, v[i] - i});
    } else {
      G[u[i]].pb({i, i - u[i]});
    }
  }
  dfs(mx);
  rep(i, 1, n) {
    printf("%lld\n", res[i]);
  }
  return 0;
}