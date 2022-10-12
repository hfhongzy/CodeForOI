#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 3e5 + 10;
int t, n, mx[N], mn[N], vis[N], cur;
ll ans;
vector<int> G[N];
void dfs(int u, int l, int r, int fa = 0) {
  vis[u] = cur;
  for(int v : G[u]) if(fa != v && l <= v && v <= r) {
    mx[v] = max(mx[u], v);
    mn[v] = min(mn[u], v);
    dfs(v, l, r, u);
  }
}
void solve(int l, int r) {
  if(l == r) {
    return ;
  }
  int mid = (l + r) >> 1;
  solve(l, mid); solve(mid + 1, r);
  mx[mid] = mn[mid] = mid; cur ++; dfs(mid, l, r);
  if(vis[mid + 1] != cur) return ;
  int l0 = l, r0 = r;
  per(i, mid - 1, l) {
    if(vis[i] != cur) { l0 = i + 1; break ; }
    mx[i] = max(mx[i], mx[i + 1]);
    mn[i] = min(mn[i], mn[i + 1]);
  }
  rep(i, mid + 2, r) {
    if(vis[i] != cur) { r0 = i - 1; break ; }
    mx[i] = max(mx[i], mx[i - 1]);
    mn[i] = min(mn[i], mn[i - 1]);
  }
  int j1 = mid + 1, j2 = mid, sum = 0; //[j1, j2]
  per(i, mid, l0) {
    if(mn[i] >= i) {
      //mark : mx[j] <= j
      //L : mx[i] <= j
      //R : mn[j] >= i
      while(j2 < r0 && mn[j2 + 1] >= i) {
        j2 ++;
        sum += (mx[j2] <= j2);
      }
      while(j1 <= j2 && mx[i] > j1) {
        sum -= (mx[j1] <= j1);
        j1 ++;
      }
      ans += sum;
    }
  }
}
int main() {
  scanf("%d", &t);
  while(t --) {
    scanf("%d", &n);
    rep(i, 1, n) G[i].clear();
    rep(i, 1, n - 1) {
      int x, y;
      scanf("%d%d", &x, &y);
      G[y].pb(x); G[x].pb(y);
    }
    ans = n; solve(1, n);
    printf("%lld\n", ans);
  }
  return 0;
}