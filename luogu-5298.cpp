#include <algorithm>
#include <cstdio>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 3e5 + 10, T = N * 21, mod = 998244353;
int qpow(int a, int b) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = 1ll * a * a % mod)
      if(b & 1) ans = 1ll * ans * a % mod;
   return ans;
}
int n, f[N], ch[N][2], p[N], a[N], cnt, rt[N];
int id, ls[T], rs[T], sum[T], mul[T];
int app() {
   id ++; ls[id] = rs[id] = sum[id] = 0; mul[id] = 1;
   return id;
}
void ins(int &u, int l, int r, int x) {
   u = app(); sum[u] = 1;
   if(l == r) return ;
   int mid = (l + r) >> 1;
   if(x <= mid) ins(ls[u], l, mid, x);
   else ins(rs[u], mid + 1, r, x);
}
void upd(int u) {
   sum[u] = (sum[ls[u]] + sum[rs[u]]) % mod;
}
void addtag(int u, int v) {
   if(v == 1 || u == 0) return ;
   sum[u] = 1ll * sum[u] * v % mod;
   mul[u] = 1ll * mul[u] * v % mod;
}
void pdown(int u) {
   if(mul[u] != 1) {
      addtag(ls[u], mul[u]);
      addtag(rs[u], mul[u]);
      mul[u] = 1;
   }
}
namespace hzy {

int merge(int x, int y, int lmul, int rmul, int p) {
   if(!x && !y) return 0;
   if(!y) { addtag(x, lmul); return x; }
   if(!x) { addtag(y, rmul); return y; }
   pdown(x); pdown(y);
   int xl = sum[ls[x]], xr = sum[rs[x]], yl = sum[ls[y]], yr = sum[rs[y]];
   ls[x] = merge(ls[x], ls[y], (lmul + (mod + 1ll - p) * yr) % mod, (rmul + (mod + 1ll - p) * xr) % mod, p);
   rs[x] = merge(rs[x], rs[y], (lmul + 1ll * p * yl) % mod, (rmul + 1ll * p * xl) % mod, p);
   return upd(x), x;
}

}
void dfs(int u) {
   int &l = ch[u][0], &r = ch[u][1];
   if(!l) {
      ins(rt[u], 1, cnt, lower_bound(a + 1, a + cnt + 1, p[u]) - a);
      return ;
   }
   if(!r) { dfs(l); rt[u] = rt[l]; return ; }
   dfs(l); dfs(r); rt[u] = hzy::merge(rt[l], rt[r], 0, 0, p[u]);
}
int P[N];
void print(int u, int l, int r) {
   if(!u) return ;
   if(l == r) { P[l] = sum[u]; return ; }
   int mid = (l + r) >> 1; pdown(u);
   print(ls[u], l, mid); print(rs[u], mid + 1, r);
}
int main() {
   scanf("%d%*d", &n);
   rep(i, 2, n) {
      scanf("%d", f + i);
      ch[f[i]][ ch[f[i]][0] >= 1 ] = i;
   }
   rep(i, 1, n) scanf("%d", p + i);

   const int inv = qpow(10000, mod - 2);
   rep(i, 1, n) if(!ch[i][0]) a[++ cnt] = p[i];
   else p[i] = 1ll * p[i] * inv % mod;
   sort(a + 1, a + cnt + 1);
   dfs(1); print(rt[1], 1, cnt);
   int ans = 0;
   rep(i, 1, cnt) {
      (ans += 1ll * i * a[i] % mod * P[i] % mod * P[i] % mod) %= mod;
   }
   printf("%d\n", ans);
   return 0;
}