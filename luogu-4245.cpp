#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;

typedef double db;
typedef long long ll;

const db pi = 2 * acos(-1);
const int N = 262144 + 5;

struct comp {
   db x, y;
   comp() {}
   comp(db a, db b) : x(a), y(b) {}
   comp operator + (const comp &b) const { return comp(x + b.x, y + b.y); }
   comp operator - (const comp &b) const { return comp(x - b.x, y - b.y); }
   comp operator * (const comp &b) const { return comp(x * b.x - y * b.y, b.x * y + x * b.y); }
   comp conj() { return comp(x, -y); }
} W[N];

int rev[N], len, n, m, mod, a[N], b[N], res[N];
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
   for(int i = 0; i < len; i ++) x[i] %= mod, y[i] %= mod;
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

int main() {
   scanf("%d%d%d", &n, &m, &mod);
   for(int i = 0; i <= n; i ++) scanf("%d", a + i);
   for(int i = 0; i <= m; i ++) scanf("%d", b + i);
   init(n + m); conv(a, b, res);
   for(int i = 0; i <= n + m; i ++) {
      printf("%d%c", res[i], " \n"[i == n + m]);
   }
   return 0;
}