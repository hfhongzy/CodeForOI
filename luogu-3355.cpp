#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 215;
const int dx[] = {1, 2, -1, -2, 1, -2, 2, -1};
const int dy[] = {2, 1, -2, -1, -2, 1, -1, 2};
int n, m, cur, a[N][N], ID[N][N], id[2], mat[N * N], vis[N * N];
vector<int> G[N * N];
bool dfs(int u) {
   for(int v : G[u]) if(vis[v] < cur) {
      vis[v] = cur;
      if(!mat[v] || dfs(mat[v])) {
         mat[v] = u; return 1;
      }
   }
   return 0;
}
int match() {
   int ans = 0;
   rep(i, 1, id[1]) {
      ++ cur;
      if(dfs(i)) ans ++;
   }
   return ans;
}
int main() {
   scanf("%d%d", &n, &m);
   rep(i, 1, m) { int u, v; scanf("%d%d", &u, &v); a[u][v] = 1; }
   rep(i, 1, n) rep(j, 1, n) ID[i][j] = !a[i][j] ? ++ id[i + j & 1] : 0;
   rep(i, 1, n) rep(j, 1, n) if(ID[i][j] && (i + j) % 2) rep(k, 0, 7) {
      int x = i + dx[k], y = j + dy[k];
      if(x >= 1 && y >= 1 && x <= n && y <= n && ID[x][y]) {
         G[ID[i][j]].push_back(ID[x][y]);
      }
   }
   printf("%d\n", id[0] + id[1] - match());
   return 0;
}