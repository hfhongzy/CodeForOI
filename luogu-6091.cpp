#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 1e6 + 10;
int n, ph, d, ans[N], php[N];
int phi(int n) {
   int ans = n;
   for(int i = 2; i * i <= n; i ++) {
      if(n % i == 0) {
         ans = ans / i * (i - 1);
         while(n % i == 0) n /= i;
      }
   }
   if(n > 1) ans = ans / n * (n - 1);
   return ans;
}
void work(int ph) {
   php[0] = 0;
   for(int i = 2; i * i <= ph; i ++) {
      if(ph % i == 0) {
         php[++ php[0]] = i;
         while(ph % i == 0) ph /= i;
      }
   }
   if(ph > 1) php[++ php[0]] = ph;
}
int qpow(int a, int b) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = 1ll * a * a % n)
      if(b & 1) ans = 1ll * ans * a % n;
   return ans;
}
int gcd(int x, int y) { return !y ? x : gcd(y, x % y); }
int minG(int n) {
   for(int g = 1; g < n; g ++) if(qpow(g, ph) == 1) {
      bool tag = 1;
      for(int i = 1; i <= php[0]; i ++) {
         if(qpow(g, ph / php[i]) == 1) {
            tag = 0; break ;
         }
      }
      if(tag) return g;
   }
   return 0;
}
void solve(int n) {
   work(ph = phi(n));
   int g = minG(n), res = 1; ans[0] = 0;
   if(!g) return ;
   for(int i = 1; i <= ph; i ++) {
      res = 1ll * res * g % n;
      if(gcd(i, ph) == 1) ans[++ ans[0]] = res;
   }
}
int main() {
   int test; scanf("%d", &test);
   while(test --) {
      scanf("%d%d", &n, &d);
      solve(n);
      printf("%d\n", ans[0]);
      sort(ans + 1, ans + ans[0] + 1);
      for(int i = d; i <= ans[0]; i += d) {
         printf("%d ", ans[i]);
      }
      putchar('\n');
   }
   return 0;
}