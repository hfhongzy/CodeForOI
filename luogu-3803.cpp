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

const int N = 4e6 + 10, mod = 998244353, g = 3;

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

int n, rev[N], W[N];
void init(int len) {
   for(n = 1; n < len; n <<= 1) ;
   rep(i, 1, n - 1) rev[i] = (rev[i >> 1] >> 1) | (i & 1 ? n >> 1 : 0);
   for(int i = 1; i < n; i <<= 1) {
      W[i] = 1;
      int w = qpow(g, (mod - 1) / (i << 1));
      for(int j = 1; j < i; j ++)
         W[i + j] = (ll)W[i + j - 1] * w % mod;
   }
}
void NTT(poly &a, int op) {
   for(int i = 1; i < n; i ++) if(i < rev[i]) swap(a[i], a[rev[i]]);
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
   int t = a.size() + b.size() - 1;
   init(t); a.resize(n); b.resize(n);
   NTT(a, 1); NTT(b, 1);
   rep(i, 0, n - 1) a[i] = (ll)a[i] * b[i] % mod;
   NTT(a, -1); a.resize(t);
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
int main() {
   int n = read(), m = read();
   poly a, b; read(n, a); read(m, b); print(a * b);
   return 0;
}