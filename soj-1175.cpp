#include <bits/stdc++.h>
#define fs first
#define sc second
#define pb push_back
#define pii pair<int, int>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 1e4 + 10;
struct node {
  int id, l, r;
} a[N];
int n, m, dep, wide, f[N], d[N], cnt[N];
vector<int> G[N];
vector<pair<char, int>> ans;
void dfs(int u, int de = 1) {
  cnt[de] ++; d[u] = de;
  if(cnt[de] > cnt[wide]) wide = de;
  if(de > d[dep]) dep = u;
  for(int v : G[u]) {
    f[v] = u;
    dfs(v, de + 1);
  }
}
void solve1() {
  vector<int> vec;
  for(int u = dep; u; u = f[u]) vec.pb(u);
  reverse(vec.begin(), vec.end());
  vector<int> cnt(vec.size());
  for(int i = 0; i < (int)vec.size(); i ++) {
    int u = vec[i];
    cnt[i] = 0;
    if(i == (int)vec.size() - 1) {
      rep(j, a[u].l, a[u].r) {
        ans.pb({'+', j}); cnt[i] ++;
      }
    } else {
      rep(j, a[u].l, a[vec[i + 1]].l - 1) {
        ans.pb({'+', j}); cnt[i] ++;
      }
      rep(j, a[vec[i + 1]].r + 1, a[u].r) {
        ans.pb({'+', j}); cnt[i] ++;
      }
    }
  }
  for(int i = 0; i < (int)vec.size(); i ++) {
    int u = vec[i];
    cnt[i] = 0;
    if(i == (int)vec.size() - 1) {
      rep(j, a[u].l, a[u].r) {
        ans.pb({'+', j}); cnt[i] ++;
      }
    } else {
      rep(j, a[u].l, a[vec[i + 1]].l - 1) {
        ans.pb({'+', j}); cnt[i] ++;
      }
      rep(j, a[vec[i + 1]].r + 1, a[u].r) {
        ans.pb({'+', j}); cnt[i] ++;
      }
    }
  }
}
int main() {
  scanf("%d%d", &n, &m);
  rep(i, 1, m) {
    scanf("%d%d", &a[i].l, &a[i].r);
    a[i].id = i;
  }
  while(n) {
    sort(a + 1, a + n + 1, [&](node x, node y) { return x.l < y.l || (x.l == y.l && x.r > y.r); });
    rep(i, 1, n) G[i].clear();
    static int st[N], R[N];
    int top = 0;
    rep(i, 0, n) cnt[i] = 0;
    rep(i, 1, n) {
      int x = 0, y = top, pre = -1;
      while(x <= y) {
        int mid = (x + y) >> 1;
        if(R[mid] >= a[i].r) {
          x = (ans = mid) + 1;
        } else {
          y = mid - 1;
        }
      }
      if(pre == -1) {
        G[0].pb(i);
      } else {
        G[pre].pb(i);
      }
      while(top && R[top] <= a[i].r) top --;
      st[++ top] = i; R[top] = a[i].r;
    }
    dep = wide = 0;
    dfs(0);
    if(d[dep] > cnt[wide]) solve1();
    else solve2();
  }
  printf("%d\n", (int)ans.size());
  for(auto x : ans) {
    if(x.fs == '-') puts("-");
    else printf("%c %d\n", ans.fs, ans.sc);
  }
  return 0;
}
