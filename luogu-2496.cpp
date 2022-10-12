#include <bits/stdc++.h>
#define debug(...) fprintf(stderr, __VA_ARGS__);
#define gmax max_element
#define rep(i, j, k) for(int i = j, t##i = k; i <= t##i; ++ i)
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
const int B = 350;
int n, m, bel[N], st[N], ql[B + 5], qm[B + 5], qr[B + 5];
ll a[N], add[B + 5], all[B + 5];
ll cross(int u, int v, int w) {
  ll x1 = v - u, x2 = w - u;
  ll y1 = a[v] - a[u], y2 = a[w] - a[u];
  return x1 * y2 - x2 * y1;
}
void build(int id) {
  int l = (id - 1) * B + 1, r = min(n, id * B);
  int ql = l, qr = l - 1;
  rep(i, l, r) {
    while(qr - ql >= 1 && cross(st[qr - 1], st[qr], i) >= 0) qr --;
    st[++ qr] = i;
  }
  ::ql[id] = ::qm[id] = ql; ::qr[id] = qr;
  rep(i, ql + 1, qr) if(a[st[i]] > a[st[::qm[id]]]) ::qm[id] = i;
}
ll calc(int u) {
  int p = u - (bel[u] - 1) * B;
  return a[u] + all[bel[u]] + add[bel[u]] * p;
}
void mktag(int id) {
  if(!all[id] && !add[id]) return ;
  int l = (id - 1) * B + 1, r = min(n, id * B);
  rep(i, l, r) a[i] = calc(i);
  all[id] = add[id] = 0;
}
ll query(int l, int r) {
  if(bel[l] == bel[r]) {
    mktag(bel[l]); return *gmax(a + l, a + r + 1);
  }
  mktag(bel[l]); mktag(bel[r]);
  ll ans = max(*gmax(a + l, a + bel[l] * B + 1), *gmax(a + (bel[r] - 1) * B + 1, a + r + 1));
  rep(i, bel[l] + 1, bel[r] - 1) ans = max(ans, calc(st[qm[i]]));
  return ans;
}
void modify(int l, int r, int t) {
  if(bel[l] == bel[r]) {
    mktag(bel[l]);
    rep(i, l, r) a[i] += t * (i - l + 1);
    build(bel[l]);
    return ;
  }
  mktag(bel[l]); mktag(bel[r]);
  rep(i, l, bel[l] * B) a[i] += (i - l + 1) * t;
  rep(i, (bel[r] - 1) * B + 1, r) a[i] += (i - l + 1) * t;
  build(bel[l]); build(bel[r]);
  rep(i, bel[l] + 1, bel[r] - 1) {
    all[i] += ((i - 1) * B + 1 - l) * t;
    add[i] += t;
    while(qm[i] < qr[i] && calc(st[qm[i]]) < calc(st[qm[i] + 1])) {
      qm[i] ++;
    }
  }
}
int main() {
  scanf("%d%d", &n, &m);
  rep(i, 1, n) scanf("%lld", a + i), bel[i] = (i - 1) / B + 1;
  rep(i, 1, bel[n]) build(i);
  int op, l, r, t;
  rep(i, 1, m) {
    scanf("%d%d%d", &op, &l, &r);
    if(op == 1) {
      printf("%lld\n", max(0ll, query(l, r) - a[1] - add[1] - all[1]));
    }
    if(op == 2) {
      mktag(bel[l]);
      if(bel[l] != bel[r]) mktag(bel[r]);
      swap(a[l], a[r]); build(bel[l]);
      if(bel[l] != bel[r]) build(bel[r]);
    }
    if(op == 3) {
      scanf("%d", &t); modify(l, r, t);
    }
  }
  return 0;
}