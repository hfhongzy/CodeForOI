#include <algorithm>
#include <cstring>
#include <cstdio>
#include <vector>
#define pb push_back
using namespace std;
const int N = 31, mod = 1e9 + 9;
int n, m, ans, _d1, _d2, g[N][N][N][N], f[3][3][3][3];
char s[N + 1][N + 1];
vector<int> dx1, dy1, dx2, dy2;
vector< pair<int, int> > dir1, dir2;
inline void upd(int &x, const int &y) {
   (x += y) >= mod ? x -= mod : 0;
}
bool valid(int x, int y) {
   return 1 <= x && x <= n && 1 <= y && y <= m;
}
int dfs(int x1, int y1, int x2, int y2) {
   if(!valid(x1, y1) || !valid(x2, y2) || s[x1][y1] != s[x2][y2]) return 0;
   if(~ g[x1][y1][x2][y2]) return g[x1][y1][x2][y2];
   int ans = 1;
   for(int i = 0; i < (int) dir1.size(); i ++)
      for(int j = 0; j < (int) dir2.size(); j ++)
         upd(ans, dfs(x1 + dir1[i].first, y1 + dir1[i].second, x2 + dir2[j].first, y2 + dir2[j].second));
   return g[x1][y1][x2][y2] = ans;
}
int calc2(int d1, int d2) {
   if(~ f[d1 + 1][d2 + 1][_d1 + 1][_d2 + 1]) return f[d1 + 1][d2 + 1][_d1 + 1][_d2 + 1];
   dx2.clear(); dy2.clear();
   dx2.pb(0); dy2.pb(0);
   if(d1) dx2.pb(d1);
   if(d2) dy2.pb(d2);
   dir1.clear(); dir2.clear();
   for(int i = 0; i < (int) dx1.size(); i ++) {
      for(int j = 0; j < (int) dy1.size(); j ++) if(dx1[i] || dy1[j]) {
         dir1.pb(pair<int, int>(dx1[i], dy1[j]));
      }
   }
   for(int u = 0; u < (int) dx2.size(); u ++) {
      for(int v = 0; v < (int) dy2.size(); v ++) if(dx2[u] || dy2[v]) {
         dir2.pb(pair<int, int>(dx2[u], dy2[v]));
      }
   }
   memset(g, -1, sizeof g);
   int ans = 0;
   for(int x1 = 1; x1 <= n; x1 ++) {
      for(int y1 = 1; y1 <= m; y1 ++) {
         for(int x2 = 1; x2 <= n; x2 ++) {
            for(int y2 = 1; y2 <= m; y2 ++) {
               upd(ans, dfs(x1, y1, x2, y2));
            }
         }
      }
   }
   return f[_d1 + 1][_d2 + 1][d1 + 1][d2 + 1] = ans;
}
int calc1(int d1, int d2) {
   dx1.clear(); dy1.clear();
   dx1.pb(0); dy1.pb(0);
   if(d1) dx1.pb(d1);
   if(d2) dy1.pb(d2);
   int ans = 0; _d1 = d1; _d2 = d2;
   upd(ans, calc2(1, 1));
   upd(ans, calc2(1, -1));
   upd(ans, calc2(-1, 1));
   upd(ans, calc2(-1, -1));
   upd(ans, mod - calc2(-1, 0));
   upd(ans, mod - calc2(1, 0));
   upd(ans, mod - calc2(0, 1));
   upd(ans, mod - calc2(0, -1));
   return ans;
}
int main() {
   scanf("%d%d", &n, &m);
   for(int i = 1; i <= n; i ++)
      scanf("%s", s[i] + 1);
   memset(f, -1, sizeof f);
   upd(ans, calc1(1, 1));
   upd(ans, calc1(1, -1));
   upd(ans, calc1(-1, 1));
   upd(ans, calc1(-1, -1));
   upd(ans, mod - calc1(-1, 0));
   upd(ans, mod - calc1(1, 0));
   upd(ans, mod - calc1(0, 1));
   upd(ans, mod - calc1(0, -1));
   printf("%d\n", ans % mod);
   return 0;
}