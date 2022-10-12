#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 1e4 + 10;
const int M = 2e6 + 10;
int n, m, ans, cnt, hd[M], nxt[M], id[M], d[N];
bool vis[N];
vector<int> G[N];
void insert(int u, int v) {
  id[++ cnt] = v; nxt[cnt] = hd[u]; hd[u] = cnt;
}
int main() {
  scanf("%d%d", &n, &m);
  rep(i, 1, n) insert(d[i] = 0, i);
  rep(i, 1, m) {
    int u, v;
    scanf("%d%d", &u, &v);
    G[u].pb(v); G[v].pb(u);
  }
  int u, z = 0;
  rep(i, 1, n) {
    while(1) {
      if(!hd[z]) { z --; continue; }
      if(vis[id[hd[z]]]) { hd[z] = nxt[hd[z]]; continue; }
      u = id[hd[z]];
      break ;
    }
    vis[u] = 1;
    int c = 0;
    for(int v : G[u]) if(!vis[v]) {
      insert(++ d[v], v);
      z = max(z, d[v]);
    } else c ++;
    ans = max(ans, c + 1);
  }
  printf("%d\n", ans);
  return 0;
}