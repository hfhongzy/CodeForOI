#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 32;
int n, m, tu[N][N], up[N][N], ri[N][N], f[N][N];
char t[N][N], s[N][N];
ll c[N][N], d[N][N];
ll solve(int xx, int yl, int yr) {
  rep(i, yl, yr) s[xx][i] = '#';
  rep(i, 1, n) rep(j, 1, m) up[i][j] = s[i][j] == '#' ? 0 : up[i - 1][j] + 1;
  rep(i, 1, n) per(j, m, 1) ri[i][j] = s[i][j] == '#' ? 0 : ri[i][j + 1] + 1;
  rep(i, xx, n) rep(j, 1, m) f[i][j] = up[i][j] > 1 && ri[i][j] > 1 ? (up[i][j] - 1) * (ri[i][j] - 1) : 0;

  rep(i, xx - 1, n) rep(j, 0, m) c[i][j] = 0;
  rep(i, xx, n) {
    rep(j, 1, m) if(up[i][j] > 1) {
      c[max(xx, i - up[i][j] + 1)][j] += ri[i][j] - 1;
      c[i][j] -= ri[i][j] - 1;
    }
  }
  rep(i, xx, n) rep(j, 1, m) c[i][j] += c[i - 1][j];
  rep(i, xx, n) rep(j, 1, m) d[i][j] = d[i][j - 1] + c[i][j] * ri[i][j] * up[i][j];

  ll tot = 0, res = 0;
  per(i, n, xx) {
    if(i < n) {
      rep(j, 1, m) tot += f[i + 1][j];
    }
    static ll ss[N];
    per(j, m, 1) ss[j] = ss[j + 1] + f[i][j];
    per(j, m, 1) ss[j] += ss[j + 1];
    per(j, m, 1) {
      if(i == xx && j <= yr) break ;
      if(!f[i][j]) continue ;
      res += (tot - c[i][j] * up[i][j]) * f[i][j] + (ss[j + 2] - ss[j + ri[i][j] + 1] - d[i][j + ri[i][j] - 1] + d[i][j]) * (up[i][j] - 1);
    }
  }
  rep(i, yl, yr) s[xx][i] = t[xx][i];
  return res;
}
int main() {
  freopen("logo.in", "r", stdin);
  freopen("logo.out", "w", stdout);
  scanf("%d%d", &n, &m);
  rep(i, 1, n) {
    scanf("%s", t[i] + 1);
    rep(j, 1, m) tu[i][j] = t[i][j] == '#' ? 0 : tu[i - 1][j] + 1, s[i][j] = t[i][j];
  }
  ll ans = 0;
  rep(x, 1, n) {
    rep(y1, 1, m) if(tu[x][y1] > 1) rep(y2, y1 + 1, m) {
      if(t[x][y2] == '#') break ;
      ans += (tu[x][y1] - 1) * solve(x, y1, y2);
    }
  }
  printf("%lld\n", ans);
  return 0;
}
/*
4 4
....
....
....
....
5 5
.....
.....
.....
.....
.....
10 10
..........
..........
..........
..........
..........
..........
..........
..........
..........
..........
*/