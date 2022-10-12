#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int mod = 10086;
typedef long long ll;
struct Base {
   ll base[64];
   int n, sz;
   void insert(ll x) {
      n ++;
      per(i, 50, 0) if(x >> i & 1) {
         if(!base[i]) { base[i] = x; sz ++; return; }
         x ^= base[i];
      }
   }
   ll rk(ll x) {
      ll ans = 0; int y = 0;
      per(i, 50, 0) if(base[i]) {
         y ++;
         if(x >> i & 1) {
            (ans += 1ll << (sz - y)) %= mod;
         }
      }
      rep(i, 1, n - sz) ans = (ans + ans) % mod;
      return ans;
   }
} b;
int n;
int main() {
   scanf("%d", &n);
   ll x;
   rep(i, 1, n) {
      scanf("%lld", &x);
      b.insert(x);
   }
   scanf("%lld", &x);
   printf("%lld\n", (1 + b.rk(x)) % mod);
   return 0;
}