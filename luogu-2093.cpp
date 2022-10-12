#include <bits/stdc++.h>
#define fs first
#define sc second
#define pb push_back
#define LOG(FMT...) fprintf(stderr, FMT);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
const int INF = 2.147e9;
struct point { int x, y, id; } q;
ll dis(point a, point b) {
  return (a.x - b.x) * (ll)(a.x - b.x) + (a.y - b.y) * (ll)(a.y - b.y);
}
struct node {
  point p; int ls, rs, xl, xr, yl, yr;
} a[N];
int n, m, rt;
bool cmpx(node a, node b) { return a.p.x < b.p.x; }
bool cmpy(node a, node b) { return a.p.y > b.p.y; }
void upd(int u) {
  const int l = a[u].ls, r = a[u].rs;
  a[u].xl = min(a[u].p.x, min(a[l].xl, a[r].xl));
  a[u].xr = max(a[u].p.x, max(a[l].xr, a[r].xr));
  a[u].yl = min(a[u].p.y, min(a[l].yl, a[r].yl));
  a[u].yr = max(a[u].p.y, max(a[l].yr, a[r].yr));
}
int build(int l, int r, int d = 1) {
  if(l > r) return 0;
  int u = (l + r) >> 1;
  nth_element(a + l, a + u, a + r + 1, d ? cmpx : cmpy);
  a[u].ls = build(l, u - 1, d ^ 1);
  a[u].rs = build(u + 1, r, d ^ 1);
  upd(u);
  // printf("%d: ls = %d, rs = %d, [%d, %d], [%d, %d]\n", u, a[u].ls, a[u].rs, a[u].xl, a[u].xr, a[u].yl, a[u].yr);
  return u;
}
typedef pair<ll, point> foo;
bool great(foo a, foo b) {
  return a.fs > b.fs || (a.fs == b.fs && a.sc.id < b.sc.id);
}
struct cmp {
  bool operator() (foo a, foo b) { return great(a, b); }
};
priority_queue< foo, vector<foo>, cmp > pq;
int k;
inline ll pw(ll x) { return x * x; }
ll maxdis(int u) {
  return pw(max(abs(a[u].xl - q.x), abs(q.x - a[u].xr))) + pw(max(abs(a[u].yl - q.y), abs(q.y - a[u].yr)));
}
void KDT(int u) {
  if(!u || (pq.size() == k && pq.top().fs > maxdis(u))) return ;
  auto cur = make_pair(dis(a[u].p, q), a[u].p);
  if(pq.size() < k) {
    pq.push(cur);
  } else if(great(cur, pq.top())) {
    pq.pop(); pq.push(cur);
  }
  if(maxdis(a[u].ls) > maxdis(a[u].rs)) {
    KDT(a[u].ls); KDT(a[u].rs);
  } else {
    KDT(a[u].rs); KDT(a[u].ls);
  }
}
int main() {
  scanf("%d", &n);
  rep(i, 1, n) {
    scanf("%d%d", &a[i].p.x, &a[i].p.y);
    a[i].p.id = i;
  }
  a[0].yl = a[0].xl = INF; a[0].yr = a[0].xr = -INF;
  rt = build(1, n);
  scanf("%d", &m);
  rep(i, 1, m) {
    scanf("%d%d%d", &q.x, &q.y, &k);
    while(pq.size()) pq.pop();
    KDT(rt);
    // printf("sz:%lu\n", pq.size());
    printf("%d\n", pq.top().sc.id);
  }
  return 0;
}