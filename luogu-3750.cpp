#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 1e5 + 10, mod = 100003;
int c, n, k, t = 1, a[N], rev[N], f[N];
int qpow(int a, int b) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = 1ll * a * a % mod)
      if(b & 1) ans = 1ll * ans * a % mod;
   return ans;
}
int main() {
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i ++) scanf("%d", a + i);
   for(int i = n; i >= 1; i --) {
      for(int j = i + i; j <= n; j += i)
         a[i] ^= rev[j];
      if(a[i]) { rev[i] = 1; c ++; }
   }
   for(int i = 1; i <= n; i ++) t = 1ll * t * i % mod;
   if(c <= k) printf("%d\n", (int) (1ll * t * c % mod));
   else {
      int inv = qpow(n, mod - 2), ans = k; f[n] = 1;
      for(int i = n - 1; i >= k + 1; i --) {
         int x = 1ll * (n - i) * inv % mod;
         f[i] = (1ll + 1ll * x * f[i + 1] % mod) * qpow(mod + 1 - x, mod - 2) % mod;
      }
      for(int i = k + 1; i <= c; i ++) {
         (ans += f[i]) %= mod;
      }
      printf("%d\n", (int) (1ll * ans * t % mod));
   }
	return 0;
}
/*
f[c], c > k, f[i]表示i个必要操作, 变i - 1个的必要操作的期望时间
f[i] = ( 1 + (n - i) / n * f[i + 1] ) /  (1 - (n - i) / n) 
*/