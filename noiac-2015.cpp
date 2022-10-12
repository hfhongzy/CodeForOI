#include <algorithm>
#include <cstdio>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 2e5 + 10, mod = 1e9 + 7;
int n, ans, T, fac[N * 10], fav[N * 10];
int qpow(int a, int b) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = (ll) a * a % mod)
      if(b & 1) ans = (ll) ans * a % mod;
   return ans;
}
int C(ll n, ll m) {
   return n < 0 || m < 0 || n < m ? 0 : 1ll * fac[n] * fav[m] % mod * fav[n - m] % mod;
}
void binom(int n) {
   fac[0] = 1;
   for(int i = 1; i <= n; i ++) fac[i] = 1ll * fac[i - 1] * i % mod;
   fav[n] = qpow(fac[n], mod - 2);
   for(int i = n; i >= 1; i --) fav[i - 1] = 1ll * fav[i] * i % mod;
}
struct node {
   ll t, x, y;
   bool operator < (const node &b) const {
      return t % T < b.t % T;
   }
} a[N];
ll t[N], x[N], y[N];
int solve() {
   ll cl = -T, cr = T;
   rep(i, 1, n + 1) {
      // printf("time %lld (mod T = %lld), at %lld\n", a[i].t, t[i], x[i]);
   }
   rep(i, 1, n) {
      ll p = a[i + 1].t / T - a[i].t / T;
      if(p == 0) continue ;
      ll x1 = x[i + 1] - x[i] - t[i + 1] + t[i];
      ll x2 = x[i + 1] - x[i] + t[i + 1] - t[i];
      //x2 >= p * c, x1 <= p * c
      if(p > 0) {
         cl = max(cl, x1 / p);
         cr = min(cr, x2 / p); 
      } else {
         cl = max(cl, x2 / p);
         cr = min(cr, x1 / p);
      }
      // printf("ok [%lld, %lld]\n", cl, cr);
      // if(cl > cr) return 0;
   }
   // printf("ok [%lld, %lld]\n", cl, cr);
   // cl = -T, cr = T;
   int ans = 0; t[n + 2] = T;
   rep(c, cl, cr) {
      int res = 1;
      rep(i, 1, n + 1) y[i] = x[i] - (a[i].t / T) * c;
      y[n + 2] = c;
      rep(i, 2, n + 2) if(t[i] == t[i - 1]) {
         if(y[i] != y[i - 1]) { res = 0; break ; }
      } else {

         ll dt = t[i] - t[i - 1], dy = y[i] - y[i - 1];
         if((dt + dy) % 2) { res = 0; break ; }
         res = 1ll * res * C(dt, (dt + dy) / 2) % mod;
         if(!res) break ;
      }
      (ans += res) %= mod;
      // if(res) printf("c = %d !!!\n", c);
   }
   // printf("{%d}\n", ans);
   return ans;
}
int main() {
   scanf("%d%d", &n, &T); binom(T);
   rep(i, 1, n) {
      ll x, y;
      scanf("%lld%lld%lld", &a[i].t, &x, &y);
      a[i].x = x - y; a[i].y = x + y;
   }
   a[n + 1] = {0, 0, 0};
   sort(a + 1, a + n + 2);
   rep(i, 1, n + 1) t[i] = a[i].t % T;
   rep(i, 1, n + 1) x[i] = a[i].x;
   ans = solve(); //printf("%d!\n", ans);
   rep(i, 1, n + 1) x[i] = a[i].y;
   ans = 1ll * ans * solve() % mod;
   printf("%d\n", ans);
   return 0;
}