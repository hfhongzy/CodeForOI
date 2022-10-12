#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1010;
const ll INF = 1ll << 60;
int n, m, v[N], g[N][N];
ll s[N], s2[N], f[N][N]; 
ll calc(int l, int r) {
   return ( (s[r] - s[l - 1]) * (s[r] - s[l - 1]) - (s2[r] - s2[l - 1]) ) / 2;
}
int main() {
   while(scanf("%d%d", &n, &m), n || m) {
      rep(i, 1, n) scanf("%d", v + i), s[i] = s[i - 1] + v[i], s2[i] = s2[i - 1] + v[i] * v[i];
      m ++;
      rep(i, 1, m) f[i][i] = 0, g[i][i] = i - 1;
      rep(i, m + 1, n) g[m + 1][i] = i - 1;
      rep(i, 1, n) f[0][i] = INF;
      f[0][0] = 0;
      rep(l, 2, n - m + 1) rep(i, 1, m) {
         int j = i + l - 1;
         f[i][j] = INF;
         rep(k, g[i][j - 1], g[i + 1][j]) {
            ll w = f[i - 1][k] + calc(k + 1, j);
            if(w < f[i][j]) {
               f[i][j] = w; g[i][j] = k;
            }
         }
      }
      printf("%lld\n", f[m][n]);
   }
   return 0;
}