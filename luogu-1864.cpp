#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
template<class T>
inline void chkmin(T &x, const T &y) { if(x > y) x = y; }
const int N = 70 + 10;
struct node {
   int v, w, p;
   bool operator < (const node &b) const {
      return v < b.v;
   }
} a[N];
int n, c, num[N];
ll dp[N][N][N], sp[N];
int main() {
   scanf("%d%d", &n, &c);
   rep(i, 1, n) scanf("%d", &a[i].v);
   rep(i, 1, n) scanf("%d", &a[i].w), num[i] = a[i].w;
   rep(i, 1, n) scanf("%d", &a[i].p);
   sort(a + 1, a + n + 1);
   rep(i, 1, n) sp[i] = sp[i - 1] + a[i].p;
   sort(num + 1, num + n + 1);
   rep(i, 1, n) a[i].w = lower_bound(num + 1, num + n + 1, a[i].w) - num;
   memset(dp, 0x3f, sizeof dp);
   rep(i, 1, n) {
      per(j, n, 1) dp[i][i][j] = min(dp[i][i][j + 1], (j == a[i].w ? 0ll : c) + a[i].p);
   }
   rep(i, 1, n + 1) rep(j, 1, n) dp[i][i - 1][j] = 0;
   per(l, n - 1, 1) rep(r, l + 1, n) {
      per(i, n, 1) {
         rep(k, l, r) {
            chkmin(dp[l][r][i], dp[l][k - 1][i] + dp[k + 1][r][i] + (a[k].w == i ? 0ll : c));
         }
         dp[l][r][i] += sp[r] - sp[l - 1];
         chkmin(dp[l][r][i], dp[l][r][i + 1]);
      }
   }
   printf("%lld\n", dp[1][n][1]);
   return 0;
}