#include <bits/stdc++.h>
#define pb push_back
#define debug(...) fprintf(stderr, __VA_ARGS__);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef double db;
const int N = 1e5 + 10;
const db INF = 1e30;
int n, m, ord[N], t_ord[N], id[N], ans[N];
db x[N], y[N], b[N], a[N];
db calc(int u, int v) {
  assert(a[u] != a[v]);
  //-a[u] x + b[u] = -a[v] x + b[v]
  return (b[v] - b[u]) / (a[v] - a[u]);
}
bool below(int u, int v) {
  return y[u] <= - a[v] * x[u] + b[v];
}
void solve(int l, int r, int ql, int qr) {
  if(ql > qr) return ;
  if(l == r) {
    rep(i, ql, qr) ans[id[i]] = !below(id[i], l) ? l : -1;
    return ;
  }
  int mid = (l + r) >> 1;
  int t1 = l, t2 = mid + 1;
  copy(ord + l, ord + r + 1, t_ord + l);
  rep(i, l, r)
    if(t_ord[i] <= mid) ord[t1 ++] = t_ord[i];
    else ord[t2 ++] = t_ord[i];

  static int q[N];
  static db g[N];
  int top = 0;
  rep(i, l, mid) {
    if(i > l && a[ord[i]] == a[ord[i - 1]]) continue ;
    while(top >= 2 && calc(q[top - 1], ord[i]) <= g[top]) {
      top --;
    }
    q[++ top] = ord[i];
    g[top] = top == 1 ? -INF : calc(q[top - 1], q[top]);
  }
  // cerr << "\n#solving " << l << " to " << r << endl;
  g[top + 1] = INF;
  // cerr << " g is ";
  // rep(i, 1, top + 1) debug("%.1f, ", g[i]);
  // debug("\n");
  // cerr << "line is \n";
  // rep(i, 1, top) debug("y = %.1f x + %.1f\n", - a[q[i]], b[q[i]]);
  vector<int> vl, vr;
  int pos = 1;
  rep(i, ql, qr) {
    while(pos <= top && x[id[i]] > g[pos + 1]) pos ++;
    if(!below(id[i], q[pos])) {
      // printf("above %d %d\n", id[i], q[pos]);
      vl.pb(id[i]);
    } else {
      // printf("below %d %d (%.1f, %.1f) & y = %.1f x + %.1f\n", id[i], q[pos], x[id[i]], y[id[i]], -a[q[pos]], b[q[pos]]);
      vr.pb(id[i]);
    }
  }
  for(int i = 0; i < (int)vl.size(); i ++) id[ql + i] = vl[i];
  for(int i = 0; i < (int)vr.size(); i ++) id[ql + (int)vl.size() + i] = vr[i];
  solve(l, mid, ql, ql + (int)vl.size() - 1);
  solve(mid + 1, r, qr - (int)vr.size() + 1, qr);
}
int main() {
  scanf("%d%d", &n, &m);
  rep(i, 1, n) scanf("%lf%lf", x + i, y + i), x[i] = log(x[i]), y[i] = log(y[i]);
  rep(i, 1, m) scanf("%lf%lf", b + i, a + i), b[i] = log(b[i]); //y <= -ax + b
  rep(i, 1, m) ord[i] = i;
  rep(i, 1, n) id[i] = i;
  sort(ord + 1, ord + m + 1, [&](int x, int y) {
    return a[x] < a[y] || (a[x] == a[y] && b[x] < b[y]);
  });
  sort(id + 1, id + n + 1, [&](int u, int v) {
    return x[u] < x[v];
  });
  solve(1, m, 1, n);
  rep(i, 1, n) printf("%d\n", ans[i]);
  return 0;
}