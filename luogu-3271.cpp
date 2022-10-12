#include <bits/stdc++.h>
#define mp make_pair
#define LOG(FMT...) fprintf(stderr, FMT)
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e6 + 5, M = 2048;
const int mod = 1e8 + 7, inv2 = (mod + 1) >> 1;
int n, m, k, x[M], y[M], c1, c2, c3, c4;
pair<int, int> a[M];
bool vx[N], vy[N];
bool exist(int x, int y) {
  if(!vx[x] || !vy[y]) return 0;
  return *lower_bound(a + 1, a + k + 1, mp(x, y)) == mp(x, y);
}
bool pd(int x, int y) {
  return 0 <= x && x <= n && 0 <= y && y <= m;
}
int calc_tot(int n, int m) { //total
  return n * (n + 1ll) * (n + 2ll) / 6 % mod * (2 * m - n + 1ll) % mod * inv2 % mod;
}
int calc0(int x, int y) { //trought (x, y) and parallel to axes
  // LOG("px %d, %d = %d\n", x, y, min(x, y) + min(n - x, y) + min(x, m - y) + min(n - x, m - y));
  return min(x, y) + min(n - x, y) + min(x, m - y) + min(n - x, m - y);
}
int F(int n, int m, int q) { // 0 <= x <= n, 0 <= y <= m, 0 <= x + y <= q
  if(n < m) swap(n, m);
  if(q <= m) {
    return ((q + 1ll) * (q + 2ll) / 2 - 1) % mod;
  }
  if(q <= n) {
    return ((2 * q - m) * (m + 1ll) / 2 + m) % mod;
  }
  if(q <= m + n) {
    return ((n + 1ll) * (m + 1ll) - (m + n - q) * (m + n - q + 1ll) / 2 - 1) % mod;
  }
  return ((n + 1ll) * (m + 1ll) - 1) % mod;
}
int calc1(int x, int y) { //trought (x, y)
  return F(x, n - x, y) + F(x, n - x, m - y) + F(y, m - y, x) + F(y, m - y, n - x);
}
void calc2(int x1, int y1, int x2, int y2) { //trought (x1, y1) and (x2, y2)
  int dx = x2 - x1, dy = y2 - y1;
  if(pd(x1 - dy, y1 + dx) && pd(x2 - dy, y2 + dx)) c2 ++;
  if(pd(x1 + dy, y1 - dx) && pd(x2 + dy, y2 - dx)) c2 ++;
  if(!(x2 + x1 + y2 + y1 & 1)) {
    int x3 = (x2 + x1 + y2 - y1) / 2;
    int x4 = x1 + x2 - x3;
    int y3 = (y1 + y2 + x1 - x2) / 2;
    int y4 = y1 + y2 - y3;
    if(pd(x3, y3) && pd(x4, y4)) {
      c2 ++;
      bool e1 = exist(x3, y3), e2 = exist(x4, y4);
      if(e1 && e2) c4 ++;
      if(e1) c3 ++;
      if(e2) c3 ++;
    }
  }
}
int main() {
  scanf("%d%d%d", &n, &m, &k);
  bool rev = 0;
  if(n > m) { rev = 1; swap(n, m); }
  rep(i, 1, k) {
    scanf("%d%d", x + i, y + i);
    if(rev) swap(x[i], y[i]);
    a[i] = mp(x[i], y[i]);
    vx[x[i]] = vy[y[i]] = 1;
  }
  sort(a + 1, a + k + 1);
  rep(i, 1, k) {
    (c1 += calc1(x[i], y[i])) %= mod;
    (c1 -= calc0(x[i], y[i])) %= mod;
  }
  rep(i, 1, k) rep(j, i + 1, k) {
    calc2(x[i], y[i], x[j], y[j]);
  }
  c4 /= 2;
  int ans = ((calc_tot(n, m) - c1 + c2 - c3 + c4) % mod + mod) % mod;
  printf("%d\n", ans);
  return 0;
}