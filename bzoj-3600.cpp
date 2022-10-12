#include <bits/stdc++.h>
#define pb push_back
#define LOG(FMT...) fprintf(stderr, FMT);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 5e5 + 10;
const ll INF = 1ll << 61;
const double lxak = 0.77;
int n, m, rt, id, uid[N], ch[N][2], fir[N], sec[N];
ll w[N];
int idcmp(int u, int v) {
  return w[u] < w[v] ? -1 : w[u] > w[v];
}
int cmp(int x, int y) {
  if(!fir[x] && !fir[y]) return 0;
  if(!fir[x]) return -1;
  if(!fir[y]) return 1;
  int r = idcmp(fir[x], fir[y]);
  return r ? r : idcmp(sec[x], sec[y]);
}
struct node {
  int u, pos;
  bool operator < (const node &b) const {
    int r = cmp(u, b.u);
    return r < 0 || (!r && pos > b.pos);
  }
};
int cur, sz[N], o, ofa, seq[N], s;
ll wl, wr;
void up(int u) {
  sz[u] = sz[ch[u][0]] + sz[ch[u][1]] + 1;
}
void dfs(int u) {
  if(u) {
    dfs(ch[u][0]); seq[++ s] = u; dfs(ch[u][1]);
  }
}
int build(int x, int y, ll l, ll r) {
  if(x > y) return 0;
  int mid = (x + y) >> 1, u = seq[mid];
  sz[u] = y - x + 1;
  w[u] = (l + r) >> 1;
  ch[u][0] = build(x, mid - 1, l, w[u]);
  ch[u][1] = build(mid + 1, y, w[u], r);
  return u;
}
int rebuild(int u, ll l, ll r) {
  s = 0; dfs(u);
  return build(1, s, l, r);
}
int insert(int &u, ll l, ll r, int fa = 0) {
  if(!u) { u = id; sz[u] = 1; w[u] = (l + r) >> 1; return u; }
  int dir = cmp(id, u), z;
  if(!dir) return u;
  if(dir < 0) z = insert(ch[u][0], l, w[u], u);
  else z = insert(ch[u][1], w[u], r, u);
  up(u);
  if(max(sz[ch[u][0]], sz[ch[u][1]]) > sz[u] * lxak) {
    wl = l; wr = r; o = u; ofa = fa;
  }
  return z;
}
#define ls u << 1, l, mid
#define rs u << 1 | 1, mid + 1, r
node mx[N * 4];
void init(int u, int l, int r) {
  mx[u] = {1, l};
  if(l == r) return ;
  int mid = (l + r) >> 1; init(ls); init(rs);
}
void modify(int u, int l, int r, int p, node v) {
  if(l == r) { mx[u] = v; return ; }
  int mid = (l + r) >> 1;
  p <= mid ? modify(ls, p, v) : modify(rs, p, v);
  mx[u] = max(mx[u << 1], mx[u << 1 | 1]);
}
node query(int u, int l, int r, int ql, int qr) {
  if(l == ql && r == qr) return mx[u];
  int mid = (l + r) >> 1;
  if(qr <= mid) return query(ls, ql, qr);
  if(ql > mid) return query(rs, ql, qr);
  return max(query(ls, ql, mid), query(rs, mid + 1, qr));
}
#undef ls
#undef rs
int main() {
  rt = id = 1; w[1] = INF >> 1; fir[1] = sec[1] = 0;
  scanf("%d%d", &n, &m);
  char op[5];
  int l, r, k;
  rep(i, 1, n) uid[i] = 1;
  init(1, 1, n);
  rep(T, 1, m) {
    scanf("%s%d%d", op, &l, &r);
    if(*op == 'C') {
      scanf("%d", &k);
      id ++; fir[id] = uid[l]; sec[id] = uid[r];
      o = 0; uid[k] = insert(rt, 0, INF);
      if(uid[k] != id) id --;
      else if(o) {
        if(o == rt) rt = rebuild(rt, 0, INF);
        else ch[ofa][w[o] > w[ofa]] = rebuild(o, wl, wr);
      }
      modify(1, 1, n, k, node{uid[k], k});
    }
    if(*op == 'Q') {
      printf("%d\n", query(1, 1, n, l, r).pos);
    }
  }
  return 0;
}
/*
5 10
C 1 1 1
C 2 1 2
Q 1 2
C 4 4 4
C 5 5 5
Q 4 5
Q 3 3
C 4 2 3
C 4 4 4
Q 3 4
*/