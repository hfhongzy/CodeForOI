#include <bits/stdc++.h>
#define pb push_back
#define lw lower_bound
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 4e5 + 10;
const ll INF = 1ll << 61;

int n, m, k, L[N], R[N], h[N], ty[N];
ll s[N], mx[N][2], add[N], cov[N];
void pu(int u) { rep(d, 0, 1) mx[u][d] = max(mx[u << 1][d], mx[u << 1 | 1][d]); s[u] = s[u << 1] + s[u << 1 | 1]; }
void build(int u, int l, int r) {
   L[u] = l; R[u] = r;
   if(l == r) { s[u] = h[l]; mx[u][0] = h[l] - (ll)k * l; mx[u][1] = h[l] + (ll)k * l; return ; }
   int mid = (l + r) >> 1; build(u << 1, l, mid); build(u << 1 | 1, mid + 1, r); pu(u);
}
#define l L[u]
#define r R[u]
void addtag(int u, ll t) { add[u] += t; mx[u][0] += t; mx[u][1] += t; s[u] += (r - l + 1) * t; }
void covtag(int u, ll t, int y) {
   add[u] = 0; cov[u] = t; ty[u] = y; s[u] = (t + t + (r - l) * (ll)(y > 0 ? k : -k)) * (r - l + 1) / 2;
   if(y > 0) mx[u][0] = t - (ll)l * k, mx[u][1] = t + (2ll * r - l) * k;
   else mx[u][0] = t - (ll)l * k, mx[u][1] = t + (ll)l * k;
}
void pd(int u) {
   if(ty[u]) { covtag(u << 1, cov[u], ty[u]); covtag(u << 1 | 1, cov[u] + (ty[u] > 0 ? k : -k) * ((l + r) / 2 + 1ll - l), ty[u]); ty[u] = 0; }
   if(add[u]) { addtag(u << 1, add[u]); addtag(u << 1 | 1, add[u]); add[u] = 0; }
}
void modify(int u, int ql, int qr, ll t, int y = 0) { //y = 0 : add
   if(l == ql && r == qr) { y ? covtag(u, t, y) : addtag(u, t); return ; }
   int mid = (l + r) >> 1; pd(u);
   if(qr <= mid) modify(u << 1, ql, qr, t, y);
   else if(ql > mid) modify(u << 1 | 1, ql, qr, t, y);
   else {
      modify(u << 1, ql, mid, t, y);
      modify(u << 1 | 1, mid + 1, qr, y ? t + (y > 0 ? k : -k) * (mid + 1ll - ql): t, y);
   }
   pu(u);
}
ll query(int u, int ql, int qr) {
   if(l == ql && r == qr) return s[u];
   int mid = (l + r) >> 1; pd(u);
   if(qr <= mid) return query(u << 1, ql, qr);
   if(ql > mid) return query(u << 1 | 1, ql, qr);
   return query(u << 1, ql, mid) + query(u << 1 | 1, mid + 1, qr);
}
struct node { bool mark; int v; };
node dfs0(int u, int ql, int qr, ll low) {
   if(l > qr || r < ql) return node{0, 0};
   if(l == r) return mx[u][0] > low ? node{1, l} : node{0, 0};
   pd(u); node res = mx[u << 1 | 1][0] > low ? dfs0(u << 1 | 1, ql, qr, low) : node{0, 0};
   if(res.mark) return res;
   return dfs0(u << 1, ql, qr, low);
}
node dfs1(int u, int ql, int qr, ll low) {
   if(l > qr || r < ql) return node{0, 0};
   if(l == r) return mx[u][1] > low ? node{1, l} : node{0, 0};
   pd(u); node res = mx[u << 1][1] > low ? dfs1(u << 1, ql, qr, low) : node{0, 0};
   if(res.mark) return res;
   return dfs1(u << 1 | 1, ql, qr, low);
}
#undef l
#undef r
set<int> S;
int main() {
   scanf("%d%d%d", &n, &m, &k);
   rep(i, 1, n) scanf("%d", h + i);
   build(1, 1, n); S.insert(1); S.insert(n + 1);
   rep(i, 2, n) if(abs(h[i] - h[i - 1]) > k) S.insert(i);
   int op, l, r, c;
   rep(i, 1, m) {
      scanf("%d%d%d", &op, &l, &r);
      if(op == 1) { printf("%lld\n", query(1, l, r)); }
      if(op == 2) { scanf("%d", &c); modify(1, l, r, c); S.insert(l); S.insert(r + 1); }
      if(op == 3) {
         vector<int> st;
         st.pb(l);
         for(auto it = S.lw(l + 1); (c = *it) <= r; it = S.lw(c + 1)) st.pb(c);
         st.pb(r + 1);
         for(int i = 1; i < (int)st.size() - 1; i ++) {
            int l1 = st[i], r1 = st[i + 1] - 1;
            ll h = query(1, l1 - 1, l1 - 1);
            int x = dfs0(1, l1, r1, h - k * (l1 - 1ll)).v;
            if(x) modify(1, l1, x, h + k, 1);
         }
         for(int i = (int)st.size() - 3; i >= 0; i --) {
            int l1 = st[i], r1 = st[i + 1] - 1;
            ll h = query(1, r1 + 1, r1 + 1);
            int x = dfs1(1, l1, r1, h + k * (r1 + 1ll)).v;
            if(x) modify(1, x, r1, h + (r1 + 1ll - x) * k, -1);
         }
         S.erase(S.lw(l), S.lw(r + 1));
         S.insert(l); S.insert(r + 1);
      }
   }
   return 0;
}