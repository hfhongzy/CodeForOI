#include <algorithm>
#include <cstdio>
using namespace std;
const int mod = 1e9 + 7, N = 5e5 + 10;
int n, p[N], q[N];
int qpow(int a, int b) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = 1ll * a * a % mod)
      if(b & 1) ans = 1ll * ans * a % mod;
   return ans;
}
int main() {
   const int inv = 570000004;
   scanf("%d", &n);
   for(int i = 1; i <= n; i ++) {
      scanf("%d%d", p + i, q + i);
      p[i] = 1ll * p[i] * inv % mod;
      q[i] = 1ll * q[i] * inv % mod;
   }
   int P = p[n], Q = q[n];
   for(int i = n - 1; i >= 1; i --) {
      int t = 1ll * p[i] * qpow(mod + 1 - 1ll * Q * q[i] % mod, mod - 2) % mod;
      int nP = 1ll * t * P % mod, nQ = (1ll * t * p[i] % mod * Q + q[i]) % mod;
      P = nP; Q = nQ;
   }
   printf("%d\n", P);
   return 0;
}