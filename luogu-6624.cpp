#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int D = 152501 + 10, N = 32, M = N * N;
const int mod = 998244353;
inline int add(int x, int y) { return x + y >= mod ? x + y - mod : x + y; }
inline int dec(int x, int y) { return x - y < 0 ? x - y + mod : x - y; }
int n, m, d, f[D], u[M], v[M], w[M];
int qpow(int a, int b) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = (ll) a * a % mod)
      if(b & 1) ans = (ll) ans * a % mod;
   return ans;
}
struct F {
   int a, b; //a + bx
   void clr() { a = b = 0; }
   F operator + (F rhs) { return (F) {add(a, rhs.a), add(b, rhs.b)}; }
   F operator - (F rhs) { return (F) {dec(a, rhs.a), dec(b, rhs.b)}; }
   F operator * (F rhs) { return (F) {(int)(1ll * a * rhs.a % mod), (int)((1ll * a * rhs.b + 1ll * b * rhs.a) % mod)}; }
   void operator += (F rhs) { *this = *this + rhs; }
   void operator -= (F rhs) { *this = *this - rhs; }
   void operator *= (F rhs) { *this = *this * rhs; }
   F inv() {
      F ans = (F) {a, b ? mod - b : 0};
      if(a != 1) {
         int v = qpow(a, mod - 2);
         v = (ll) v * v % mod;
         ans.a = (ll) ans.a * v % mod;
         ans.b = (ll) ans.b * v % mod;
      }
      return ans;
   }
   int low() { return a == 0 ? 0 : }
} mat[N][N];
struct _ufs {
   int f[N];
   void init(int n) { rep(i, 1, n) f[i] = i; }
   int find(int u) { return u == f[u] ? u : f[u] = find(f[u]); }
   void unite(int u, int v) { f[find(u)] = find(v); }
} ufs;
bool check(int d) {
   ufs.init(n);
   rep(i, 1, m) if(w[i] % d == 0) ufs.unite(u[i], v[i]);
   rep(i, 1, n) if(ufs.find(1) != ufs.find(i)) return false;
   return true;
}
int solve(int d) {
   rep(i, 1, n) rep(j, 1, n) mat[i][j].clr();
   rep(i, 1, m) if(w[i] % d == 0) {
      mat[u[i]][u[i]] += (F) {1, w[i]};
      mat[v[i]][v[i]] += (F) {1, w[i]};
      mat[u[i]][v[i]] -= (F) {1, w[i]};
      mat[v[i]][u[i]] -= (F) {1, w[i]};
   }
   F ans = (F) {1, 0};
   rep(i, 2, n) {
      int k = i;
      rep(j, i, n) if(mat[j][i].low() < mat[k][i].low()) { k = j; break; }
      if(!k) return 0;
      if(k != i) {
         // puts("swap");
         ans = (F) {0, 0};
         rep(j, i, n) swap(mat[i][j], mat[k][j]);  
      }
      F t = mat[i][i].inv(); ans *= mat[i][i];
      rep(j, i + 1, n) {
         F v = mat[j][i] * t;
         rep(k, i, n) mat[j][k] -= v * mat[i][k];
      }
   }
   return ans.b;
}
int main() {
   scanf("%d%d", &n, &m);
   rep(i, 1, m) { scanf("%d%d%d", u + i, v + i, w + i); d = max(d, w[i]); }
   rep(i, 1, d) f[i] = check(i) ? solve(i) : 0;
   per(i, d, 1) for(int j = i + i; j <= d; j += i) f[i] = dec(f[i], f[j]);
   int ans = 0;
   rep(i, 1, d) ans = (ans + (ll) f[i] * i) % mod;
   printf("%d\n", ans);
   return 0;
}