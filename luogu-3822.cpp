#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 1e6 + 10;
int n, m;
set<int> diff;
void add(int k, uint *a, uint *b) {
  int u = k >> 5, v = k & 31;
  uint t = a[u];
  a[u] += (1u << v);
  if(a[u] == b[u]) diff.erase(u);
  else if(t == b[u]) diff.insert(u);
  if(a[u] < t) {
    rep(i, u + 1, m) {
      t = a[i];
      a[i] ++;
      if(a[i] == b[i]) diff.erase(i);
      else if(t == b[i]) diff.insert(i);
      if(a[i]) break ;
    }
  }
}
int query(uint *a, int k) {
  return a[k >> 5] >> (k & 31) & 1;
}
uint a[N], b[N];
int main() {
  scanf("%d%*d%*d%*d", &n);
  m = (30 * n) >> 5;
  int op, x, y;
  rep(T, 1, n) {
    scanf("%d%d", &op, &x);
    if(op == 1) {
      scanf("%d", &y);
      bool neg = x < 0;
      if(neg) x = -x;
      for(int i = 0; x; x >>= 1, i ++) {
        if(x & 1) {
          !neg ? add(y + i, a, b) : add(y + i, b, a);
        }
      }
    }
    if(op == 2) {
      int z0 = x >> 5, z1 = x & 31;
      int cmp = 0; //cmp = 1 : a < b
      uint ma = a[z0] & ((1u << z1) - 1);
      uint mb = b[z0] & ((1u << z1) - 1);
      if(ma == mb) {
        auto it = diff.lower_bound(z0);
        if(it != diff.begin()) {
          it --;
          cmp = a[*it] < b[*it];
        }
      } else cmp = ma < mb;
      int ans = (query(a, x) - query(b, x) - cmp) & 1;
      putchar('0' ^ ans);
      putchar('\n');
    }
  }
  return 0;
}