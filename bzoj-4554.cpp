#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 2510;

int n, m, r, c, cur, ID[N][N], ID2[N][N], mat[N], vis[N];
int nl, nr;
vector<int> G[N];
char a[N][N];
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
   rep(i, 1, n) scanf("%s", a[i] + 1);
   rep(i, 1, n) rep(j, 1, m) {
      if(j == 1 || (a[i][j - 1] == '#' && a[i][j] != '#')) nl ++;
      ID[i][j] = nl;
   }
   rep(j, 1, m) rep(i, 1, n) {
      if(i == 1 || (a[i - 1][j] == '#' && a[i][j] != '#')) nr ++;
      ID2[i][j] = nr;
   }
   rep(i, 1, n) rep(j, 1, m) if(a[i][j] == '*') G[ID[i][j]].push_back(ID2[i][j]);
   printf("%d\n", match());
   return 0;
}