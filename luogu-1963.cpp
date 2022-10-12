#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 1e4 + 5;
int n, cur, d[N], mat[N], vis[N], p[N];
vector<int> G[N];
bool dfs(int u) {
   int v1 = (u - 1 + d[u]) % n + 1, v2 = (u - 1 - d[u] + n) % n + 1;
   int v = min(v1, v2);
   if(vis[v] < cur) {
      vis[v] = cur;
      if(!mat[v] || dfs(mat[v])) { mat[v] = u; p[u] = v; return 1; }
   }
   if(v1 == v2) return 0;
   v = max(v1, v2);
   if(vis[v] < cur) {
      vis[v] = cur;
      if(!mat[v] || dfs(mat[v])) { mat[v] = u; p[u] = v; return 1; }
   }
   return 0;
}
int main() {
   scanf("%d", &n);
   rep(i, 1, n) scanf("%d", d + i);
   rep(i, 1, n) if(d[i] > n / 2) { puts("No Answer"); return 0; }
   int ans = 0;
   per(i, n, 1) {
      cur ++;
      if(dfs(i)) ans ++;
   }
   if(ans < n) puts("No Answer");
   else rep(i, 1, n) printf("%d%c", p[i] - 1, " \n"[i == n]);
   return 0;
}