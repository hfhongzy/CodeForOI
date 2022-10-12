#include <bits/stdc++.h>
#define LOG(FMT...) fprintf(stderr, FMT)
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int N = 1e5 + 10;
const int M = 510;
const int INF = 1e9;
struct node {
  int x, y;
  node operator - (const node &b) const { return {x - b.x, y - b.y}; }
  ll det(const node &b) const { return (ll)x * b.y - (ll)y * b.x; }
} a[N], b[N], st1[N], st2[N];
int n, m, ans, d[M][M];
bool G[M][M];
bool pd(node a, node b, node c) { return (b - a).det(c - a) >= 0; }
int s1, s2;
void convex() {
  sort(a + 1, a + n + 1, [&](node a, node b) { return a.x < b.x || (a.x == b.x && a.y < b.y); });
  st1[s1 = 1] = a[1];
  rep(i, 2, n) {
    while(s1 >= 2 && (st1[s1] - st1[s1 - 1]).det(a[i] - st1[s1 - 1]) >= 0) s1 --;
    st1[++ s1] = a[i];
  }
  st2[s2 = 1] = a[1];
  rep(i, 2, n) {
    while(s2 >= 2 && (st2[s2] - st2[s2 - 1]).det(a[i] - st2[s2 - 1]) <= 0) s2 --;
    st2[++ s2] = a[i];
  }
}
int main() {
  freopen("lo.in", "r", stdin);
  freopen("lo.out", "w", stdout);
  scanf("%d%d", &n, &m);
  rep(i, 1, n) {
    scanf("%d%d", &a[i].x, &a[i].y);
  }
  rep(i, 1, m) {
    scanf("%d%d", &b[i].x, &b[i].y);
  }
  convex();
  rep(i, 1, m) rep(j, 1, m) if(i != j) {
    if(!pd(b[i], b[j], st1[1]) || !pd(b[i], b[j], st1[s1]))  continue ;
    ll dx = b[i].x - b[j].x, dy = b[i].y - b[j].y;
    if(dx < 0) { dx = -dx; dy = -dy; }
    if(dx == 0) { G[i][j] = 1; continue ; }
    int l = 1, r = s1 - 1; node u = st1[s1];
    while(l <= r) {
      int mid = (l + r) >> 1;
      if((st1[mid + 1].y - st1[mid].y) * dx < dy * (st1[mid + 1].x - st1[mid].x)) {
        u = st1[mid];
        r = mid - 1;
      } else {
        l = mid + 1;
      }
    }
    if(!pd(b[i], b[j], u)) continue ;
    l = 1; r = s2 - 1; u = st2[s2];
    while(l <= r) {
      int mid = (l + r) >> 1;
      if((st2[mid + 1].y - st2[mid].y) * dx > dy * (st2[mid + 1].x - st2[mid].x)) {
        u = st2[mid];
        r = mid - 1;
      } else {
        l = mid + 1;
      }
    }
    if(pd(b[i], b[j], u)) G[i][j] = 1;
  }
  rep(i, 1, m) rep(j, 1, m) d[i][j] = i == j ? 0 : (G[i][j] ? 1 : INF);
  ans = INF;
  rep(k, 1, m) {
    rep(i, 1, m) if(G[k][i]) rep(j, 1, m) if(G[j][k]) ans = min(ans, d[i][j] + 2);
    rep(i, 1, m) rep(j, 1, m) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
  }
  if(ans == INF) ans = -1;
  printf("%d\n", ans);
  return 0;
}