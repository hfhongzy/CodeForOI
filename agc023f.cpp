#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;

typedef long long ll;

const int N = 2e5 + 10;
struct node {
  int u, t, c0, c1;
  bool operator < (const node &b) const {
    return (ll)c1 * b.c0 > (ll)b.c1 * c0;
  }
} z[N];
priority_queue<node> pq;
int n, tim, fa[N], a[N], f[N];
ll ans;
int find(int u) {
  return u == f[u] ? u : f[u] = find(f[u]);
}
int main() {
  scanf("%d", &n);
  rep(i, 2, n) scanf("%d", fa + i);
  rep(i, 1, n) scanf("%d", a + i), f[i] = i;
  rep(i, 1, n) {
    z[i] = a[i] ? node{i, 0, 0, 1} : node{i, 0, 1, 0};
    pq.push(z[i]);
  }
  while(pq.size()) {
    node c = pq.top(); pq.pop();
    int u = c.u;
    if(u == 1 || z[u].t != c.t) continue ;
    int v = find(fa[u]); f[u] = v;
    ans += (ll)z[v].c1 * z[u].c0;
    z[v].c0 += z[u].c0; z[v].c1 += z[u].c1; z[v].t = ++ tim;
    pq.push(z[v]);
  }
  printf("%lld\n", ans);
  return 0;
}