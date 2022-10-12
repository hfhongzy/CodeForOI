#include <algorithm>
#include <cstdio>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;
const int mod = 1e9 + 7;
const int inv2 = (mod + 1) >> 1, inv3 = 333333336;
inline int add(int x, int y) { return x + y >= mod ? x + y - mod : x + y; }
inline int dec(int x, int y) { return x - y < 0 ? x - y + mod : x - y; }
inline void upd(int &x, int y) { (x += y) >= mod ? x -= mod : 0; }

ll n, m;
int p[N], c, sp[N], sp2[N];
bool tag[N];
void sieve(int n) {
   for(int i = 2; i <= n; i ++) {
      if(!tag[i]) {
         p[++ c] = i;
         sp[c] = add(sp[c - 1], i);
         sp2[c] = (sp2[c - 1] + 1ll * i * i) % mod;
      }
      for(int j = 1; i * p[j] <= n; j ++) {
         tag[i * p[j]] = 1;
         if(i % p[j] == 0) break ;
      }
   }
}
ll pos[N * 2]; //开二倍
int len, g1[N * 2], g2[N * 2], idx1[N], idx2[N];
int S1(ll n) {
   if(n >= mod) n %= mod;
   return n * (n + 1) / 2 % mod;
}
int S2(ll n) {
   if(n >= mod) n %= mod;
   return n * (n + 1) / 2 % mod * (2 * n + 1) % mod * inv3 % mod;
}
int S(ll n, int j) {
   if(p[j] >= n) return 0;
   int z = n <= m ? idx1[n] : idx2[::n / n];
   int res = dec(dec(g2[z], g1[z]), dec(sp2[j], sp[j]));
   for(int k = j + 1; k <= c && (ll) p[k] * p[k] <= n; k ++) {
      int e = 1;
      for(ll x = p[k]; x <= n; x *= p[k], e ++) {
         ll xx = x % mod;
         upd(res, xx * (xx - 1) % mod * ((e > 1) + S(n / x, k)) % mod);
      }
   }
   return res;
}
int main() {
   scanf("%lld", &n);
   for(m = 1; m * m <= n; m ++) ;
   sieve(m);
   for(ll l = 1, r; l <= n; l = r + 1) {
      ll t = n / l; r = n / t;
      pos[++ len] = t;
      g1[len] = dec(S1(t), 1);
      g2[len] = dec(S2(t), 1);
      if(t <= m) idx1[t] = len;
      else idx2[r] = len; //idx: value -> index
   }
   for(int i = 1; i <= c; i ++) {
      ll up = (ll) p[i] * p[i];
      for(int j = 1; up <= pos[j]; j ++) {
         ll t = pos[j] / p[i];
         int z = t <= m ? idx1[t] : idx2[n / t];
         g1[j] = dec(g1[j], (ll) p[i] * dec(g1[z], sp[i - 1]) % mod);
         g2[j] = dec(g2[j], up % mod * dec(g2[z], sp2[i - 1]) % mod);
      }
   }
   printf("%d\n", add(1, S(n, 0)));
   return 0;
}