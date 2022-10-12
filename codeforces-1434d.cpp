#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;

#define fs first
#define sc second
#define pb push_back
#define mp make_pair
#define eb emplace_back

typedef double db;
typedef long long ll;
typedef long double ldb;
typedef unsigned uint;
typedef unsigned long long ull;

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

unsigned seed = chrono::system_clock::now().time_since_epoch().count();
mt19937 Rand(seed);
// mt19937_64 
uniform_int_distribution<ll> range(0, 1ll << 32);
inline void ucin() {
   ios::sync_with_stdio(0); cin.tie(0);
}
// uniform_real_distribution<double> dbran;
template<class T> inline void chkmax(T &x, const T &y) { if(x < y) x = y; }
template<class T> inline void chkmin(T &x, const T &y) { if(x > y) x = y; }

const int N = 5e5 + 10;
const int INF = 2e9 + 10;

struct Edge { int v, w; };
int n, m, u1[N], u2[N];
vector<Edge> G[N];
int dfs(int u, int fa = 0) {
   int f = 0, g = 0; u1[u] = u2[u] = u;
   for(auto &x : G[u]) if(x.v ^ fa) {
      int h = dfs(x.v, u) + 1;
      if(h > f) { g = f; u2[u] = u1[u]; f = h; u1[u] = u1[x.v]; }
      else if(h > g) { g = h; u2[u] = u1[x.v]; }
   }
   return f;
}
struct QAQ {
   int rt, idx, dfn[N], pos[N], dr[N], w[N], d[N];
   void dfs(int u, int fa = 0) {
      dfn[u] = ++ idx; pos[idx] = u;
      for(auto &x : G[u]) if(x.v ^ fa) {
         w[x.v] = x.w ^ w[u];
         d[x.v] = 1 + d[u];
         dfs(x.v, u);
      }
      dr[u] = idx;
   }
   int Max[N << 2][2];
   bool flip[N];
   void build(int u, int l, int r) {
      if(l == r) {
         int x = pos[l];
         Max[u][ w[x] ] = d[x];
         Max[u][ w[x] ^ 1 ] = 0;
         return ;
      }
      int mid = (l + r) >> 1;
      build(u << 1, l, mid);
      build(u << 1 | 1, mid + 1, r);
      rep(i, 0, 1) Max[u][i] = max(Max[u << 1][i], Max[u << 1 | 1][i]);
   }
   int query(int u, int l, int r, int ql, int qr) {

   }
   void build() {
      dfs(rt);
   }
} qaq[2];
int main() {
   scanf("%d", &n);
   int u, v, w;
   rep(i, 1, n - 1) {
      scanf("%d%d%d", &u, &v, &w);
      G[u].pb({v, w});
      G[v].pb({u, w});
   }
   dfs(1);
   // printf("%d %d!\n", u1[1], u2[1]);
   scanf("%d", &m);
   rep(i, 1, m) {
      int id; scanf("%d", &id);

   }
   dfs(1);
   return 0;
}
