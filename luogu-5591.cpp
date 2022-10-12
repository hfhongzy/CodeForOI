#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int mod = 998244353;
int qpow(int a, int b) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = (ll) a * a % mod)
      if(b & 1) ans = (ll) ans * a % mod;
   return ans;
}
int inv(int a) { return qpow(a, mod - 2); }
int n, p, k, ans, w[1 << 20];
int main() {
   scanf("%d%d%d", &n, &p, &k);
   w[0] = 1; w[1] = qpow(3, (mod - 1) / k);
   for(int i = 2; i < k; i ++) w[i] = (ll) w[i - 1] * w[1] % mod;
   
   for(int t = 0; t < k; t ++) {
      ans = (ans + (t == 0 ? k * (k - 1ll) / 2 % mod : k * (ll)inv(w[k - t] - 1) % mod) * qpow((ll)p * w[t] % mod + 1, n)) % mod;
   }
   ans = (ll)ans * inv(k) % mod;
   ans = ((ll)n * p % mod * qpow(p + 1, n - 1) % mod + mod - ans);
   ans = (ll)ans * inv(k) % mod;
   if(ans < 0) ans += mod;
   printf("%d\n", ans);
   return 0;
}