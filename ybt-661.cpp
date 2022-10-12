#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
const int M = N * 90;
const ll INF = 1ll << 60;
int n, k, a[N];
struct node {
  int l, r, v, u; // v \in [l, r]
  ll w;
  bool operator < (node b) const {
    return w < b.w;
  }
};
priority_queue<node> pq;
struct data {
  int pos; ll w;
  bool operator < (data b) const {
    return w < b.w;
  }
} mx[M];
int id, ls[M], rs[M], rt[N];
ll tag[M];
void build(int &u, int l, int r) {
  u = ++ id; mx[u] = data{l, 0};
  if(l == r) {
    return ;
  }
  int mid = (l + r) >> 1;
  build(ls[u], l, mid);
  build(rs[u], mid + 1, r);
}
void upd(int &u, int p, int l, int r, int ql, int qr, ll d) {
  u = ++ id; ls[u] = ls[p]; rs[u] = rs[p]; tag[u] = tag[p];
  if(l == ql && r == qr) {
    mx[u] = mx[p]; mx[u].w += d; tag[u] += d;
    return ;
  }
  int mid = (l + r) >> 1;
  if(qr <= mid) {
    upd(ls[u], ls[p], l, mid, ql, qr, d);
  } else if(ql > mid) {
    upd(rs[u], rs[p], mid + 1, r, ql, qr, d);
  } else {
    upd(ls[u], ls[p], l, mid, ql, mid, d);
    upd(rs[u], rs[p], mid + 1, r, mid + 1, qr, d);
  }
  mx[u] = max(mx[ls[u]], mx[rs[u]]);
  mx[u].w += tag[u];
}
data query(int u, int l, int r, int ql, int qr) {
  if(l == ql && r == qr) {
    return mx[u];
  }
  int mid = (l + r) >> 1;
  data ans;
  if(qr <= mid) {
    ans = query(ls[u], l, mid, ql, qr);
  } else if(ql > mid) {
    ans = query(rs[u], mid + 1, r, ql, qr);
  } else {
    ans = max(query(ls[u], l, mid, ql, mid), query(rs[u], mid + 1, r, mid + 1, qr));
  }
  ans.w += tag[u];
  return ans;
}
int main() {
  freopen("seq.in", "r", stdin);
  freopen("seq.out", "w", stdout);
  scanf("%d%d", &n, &k);
  rep(i, 1, n) scanf("%d", a + i);
  unordered_map<int, int> pos;
  build(rt[0], 1, n);
  rep(i, 1, n) {
    upd(rt[i], rt[i - 1], 1, n, pos[a[i]] + 1, i, a[i]);
    pos[a[i]] = i;
    data t = query(rt[i], 1, n, 1, i);
    // printf("(%d, %lld)\n", t.pos, t.w);
    pq.push({1, i, t.pos, i, t.w});
  }
  ll res = -1;
  while(k --) {
    node t = pq.top(); pq.pop();
    // printf("[%d, %d][%d, %d] = %lld!\n", t.l, t.r, t.v, t.u, t.w);
    if(!k) res = t.w;
    if(t.l < t.v) {
      data qaq = query(rt[t.u], 1, n, t.l, t.v - 1);
      // printf("extend [%d, %d][%d, %d] = %lld ..\n", t.l, t.v - 1, qaq.pos, t.u, qaq.w);
      pq.push({t.l, t.v - 1, qaq.pos, t.u, qaq.w});
    }
    if(t.v < t.r) {
      data qaq = query(rt[t.u], 1, n, t.v + 1, t.r);
      // printf("extend [%d, %d][%d, %d] = %lld ..\n", t.v + 1, t.r, qaq.pos, t.u, qaq.w);
      pq.push({t.v + 1, t.r, qaq.pos, t.u, qaq.w});
    }
  }
  printf("%lld\n", res);
  return 0;
}