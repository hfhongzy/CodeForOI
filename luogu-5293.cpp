#include <bits/stdc++.h>
#define pb push_back
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;

typedef long double db;
typedef long long ll;

const db pi = acos(-1);
const int N = 262144 + 5;

int mod;
namespace MTT {

struct comp {
   db x, y;
   comp() {}
   comp(db a, db b) : x(a), y(b) {}
   comp operator + (const comp &b) const { return comp(x + b.x, y + b.y); }
   comp operator - (const comp &b) const { return comp(x - b.x, y - b.y); }
   comp operator * (const comp &b) const { return comp(x * b.x - y * b.y, b.x * y + x * b.y); }
   comp conj() { return comp(x, -y); }
} W[N];
int rev[N];
int getn(int len) { int n = 1; while(n < len) n <<= 1; return n; }
void prework(int n) {
   for(int i = 1; i < n; i <<= 1) {
      W[i] = comp(1, 0);
      comp w(cos(pi / i), sin(pi / i));
      for(int j = 1; j < i; j ++)
         W[i + j] = W[i + j - 1] * w;
   }
}
void fft(comp *a, int n, int ty) {
   for(int i = 1; i < n; i ++)
      if(i < (rev[i] = rev[i >> 1] >> 1 | (i & 1 ? n >> 1 : 0)))
         swap(a[i], a[rev[i]]);
   for(int i = 1; i < n; i <<= 1) {
      for(int j = 0; j < n; j += i << 1) {
         for(int k = 0; k < i; k ++) {
            comp t = a[j + k + i] * W[i + k];
            a[j + k + i] = a[j + k] - t; a[j + k] = a[j + k] + t;
         }
      }
   }
   if(ty == 1) return ;
   reverse(a + 1, a + n);
   for(int i = 0; i < n; i ++)
      a[i].x /= n, a[i].y /= n;
}
void conv(int *x, int *y, int *z, int n) {
   // rep(i, 0, n - 1) debug("x%d = %d\n", i, x[i]);
   // rep(i, 0, n - 1) debug("y%d = %d\n", i, y[i]);
   for(int i = 0; i < n; i ++) x[i] %= mod, y[i] %= mod;
   static comp a[N], b[N], f1, f0, g1, g0, dfta[N], dftb[N], dftc[N], dftd[N];
   for(int i = 0; i < n; i ++) a[i] = comp(x[i] & 32767, x[i] >> 15);
   for(int i = 0; i < n; i ++) b[i] = comp(y[i] & 32767, y[i] >> 15);
   fft(a, n, 1); fft(b, n, 1);
   for(int i = 0; i < n; i ++) {
      int j = (n - i) & (n - 1);
      f1 = (a[i] + a[j].conj()) * comp(0.5, 0);
      f0 = (a[i] - a[j].conj()) * comp(0, -0.5);
      g1 = (b[i] + b[j].conj()) * comp(0.5, 0);
      g0 = (b[i] - b[j].conj()) * comp(0, -0.5);
      dfta[i] = f0 * g0; dftb[i] = f0 * g1;
      dftc[i] = g0 * f1; dftd[i] = f1 * g1;
   }
   for(int i = 0; i < n; i ++) {
      a[i] = dfta[i] + dftb[i] * comp(0, 1);
      b[i] = dftc[i] + dftd[i] * comp(0, 1);
   }
   fft(a, n, -1); fft(b, n, -1);
   for(int i = 0; i < n; i ++) {
      ll xa = (ll) (a[i].x + 0.5) % mod;
      ll xb = (ll) (a[i].y + 0.5) % mod;
      ll xc = (ll) (b[i].x + 0.5) % mod;
      ll xd = (ll) (b[i].y + 0.5) % mod;
      z[i] = ((xa << 30) + ((xb + xc) << 15) + xd) % mod;
   }
   // rep(i, 0, n - 1) debug("z%d = %d\n", i, z[i]);
}

}
int qpow(int a, int b, int mod = ::mod) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = (ll) a * a % mod)
      if(b & 1) ans = (ll) ans * a % mod;
   return ans;
}
struct ModRoot {
   int g;
   operator int() const { return g; }
   int get(int p) {
      vector<int> vec; vec.clear(); int x = p - 1;
      for(int i = 2; i * i <= x; i ++) {
         if(x % i == 0) {
            vec.pb(i);
            while(x % i == 0) x /= i;
         }
      }
      if(x > 1) vec.pb(x);
      for(int i = 2; i < p; i ++) {
         bool mark = 1;
         for(int v : vec) {
            if(qpow(i, (p - 1) / v, p) == 1) {
               mark = 0; break ;
            }
         }
         if(mark) return g = i;
      }
      return g = 0;
   }
} g;
int n, k, l, x, y, w1, w[N];
struct mat {
   int a[4][4];
   mat operator * (mat b) {
      mat c;
      rep(i, 1, n) rep(j, 1, n) {
         ll z = 0;
         rep(k, 1, n) z += (ll)a[i][k] * b.a[k][j];
         c.a[i][j] = z % mod;
      }
      return c;
   }
   void I() { rep(i, 1, n) rep(j, 1, n) a[i][j] = i == j; }
} v;
mat Pow(mat a, int b) {
   mat ans; ans.I();
   for(; b >= 1; b >>= 1, a = a * a)
      if(b & 1) ans = ans * a;
   return ans;
}
int omega(ll i) { return w[(i % k + k) % k]; }
void dft(int *a, int n) {
   static int x[N], y[N], z[N];
   rep(i, 0, n - 1) x[i] = (ll)a[i] * omega(- i * (i - 1ll) / 2) % mod;
   rep(i, 0, 2 * (n - 1)) y[i] = omega(i * (i - 1ll) / 2);
   reverse(y, y + 2 * (n - 1) + 1);
   MTT::prework(4 * n);
   MTT::conv(x, y, z, MTT::getn(4 * n));
   rep(i, 0, n - 1) a[i] = (ll)z[2 * (n - 1) - i] * omega(- i * (i - 1ll) / 2) % mod;
}
int main() {
   static int a[N];
   scanf("%d%d%d%d%d%d", &n, &k, &l, &x, &y, &mod);
   rep(i, 1, n) rep(j, 1, n) scanf("%d", &v.a[i][j]);
   g.get(mod); //cerr << "g = " << g << endl;
   w[0] = 1; w1 = qpow(g, (mod - 1) / k);
   rep(i, 1, k) w[i] = (ll)w[i - 1] * w1 % mod;
   int inv = qpow(k, mod - 2);
   rep(i, 0, k - 1) {
      mat t = v;
      rep(x, 1, n) rep(y, 1, n) t.a[x][y] = (ll)t.a[x][y] * w[k - i] % mod;
      rep(x, 1, n) t.a[x][x] ++;
      a[i] = (ll)Pow(t, l).a[x][y] * inv % mod;
      // debug("a[%d] = %d\n", i, a[i]);
   }
   dft(a, k);
   rep(i, 0, k - 1) printf("%d\n", a[i]);
   return 0;
}