#include <algorithm>
#include <cstdio>
#define rep(i, j, k) for(int i = j; i <= k; i ++)
#define per(i, j, k) for(int i = j; i >= k; i --)
using namespace std;
typedef long long ll;
const int N = 55, mod = 1e9 + 7;
int n, m, ans, dp[N][8];
ll st[N];
int main() {
   int t, test = 0; scanf("%d", &t);
   while(t --) {
      scanf("%d%d", &n, &m);
      rep(i, 1, m) {
         st[i] = 0;
         int x; scanf("%d", &x);
         rep(j, 1, x) {
            int y; scanf("%d", &y);
            st[i] |= 1ll << (y - 1);
         }
      }
      ans = 0;
      rep(x, 0, n - 1) rep(y, 0, n - 1) rep(z, 0, n - 1) {
         dp[0][0] = 1;
         rep(i, 1, m) {
            int tmp = ((st[i] >> x & 1) << 2) ^ ((st[i] >> y & 1) << 1) ^ (st[i] >> z & 1);
            rep(j, 0, 7) {
               int la = j ^ tmp;
               dp[i][j] = (dp[i - 1][j] + dp[i - 1][la]) % mod;
            }
         }
         (ans += dp[m][7]) %= mod;
      }
      printf("Case #%d: %d\n", ++ test, ans);
   }
   return 0;
}