#include <algorithm>
#include <cstdio>
#include <vector>
#include <cmath>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long double db;
const int N = 110;
struct Edge { int v, w; };
int n, m;
vector<Edge> G[N];
db a[N][N];
void gauss(int n) {
   rep(i, 1, n) {
      int k = i;
      rep(j, i, n) if(fabs(a[k][i]) < fabs(a[j][i])) k = j;
      if(k != i) {
         rep(j, i, n + 1) swap(a[k][j], a[i][j]);
      }
      rep(j, i + 1, n) {
         db t = a[j][i] / a[i][i];
         rep(k, i, n + 1) {
            a[j][k] -= t * a[i][k];
         }
      }
   }
   per(i, n, 1) {
      rep(j, i + 1, n)
         a[i][n + 1] -= a[i][j] * a[j][n + 1];
      a[i][n + 1] /= a[i][i];
   }
}
int main() {
   scanf("%d%d", &n, &m);
   rep(i, 1, m) {
      int u, v, w;
      scanf("%d%d%d", &u, &v, &w);
      G[u].push_back((Edge) {v, w});
      if(u != v) G[v].push_back((Edge) {u, w});
   }
   db ans = 0;
   rep(i, 0, 29) {
      rep(j, 0, n) fill(a[j], a[j] + n + 2, 0);
      rep(u, 1, n) {
         a[u][u] = -1;
         if(u == n) a[u][n + 1] = 0;
         else {
            rep(j, 0, (int) G[u].size() - 1) {
               int w = G[u][j].w >> i & 1, v = G[u][j].v;
               if(!w) a[u][v] += 1.0 / G[u].size();
               else {
                  a[u][v] -= 1.0 / G[u].size();
                  a[u][n + 1] -= 1.0 / G[u].size(); //f += 1/d - x / d
               }
            }
         }
      }
      gauss(n); ans += (1 << i) * a[1][n + 1];
   }
   printf("%.3Lf\n", ans);
   return 0;
}