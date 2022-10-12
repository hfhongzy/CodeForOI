#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 512;

int n, m, k, cur, mat[N], vis[N], a[N][N];
vector<int> G[N];
bool dfs(int u) {
   for(int v : G[u]) if(vis[v] < cur) {
      vis[v] = cur;
      if(!mat[v] || dfs(mat[v])) { mat[v] = u; return 1; }
   }
   return 0;
}
int match() {
   int ans = 0;
   rep(i, 1, n) { cur ++; if(dfs(i)) ans ++; }
   return ans;
}

int main() {
   scanf("%d%d%d", &n, &m, &k);
   rep(i, 1, n) rep(j, 1, m) scanf("%d", a[i] + j);
   int l = 0, r = 1e9, mid;
   while(l <= r) {
      mid = (l + r) >> 1;
      rep(i, 1, n) G[i].clear();
      rep(i, 1, m) mat[i] = 0;
      rep(i, 1, n) rep(j, 1, m) if(a[i][j] <= mid) G[i].pb(j);
      if(match() >= n - k + 1) {
         r = mid - 1;
      } else {
         l = mid + 1;
      }
   }
   printf("%d\n", r + 1);
   return 0;
}