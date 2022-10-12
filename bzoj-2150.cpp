#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 2510;

int n, m, r, c, cur, a[N][N], ID[N][N], id[2], mat[N], vis[N];
int nl, nr;
vector<int> G[N];
char s[N][N];
bool dfs(int u) {
   for(int v : G[u]) if(vis[v] < cur) {
      vis[v] = cur;
      if(!mat[v] || dfs(mat[v])) { mat[v] = u; return 1; }
   }
   return 0;
}
int match() {
   int ans = 0;
   rep(i, 1, nl) { ++ cur; if(dfs(i)) ans ++; }
   return ans;
}
int main() {
   scanf("%d%d%d%d", &n, &m, &r, &c);
   const int dx[] = {r, c, r, c}, dy[] = {c, r, -c, -r};
   rep(i, 1, n) scanf("%s", s[i] + 1);
   rep(i, 1, n) rep(j, 1, m) if(s[i][j] == '.') ID[i][j] = ++ nl;
   rep(i, 1, n) rep(j, 1, m) if(ID[i][j]) rep(k, 0, 3) {
      int x = i + dx[k], y = j + dy[k];
      if(y >= 1 && x <= n && y <= m && ID[x][y]) {
         G[ID[i][j]].push_back(ID[x][y]);
      }
   }
   nr = nl;
   printf("%d\n", nl - match());
   return 0;
}