#include <algorithm>
#include <cstdio>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int n, m;
ll tag[N << 2], s0[N << 2], s1[N << 2], s2[N << 2];
ll S1(ll n) { return n * (n + 1) / 2; }
ll S2(ll n) { return n * (n + 1) * (2 * n + 1) / 6; }
void addtag(int u, int l, int r, int v) {
   tag[u] += v;
   s0[u] += (r - l + 1ll) * v;
   s1[u] += (S1(r) - S1(l - 1)) * v;
   s2[u] += (S2(r) - S2(l - 1)) * v;
}
void pushd(int u, int l, int r) {
   if(tag[u]) {
      int mid = (l + r) >> 1;
      addtag(u << 1, l, mid, tag[u]);
      addtag(u << 1 | 1, mid + 1, r, tag[u]);
      tag[u] = 0;
   }
}
void pushu(int u) {
   s0[u] = s0[u << 1] + s0[u << 1 | 1];
   s1[u] = s1[u << 1] + s1[u << 1 | 1];
   s2[u] = s2[u << 1] + s2[u << 1 | 1];
}
void modify(int u, int l, int r, int ql, int qr, int v) {
   if(l == ql && r == qr) { addtag(u, l, r, v); return ; }
   int mid = (l + r) >> 1; pushd(u, l, r);
   if(qr <= mid) modify(u << 1, l, mid, ql, qr, v);
   else if(ql > mid) modify(u << 1 | 1, mid + 1, r, ql, qr, v);
   else {
      modify(u << 1, l, mid, ql, mid, v);
      modify(u << 1 | 1, mid + 1, r, mid + 1, qr, v);
   }
   pushu(u);
}
struct node {
   ll s0, s1, s2;
   node operator + (const node &b) {
      return (node) {s0 + b.s0, s1 + b.s1, s2 + b.s2};
   }
};
node query(int u, int l, int r, int ql, int qr) {
   if(l == ql && r == qr) return (node) {s0[u], s1[u], s2[u]};
   int mid = (l + r) >> 1; pushd(u, l, r);
   if(qr <= mid) return query(u << 1, l, mid, ql, qr);
   if(ql > mid) return query(u << 1 | 1, mid + 1, r, ql, qr);
   return query(u << 1, l, mid, ql, mid) + query(u << 1 | 1, mid + 1, r, mid + 1, qr);
}
void print(ll x, ll y) {
   ll tx = x, ty = y;
   while(ty) { swap(tx, ty); ty %= tx; }
   x /= tx; y /= tx;
   printf("%lld/%lld\n", x, y);
}
int main() {
   scanf("%d%d", &n, &m); char op[5];
   rep(i, 1, m) {
      int l, r, v;
      scanf("%s%d%d", op, &l, &r);
      if(*op == 'C') {
         scanf("%d", &v);
         if(l != r) modify(1, 1, n, l, r - 1, v);
      }
      if(*op == 'Q') {
         if(l == r) puts("0/1");
         else {
            r --;
            node nd = query(1, 1, n, l, r);
            ll ans = - (l - 1) * (r + 1ll) * nd.s0;
            ans += (r + l) * nd.s1;
            ans -= nd.s2;
            print(ans, (r - l + 2ll) * (r - l + 1ll) / 2);
         }
      }
   } 
   return 0;
}