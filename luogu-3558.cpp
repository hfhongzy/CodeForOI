#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
template<class T>
inline void chkmin(T &x, const T &y) { if(x > y) x = y; }
const int N = 1e6 + 10;
int n, a[N], f[N][3];
int main() {
   scanf("%d", &n);
   rep(i, 1, n) scanf("%d", a + i);
   rep(i, -1, 1) f[1][i + 1] = i == a[1] ? 0 : int(1e9);
   rep(i, 2, n) {
      rep(j, -1, 1) f[i][j + 1] = int(1e9);
      rep(j, -1, 1) {
         if(j == -1) {
            chkmin(f[i][0], f[i - 1][j + 1] + a[i] + 1);
            if(~ a[i]) chkmin(f[i][1], f[i - 1][j + 1] + a[i]);
            if(a[i] == 1) chkmin(f[i][2], f[i - 1][j + 1]);
         } else if(j == 0) {
            if(a[i] == 0) chkmin(f[i][1], f[i - 1][j + 1]);
            if(a[i] == 1) chkmin(f[i][2], f[i - 1][j + 1]);
         } else {
            chkmin(f[i][2], f[i - 1][j + 1] + 1 - a[i]);
         }
      }
   }
   int res = min(f[n][0], min(f[n][1], f[n][2]));
   if(res > N) puts("BRAK");
   else printf("%d\n", res);
   return 0;
}