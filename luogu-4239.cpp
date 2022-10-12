#include <algorithm>
#include <cstdio>
#include <vector>
#include <cmath>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
typedef double db;
const db pi = 2 * acos(-1);
const int N = 4e5 + 10, mod = 1e9 + 7;
int n, m, len, rev[N], k;
inline int add(int x, int y) {
   return x + y >= mod ? x + y - mod : x + y;
}
inline int dec(int x, int y) {
   return x - y < 0 ? x - y + mod : x - y;
}
int qpow(int a, int b) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = 1ll * a * a % mod)
      if(b & 1) ans = 1ll * ans * a % mod;
   return ans;
}

struct comp {
   db x, y;
   comp() {}
   comp(db a, db b) : x(a), y(b) {}
   comp operator + (const comp &b) const { return comp(x + b.x, y + b.y); }
   comp operator - (const comp &b) const { return comp(x - b.x, y - b.y); }
   comp operator * (const comp &b) const { return comp(x * b.x - y * b.y, b.x * y + x * b.y); }
   comp conj() { return comp(x, -y); }
} W[N];
void init(int n) {
   int k = 0;
   for(len = 1; len <= n; len <<= 1) k ++;
   for(int i = 1; i < len; i ++)
      rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
   for(int i = 0; i < len; i ++)
      W[i] = comp(cos(pi * i / len), sin(pi * i / len));
}
void fft(comp *a, int ty) {
   for(int i = 1; i < len; i ++)
      if(i < rev[i]) swap(a[i], a[rev[i]]);
   static comp t1, t2;
   for(int i = 1; i < len; i <<= 1) {
      for(int j = 0; j < len; j += i << 1) {
         for(int k = j; k < j + i; k ++) {
            t1 = a[k], t2 = W[len / (i << 1) * (k - j)] * a[k + i];
            a[k] = t1 + t2; a[k + i] = t1 - t2;
         }
      }
   }
   if(ty == -1) {
      reverse(a + 1, a + len);
      for(int i = 0; i < len; i ++)
         a[i].x /= len, a[i].y /= len;
   }
}
void conv(int *x, int *y, int *z) {
   static comp a[N], b[N], f1, f0, g1, g0, dfta[N], dftb[N], dftc[N], dftd[N];
   for(int i = 0; i < len; i ++) a[i] = comp(x[i] & 32767, x[i] >> 15);
   for(int i = 0; i < len; i ++) b[i] = comp(y[i] & 32767, y[i] >> 15);
   fft(a, 1); fft(b, 1);
   for(int i = 0; i < len; i ++) {
      int j = (len - i) & (len - 1);
      f1 = (a[i] + a[j].conj()) * comp(0.5, 0);
      f0 = (a[i] - a[j].conj()) * comp(0, -0.5);
      g1 = (b[i] + b[j].conj()) * comp(0.5, 0);
      g0 = (b[i] - b[j].conj()) * comp(0, -0.5);
      dfta[i] = f0 * g0; dftb[i] = f0 * g1;
      dftc[i] = g0 * f1; dftd[i] = f1 * g1;
   }
   for(int i = 0; i < len; i ++) {
      a[i] = dfta[i] + dftb[i] * comp(0, 1);
      b[i] = dftc[i] + dftd[i] * comp(0, 1);
   }
   fft(a, -1); fft(b, -1);
   for(int i = 0; i < len; i ++) {
      ll xa = (ll) (a[i].x + 0.5) % mod;
      ll xb = (ll) (a[i].y + 0.5) % mod;
      ll xc = (ll) (b[i].x + 0.5) % mod;
      ll xd = (ll) (b[i].y + 0.5) % mod;
      z[i] = ((xa << 30) + ((xb + xc) << 15) + xd) % mod;
   }
}
#define poly vector<int>
void print(const poly &a) {
   for(int i = 0; i < (int) a.size(); i ++) {
      printf("%d ", a[i]);
   }
   putchar('\n');
}
poly operator + (poly a, poly b) {
   poly ans(max(a.size(), b.size()));
   for(int i = 0; i < (int) ans.size(); i ++) {
      ans[i] = add(i < a.size() ? a[i] : 0, i < b.size() ? b[i] : 0);
   }
   return ans;
}
poly operator - (poly a, poly b) {
   poly ans(max(a.size(), b.size()));
   for(int i = 0; i < (int) ans.size(); i ++) {
      ans[i] = dec(i < a.size() ? a[i] : 0, i < b.size() ? b[i] : 0);
   }
   return ans;
}
poly operator * (int k, poly a) {
   if(k == 1) return a;
   for(int i = 0; i < (int) a.size(); i ++)
      a[i] = 1ll * k * a[i] % mod;
   return a;
}
poly operator * (poly a, poly b) {
   static int dfta[N], dftb[N], res[N];
   int deg = (int) a.size() + b.size() - 2; init(deg);
   for(int i = 0; i < len; i ++) dfta[i] = i < a.size() ? a[i] : 0;
   for(int i = 0; i < len; i ++) dftb[i] = i < b.size() ? b[i] : 0; 
   conv(dfta, dftb, res);
   poly ans(deg + 1);
   for(int i = 0; i <= deg; i ++) ans[i] = res[i];
   return ans;
}
poly Inv(poly a, int n = -1) { //mod x^n
   if(n == -1) n = a.size();
   if(n == 1) return poly(1, qpow(a[0], mod - 2));
   a.resize(n);
   poly f0 = Inv(a, (n + 1) >> 1);
   poly ans = 2 * f0 - f0 * f0 * a; ans.resize(n);
   return ans;
} 
int main() {
   scanf("%d", &n); n --;
   poly A; A.resize(n + 1);
   for(int i = 0; i <= n; i ++) scanf("%d", &A[i]);
   print(Inv(A));
   return 0;
}