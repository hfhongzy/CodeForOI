#include <bits/stdc++.h>
#define pb push_back
#define debug(...) fprintf(stderr, __VA_ARGS__);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 1e5 + 10;
int n, m, s[N], t[N], x[N], y[N];
vector<int> G[N];
vector< vector<int> > vec, ans;
void bfs(int *d, int s) {
  fill(d + 1, d + n + 1, N);
  queue<int> q; q.push(s); d[s] = 0;
  while(q.size()) {
    int u = q.front(); q.pop();
    for(int v : G[u]) if(N == d[v]) {
      d[v] = d[u] + 1; q.push(v);
    }
  }
}
bool judge(int sz, int k) {
  // printf("!");
  //1:没有跨两层以上边;2:i内部边,i-1和i+1内部也有3:对应点有边
  for(int i = 0; i < k; i ++) {
    for(int j = 0; j < sz; j ++) {
      int u = vec[i][j];
      int l, lc = 0, r, rc = 0;
      for(int v : G[u]) {
        if(abs(x[v] - x[u]) > 1) return 0;
        if(x[v] == x[u] - 1) {
          lc ++; l = v;
        }
        if(x[v] == x[u] + 1) {
          rc ++; r = v;
        }
      }
      if(lc > 1 || rc > 1) return 0;
      if((i && !lc) || (i < k - 1 && !rc)) return 0;
      vector<int> sm, sl, sr;
      for(int v : G[u]) if(x[v] == x[u]) sm.pb(y[v]);
      sort(sm.begin(), sm.end());
      if(i) {
        for(int v : G[l]) if(x[v] == x[l]) sl.pb(y[v]);
        sort(sl.begin(), sl.end());
        if(sl != sm) return 0;
      }
      if(i < k - 1) {
        for(int v : G[r]) if(x[v] == x[r]) sr.pb(y[v]);
        sort(sr.begin(), sr.end());
        if(sr != sm) return 0;
      }
    }
  }
  return 1;
}
int main() {
  scanf("%d%d", &n, &m);
  int u, v;
  rep(i, 1, m) {
    scanf("%d%d", &u, &v);
    G[u].pb(v); G[v].pb(u);
  }
  ans.resize(1);
  rep(i, 1, n) ans[0].pb(i);
  int rt = 1;
  rep(i, 1, n) if(G[i].size() < G[rt].size()) rt = i;
  bfs(s, rt);
  for(int v : G[rt]) {
    bfs(t, v);
    bool mk = 0;
    vec.clear(); vec.resize(1);
    rep(i, 1, n)
      if(s[i] == t[i]) { mk = 1; break ; }
      else if(s[i] < t[i]) vec[0].pb(i);
    int sz = int(vec[0].size());
    if(mk || n % sz) continue ;
    int k = n / sz;
    fill(x + 1, x + n + 1, -1);
    for(int i = 0; i < sz; i ++) {
      x[vec[0][i]] = 0;
      y[vec[0][i]] = i;
    }
    vec.resize(k);
    for(int i = 1; i < k && !mk; i ++) {
      for(int j = 0; j < sz; j ++) {
        int u = vec[i - 1][j], _u = 0;
        for(int v : G[u]) if(-1 == x[v]) {
          _u = v; break ;
        }
        if(!_u) { mk = 1; break ; }
        x[_u] = i; y[_u] = j; vec[i].pb(_u);
      }
    }
    // debug("this is, %d\n", (int)mk);
    // for(int v : vec[0]) debug("[%d]", v);
    // debug("\n");
    if(mk || !judge(sz, k)) continue ;
    // cerr << "yes";
    if(vec.size() > ans.size()) ans = vec;
  }
  printf("%d %d\n", int(ans.size()), n / int(ans.size()));
  for(auto x : ans) {
    for(auto y : x) printf("%d ", y);
    putchar('\n');
  }
  return 0;
}
/*
12 20
5 12
6 10
8 1
11 3
5 1
12 4
12 2
11 8
2 8
6 4
7 11
9 1
8 10
9 6
4 1
2 5
10 3
7 2
8 4
9 10
*/