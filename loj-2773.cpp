#include <bits/stdc++.h>
#define fs first
#define sc second
#define mp make_pair
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;
int n, m, l1, r1, l2, r2, a[N], b[N], pos[N], y[N];
ll ans, sa[N], sb[N];
bool rev;
void upd(ll v, int l1, int r1, int l2, int r2) {
   if(v > ans) {
      ans = v;
      if(rev) swap(l1, l2), swap(r1, r2);
      ::l1 = l1; ::r1 = r1; ::l2 = l2; ::r2 = r2;
   }
}
pair<ll, int> w[N << 2];
ll tag[N << 2];
void addtag(int u, ll v) { tag[u] += v; w[u].fs += v; }
void pushup(int u) { w[u] = max(w[u << 1], w[u << 1 | 1]); }
void pushdown(int u) {
   if(tag[u]) {
      addtag(u << 1, tag[u]);
      addtag(u << 1 | 1, tag[u]);
      tag[u] = 0;
   }
}
void build(int u, int l, int r) {
   tag[u] = 0;
   if(l == r) { w[u] = mp(sa[n] - sb[l - 1], l); return ; }
   int mid = (l + r) >> 1;
   build(u << 1, l, mid);
   build(u << 1 | 1, mid + 1, r);
   pushup(u);
}
void modify(int u, int l, int r, int ql, int qr, ll v) {
   if(l == ql && r == qr) { addtag(u, v); return ; }
   int mid = (l + r) >> 1; pushdown(u);
   if(qr <= mid) modify(u << 1, l, mid, ql, qr, v);
   else if(ql > mid) modify(u << 1 | 1, mid + 1, r, ql, qr, v);
   else {
      modify(u << 1, l, mid, ql, mid, v);
      modify(u << 1 | 1, mid + 1, r, mid + 1, qr, v);
   }
   pushup(u);
}
int st1[N], top1, st2[N], top2;
void solve() {
   rep(i, 1, n + m) pos[i] = 0;
   rep(i, 1, n) pos[a[i]] = i;
   rep(i, 1, m) y[i] = pos[b[i]];
   int p = 0;
   rep(i, 1, n) if(sa[i] >= (sa[n] + 1) / 2) { p = i; break ; }
   // cerr << p << endl;
   top1 = top2 = 0; build(1, 1, m);
   rep(i, 1, m) {
      if(y[i] > p) {
         while(top2 && y[st2[top2]] > y[i]) {
            modify(1, 1, m, st2[top2 - 1] + 1, st2[top2], sa[n] - sa[ y[st2[top2]] - 1 ]);
            top2 --;
         }
         modify(1, 1, m, st2[top2] + 1, i, sa[y[i] - 1] - sa[n]);
         st2[++ top2] = i;
      } else if(y[i]) {
         while(top1 && y[st1[top1]] < y[i]) {
            modify(1, 1, m, st1[top1 - 1] + 1, st1[top1], sa[ y[st1[top1]] ]);
            top1 --;
         }
         modify(1, 1, m, st1[top1] + 1, i, - sa[y[i]]);
         st1[++ top1] = i;
      }
      int l = w[1].sc;
      // if(l < )
      int tl = lower_bound(st1 + 1, st1 + top1 + 1, l) - st1;
      int tr = lower_bound(st2 + 1, st2 + top2 + 1, l) - st2;
      tl = (tl <= top1 ? y[st1[tl]] + 1 : 1);
      tr = (tr <= top2 ? y[st2[tr]] - 1 : n);
      upd(sb[i] + w[1].fs, tl, tr, l, i);
   }
}
int main() {
   scanf("%d%d", &n, &m);
   rep(i, 1, n) scanf("%d", a + i);
   rep(i, 1, n) scanf("%lld", sa + i), sa[i] += sa[i - 1];
   rep(i, 1, m) scanf("%d", b + i);
   rep(i, 1, m) scanf("%lld", sb + i), sb[i] += sb[i - 1];
   upd(sa[n], 1, n, 0, 0); upd(sb[m], 0, 0, 1, m);
   solve();
   swap(sa, sb); swap(a, b); swap(n, m); rev = 1;
   solve();
   printf("%lld\n%d %d\n%d %d\n", ans, l1, r1, l2, r2);
   return 0;
}