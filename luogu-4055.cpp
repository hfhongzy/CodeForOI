#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 110;

int n, m, nl, nr, cur, ID[N][N], mat[N * N], vis[N * N];
vector<int> G[N * N];
char s[N][N];
bool dfs(int u) {
   for(int v : G[u]) if(vis[v] < cur) {
      vis[v] = cur;
      if(!mat[v] || dfs(mat[v])) { mat[v] = u; mat[u] = v; return 1; }
   }
   return 0;
}
int match() {
   int ans = 0;
   rep(i, 1, nl) { cur ++; if(dfs(i)) ans ++; }
   return ans;
}
bool mark[N];
void dfs2(int u) {
   if(mark[u]) return ;
   mark[u] = 1;
   for(int v : G[u]) if(mat[v]) dfs2(mat[v]);
}
int main() {
   scanf("%d%d", &n, &m);
   rep(i, 1, n) scanf("%s", s[i] + 1);
   rep(i, 1, n) rep(j, 1, m) if(s[i][j] != '#') {
      if(i + j & 1) ID[i][j] = ++ nl;
   }
   nr = nl;
   rep(i, 1, n) rep(j, 1, m) if(s[i][j] != '#') {
      if(!(i + j & 1)) ID[i][j] = ++ nr;
   }
   rep(i, 1, n) rep(j, 1, m) if(ID[i][j]) {
      if(ID[i - 1][j]) G[ID[i][j]].pb(ID[i - 1][j]), G[ID[i - 1][j]].pb(ID[i][j]);
      if(ID[i + 1][j]) G[ID[i][j]].pb(ID[i + 1][j]), G[ID[i + 1][j]].pb(ID[i][j]);
      if(ID[i][j - 1]) G[ID[i][j]].pb(ID[i][j - 1]), G[ID[i][j - 1]].pb(ID[i][j]);
      if(ID[i][j + 1]) G[ID[i][j]].pb(ID[i][j + 1]), G[ID[i][j + 1]].pb(ID[i][j]);
   }
   if(match() * 2 == nr) { puts("LOSE"); return 0; }
   puts("WIN");
   rep(i, 1, nr) if(!mat[i]) dfs2(i);
   rep(i, 1, n) rep(j, 1, m) if(s[i][j] != '#' && mark[ID[i][j]]) {
      printf("%d %d\n", i, j);
   }
   return 0;
}