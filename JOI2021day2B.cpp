#include <bits/stdc++.h>
#define fs first
#define sc second
#define pb push_back
#define LOG(FMT...) fprintf(stderr, FMT);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
char gc() {
  // return getchar();
  static char buf[1 << 17], *S, *T;
  if(S == T) T = (S = buf) + fread(buf, 1, 1 << 17, stdin);
  return S == T ? EOF : *S ++;
}
template<class T> void read(T &x) {
  x = 0; char c = gc(); bool na = 0;
  for(; c < '0' || c > '9'; c = gc()) na |= c == '-';
  for(; c >= '0' && c <= '9'; c = gc()) x = x * 10 + (c & 15);
  if(na) x = -x;
}
typedef pair<int, int> pii;
template<class T>
void chkmin(T &x, const T &y) { if(x > y) x = y; }

const int N = 2.5e5 + 10;
const int M = N * 9;
const int INF = 2000000050;
typedef long long ll;
struct point {
  int x, y;
} a[N];
struct node {
  int l, mid, r, u; ll val;
  bool operator < (const node &b) const {
    return val > b.val;
  }
};
priority_queue<node> pq;
int n, m, ind[N], k, Tl[N], Tr[N], id, ls[M], rs[M];
pii mn[M];
int newnode() {
  ++ id; mn[id].fs = INF; return id;
}
void build(int &u, int l, int r) {
  u = newnode();
  if(l == r) return ;
  int mid = (l + r) >> 1;
  build(ls[u], l, mid);
  build(rs[u], mid + 1, r);
}
void ins(int &u, int la, int l, int r, int p, pii w1) {
  u = ++ id;
  mn[u] = min(w1, mn[la]);
  if(l == r) return ;
  int mid = (l + r) >> 1;
  if(p <= mid) rs[u] = rs[la], ins(ls[u], ls[la], l, mid, p, w1);
  else ls[u] = ls[la], ins(rs[u], rs[la], mid + 1, r, p, w1);
}
pii qval;
void query(int u, int l, int r, int ql, int qr) {
  if(!u || qval <= mn[u]) return ;
  if(l == ql && r == qr) {
    qval = mn[u]; return ;
  }
  int mid = (l + r) >> 1;
  if(qr <= mid) return query(ls[u], l, mid, ql, qr);
  if(ql > mid) return query(rs[u], mid + 1, r, ql, qr);
  if(l & 1) {
    query(ls[u], l, mid, ql, mid);
    query(rs[u], mid + 1, r, mid + 1, qr);
  } else {
    query(rs[u], mid + 1, r, mid + 1, qr);
    query(ls[u], l, mid, ql, mid);
  }
}
//树套树(y,x)
//w1:贡献者较小
//w2:贡献者大，第一维变n-y+1
//x:[l,r] y:<= y
pii query(int l, int r, int y) {
  if(!y) return pii(INF, 0);
  qval = pii(INF, 0);
  query(Tl[y], 1, n, l, r);
  return qval;
}
pii query2(int l, int r, int y) {
  if(y == n) return pii(INF, 0);
  qval = pii(INF, 0);
  query(Tr[y + 1], 1, n, l, r);
  return qval;
}
pair<ll, int> solve(int l, int r, int i) {
  pair<ll, int> c1 = query(l, r, ind[i]);
  pair<ll, int> c2 = query2(l, r, ind[i]);
  c1.fs += c1.fs == INF ? INF : a[i].x + a[i].y;
  c2.fs += c2.fs == INF ? INF : a[i].x - a[i].y;
  return min(c1, c2);
}
static char pbuf[5000005], *pp = pbuf;
void write(ll x) {
  static int st[64];
  int top = 0;
  if(!x) st[++ top] = 0;
  while(x) st[++ top] = x % 10, x /= 10;
  while(top) *pp ++ = st[top --] ^ '0';
}
int main() {
  static int num[N];
  read(n); read(k);
  rep(i, 1, n) {
    read(a[i].x); read(a[i].y);
    num[i] = a[i].y;
  }
  sort(num + 1, num + n + 1);
  sort(a + 1, a + n + 1, [&](point u, point v) {
    return u.x == v.x ? u.y < v.y : u.x < v.x;
  });
  vector<int> foo_y[N];
  rep(i, 1, n) {
    ind[i] = lower_bound(num + 1, num + n + 1, a[i].y) - num;
    foo_y[ind[i]].pb(i);
  }
  build(Tl[0], 1, n);
  rep(i, 1, n) {
    Tl[i] = Tl[i - 1];
    for(int v : foo_y[i]) {
      ins(Tl[i], Tl[i], 1, n, v, pii(-a[v].x - a[v].y, v));
    }
  }
  build(Tr[n + 1], 1, n);
  per(i, n, 1) {
    Tr[i] = Tr[i + 1];
    for(int v : foo_y[i]) {
      ins(Tr[i], Tr[i], 1, n, v, pii(-a[v].x + a[v].y, v));
    }
  }
  //insert(i, ind[i], pii(-a[i].x - a[i].y, i), pii(-a[i].x + a[i].y, i));
  rep(i, 2, n) {
    pair<ll, int> c1 = solve(1, i - 1, i);
    pq.push({1, c1.sc, i - 1, i, c1.fs});
  }
  rep(i, 1, k) {
    node cur = pq.top(); pq.pop();
    write(cur.val); *pp ++ = '\n';
    if(i == k) break ;
    if(cur.l < cur.mid) {
      pair<ll, int> c1 = solve(cur.l, cur.mid - 1, cur.u);
      pq.push({cur.l, c1.sc, cur.mid - 1, cur.u, c1.fs});
    }
    if(cur.mid < cur.r) {
      pair<ll, int> c1 = solve(cur.mid + 1, cur.r, cur.u);
      pq.push({cur.mid + 1, c1.sc, cur.r, cur.u, c1.fs});
    }
  }
  fwrite(pbuf, 1, pp - pbuf, stdout);
  return 0;
}