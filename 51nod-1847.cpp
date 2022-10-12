#include <bits/stdc++.h>
#define uint QAQAQ
using namespace std;

typedef unsigned uint;
// typedef unsigned long long uint;
typedef unsigned long long ull;

const int N = 1e6 + 5, M = 1e3 + 10, K = 52;

uint n, c, k, p[N], pk[N], spk[N], phi[N];
uint pos[N], idx1[N], idx2[N], m, ss, g[N], h[N], a[N];
bool tag[N];
uint qpow(uint a, uint b) {
   uint ans = 1;
   for(; b; b >>= 1, a *= a) if(b & 1) ans *= a;
   return ans;
}
void sieve(uint n) {
   phi[1] = 1;
   for(uint i = 2; i <= n; i ++) {
      if(!tag[i]) {
         p[++ c] = i; phi[i] = i - 1;
         pk[c] = qpow(i, k); spk[c] = spk[c - 1] + pk[c];
      }
      for(uint j = 1; j <= c && i * p[j] <= n; j ++) {
         uint u = i * p[j]; tag[u] = 1;
         if(i % p[j] == 0) { phi[u] = phi[i] * p[j]; break ; }
         phi[u] = phi[i] * (p[j] - 1);
      }
      phi[i] += phi[i - 1];
   }
}
bool vis[M];
uint ans[M];
uint Sum(uint u) {
   if(u < N) return phi[u];
   uint x = n / u;
   if(vis[x]) return ans[x];
   vis[x] = 1;
   uint &res = ans[x]; res = u * (u + 1) / 2;
   for(uint i = 2, j; i <= u; i = j + 1) {
      j = u / (u / i);
      res -= (j - i + 1) * Sum(u / i);
   }
   return res;
}
uint S[K][K];
void init(uint n) {
   S[0][0] = 1;
   for(uint i = 1; i <= n; i ++)
      for(uint j = 1; j <= i; j ++)
         S[i][j] = S[i - 1][j - 1] + S[i - 1][j] * j;
}
uint calc(uint n) { //\sum i^k
   uint ans = 0;
   for(uint i = 1; i <= k && i <= n; i ++) {
      uint res = 1;
      for(uint x = n + 1; x > n - i; x --) {
         res *= ( x % (i + 1) ) ? x : x / (i + 1);
      }
      ans += res * S[k][i];
   }
   return ans;
}
uint solve(uint x) {
   int z = x <= ss ? idx1[x] : idx2[n / x];
   return h[z] + a[z];
}
int main() {
   cin >> n >> k;
   for(ss = 1; ss * ss <= n; ss ++) ;
   sieve(N - 1); init(k);
   for(uint l = 1, r; l <= n; l = r + 1) {
      r = n / (n / l);
      pos[++ m] = n / l; a[m] = n / l - 1;
      g[m] = calc(n / l) - 1;
      if(n / l <= ss) idx1[n / l] = m;
      else idx2[r] = m;
   }
   for(uint i = 1; i <= c; i ++) {
      for(uint j = 1; j <= m && (ull) p[i] * p[i] <= pos[j]; j ++) {
         uint x = pos[j] / p[i];
         uint z = x <= ss ? idx1[x] : idx2[n / x];
         a[j] -= a[z] - i + 1;
         g[j] -= pk[i] * (g[z] - spk[i - 1]);
         h[j] += g[z] - spk[i - 1];
      }
   }
   uint ans = 0, la = 0, cur = 0;
   for(uint l = 2, r; l <= n; l = r + 1, la = cur) {
      r = n / (n / l); cur = solve(r);
      ans += (2 * Sum(n / l) - 1) * (cur - la);
   }
   cout << ans << '\n';
   return 0;
}