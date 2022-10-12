#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 2e5 + 10;
struct node {
  int l, r, w;
} a[N];
int n, m, h, bit[N], arr[N], ans[N];
vector<int> op;
void clr() {
  for(int u : op)
    for(; u <= h; u += u & (-u))
      bit[u] = 0;
}
void add(int u, int v) {
  op.pb(u);
  for(; u <= h; u += u & (-u))
    bit[u] += v;
}
int qry(int u) {
  int z = 0;
  for(; u; u &= u - 1) z += bit[u];
  return z;
}
void solve(int l, int r, int ql, int qr) {
  if(l > r || ql > qr) return ;
  if(l == r)  {
    rep(i, ql, qr)
      if(a[i].w - (a[i].l <= arr[l] && arr[l] <= a[i].r) == 0)
        ans[l] ++;
    return ;
  }
  int mid = (l + r) >> 1;
  op.clear();
  rep(i, l, mid) add(arr[i], 1);
  static node t1[N], t2[N];
  int p1 = 0, p2 = 0;
  rep(i, ql, qr) {
    int z = qry(a[i].r) - qry(a[i].l - 1);
    if(z >= a[i].w) {
      t1[p1 ++] = a[i];
    } else {
      t2[p2] = a[i];
      t2[p2 ++].w -= z;
    }
  }
  clr();
  for(int i = 0; i < p1; i ++) a[ql + i] = t1[i];
  for(int i = 0; i < p2; i ++) a[ql + p1 + i] = t2[i];
  solve(l, mid, ql, ql + p1 - 1);
  solve(mid + 1, r, ql + p1, qr);
}
int main() {
  scanf("%d%d", &n, &m);
  rep(i, 1, n) {
    scanf("%d%d%d", &a[i].l, &a[i].r, &a[i].w);
    h = max(h, a[i].r);
  }
  rep(i, 1, m) scanf("%d", arr + i);
  solve(1, m, 1, n);
  rep(i, 1, m) printf("%d\n", ans[i]);
  return 0;
}