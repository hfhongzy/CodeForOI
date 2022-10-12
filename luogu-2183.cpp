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
ll pd[P];
void init(ll pi, ll pk) {
   pd[0] = 1;
   for(int i = 1; i <= pk; i ++)
      pd[i] = i % pi ? pd[i - 1] * i % pk : pd[i - 1];
}
ll Fac(ll n, ll pi, ll pk, ll &x) {
   return !n ? 1 : (x += n / pi, Fac(n / pi, pi, pk, x) * qpow(pd[pk], n / pk, pk) % pk * pd[n % pk] % pk);
}
ll calc(ll n, ll m, ll p, ll pi, ll pk) { //C(n, m) mod pk
   init(pi, pk);
   ll x = 0, y = 0, z = 0;
   ll ans = Fac(n, pi, pk, x) * inv(Fac(m, pi, pk, y), pk) % pk * inv(Fac(n - m, pi, pk, z), pk) % pk;
   ans = ans * qpow(pi, x - y - z, pk) % pk;
   return ans * (p / pk) % p * inv(p / pk, pk) % p;
}
ll exlucas(ll n, ll m, ll p) {
   ll ans = 0, x = p;
   for(ll i = 2; i * i <= x; i ++) if(x % i == 0) {
      ll pk = 1;
      while(x % i == 0) pk *= i, x /= i;
      (ans += calc(n, m, p, i, pk)) %= p;
   }
   if(x > 1) (ans += calc(n, m, p, x, x)) %= p;
   return ans;
}
int main() {
   int n, m, p, ans = 1;
   scanf("%d%d%d", &p, &n, &m);
   for(int i = 1; i <= m; i ++) {
      int x; scanf("%d", &x);
      if(n < x) { ans = 0; break;  }
      else {
         ans = ans * exlucas(n, x, p) % p;
         n -= x;
      }
   }
   if(ans) printf("%d\n", ans);
   else puts("Impossible");
   return 0;
}