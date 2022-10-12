#include <algorithm>
#include <cstdio>
using namespace std;
const int V = 410;
int s, t;
char fir[10];
bool f[18][V + 5][V + 5];
bool tranA(int i, int j, int k) {
   int u = j * k, c = 0, px = 0, py = 0;
   for(int x = s; x * x <= u; x ++) if(u % x == 0) {
      int y = u / x;
      if(x > y) break ;
      if(y <= V && !f[i - 1][x][y]) {
         c ++; px = x; py = y;
         if(c >= 2) break ;
      }
   }
   return c == 1 && px == j && py == k;
}
bool tranB(int i, int j, int k) {
   int u = j + k, c = 0, px = 0, py = 0;
   for(int x = s; x * 2 <= u; x ++) {
      int y = u - x;
      if(x > y) break ;
      if(y <= V && !f[i - 1][x][y]) {
         c ++; px = x; py = y;
         if(c >= 2) break ;
      }
   }
   return c == 1 && px == j && py == k;
}
bool chkA(int i, int j, int k) {
   int u = j * k, c = 0, px = 0, py = 0;
   for(int x = s; x * x <= u; x ++) if(u % x == 0) {
      int y = u / x;
      if(x > y) break ;
      if(y <= V && f[i][x][y] && !f[i - 1][x][y]) {
         c ++; px = x; py = y;
         if(c >= 2) break ;
      }
   }
   return c == 1 && px == j && py == k;
}
bool chkB(int i, int j, int k) {
   int u = j + k, c = 0, px = 0, py = 0;
   for(int x = s; x * 2 <= u; x ++) {
      int y = u - x;
      if(x > y) break ;
      if(y <= V && f[i][x][y] && !f[i - 1][x][y]) {
         c ++; px = x; py = y;
         if(c >= 2) break ;
      }
   }
   return c == 1 && px == j && py == k;
}
int main() {
   scanf("%d%s%d", &s, fir, &t);
   for(int i = 1; i <= t + 1; i ++) {
      bool A = (*fir == 'A') ^ (i % 2 == 0);
      for(int j = s; j <= V; j ++) {
         for(int k = j; k <= V; k ++) {
            if(f[i - 1][j][k]) f[i][j][k] = 1;
            else f[i][j][k] = A ? tranA(i, j, k) : tranB(i, j, k);
         }
      }
   }
   bool tA = (*fir == 'A') ^ ((t + 2) % 2 == 0);
   for(int sum = 2 * s; sum <= 2 * V; sum ++) {
      for(int m = s; m <= V && m <= sum; m ++) {
         int n = sum - m;
         if(n < m) break ;
         if(n > V) continue ;
         if(f[t][m][n] || !f[t + 1][m][n]) continue ;
         bool tag = tA ? chkA(t + 1, m, n) : chkB(t + 1, m, n);
         if(tag) {
            printf("%d %d\n", m, n);
            return 0;
         }
      }
   }
   puts("no res");
   return 0;
}