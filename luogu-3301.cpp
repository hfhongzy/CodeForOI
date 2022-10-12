#include <algorithm>
#include <cstdio>
using namespace std;
typedef long long ll;
const int P = 1e6 + 10;
ll qpow(ll a, ll b, ll p) {
   ll ans = 1;
   for(; b >= 1; b >>= 1, a = a * a % p)
      if(b & 1) ans = ans * a % p;
   return ans;
}
void exgcd(ll a, ll b, ll &x, ll &y) {
   if(!b) x = 1, y = 0;
   else exgcd(b, a % b, y, x), y -= a / b * x;
}
ll inv(ll A, ll mod) {
   if(!A) return 0;
   ll x, y; exgcd(A, mod, x, y);
   return (x % mod + mod) % mod;
}
ll pd[7][P], *cur;
void init(ll *pd, ll pi, ll pk) {
   pd[0] = 1;
   for(int i = 1; i <= pk; i ++)
      pd[i] = i % pi ? pd[i - 1] * i % pk : pd[i - 1];
}
ll Fac(ll n, ll pi, ll pk, ll &x) {
   return !n ? 1 : (x += n / pi, Fac(n / pi, pi, pk, x) * qpow(cur[pk], n / pk, pk) % pk * cur[n % pk] % pk);
}
ll calc(ll n, ll m, ll p, ll pi, ll pk) { //C(n, m) mod pk
   ll x = 0, y = 0, z = 0;
   ll ans = Fac(n, pi, pk, x) * inv(Fac(m, pi, pk, y), pk) % pk * inv(Fac(n - m, pi, pk, z), pk) % pk;
   ans = ans * qpow(pi, x - y - z, pk) % pk;
   return ans * (p / pk) % p * inv(p / pk, pk) % p;
}
ll exlucas(ll n, ll m, ll p) {
   static ll pi[7], pk[7]; static int cnt;
   if(!cnt) {
      ll x = p;
      for(ll i = 2; i * i <= x; i ++) if(x % i == 0) {
         cnt ++; pi[cnt] = i; pk[cnt] = 1;
         while(x % i == 0) pk[cnt] *= i, x /= i;
      }
      if(x > 1) { cnt ++; pi[cnt] = pk[cnt] = x; }
      for(int i = 1; i <= cnt; i ++) {
         init(pd[i], pi[i], pk[i]);
      }
   }
   ll ans = 0;
   for(int i = 1; i <= cnt; i ++) {
      cur = pd[i]; (ans += calc(n, m, p, pi[i], pk[i])) %= p;
   }
   return ans;
}
int n, ans, n1, n2, m, p, a[9];
void dfs(int u, int m, int f) {
   if(u == n1 + 1) {
      if(f == 1) (ans += exlucas(m - 1, n - 1, p)) %= p;
      else (ans += p - exlucas(m - 1, n - 1, p)) %= p;
      return ;
   }
   dfs(u + 1, m, f);
   if(m - a[u] > 0) dfs(u + 1, m - a[u], -f);
}
int main() {
   int test; scanf("%d%d", &test, &p);
   while(test --) {
      scanf("%d%d%d%d", &n, &n1, &n2, &m);
      for(int i = 1; i <= n1; i ++) scanf("%d", a + i);
      for(int i = 1; i <= n2; i ++) {
         int x; scanf("%d", &x); m -= x - 1;
      }
      if(m < n) { puts("0"); continue ; }
      ans = 0; dfs(1, m, 1); printf("%d\n", ans);
   }
   return 0;
}