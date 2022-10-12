#include <bits/stdc++.h>
#define pb push_back
#define LOG(FMT...) fprintf(stderr, FMT);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 5e5 + 10;
const int M = 3e6 + 10;
struct Edge {
  int v, nxt;
} e[M];
int n, m, hd[N], ec;
void clr(int n) {
  fill(hd + 1, hd + n + 1, -1); ec = 0;
}
void add(int u, int v) {
  e[ec] = {v, hd[u]}; hd[u] = ec ++;
}
int dfn[N], low[N], idx, bcc, bel[N], c[N];
stack<int> st;
void tarjan(int u, int p = 0) {
  low[u] = dfn[u] = ++ idx; st.push(u);
  for(int i = hd[u]; ~i; i = e[i].nxt) {
    int v = e[i].v;
    if(!(i ^ p ^ 1)) continue ;
    if(!dfn[v]) {
      tarjan(v, i);
      low[u] = min(low[u], low[v]);
    } else {
      low[u] = min(low[u], dfn[v]);
    }
  }
  if(low[u] == dfn[u]) {
    int v = 0; ++ bcc;
    while(v ^ u) {
      v = st.top(); st.pop(); bel[v] = bcc;
    }
  }
}
int sg[N];
void dfs(int u, int fa = 0) {
  sg[u] = c[u];
  for(int i = hd[u]; ~i; i = e[i].nxt) {
    int v = e[i].v;
    if(v == fa) continue;
    dfs(v, u);
    sg[u] ^= sg[v] + 1;
  }
}
int main() {
  scanf("%d%d", &n, &m); clr(n);
  int u, v;
  rep(i, 1, m) {
    scanf("%d%d", &u, &v);
    add(u, v); add(v, u);
  }
  tarjan(1, M);
  m = ec; clr(bcc);
  for(int i = 0; i < m; i += 2) {
    u = bel[e[i + 1].v]; v = bel[e[i].v];
    if(u != v) {
      add(u, v); add(v, u);
    } else {
      c[u] ^= 1;
    }
  }
  dfs(bel[1]);
  printf("%d\n", sg[bel[1]]);
  return 0;
}