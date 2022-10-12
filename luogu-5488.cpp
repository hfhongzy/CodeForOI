#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;

typedef long long ll;
typedef vector<int> poly;

const int N = 4e5 + 10, mod = 1004535809, g = 3;
int read() {
   int x = 0; char c = getchar();
   for(; c < '0' || c > '9'; c = getchar()) ;
   for(; c >= '0' && c <= '9'; c = getchar())
      x = (x * 10ll + (c & 15)) % mod;
   return x;
}
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

int rev[N], W[N], inv[N];
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
   int t = a.size() + b.size() - 1, n = getn(t);
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
int main() {
   int n = read(), k = read(), t = read(); prework(n * 2);
   poly a, b; read(n - 1, a); b.resize(n);
   if(t == 0) {
      b[0] = 1;
      for(int i = 0; i < n - 1; i ++) {
         b[i + 1] = (ll)b[i] * (i + k) % mod * inv[i + 1] % mod;
      }
   } else {
      b[0] = 1;
      for(int i = 0; i < n - 1; i ++) {
         b[i + 1] = (ll)b[i] * (k + mod - i) % mod * inv[i + 1] % mod;
      }
      for(int i = 1; i < n; i += 2) b[i] = b[i] ? mod - b[i] : 0;
   }
   a = a * b; a.resize(n); print(a);
   return 0;
}