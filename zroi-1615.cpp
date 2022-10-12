#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int mod = 998244853;
const int N = 2.5e5 + 50;
const int P = 4e6 + 10;
struct modint {
   int x;
   void operator = (int y) { x = y; }
   modint operator + (const modint &b) {
      return (modint) { x + b.x >= mod ? x + b.x - mod : x + b.x };
   }
   modint operator - (const modint &b) {
      return (modint) { x - b.x < 0 ? x - b.x + mod : x - b.x };
   }
   modint operator * (const modint &b) {
      return (modint) { (int)(1ll * x * b.x % mod) };
   }
   bool operator == (const modint &b) {
      return x == b.x;
   }
} pd[N << 2], inv[P], pre[N], w[N];
int test, n, q, idx, dfn[N], pos[N], dr[N];
int p[P], pc, a[N];
bool tag[P];
vector<int> G[N];
void sieve(int n) {
   pc = 0; fill(tag + 1, tag + n + 1, 0);
   for(int i = 2; i <= n; i ++) {
      if(!tag[i]) {
         p[++ pc] = i;
      }
      for(int j = 1; j <= pc && i * p[j] <= n; j ++) {
         tag[i * p[j]] = 1;
         if(i % p[j] == 0) break ;
      }
   }
}
void build(int u, int l, int r) {
   if(l == r) {
      pd[u] = w[pos[l]];
      return ;
   }
   int mid = (l + r) >> 1;
   build(u << 1, l, mid);
   build(u << 1 | 1, mid + 1, r);
   pd[u] = 1; 
}
void modify(int u, int l, int r, int ql, int qr, modint x) {
   if(l == ql && r == qr) {
      pd[u] = pd[u] * x; return ;
   }
   int mid = (l + r) >> 1;
   if(qr <= mid) modify(u << 1, l, mid, ql, qr, x);
   else if(ql > mid) modify(u << 1 | 1, mid + 1, r, ql, qr, x);
   else {
      modify(u << 1, l, mid, ql, mid, x);
      modify(u << 1 | 1, mid + 1, r, mid + 1, qr, x);
   }
}
int d[N], f[N][20];
void dfs(int u, int fa = 0) {
   dfn[u] = ++ idx; pos[idx] = u; f[u][0] = fa; d[u] = d[fa] + 1;
   rep(i, 1, 19) f[u][i] = f[f[u][i - 1]][i - 1];
   w[u] = p[a[u]];
   if(fa) w[u] = w[u] * w[fa];
   for(int v : G[u]) {
      if(v == fa) continue ;
      dfs(v, u);
   }
   dr[u] = idx;
}
int lca(int u, int v) {
   if(d[u] < d[v]) swap(u, v);
   int c = d[u] - d[v];
   for(int i = 19; ~ i; i --) if(c >> i & 1) {
      u = f[u][i];
   }
   if(u == v) return u;
   for(int i = 19; ~ i; i --) if(f[u][i] ^ f[v][i]) {
      u = f[u][i]; v = f[v][i];
   }
   return f[u][0];
}
modint query(int u, int l, int r, int p) {
   if(p == 0) return (modint) {1};
   if(l == r) return pd[u];
   int mid = (l + r) >> 1;
   if(p <= mid) return pd[u] * query(u << 1, l, mid, p);
   return pd[u] * query(u << 1 | 1, mid + 1, r, p);
}
int main() {
   sieve(4e6); //cout << pc << endl;
   inv[1] = 1;
   rep(i, 2, 4e6) {
     inv[i] = (modint) {mod - mod / i} * inv[mod % i];
   }
   scanf("%d", &test);
   while(test --) {
      scanf("%d%d", &n, &q);
      random_shuffle(p + 1, p + n + 1);
      pre[0] = 1;
      rep(i, 1, n) {
         pre[i] = pre[i - 1] * (modint) {p[i]};
      }
      rep(i, 1, n) scanf("%d", a + i);
      rep(i, 1, n) G[i].clear();
      int u, v;
      rep(i, 1, n - 1) {
         scanf("%d%d", &u, &v);
         G[u].push_back(v);
         G[v].push_back(u);
      }
      idx = 0; dfs(1); build(1, 1, n);
      int op, x, y;
      rep(i, 1, q) {
         scanf("%d%d%d", &op, &x, &y);
         if(op == 1) {
            bool tag = 0;
            int ff = lca(x, y), len = 1 + d[x] + d[y] - (d[ff] << 1);
            if(query(1, 1, n, dfn[x]) * query(1, 1, n, dfn[y]) == pre[len] * query(1, 1, n, dfn[ff]) * query(1, 1, n, dfn[f[ff][0]])) {
               tag = 1;
            }
            puts(tag ? "Yes" : "No");
         } else {
            modify(1, 1, n, dfn[x], dr[x], (modint) {p[y]} * inv[ p[a[x]] ]);
            a[x] = y;
         }
      }
   }
   return 0;
}