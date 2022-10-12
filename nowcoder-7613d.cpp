#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;

typedef double db;
typedef long long ll;

const int N = 2e5 + 10;
const int INF = 2e9 + 10;
ll pw(ll x) {
   return x * x;
}
struct node {
   int x, y, r;
} a[N];
struct event {
   int id, x;
   bool operator < (const event &b) const {
      return x < b.x || (x == b.x && id < b.id);
   }
} b[N * 2];
struct arc {
   int id, ty;
};
int cur;
set<arc> S;

db lev(int id, int ty) {
   return a[id].y + ty * sqrt(pw(a[id].r) - pw(a[id].x - cur));
}
bool operator < (arc A, arc B) {
   db t1 = lev(A.id, A.ty), t2 = lev(B.id, B.ty);
   return fabs(t1 - t2) > 1e-8 ? t1 < t2 : 0;
}
int n, q, logn, m, d[N], f[N][20];
int lca(int u, int v) {
   if(d[u] < d[v]) swap(u, v);
   int c = d[u] - d[v];
   per(i, logn - 1, 0) if(c >> i & 1) u = f[u][i];
   if(u == v) return v;
   per(i, logn - 1, 0) if(f[u][i] ^ f[v][i])
      u = f[u][i], v = f[v][i];
   return f[v][0];
}
int main() {
   scanf("%d", &n);
   for(logn = 1; (1 << logn) <= n + 1; logn ++) ;
   rep(i, 1, n) {
      scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].r);
      b[++ m] = {i, a[i].x - a[i].r};
      b[++ m] = {-i, a[i].x + a[i].r};
   }
   rep(i, 1, n) f[i][0] = n + 1;
   sort(b + 1, b + 2 * m + 1);
   rep(i, 1, 2 * m) {
      cur = b[i].x;
      int u = b[i].id;
      if(u > 0) {
         auto it = S.lower_bound({u, 0});
         if(it != S.end()) {
            if(it->ty == -1) {
               f[u][0] = f[it->id][0];
            } else {
               f[u][0] = it->id;
            }
         }
         d[u] = d[f[u][0]] + 1;
         S.insert({u, 1});
         S.insert({u, -1});
      } else {
         u = -u;
         S.erase({u, -1});
         S.erase({u, 1});
      }
   }
   rep(i, 1, logn - 1) rep(u, 1, n) f[u][i] = f[f[u][i - 1]][i - 1];
   scanf("%d", &q);
   int u, v;
   rep(i, 1, q) {
      scanf("%d%d", &u, &v);
      int x = lca(u, v);
      printf("%d\n", d[u] + d[v] - 2 * d[x] - 1 - (x != u && x != v));
   }
   return 0;
}