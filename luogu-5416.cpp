#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 5e5 + 10; //5e5
const ll INF = 1ll << 60;
int n, m, dl[N], dr[N], idx, add[N];
vector<int> del[N], G[N];
ll c[N], x[N];
void dfs(int u) {
  dl[u] = ++ idx;
  for(int v : G[u]) dfs(v);
  dr[u] = idx;
}
#define ls u << 1, l, mid
#define rs u << 1 | 1, mid + 1, r
struct node { ll x, y; };
node operator - (node a, node b) {
  return node{a.x - b.x, a.y - b.y};
}
bool cross(node a, node b) { // <= 0
  return (long double)a.x * b.y <= (long double)b.x * a.y;
}
bool operator < (node a, node b) {
  return a.x < b.x || (a.x == b.x && a.y < b.y);
}
bool operator == (node a, node b) {
  return a.x == b.x && a.y == b.y;
}
vector<node> vec[N * 4];
int pos[N * 4];
void hang(int u, int l, int r, int ql, int qr, node cur) {
  if(l == ql && r == qr) { vec[u].pb(cur); return ; }
  int mid = (l + r) >> 1;
  if(qr <= mid) return hang(ls, ql, qr, cur);
  if(ql > mid) return hang(rs, ql, qr, cur);
  hang(ls, ql, mid, cur); hang(rs, mid + 1, qr, cur);
}
void build(vector<node> &v) {
  static node st[N];
  int t = 0;
  v.resize(unique(v.begin(), v.end()) - v.begin());
  for(auto x : v) {
    // if(t && x.x == st[t].x) continue ;
    while(t >= 2 && cross(st[t] - st[t - 1], x - st[t - 1])) t --;
    st[++ t] = x;
  }
  v.clear();
  rep(i, 1, t) v.pb(st[i]);
}
void build(int u, int l, int r) {
  if(l < r) {
    int mid = (l + r) >> 1;
    build(ls); build(rs);
  }
  build(vec[u]);
}
void init(int id) {
  vector<int> &v = del[id];
  int sz = int(v.size()), st = add[id];
  node cur = {x[id], c[id]};
  if(!sz) {
    hang(1, 1, n, dl[st], dr[st], cur);
    return ;
  }
  sort(v.begin(), v.end(), [&](int x, int y) {
    return dl[x] < dl[y];
  });
  hang(1, 1, n, dl[st], dl[v[0]] - 1, cur);
  for(int i = 0; i < sz - 1; i ++)
    if(dr[v[i]] + 1 <= dl[v[i + 1]] - 1)
      hang(1, 1, n, dr[v[i]] + 1, dl[v[i + 1]] - 1, cur);
  if(dr[v[sz - 1]] + 1 <= dr[st])
    hang(1, 1, n, dr[v[sz - 1]] + 1, dr[st], cur);
}
struct qry {
  int u, id; ll a;
  bool operator < (qry rhs) const {
    return a < rhs.a;
  }
} q[N];
ll calc(ll x, ll c, ll a) { return a * (a - 2 * x) + c; }
ll query(vector<node> &v, int &p, ll a) {
  int sz = int(v.size());
  if(p >= sz) return INF;
  while(p + 1 < sz && calc(v[p].x, v[p].y, a) >= calc(v[p + 1].x, v[p + 1].y, a)) {
    p ++;
  }
  return calc(v[p].x, v[p].y, a);
}
ll query(int u, int l, int r, int p, ll a) {
  ll z = query(vec[u], pos[u], a);
  if(l == r) return z;
  int mid = (l + r) >> 1;
  return min(z, p <= mid ? query(ls, p, a) : query(rs, p, a));
}
int main() {
  scanf("%d%d%lld", &n, &m, c); add[0] = 1; x[0] = 0;
  int op, f, id; ll xi, ci;
  rep(i, 2, n) {
    scanf("%d%d%d", &op, &f, &id); f ++;
    G[f].pb(i);
    if(op == 0) {
      scanf("%lld%*d%*d%lld", &xi, &ci);
      add[id] = i; c[id] = ci + xi * xi; x[id] = xi;
    }
    if(op == 1) {
      del[id].pb(i);
    }
  }
  dfs(1);
  static int p[N];
  rep(i, 0, n) p[i] = i;
  sort(p, p + n + 1, [&](int a, int b) {
    return node{x[a], c[a]} < node{x[b], c[b]};
  });
  rep(i, 0, n) {
    int u = p[i];
    if(add[u]) init(u);
  }
  build(1, 1, n);
  rep(i, 1, m) {
    scanf("%d%lld", &q[i].u, &q[i].a);
    q[i].u ++; q[i].id = i;
  }
  static ll res[N];
  sort(q + 1, q + m + 1);
  rep(i, 1, m) {
    res[q[i].id] = query(1, 1, n, dl[q[i].u], q[i].a);
  }
  rep(i, 1, m) printf("%lld\n", res[i]);
  return 0;
}
/*
4 1 2
0 0 1 8 2 3 7
0 1 2 10 1 6 2
1 1 1
1 4
*/