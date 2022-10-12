#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 155;
int n, k, mod;
inline void upd(int &x, const int &y) {
   (x += y) >= mod ? x -= mod : 0;
}
namespace part1 {

int f[N];
void main() {
   f[0] = 1; k >>= 1;
   for(int i = 1; i <= n; i ++) {
      f[i] = i <= k;
      for(int j = max(0, i - k - 1); j < i; j ++) { //choose [j + 2, i]
         upd(f[i], f[j]);
      }
   }
   printf("%d\n", (int) (1ll * f[n / 2] * f[n - n / 2] % mod));
}

}
namespace part2 {

int ans, f[N][N][N];
void main() {
   int c = (1 + k) / 2 - 1 + (n + 1) / 2;
   f[0][0][0] = 1;
   for(int i = 1; i <= c; i ++) {
      if(i <= (1 + k) / 2 - 1) {
         for(int j = 0; j <= i - 1; j ++) upd(f[i][0][0], f[i - 1][0][j]);
         for(int j = 1; j <= i; j ++) upd(f[i][0][j], f[i - 1][0][j - 1]);
      } else if(i <= n / 2) {
         for(int x = 0; x <= k + 1; x ++) // 0 0
            for(int y = 0; y <= i - 1; y ++)
               upd(f[i][0][0], f[i - 1][x][y]);
         for(int x = 0; x <= k + 1; x ++) if(x != 1) // 1 0
            for(int z = 0; z <= i - 1; z ++)
               upd(f[i][x][0], f[i - 1][!x ? 0 : x - 1][z]);
         for(int y = 1; y <= i; y ++) // 0 1
            for(int z = 0; z <= k + 1; z ++)
               upd(f[i][0][y], f[i - 1][z][y - 1]);
         for(int x = 2; x <= k + 1; x ++) { // 1 1
            for(int y = 1; y <= i && 1 + y <= x; y ++) {
               if(1 + y == x) {
                  for(int z = 0; z < x; z ++) {
                     upd(f[i][x][y], f[i - 1][z][y - 1]);
                  }
               } else {
                  f[i][x][y] = f[i - 1][x - 1][y - 1];
               }
            }
         }
      } else {
         for(int x = 0; x <= k + 1; x ++) {
            if(x == 0) {
               for(int y = 0; y <= k + 1; y ++)
                  for(int z = 0; z <= i - 1; z ++)
                     upd(f[i][0][0], f[i - 1][y][z]);
               for(int z = 0; z <= i - 1; z ++)
                  upd(f[i][0][0], f[i - 1][0][z]);
            } else if(x != 1) {
               for(int z = 0; z <= i - 1; z ++)
                  upd(f[i][x][0], f[i - 1][x - 1][z]);
            }
         }
      }
   }
   for(int y = 0; y <= k + 1; y ++)
      for(int z = 0; z <= n / 2; z ++)
         upd(ans, f[c][y][z]);
   printf("%d\n", ans);
}

}
int main() {
   scanf("%d%d%d", &n, &k, &mod);
   if(k % 2 == 0) part1::main();
   else part2::main();
   return 0;
}