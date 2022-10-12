#include <bits/stdc++.h>
#define debug(...) fprintf(stderr, __VA_ARGS__);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;

const int N = 210;
const int M = 1e5 + 10;

struct discrete {
  vector<int> v;
  vector<int>::iterator ep;
  void push(int x) { v.push_back(x); }
  int size() { return ep - v.begin(); }
  void build() { sort(v.begin(), v.end()); ep = unique(v.begin(), v.end()); }
  int get(int x) { return lower_bound(v.begin(), ep, x) - v.begin() + 1; }
} ds;

int n, m, q, B, a[N][N], cnt[N * N], cur, ans[M];

struct Query {
  int xl, yl, xr, yr, id;
  void init() {
    if(xl > xr) swap(xl, xr);
    if(yl > yr) swap(yl, yr);
  }
  bool operator < (const Query &b) const {
    return xl / B == b.xl / B ? (yl / B == b.yl / B ? (xr / B == b.xr / B ? yr < b.yr : xr < b.xr) : yl < b.yl) : xl < b.xl;
  }
} c[M];

void add(int x) { cur += 2 * cnt[x] + 1; cnt[x] ++; }
void del(int x) { cur -= 2 * cnt[x] - 1; cnt[x] --; }
void addx(int x, int l, int r) { rep(i, l, r) add(a[x][i]); }
void delx(int x, int l, int r) { rep(i, l, r) del(a[x][i]); }
void addy(int y, int l, int r) { rep(i, l, r) add(a[i][y]); }
void dely(int y, int l, int r) { rep(i, l, r) del(a[i][y]); }

int main() {
  scanf("%d%d", &n, &m);
  B = max(1, int(pow(n * m, 0.5) / pow(m, 0.25)));
  rep(i, 1, n) rep(j, 1, m) {
    scanf("%d", &a[i][j]);
    ds.push(a[i][j]);
  }
  ds.build();
  rep(i, 1, n) rep(j, 1, m) a[i][j] = ds.get(a[i][j]);
  scanf("%d", &q);
  rep(i, 1, q) {
    scanf("%d%d%d%d", &c[i].xl, &c[i].yl, &c[i].xr, &c[i].yr);
    c[i].init();
    c[i].id = i;
  }
  sort(c + 1, c + q + 1);
  int xl = 1, yl = 1, xr = 0, yr = 0;
  rep(i, 1, q) {
    while(xl > c[i].xl) addx(-- xl, yl, yr);
    while(xr < c[i].xr) addx(++ xr, yl, yr);
    while(yl > c[i].yl) addy(-- yl, xl, xr);
    while(yr < c[i].yr) addy(++ yr, xl, xr);

    while(xl < c[i].xl) delx(xl ++, yl, yr);
    while(xr > c[i].xr) delx(xr --, yl, yr);
    while(yl < c[i].yl) dely(yl ++, xl, xr);
    while(yr > c[i].yr) dely(yr --, xl, xr);
    ans[c[i].id] = cur;
  }
  rep(i, 1, q) {
    printf("%d\n", ans[i]);
  }
  return 0;
}