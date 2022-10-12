#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;

typedef long long ll;
typedef vector<int> poly;

const int N = 1 << 22 | 5, M = 1 << 15, mod = 998244353;

int add(int x, int y) { return (x += y) >= mod ? x - mod : x; }
void ADD(int &x, int y) { (x += y) >= mod ? x -= mod : 0; }
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
      int w = qpow(3, (mod - 1) / (i << 1));
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
poly fix(poly a, int n) { a.resize(n); return a; }
poly operator * (poly a, poly b) {
   int t = a.size() + b.size() - 1, n = getn(t); prework(n);
   NTT(a, n, 1); NTT(b, n, 1);
   rep(i, 0, n - 1) a[i] = (ll)a[i] * b[i] % mod;
   NTT(a, n, -1);
   return a;
}
int n, c, m;
poly a, b;
struct fpw {
   int pw[M * 2], pw2[M * 2];
   void init(int c) {
      pw[0] = 1;
      for(int i = 1; i < M; i ++)
         pw[i] = (ll)pw[i - 1] * c % mod;
      pw2[0] = 1; pw2[1] = (ll)c * pw[M - 1] % mod;
      for(int i = 2; i < M; i ++)
         pw2[i] = (ll)pw2[i - 1] * pw2[1] % mod;
   }
   int q(int x) { return (ll)pw2[x >> 15] * pw[x & 32767] % mod; }
} pc, pi;
int C(int n) { return n * (n - 1ll) / 2 % (mod - 1); }
int main() {
   scanf("%d%d%d", &n, &c, &m);
   a.resize(n + m); b.resize(n + m); pc.init(c); pi.init(qpow(c, mod - 2));
   rep(i, 0, n - 1) scanf("%d", &a[i]), a[i] = (ll)a[i] * pi.q(C(i)) % mod;
   rep(i, 0, n + m - 1) b[i] = pc.q(C(n + m - 1 - i));
   a = a * b;
   rep(i, 0, m - 1) {
      printf("%d%c", int((ll)pi.q(C(i)) * a[n + m - 1 - i] % mod), " \n"[i == m - 1]);
   }
   return 0;
}