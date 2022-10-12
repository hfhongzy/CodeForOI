#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
const int mod = 998244353;
int qpow(int a, int b) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = (ll) a * a % mod)
      if(b & 1) ans = (ll) ans * a % mod;
   return ans;
}
struct node {
   int k, b;
   void e() { k = 1; b = 0; }
   bool empty() { return k == 1 && b == 0; }
   node operator + (node rhs) {
      return {(ll)k * rhs.k % mod, ((ll)b * rhs.k + rhs.b) % mod};
   }
   void operator += (node rhs) { *this = *this + rhs; }
} bit[N], btw[N], seg[N];
int n, m, op[N], l[N], r[N], L[N], R[N], p[N];

void zip(int l, int r) {
   static int tmp[N];
   const int mid = (l + r) >> 1;
   int x = l, y = mid + 1;
   rep(i, l, r) {
      if(x <= mid && (y > r || ::l[ p[x] ] < ::l[ p[y] ])) {
         tmp[i] = p[x ++];
      } else {
         tmp[i] = p[y ++];
      }
   }
   copy(tmp + l, tmp + r + 1, p + l);
}
void modify(int u, int l, int r, int p, node x) {
   if(l == r) { seg[u] = x; return ; }
   int mid = (l + r) >> 1;
   if(p <= mid) modify(u << 1, l, mid, p, x);
   else modify(u << 1 | 1, mid + 1, r, p, x);
   seg[u] = seg[u << 1] + seg[u << 1 | 1];
}
node query(int u, int l, int r, int ql, int qr) {
   if(l == ql && r == qr) return seg[u];
   int mid = (l + r) >> 1;
   if(qr <= mid) return query(u << 1, l, mid, ql, qr);
   if(ql > mid) return query(u << 1 | 1, mid + 1, r, ql, qr);
   return query(u << 1, l, mid, ql, mid) + query(u << 1 | 1, mid + 1, r, mid + 1, qr);
}
void solve(int l, int r) {
   if(l == r) { p[l] = l; return ; }
   int mid = (l + r) >> 1;
   solve(l, mid); solve(mid + 1, r);
   int x = l;
   rep(i, mid + 1, r) if(op[p[i]] == 2) {
      for(; x <= mid && op[p[x]] == 1 && ::l[p[x]] <= ::l[p[i]]; x ++) {
         int t = 2 * qpow(::r[p[x]] - ::l[p[x]] + 1, mod - 2) % mod;
         insert(n - ::r[p[x]] + 1, {(1 + 2 * (mod - t)) % mod, t});
      }
      btw[p[i]] = query(n - ::r[p[i]] + 1);
   }
   zip(l, r);
}
struct SMT {
   node a[N], tag[N];
   void init(int n) {
      rep(i, 1, 4 * n) {
         a[i].e(); tag[i].e();
      }
   }
   void addtag(int u, node x) { a[u] += x; tag[u] += x; }
   void pdown(int u) {
      if(!tag[u].empty()) {
         addtag(u << 1, tag[u]);
         addtag(u << 1 | 1, tag[u]);
         tag[u].e();
      }
   }
   void modify(int u, int l, int r, int ql, int qr, node x) {
      if(l == ql && r == qr) { addtag(u, x); return ; }
      int mid = (l + r) >> 1; pdown(u);
      if(qr <= mid) modify(u << 1, l, mid, ql, qr, x);
      else if(ql > mid) modify(u << 1 | 1, mid + 1, r, ql, qr, x);
      else {
         modify(u << 1, l, mid, ql, mid, x);
         modify(u << 1 | 1, mid + 1, r, mid + 1, qr, x);
      }
      a[u] = a[u << 1] + a[u << 1 | 1];
   }
   node query(int u, int l, int r, int p) {
      if(l == r) return a[u];
      int mid = (l + r) >> 1; pdown(u);
      return p <= mid ? query(u << 1, l, mid, p) : query(u << 1 | 1, mid + 1, r, p);
   }
} smt;
int main() {
   scanf("%d%d", &n, &m);
   smt.init(n);
   rep(i, 1, m) {
      scanf("%d%d%d", op + i, l + i, r + i);
      if(op[i] == 1) {
         smt.modify(1, 1, n, l[i], r[i]);
      }
   }
   rep(i, 1, m) {
      if(op[i] == 1) {
         L[i] = l[i]; R[i] = r[i];
      } else {
      }
   }
   solve(1, m);
   
   return 0;
}
// x <= l, r <= y < n + 1 (w = 2)
// x <= l, l <= y < r
// l < x <= r, y >= r
//op = 1 : L, R 表示贡献的区间，op = 2：L，[R1, R2] 表示询问的区间 