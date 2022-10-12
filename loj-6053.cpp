#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;
const int mod = 1e9 + 7;
const int inv2 = (mod + 1) >> 1, inv3 = 333333336;
inline int add(int x, int y) { return x + y >= mod ? x + y - mod : x + y; }
inline int dec(int x, int y) { return x - y < 0 ? x - y + mod : x - y; }
inline void upd(int &x, int y) { (x += y) >= mod ? x -= mod : 0; }

ll n, m;
int p[N], c, sp[N];
bool tag[N];
void sieve(int n) {
   for(int i = 2; i <= n; i ++) {
      if(!tag[i]) { p[++ c] = i; sp[c] = add(sp[c - 1], i); }
      for(int j = 1; i * p[j] <= n; j ++) {
         tag[i * p[j]] = 1;
         if(i % p[j] == 0) break ;
      }
   }
}
ll pos[N * 2];
int len, g[N * 2], h[N * 2], idx1[N], idx2[N];
int S1(ll n) {
   if(n >= mod) n %= mod;
   return n * (n + 1) / 2 % mod;
}
int S(ll n, int j) {
   if(p[j] >= n) return 0;
   int z = n <= m ? idx1[n] : idx2[::n / n];
   int res = dec(dec(g[z], h[z]), dec(sp[j], j));
   for(int k = j + 1; k <= c && (ll) p[k] * p[k] <= n; k ++) {
      int e = 1;
      for(ll x = p[k]; x <= n; x *= p[k], e ++) {
         upd(res, 1ll * (p[k] ^ e) * (S(n / x, k) + (e > 1)) % mod);
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
      g[len] = dec(S1(t), 1);
      h[len] = t - 1 >= mod ? (t - 1) % mod : t - 1;
      if(t <= m) idx1[t] = len;
      else idx2[r] = len; //idx: value -> index
   }
   for(int i = 1; i <= c; i ++) {
      ll up = (ll) p[i] * p[i];
      for(int j = 1; up <= pos[j]; j ++) {
         ll t = pos[j] / p[i];
         int z = t <= m ? idx1[t] : idx2[n / t];
         g[j] = dec(g[j], 1ll * p[i] * (g[z] + mod - sp[i - 1]) % mod);
         h[j] = dec(h[j], dec(h[z], i - 1));
      }
   }
   printf("%d\n", add(3, S(n, 0)));
   return 0;
}