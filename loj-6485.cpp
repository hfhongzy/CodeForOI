#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int inv4 = 748683265;
int qpow(int a, int b) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = (ll) a * a % mod)
      if(b & 1) ans = (ll) ans * a % mod;
   return ans;
}
ll n;
int s, a[4];
int main() {
   const int w[4] = {1, 911660635, 998244352, 86583718};
   int test; scanf("%d", &test);
   while(test --) {
      scanf("%lld%d%d%d%d%d", &n, &s, a, a + 1, a + 2, a + 3);
      const int nn = n % (mod - 1);
      int ans = 0;
      rep(i, 0, 3) {
         int res = 0;
         rep(k, 0, 3) {
            res = (res + (ll)w[k * (i - n) & 3] * qpow((s + w[k]) % mod, nn)) % mod;
         }
         ans = (ans + (ll)res * a[i]) % mod;
      }
      ans = (ll)inv4 * ans % mod;
      printf("%d\n", ans);
   }
   return 0;
}