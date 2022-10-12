#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
mt19937 rnd;
namespace Cipolla {
   //w = \sqrt(a^2 - n)
   //ans = (a + w)^{(p + 1)/2}
   int mod, a, w;
   int qpow(int a, int b) {
      int ans = 1;
      for(; b >= 1; b >>= 1, a = (ll) a * a % mod)
         if(b & 1) ans = (ll) ans * a % mod;
      return ans;
   }
   struct node {
      int x, y;
      node operator * (node b) {
         return {
            static_cast<int>(((ll) x * b.x + (ll) y * b.y % mod * w) % mod),
            static_cast<int>(((ll) x * b.y + (ll) y * b.x) % mod)
         };
      }
   };
   node nqpow(node a, int b) {
      node ans = {1, 0};
      for(; b >= 1; b >>= 1, a = a * a)
         if(b & 1) ans = ans * a;
      return ans;
   }
   int sqrt(int n, int p) {
      if(n == 0) return 0;
      uniform_int_distribution<int> ran(1, p - 1);
      a = ran(rnd);
      while(qpow(w = ((ll) a * a + p - n) % p, (p - 1) / 2) != p - 1) a = ran(rnd);
      return nqpow({a, 1}, (p + 1) / 2).x;
   }
};
int n, p;
int main() {
   int test;
   scanf("%d", &test);
   while(test --) {
      scanf("%d%d", &n, &p);
      Cipolla::mod = p;
      int z = Cipolla::qpow(n % p, (p - 1) / 2);
      if(z == p - 1) {
         puts("Hola!");
      } else if(z == 0) {
         puts("0");
      } else {
         if(n >= p) n %= p;
         int x = Cipolla::sqrt(n, p), y = x ? p - x : 0;
         if(x == y) printf("%d\n", x);
         else printf("%d %d\n", min(x, y), max(x, y));
      }
   }
   return 0;
}