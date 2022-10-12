#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;
int n, m, a[N];
#define ls u << 1, l, mid
#define rs u << 1 | 1, mid + 1, r
int fir[N * 4], sec[N * 4], cnt[N * 4], tag[N * 4];
ll sum[N * 4];
void upd(int u) {
  sum[u] = sum[u << 1] + sum[u << 1 | 1];
  int lmx = fir[u << 1], rmx = fir[u << 1 | 1];
  if(lmx == rmx) {
    fir[u] = lmx;
    cnt[u] = cnt[u << 1] + cnt[u << 1 | 1];
    sec[u] = max(sec[u << 1], sec[u << 1 | 1]);
  } else {
    if(lmx < rmx) {
      fir[u] = rmx;
      cnt[u] = cnt[u << 1 | 1];
      sec[u] = max(sec[u << 1 | 1], lmx);
    } else {
      fir[u] = lmx;
      cnt[u] = cnt[u << 1];
      sec[u] = max(sec[u << 1], rmx);
    }
  }
}
void addtag(int u, int t) {
  if(t >= fir[u]) return ;
  sum[u] -= (ll)cnt[u] * (fir[u] - t);
  fir[u] = tag[u] = t;
}
void down(int u) {
  if(!~tag[u]) return ;
  addtag(u << 1, tag[u]);
  addtag(u << 1 | 1, tag[u]);
  tag[u] = -1;
}
void build(int u, int l, int r) {
  tag[u] = -1;
  if(l == r) { sum[u] = fir[u] = a[l]; sec[u] = -1; cnt[u] = 1; return ; }
  int mid = (l + r) >> 1;
  build(ls); build(rs); upd(u);
}
ll qsum(int u, int l, int r, int ql, int qr) {
  if(l == ql && r == qr) return sum[u];
  int mid = (l + r) >> 1; down(u);
  if(qr <= mid) return qsum(ls, ql, qr);
  if(ql > mid) return qsum(rs, ql, qr);
  return qsum(ls, ql, mid) + qsum(rs, mid + 1, qr);
}
int qmax(int u, int l, int r, int ql, int qr) {
  if(l == ql && r == qr) return fir[u];
  int mid = (l + r) >> 1; down(u);
  if(qr <= mid) return qmax(ls, ql, qr);
  if(ql > mid) return qmax(rs, ql, qr);
  return max(qmax(ls, ql, mid), qmax(rs, mid + 1, qr));
}
void mkmin(int u, int l, int r, int ql, int qr, int val) {
  if(r < ql || l > qr) return ;
  if(val >= fir[u]) return ;
  int mid = (l + r) >> 1; down(u);
  if(ql <= l && r <= qr && val > sec[u]) {
    sum[u] -= (ll)cnt[u] * (fir[u] - val);
    fir[u] = tag[u] = val;
    return ;
  }
  mkmin(ls, ql, qr, val);
  mkmin(rs, ql, qr, val);
  upd(u);
}
#undef ls
#undef rs
int main() {
  int test;
  scanf("%d", &test);
  while(test --) {
    scanf("%d%d", &n, &m);
    rep(i, 1, n) scanf("%d", a + i);
    build(1, 1, n);
    int op, l, r, t;
    rep(i, 1, m) {
      scanf("%d%d%d", &op, &l, &r);
      if(op == 0) {
        scanf("%d", &t); mkmin(1, 1, n, l, r, t);
      }
      if(op == 1) {
        printf("%d\n", qmax(1, 1, n, l, r));
      }
      if(op == 2) {
        printf("%lld\n", qsum(1, 1, n, l, r));
      }
    }
  }
  return 0;
}