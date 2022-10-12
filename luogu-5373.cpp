#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;

typedef long long ll;
typedef vector<int> poly;

const int N = 65536 + 10, mod = 998244353, g = 3;
int add(int x, int y) { return (x += y) >= mod ? x - mod : x; }
int dec(int x, int y) { return x - y < 0 ? x - y + mod : x - y; }
void ADD(int &x, int y) { (x += y) >= mod ? x -= mod : 0; }
void DEC(int &x, int y) { (x -= y) < 0 ? x += mod : 0; }
int qpow(int a, int b) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = (ll)a * a % mod)
      if(b & 1) ans = (ll)ans * a % mod;
   return ans;
}

int rev[N], W[N];
int getn(int len) { int n = 1; while(n < len) n <<= 1; return n; } //[0, len - 1]
void prework(int n) {
   for(int i = 1; i < n; i <<= 1) {
      W[i] = 1;
      int w = qpow(g, (mod - 1) / (i << 1));
      for(int j = 1; j < i; j ++)
         W[i + j] = (ll)W[i + j - 1] * w % mod;
   }
}
void NTT(poly &a, int n, int op) {
   a.resize(n);
   for(int i = 1; i < n; i ++)
      if(i < (rev[i] = (rev[i >> 1] >> 1) | (i & 1 ? n >> 1 : 0)))
         swap(a[i], a[rev[i]]);
   for(int i = 1; i < n; i <<= 1) {
      for(int j = 0; j < n; j += i << 1) {
         for(int k = 0; k < i; k ++) {
            int q = 1ll * W[i + k] * a[j + k + i] % mod;
            a[j + k + i] = add(a[j + k], mod - q); ADD(a[j + k], q);
         }
      }
   }
   if(op == 1) return ;
   reverse(a.begin() + 1, a.end());
   int inv = mod - (mod - 1) / n;
   rep(i, 0, n - 1) a[i] = (ll)a[i] * inv % mod;
}
poly operator + (poly a, poly b) {
   if(a.size() < b.size()) a.resize(b.size());
   for(int i = 0; i < (int)b.size(); i ++) ADD(a[i], b[i]);
   return a;
}
poly operator * (poly a, poly b) {
   int t = a.size() + b.size() - 1, n = getn(t);
   NTT(a, n, 1); NTT(b, n, 1);
   rep(i, 0, n - 1) a[i] = (ll)a[i] * b[i] % mod;
   NTT(a, n, -1); a.resize(t);
   return a;
}
poly operator * (poly a, int b) {
   for(int &v : a) v = (ll)v * b % mod;
   return a;
}
poly fix(poly a, int n) { a.resize(n); return a; }
void read(int n, poly &a) {
   a.resize(n + 1);
   for(int i = 0; i <= n; i ++) scanf("%d", &a[i]);
}
void print(poly a) {
   for(int v : a) printf("%d ", v);
   putchar('\n');
}
poly Nest(poly a, poly b) { //a.size() >= b.size()
   int sz = a.size(), m = sqrt(sz) + 1, n = getn(sz);
   vector<poly> p(m + 1), q(m);
   NTT(b, n << 1, 1);
   p[0] = q[0] = {1}; p[0].resize(n); p[1].resize(n);
   for(int i = 1; i <= m; i ++) {
      NTT(p[i] = p[i - 1], n << 1, 1);
      for(int j = 0; j < (n << 1); j ++) p[i][j] = (ll)p[i][j] * b[j] % mod;
      NTT(p[i], n << 1, -1); p[i].resize(n);
   }
   q[1] = p[m];
   NTT(b = q[1], n << 1, 1);
   for(int i = 2; i < m; i ++) {
      NTT(q[i] = q[i - 1], n << 1, 1);
      for(int j = 0; j < (n << 1); j ++) q[i][j] = (ll)q[i][j] * b[j] % mod;
      NTT(q[i], n << 1, -1); q[i].resize(n);
   }
   poly ans = {0};
   for(int i = 0; i < m; i ++) {
      b = poly(n, 0);
      for(int j = 0; j < m; j ++) {
         if(i * m + j >= sz) break ;
         for(int k = 0; k < n; k ++) {
            b[k] = (b[k] + (ll)p[j][k] * a[i * m + j]) % mod;
         }
      }
      ans = ans + fix(q[i] * b, sz);
   }
   return ans;
}
int main() {
   int n, m; scanf("%d%d", &n, &m); prework(n * 2);
   poly a, b; read(n, a); read(m, b); print(Nest(a, b));
   return 0;
}