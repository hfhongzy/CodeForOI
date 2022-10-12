#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 5005;
int n;
bool g[N][N];
int dfn[N * 2], low[N * 2], idx, bel[N * 2], scc;
vector<int> G[N * 2];
stack<int> st;
bool ins[N * 2];
void tarjan(int u) {
  dfn[u] = low[u] = ++ idx; st.push(u); ins[u] = 1;
  for(int v : G[u]) {
    if(!dfn[v]) {
      tarjan(v); low[u] = min(low[u], low[v]);
    } else if(ins[v]) {
      low[u] = min(low[u], dfn[v]);
    }
  }
  if(low[u] == dfn[u]) {
    int v = 0; scc ++;
    do {
      v = st.top(); st.pop(); ins[v] = 0; bel[v] = scc;
    } while(v != u);
  }
}
int main() {
  scanf("%d", &n);
  rep(i, 1, n) {
    int x, y; scanf("%d", &x);
    while(x --) { scanf("%d", &y); g[i][y] = 1; }
  }
  rep(i, 1, n) rep(j, i + 1, n) {
    if(g[i][j]) G[n + i].pb(j), G[n + j].pb(i);
    else G[i].pb(n + j), G[j].pb(n + i);
  }
  rep(i, 1, 2 * n) if(!dfn[i]) tarjan(i);
  rep(i, 1, n) if(bel[i] == bel[i + n]) { puts("0"); exit(0); }
  vector<int> A, B;
  rep(i, 1, n) (bel[i] < bel[i + n] ? A : B).pb(i);
  int ans = A.size() && B.size();
  vector<int> a(A.size()), b(B.size());
  for(int i = 0; i < (int)A.size(); i ++) {
    int u = A[i], cnt = 0;
    for(int v : B) if(g[u][v]) { cnt ++; a[i] = v; }
    if(cnt >= 2) a[i] = -1;
    if(!cnt && A.size() > 1) ans ++;
  }
  for(int i = 0; i < (int)B.size(); i ++) {
    int v = B[i], cnt = 0;
    for(int u : A) if(!g[u][v]) { cnt ++; b[i] = u; }
    if(!cnt && B.size() > 1) ans ++;
    if(cnt <= 1) {
      for(int j = 0; j < (int)A.size(); j ++)
        if((!b[i] || b[i] == A[j]) && (!a[j] || a[j] == v))
          ans ++;
    }
  }
  printf("%d\n", ans);
  return 0;
}