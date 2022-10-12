#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;

typedef long long ll;
typedef vector<int> poly;

const int N = 5e5 + 10;
int mod, g, w[N], p[32], tot, pos[N];
int qpow(int a, int b) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = (ll)a * a % mod)
      if(b & 1) ans = (ll)ans * a % mod;
   return ans;
}
void init(int n) {
   tot = 0; int x = n;
   for(int i = 2; i * i <= x; i ++)
      while(x % i == 0) { x /= i; p[++ tot] = i; }
   if(x > 1) p[++ tot] = x;
   for(g = 2; g < n; g ++) {
      bool mark = 1;
      rep(i, 1, tot) if(qpow(g, n / p[i]) == 1) { mark = 0; break ; }
      if(mark) break ;
   }
   w[0] = 1;
   rep(i, 1, n) w[i] = (ll)w[i - 1] * g % mod;
   rep(i, 0, n - 1) {
      pos[i] = 0;
      int v = i, c = n;
      rep(j, 1, tot) {
         pos[i] += (v % p[j]) * (c / p[j]);
         v /= p[j]; c /= p[j];
      }
   }
}
int n, c;
poly a, b;
void dft(poly &a, int op) {
   poly t = a;
   rep(i, 0, n - 1) a[pos[i]] = t[i];
   for(int s = 1, i = tot; i >= 1; i --) {
      s *= p[i];
      copy(a.begin(), a.end(), t.begin());
      fill(a.begin(), a.end(), 0);
      for(int s2 = s / p[i], j = 0; j < n; j += s) {
         for(int k = 0, _k = 0; k < s; k ++, _k = _k + 1 == s2 ? 0 : _k + 1) {
            for(int z = j, d = 0; d < p[i]; d ++, z += s2) {
               int W = w[k * d * (n / s) % n];
               a[j + k] = (a[j + k] + (ll)W * t[z + _k]) % mod;
            }
         }
      }
   }
   if(op == 1) return ;
   reverse(a.begin() + 1, a.end());
   int inv = qpow(n, mod - 2);
   rep(i, 0, n - 1) a[i] = (ll)a[i] * inv % mod;
}
int main() {
   scanf("%d%d", &n, &c); mod = n + 1; init(n);
   a.resize(n); b.resize(n);
   rep(i, 0, n - 1) scanf("%d", &a[i]);
   rep(i, 0, n - 1) scanf("%d", &b[i]);
   dft(a, 1); dft(b, 1);
   rep(i, 0, n - 1) a[i] = (ll)a[i] * qpow(b[i], c) % mod;
   dft(a, -1);
   rep(i, 0, n - 1) printf("%d\n", a[i]);
   return 0;
}