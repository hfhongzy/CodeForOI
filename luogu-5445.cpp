#include <bits/stdc++.h>
#define pb push_back
#define LOG(FMT...) fprintf(stderr, FMT)
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 4e6 + 10;
struct node {
  int op, x, y, zl, zr, w;
} a[N];
int n, q, c, ans[N];
char s[N];
namespace ns {

int bit[N];
void ins(int u, int v) {
  for(; u <= n; u += u & (-u))
    bit[u] += v;
}
void ins(int l, int r, int v) {
  ins(l, v); ins(r + 1, -v);
}
int qry(int u) {
  int z = 0;
  for(; u >= 1; u &= u - 1)
    z += bit[u];
  return z;
}

}
void cdq(int l, int r) {
  if(l == r) {
    return ;
  }
  int mid = (l + r) >> 1;
  cdq(l, mid); cdq(mid + 1, r);
  int p = l;
  rep(i, mid + 1, r) if(!a[i].op) {
    for(; p <= mid && a[p].y <= a[i].y; p ++) if(a[p].op) {
      ns::ins(a[p].zl, a[p].zr, a[p].w);
    }
    ans[a[i].w] += ns::qry(a[i].zl);
  }
  rep(i, l, p - 1) if(a[i].op) {
    ns::ins(a[i].zl, a[i].zr, -a[i].w);
  }
  inplace_merge(a + l, a + mid + 1, a + r + 1, [&](node a, node b) {
    return a.y < b.y;
  });
}
void build(int t, int l, int r, int v) {
  a[++ c] = {1, t, l, l, r, v * (q - t + 1)};
  a[++ c] = {1, t, r + 1, l, r, - v * (q - t + 1)};
}
int main() {
  scanf("%d%d%s", &n, &q, s + 1);
  set<int> s0 = {0, n + 1};
  int st = 0;
  rep(i, 1, n) {
    if(s[i] == '0') { s0.insert(i); st = 0; continue ; }
    if(!st) st = i;
    if(s[i + 1] != '1') {
      build(0, st, i, 1);
    }
  }
  char op[10];
  rep(i, 1, q) {
    int u, v;
    scanf("%s%d", op, &u);
    if(*op == 't') {
      ans[i] = -1;
      int z = c;
      if(s[u] == '1') {
        auto it = s0.lower_bound(u), pre = it, suf = it; pre --;
        s0.insert(u);
        int l = *pre + 1, r = *suf - 1;
        build(i, l, r, -1);
        if(l != u) build(i, l, u - 1, 1);
        if(u != r) build(i, u + 1, r, 1);
      } else {
        s0.erase(u);
        auto it = s0.lower_bound(u), suf = it, pre = it; pre --;
        int l = *pre + 1, r = *suf - 1;
        if(l != u) build(i, l, u - 1, -1);
        if(u != r) build(i, u + 1, r, -1);
        build(i, l, r, 1);
      }
      sort(a + z + 1, a + c + 1, [&](node a, node b) {
        return a.y < b.y;
      });
      s[u] ^= 1;
    }
    if(*op == 'q') {
      scanf("%d", &v); -- v;
      auto it = s0.lower_bound(u);
      if(*it > v) ans[i] = -(q - i + 1);
      a[++ c] = {0, i, u, v, v, i};
    }
  }
  cdq(1, c);
  rep(i, 1, q) if(~ans[i]) printf("%d\n", ans[i]);
  return 0;
}