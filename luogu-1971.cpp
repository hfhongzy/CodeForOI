#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 80;

int n, m, k, nl, nr, cur, ID[N][N], mat[N * N], vis[N * N], seq[N * N];
vector<int> G[N * N];
char s[N][N];
bool ban[N * N], mark[N * N];
bool dfs(int u) {
   if(ban[u]) return 0;
   for(int v : G[u]) if(vis[v] < cur) {
      vis[v] = cur;
      if(!ban[v] && (!mat[v] || dfs(mat[v]))) { mat[v] = u; mat[u] = v; return 1; }
   }
   return 0;
}
void match() {
   rep(i, 1, nl) { cur ++; dfs(i); }
}
int main() {
   scanf("%d%d", &n, &m);
   rep(i, 1, n) scanf("%s", s[i] + 1);
   rep(i, 1, n) rep(j, 1, m) if(s[i][j] != 'O') {
      ID[i][j] = ++ nl;
      if(s[i][j] == '.') seq[0] = nl;
   }
   nr = nl;
   rep(i, 1, n) rep(j, 1, m) if(s[i][j] == 'O') ID[i][j] = ++ nr;
   rep(i, 1, n) rep(j, 1, m) {
      if(i < n && bool(s[i][j] == 'O') != bool(s[i + 1][j] == 'O')) G[ID[i][j]].pb(ID[i + 1][j]), G[ID[i + 1][j]].pb(ID[i][j]);;
      if(j < m && bool(s[i][j] == 'O') != bool(s[i][j + 1] == 'O')) G[ID[i][j]].pb(ID[i][j + 1]), G[ID[i][j + 1]].pb(ID[i][j]);;
   }
   scanf("%d", &k);
   rep(i, 1, 2 * k) { int x, y; scanf("%d%d", &x, &y); seq[i] = ID[x][y]; }
   match();
   rep(i, 0, 2 * k - 1) {
      int u = seq[i]; ban[u] = 1;
      if(mat[u]) {
         int v = mat[u]; mat[u] = mat[v] = 0;
         cur ++;
         if(dfs(v)) mark[i] = 1;
      } else {
         mark[i] = 1;
      }
   }
   vector<int> ans;
   for(int i = 0; i <= 2 * k - 2; i += 2) if(!mark[i] && !mark[i + 1]) ans.pb(i / 2 + 1);
   printf("%d\n", (int)ans.size());
   for(int v : ans) printf("%d\n", v);
   return 0;
}