#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
struct node { int x, y; };
struct tree {
  vector<int> ls, rs;
  tree(int n) { ls = rs = vector<int>(n + 1); }
  bool Leaf(int u) { return !(ls[u] || rs[u]); }
};
int m;
vector<tree> T;
bool dfs(vector<node> &v) {
  if(!v.size()) return 0;
  vector<node> v1, v2, v3, v4;
  for(node &c : v) {
    if(T[c.x].Leaf(c.y)) return 1;
    int l = T[c.x].ls[c.y], r = T[c.x].rs[c.y];
    if(!l) v1.pb({c.x, r});
    else if(!r) v2.pb({c.x, l});
    else {
      if(T[c.x].Leaf(l)) v3.pb({c.x, r});
      if(T[c.x].Leaf(r)) v4.pb({c.x, l});
    }
  }
  return dfs(v1) && dfs(v2) && dfs(v3) && dfs(v4);
}
int main() {
  int test;
  scanf("%d", &test);
  rep(_, 1, test) {
    T.clear();
    scanf("%d", &m);
    rep(t, 1, m) {
      int n;
      scanf("%d", &n);
      tree S(n);
      rep(i, 1, n) scanf("%d%d", &S.ls[i], &S.rs[i]);
      bool ok = 1;
      rep(i, 1, n) if(!S.Leaf(S.ls[i]) && !S.Leaf(S.rs[i])) ok = 0, i = n;
      if(ok) T.pb(S);
    }
    vector<node> pa;
    rep(i, 0, int(T.size()) - 1) pa.pb({i, 1});
    puts(dfs(pa) ? "Almost Complete" : "No");
  }
  return 0;
}