#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1610;
bitset<N> a[N];
void gauss(int n) {
   for(int i = 1; i <= n; i ++) {
      int k = 0;
      for(k = i; k <= n; k ++) if(a[k][i]) break ;
      if(k <= n) {
         swap(a[k], a[i]);
         for(int j = i + 1; j <= n; j ++) if(a[j][i]) a[j] ^= a[i];
      }
   }
   for(int i = n; i >= 1; i --) {
      if(!a[i][i]) { a[i][n + 1] = 1; continue ; }
      for(int j = i + 1; j <= n; j ++) if(a[i][j]) a[i][n + 1] = a[i][n + 1] ^ a[j][n + 1];
   }
}
int n, m;
// #define ID(x, y) m * (x - 1) + y
int main() {
   scanf("%d%d", &n, &m);
   int c = 0;
   rep(i, 1, n) rep(j, 1, m) {
      c ++; a[c][c] = 1;
      if(i > 1) a[c][c - m] = 1;
      if(j > 1) a[c][c - 1] = 1;
      if(i < n) a[c][c + m] = 1;
      if(j < m) a[c][c + 1] = 1;
   }
   gauss(n * m);
   c = 0;
   rep(i, 1, n) {
      rep(j, 1, m) printf("%d ", (int) a[++ c][n * m + 1]);
      putchar('\n');
   }
   return 0;
}