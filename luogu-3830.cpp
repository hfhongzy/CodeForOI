#include <algorithm>
#include <cstdio>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef double db;
const int N = 105;
int n, q;
int main() {
   scanf("%d%d", &q, &n);
   if(q == 1) {
      static db f[N];
      f[1] = 0;
      rep(i, 2, n) {
         f[i] = f[i - 1] + 2.0 / i;
      }
      printf("%.6f\n", f[n]);
   }
   if(q == 2) {
      static db f[N][N], ans;
      f[1][0] = 1;
      rep(i, 2, n) {
         f[i][0] = 1;
         rep(j, 1, n) {
            rep(k, 1, i - 1) {
               f[i][j] += f[k][j - 1] + f[i - k][j - 1] - f[k][j - 1] * f[i - k][j - 1];
            }
            f[i][j] /= i - 1;
         }
      }
      rep(i, 1, n - 1) ans += f[n][i];
      printf("%.6f\n", ans);
   }
   return 0;
}