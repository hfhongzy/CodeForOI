#include <bits/stdc++.h>
#define pb push_back
#define debug(...) fprintf(stderr, __VA_ARGS__);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;

const int N = 2e5 + 10;

struct discrete {
  vector<int> v;
  vector<int>::iterator ep;
  int operator [](int x) { return v[x - 1]; }
  void push(int x) { v.pb(x); }
  int size() { return ep - v.begin(); }
  void build() { sort(v.begin(), v.end()); ep = unique(v.begin(), v.end()); }
  int get(int x) { return lower_bound(v.begin(), ep, x) - v.begin() + 1; }
} num;
struct node {
  int l, r, l2, id;
  bool operator < (const node &b) const {
    return l2 == b.l2 ? r < b.r : l2 < b.l2;
  }
} c[N];
int n, q, sz, mr[N], ml[N], a[N];
int ans[N], cur;
int query(int l, int r) {
  static int fir[N];
  int ans = 0;
  rep(i, l, r) {
    if(!fir[a[i]]) fir[a[i]] = i;
    ans = max(ans, i - fir[a[i]]);
  } 
  rep(i, l, r) fir[a[i]] = 0;
  return ans;
}
void add(int x) {
  ml[a[x]] = min(ml[a[x]], x);
  mr[a[x]] = max(mr[a[x]], x);
  cur = max(cur, x - ml[a[x]]);
}
int main() {
  scanf("%d", &n); sz = (int)sqrt(n);
  rep(i, 1, n) { scanf("%d", a + i); num.push(a[i]); }
  num.build();
  rep(i, 1, n) a[i] = num.get(a[i]);
  scanf("%d", &q);
  rep(i, 1, q) {
    scanf("%d%d", &c[i].l, &c[i].r);
    c[i].id = i;
    c[i].l2 = (c[i].l + sz - 1) / sz;
  }
  sort(c + 1, c + q + 1);
  rep(i, 1, n) {
    ml[a[i]] = n; mr[a[i]] = 0;
  }
  for(int i = 1, j; i <= q; i = j + 1) {
    j = i;
    while(j < q && c[j + 1].l2 == c[j].l2) j ++;
    int br = min(n, c[i].l2 * sz), r = br;
    for(int k = i; k <= j; k ++) {
      if(c[k].r <= r) {
        ans[c[k].id] = query(c[k].l, c[k].r);
      } else {
        while(r < c[k].r) add(++ r);
        int t = query(c[k].l, br);
        per(p, br, c[k].l) t = max(t, mr[a[p]] - p);
        ans[c[k].id] = max(cur, t);
      }
    }
    rep(k, br + 1, r) {
      ml[a[k]] = n; mr[a[k]] = 0;
    }
    cur = 0;
  }
  rep(i, 1, q) printf("%d\n", ans[i]);
  return 0;
}