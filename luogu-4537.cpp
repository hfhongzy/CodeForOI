#include <bits/stdc++.h>
using namespace std;
int n, m, ans, sx, sy;
bool vis[16][16];
void dfs(int x, int y) {
   if(x < 0 || x > n || y < 0 || y > m) return ;
   if((x == 0 || x == n || y == 0 || y == m) && !(x == sx && y == sy)) {
      ans ++; return ;
   }
   if(vis[x][y]) return ;
   vis[x][y] = 1;
   dfs(x - 1, y);
   dfs(x + 1, y);
   dfs(x, y - 1);
   dfs(x, y + 1);
   vis[x][y] = 0;
}
int main() {
   cin >> n >> m;
   sy = 0;
   for(sx = 0; sx < n; sx ++) dfs(sx, sy);
   sx = n;
   for(sy = 0; sy < m; sy ++) dfs(sx, sy);
   sy = m;
   for(sx = n - 1; sx >= 0; sx --) dfs(sx, sy);
   sx = 0;
   for(sy = m - 1; sy >= 0; sy --) dfs(sx, sy);
   ans -= 4 * (n + m);
   cout << ans / 2 << '\n';
   return 0;
}