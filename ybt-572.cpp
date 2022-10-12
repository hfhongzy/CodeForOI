#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 305;
const int S = 2e6 + 10;
int n, len[N], id = 1, ch[S][26], fa[S];
char s[N][N], dir[S];
short d[S];
vector<int> G[N];
int child(int u, int c) {
  int &v = ch[u][c];
  if(!v) { v = ++ id; d[v] = d[u] + 1; fa[v] = u; dir[v] = c; }
  return v;
}
void out(int u) {
  if(u <= 1) return ;
  out(fa[u]); putchar(dir[u] + 'a');
}
int mat[S], vis[S], ml[N], cur, lim;
bool dfs(int u) {
  for(int v : G[u]) if(vis[v] < cur) {
    if(d[v] > lim) break ;
    vis[v] = cur;
    if(!mat[v] || dfs(mat[v])) {
      mat[v] = u; ml[u] = v; return 1;
    }
  }
  return 0;
}
bool solve() {
  rep(i, 1, n) ml[i] = 0;
  rep(i, 1, id) mat[i] = 0;
  rep(i, 1, n) {
    cur ++;
    if(!dfs(i)) return 0;
  }
  return 1;
}
struct node {
  int u, p;
};
void init(int row, char s[N], int n) {
  static int nxt[N][26];
  rep(i, 0, 25) nxt[n][i] = -1;
  per(i, n - 1, 0) {
    rep(j, 0, 25) nxt[i][j] = nxt[i + 1][j];
    nxt[i][s[i + 1] - 'a'] = i + 1;
  }
  int cnt = ::n;
  queue<node> q; q.push({1, 0});
  while(q.size()) {
    node now = q.front(); q.pop();
    for(int i = 0; i < 26; i ++) if(~nxt[now.p][i]) {
      int v = child(now.u, i);
      G[row].pb(v);
      q.push({v, nxt[now.p][i]});
      if(!-- cnt) return ;
    }
  }
}
bool check(int mid, bool o = 0) {
  lim = mid;
  if(!solve()) return 0;
  if(!o) return 1;
  printf("%d\n", mid);
  rep(i, 1, n) {
    out(ml[i]); putchar('\n');
  }
  return 1;
}
int main() {
  freopen("diff.in", "r", stdin);
  freopen("diff.out", "w", stdout);
  scanf("%d", &n);
  rep(i, 1, n) {
    scanf("%s", s[i] + 1);
    len[i] = strlen(s[i] + 1);
    init(i, s[i], len[i]);
  }
  lim = 500;
  if(!solve()) { puts("-1"); return 0; }
  int l = 1, r = (int)(*max_element(d + 1, d + id + 1));
  while(l <= r) {
    int mid = (l + r) >> 1;
    if(check(mid)) r = mid - 1;
    else l = mid + 1;
  }
  check(r + 1, 1);
  return 0;
}