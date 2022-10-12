#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 2e5 + 10, mod = 1e9 + 7;
const int inv2 = (mod + 1) >> 1, inv6 = 166666668;
int n, m, a[N], sum1[N], sum2[N];
//s2[k] = Ak^2 + Bk + C
inline int add(const int &x, const int &y) {
   return x + y >= mod ? x + y - mod : x + y;
}
inline void upd(int &x, const int &y) {
   (x += y) >= mod ? x -= mod : 0;
}
namespace segC {

int sum[N << 2], tag[N << 2];
void mktag(int u, int l, int r, int x) {
   upd(sum[u], (r - l + 1ll) * x % mod);
   upd(tag[u], x);
}
void pdown(int u, int l, int r) {
   if(tag[u]) {
      int mid = (l + r) >> 1;
      mktag(u << 1, l, mid, tag[u]);
      mktag(u << 1 | 1, mid + 1, r, tag[u]);
      tag[u] = 0;
   }
}
void pup(int u) {
   sum[u] = add(sum[u << 1], sum[u << 1 | 1]);
}
void build(int u, int l, int r) {
   if(l == r) { sum[u] = a[l]; return ; }
   int mid = (l + r) >> 1;
   build(u << 1, l, mid);
   build(u << 1 | 1, mid + 1, r);
   pup(u);
}

}

namespace segB {

int sum[N << 2], tag[N << 2];
void mktag(int u, int l, int r, int x) {
   upd(sum[u], 1ll * (sum1[r] - sum1[l - 1] + mod) * x % mod);
   upd(tag[u], x);
}
void pdown(int u, int l, int r) {
   if(tag[u]) {
      int mid = (l + r) >> 1;
      mktag(u << 1, l, mid, tag[u]);
      mktag(u << 1 | 1, mid + 1, r, tag[u]);
      tag[u] = 0;
   }
}
void pup(int u) {
   sum[u] = add(sum[u << 1], sum[u << 1 | 1]);
}

}

namespace segA {

int sum[N << 2], tag[N << 2];
void mktag(int u, int l, int r, int x) {
   upd(sum[u], 1ll * (sum2[r] - sum2[l - 1] + mod) * x % mod);
   upd(tag[u], x);
}
void pdown(int u, int l, int r) {
   if(tag[u]) {
      int mid = (l + r) >> 1;
      mktag(u << 1, l, mid, tag[u]);
      mktag(u << 1 | 1, mid + 1, r, tag[u]);
      tag[u] = 0;
   }
}
void pup(int u) {
   sum[u] = add(sum[u << 1], sum[u << 1 | 1]);
}

}
int va, vb, vc;
void modify(int u, int l, int r, int ql, int qr) {
   if(l == ql && r == qr) {
      if(va) segA::mktag(u, l, r, va);
      segB::mktag(u, l, r, vb);
      segC::mktag(u, l, r, vc);
      return ;
   }
   int mid = (l + r) >> 1;
   segA::pdown(u, l, r); segB::pdown(u, l, r); segC::pdown(u, l, r);
   if(qr <= mid) modify(u << 1, l, mid, ql, qr);
   else if(ql > mid) modify(u << 1 | 1, mid + 1, r, ql, qr);
   else {
      modify(u << 1, l, mid, ql, mid);
      modify(u << 1 | 1, mid + 1, r, mid + 1, qr);
   }
   segA::pup(u); segB::pup(u); segC::pup(u);
}
int query(int u, int l, int r, int ql, int qr) {
   if(l == ql && r == qr) return add(segA::sum[u], add(segC::sum[u], segB::sum[u]));
   int mid = (l + r) >> 1;
   segA::pdown(u, l, r); segB::pdown(u, l, r); segC::pdown(u, l, r);
   if(qr <= mid) return query(u << 1, l, mid, ql, qr);
   if(ql > mid) return query(u << 1 | 1, mid + 1, r, ql, qr);
   return add(query(u << 1, l, mid, ql, mid), query(u << 1 | 1, mid + 1, r, mid + 1, qr));
}
int query(int l, int r) {
   if(r == 0) return 0; if(l == 0) l ++;
   return query(1, 1, n, l, r);
}
int main() {
   scanf("%d%d", &n, &m);
   for(int i = 1; i <= n; i ++) scanf("%d", a + i);
   for(int i = 1; i <= n; i ++) sum1[i] = add(sum1[i - 1], i), sum2[i] = add(sum2[i - 1], 1ll * i * i % mod);
   for(int i = 1; i <= n; i ++) upd(a[i], a[i - 1]);
   for(int i = 1; i <= n; i ++) upd(a[i], a[i - 1]);
   segC::build(1, 1, n);
   for(int i = 1; i <= m; i ++) {
      int op, l, r, v;
      scanf("%d%d%d", &op, &l, &r);
      if(l > r) swap(l, r);
      if(op == 1) {
         scanf("%d", &v); int v0 = v; v = 1ll * v * inv2 % mod;
         va = v; vb = v * (3 - 2ll * l + mod) % mod; vc = v * (mod + 1ll - l) % mod * (mod + 2ll - l) % mod;
         modify(1, 1, n, l, r);
         if(r != n) {
            va = 0;
            vc = v0 * (sum1[r - l + 1l] - r * (r - l + 1ll) % mod + mod) % mod;
            vb = v0 * (r - l + 1ll) % mod;
            modify(1, 1, n, r + 1, n);
         }
      }
      if(op == 2) {
         int ans = (r - l + 1ll) * query(n, n) % mod;
         upd(ans, mod - query(l - 1, r - 1));
         upd(ans, mod - query(n - r, n - l));
         printf("%d\n", ans % mod);
      }
   }
   return 0;
}