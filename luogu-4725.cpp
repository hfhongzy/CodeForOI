#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;

int read() {
   int x = 0; char c = getchar();
   for(; c < '0' || c > '9'; c = getchar()) ;
   for(; c >= '0' && c <= '9'; c = getchar())
      x = x * 10 + (c & 15);
   return x;
}
typedef long long ll;
typedef vector<int> poly;

const int N = 4e5 + 10, mod = 998244353, g = 3;

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

int n, rev[N], W[N], inv[N];
int getn(int len) { int n = 1; while(n < len) n <<= 1; return n; } //[0, len - 1]
void prework(int n) {
   for(int i = 1; i < n; i <<= 1) {
      W[i] = 1;
      int w = qpow(g, (mod - 1) / (i << 1));
      for(int j = 1; j < i; j ++)
         W[i + j] = (ll)W[i + j - 1] * w % mod;
   }
   inv[1] = 1;
   for(int i = 2; i <= n; i ++) inv[i] = (mod - mod / i) * (ll)inv[mod % i] % mod;
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
poly operator * (poly a, poly b) {
   int t = a.size() + b.size() - 1; n = getn(t);
   NTT(a, n, 1); NTT(b, n, 1);
   rep(i, 0, n - 1) a[i] = (ll)a[i] * b[i] % mod;
   NTT(a, n, -1); a.resize(t);
   return a;
}
void read(int n, poly &a) {
   a.resize(n + 1);
   for(int i = 0; i <= n; i ++) a[i] = read();
}
void print(poly a) {
   for(int v : a) printf("%d ", v);
   putchar('\n');
}
poly fix(poly a, int n) { a.resize(n); return a; }
poly operator + (poly a, poly b) {
   if(a.size() < b.size()) a.resize(b.size());
   for(int i = 0; i < (int)b.size(); i ++) ADD(a[i], b[i]);
   return a;
}
poly operator - (poly a, poly b) {
   if(a.size() < b.size()) a.resize(b.size());
   for(int i = 0; i < (int)b.size(); i ++) DEC(a[i], b[i]);
   return a;
}
poly operator / (poly a, int b) {
   b = 2 ? (mod + 1) / 2 : qpow(b, mod - 2);
   for(int i = 0; i < (int)a.size(); i ++) a[i] = (ll)a[i] * b % mod;
   return a;
}
poly Inv(poly a) { //deg(A) = 2^k - 1
   int sz = a.size();
   poly c(1, qpow(a[0], mod - 2)), t;
   for(int i = 1; i < sz; i <<= 1) {
      NTT(t = fix(a, i << 1), i << 2, 1); NTT(c, i << 2, 1);
      for(int j = 0; j < (i << 2); j ++) c[j] = (2 * c[j] - (ll)t[j] * c[j] % mod * c[j] % mod + mod) % mod;
      NTT(c, i << 2, -1); c.resize(i << 1);
   }
   c.resize(sz);
   return c;
}
poly Sqrt(poly a) {
   int sz = a.size();
   poly c(1, 1);
   for(int i = 1; i < sz; i <<= 1) {
      c = (c * c + fix(a, i << 1)) * Inv(fix(c, i << 1)) / 2;
      c.resize(i << 1);
   }
   c.resize(sz);
   return c;
}
poly Der(poly a) {
   for(int i = 0; i < (int)a.size() - 1; i ++)
      a[i] = a[i + 1] * (i + 1ll) % mod;
   a.pop_back();
   return a;
}
poly Int(poly a) {
   a.push_back(0);
   for(int i = (int)a.size() - 1; i >= 1; i --) a[i] = (ll)a[i - 1] * inv[i] % mod;
   a[0] = 0;
   return a;
}
poly Ln(poly a) {
   return Int(fix(Der(a) * Inv(a), a.size() - 1));
}
int main() {
   int n = read(); prework(n * 2);
   poly a; read(n - 1, a); print(Ln(a));
   return 0;
}