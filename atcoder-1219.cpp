#include <bits/stdc++.h>
#define pb push_back
#define debug(...) fprintf(stderr, __VA_ARGS__);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;

typedef long long ll;
const int N = 1e5 + 10;

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
int n, q, sz, cnt[N], a[N];
ll ans[N], cur;
ll query(int l, int r) {
  static int cnt[N];
  rep(i, l, r) cnt[a[i]] ++;
  ll ans = 0;
  rep(i, l, r) ans = max(ans, (ll)cnt[a[i]] * num[a[i]]); 
  rep(i, l, r) cnt[a[i]] = 0;
  return ans;
}
void add(int x) {
  cnt[x] ++; cur = max(cur, (ll)cnt[x] * num[x]);
}
void del(int x) { cnt[x] --; }
int main() {
  scanf("%d%d", &n, &q); sz = (int)sqrt(n);
  rep(i, 1, n) { scanf("%d", a + i); num.push(a[i]); }
  num.build();
  rep(i, 1, n) a[i] = num.get(a[i]);
  rep(i, 1, q) {
    scanf("%d%d", &c[i].l, &c[i].r);
    c[i].id = i;
    c[i].l2 = (c[i].l + sz - 1) / sz;
  }
  sort(c + 1, c + q + 1);
  for(int i = 1, j; i <= q; i = j + 1) {
    j = i;
    while(j < q && c[j + 1].l2 == c[j].l2) j ++;
    int br = min(n, c[i].l2 * sz), r = br;
    for(int k = i; k <= j; k ++) {
      if(c[k].r <= r) {
        ans[c[k].id] = query(c[k].l, c[k].r);
      } else {
        while(r < c[k].r) add(a[++ r]);
        ll tmp = cur;
        per(p, br, c[k].l) add(a[p]);
        ans[c[k].id] = cur;
        per(p, br, c[k].l) del(a[p]);
        cur = tmp;
      }
    }
    rep(k, br + 1, r) del(a[k]);
    cur = 0;
  }
  rep(i, 1, q) printf("%lld\n", ans[i]);
  return 0;
}