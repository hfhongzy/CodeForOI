#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;

typedef long long ll;
typedef double db;

const int N = 510;
const db eps = 1e-8;

int sign(db x) { return x < -eps ? -1 : x > eps; }
int cmp(db x, db y) { return sign(x - y); }

struct P {
  db x, y, t; int id;
  P() {}
  P(db a, db b, db c = 0, int i = 0) : x(a), y(b), t(c), id(i) {}
  bool operator < (P b) const {
    int c = cmp(x, b.x);
    return c ? c == -1 : cmp(y, b.y) == -1;
  }
  db len() { return sqrt(x * x + y * y); }
  db to(P b) {
    return sqrt((x - b.x) * (x - b.x) + (y - b.y) * (y - b.y));
  }
  P operator - (P b) { return P(x - b.x, y - b.y, 0, 0); };
  friend db cross(P p1, P p2, P p3) { //p1 -> p2 * p1 -> p3
    P v1(p2.x - p1.x, p2.y - p1.y), v2(p3.x - p1.x, p3.y - p1.y);
    return v1.x * v2.y - v1.y * v2.x;
  }
  friend int crossop(P p1, P p2, P p3) { return sign(cross(p1, p2, p3)); }
  db theta() { return atan2(y, x); }
} p[N];
void solve(vector<P> ps, vector<P> &qs) {
  int n = ps.size();
  if(n <= 1) { qs = ps; return ; }
  sort(ps.begin(), ps.end());
  qs.resize(2 * n); int r = 0;
  for(int i = 0; i < n; i ++) {
    while(r >= 2 && crossop(qs[r - 2], qs[r - 1], ps[i]) >= 0) r --;
    qs[r ++] = ps[i];
  }
  int t = r;
  for(int i = n - 2; i >= 0; i --) {
    while(r >= t + 1 && crossop(qs[r - 2], qs[r - 1], ps[i]) >= 0) r --;
    qs[r ++] = ps[i];
  }
  qs.resize(r - 1);
}
vector<int> ans;
int n;
vector<P> out(vector<P> ps, int s) {
  vector<P> ans;
  for(auto x : ps) if(x.id != s) ans.pb(x);
  return ans;
}
void work(vector<P> ps, int st) {
  if(ps.size() == 1) { ans.pb(n - 1); return ; } 
  if(ps.size() == 2) { ans.pb(st); ans.pb(n - 1); return ; }
  vector<P> qs;
  solve(ps, qs);
  int sz = (int)qs.size(); ans.pb(st);
  for(int i = 0; i < sz; i ++) if(qs[i].id == st) {
    if(qs[i ? i - 1 : sz - 1].id != n - 1) {
      work(out(ps, st), qs[i ? i - 1 : sz - 1].id);
    } else {
      work(out(ps, st), qs[i + 1 < sz ? i + 1 : 0].id);
    }
    return ;
  }
}
void solve1(vector<P> &ps) {
  ans.clear(); ::n = ps.size(); work(ps, 0);
  for(int v : ans) printf("%d ", v + 1);
  puts("");
}
void solve2(vector<P> &ps) {
  int n = ps.size();
  rep(i, 1, n - 1) if(!ps[i].id) { swap(ps[i], ps[0]); break ; }
  rep(i, 1, n - 1) ps[i].t = (ps[i] - ps[0]).theta();
  sort(ps.begin() + 1, ps.end(), [&](P a, P b) { return a.t < b.t; });
  vector<int> ans; ans.pb(0);
  int s = 0;
  rep(i, 1, n - 1) if(ps[i].id == n - 1) { s = i; break ; }
  rep(i, s + 1, n - 1) ans.pb(ps[i].id);
  rep(i, 1, s) ans.pb(ps[i].id);
  for(int v : ans) printf("%d ", v + 1);
  puts("");
}
int main() {
  int t; scanf("%d", &t);
  while(t --) {
    int n;
    scanf("%d", &n);
    vector<P> ps, qs;
    rep(i, 0, n - 1) {
      db x, y;
      scanf("%lf%lf", &x, &y);
      ps.pb(p[i] = (P){x, y, 0, i});
    }
    solve(ps, qs);
    bool mark = 0;
    rep(i, 0, (int)qs.size() - 1) if(!qs[i].id) { mark = 1; break ; }
    mark ? solve1(ps) : solve2(ps);
  }
  return 0;
}