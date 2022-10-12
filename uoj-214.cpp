#include <bits/stdc++.h>
#define ppc(x) __builtin_popcount(x)
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int M = 26 * 30;
const int mod = 998244353;
int add(int x, int y) { return (x += y) >= mod ? x -= mod : x; }
int dec(int x, int y) { return (x -= y) < 0 ? x += mod : x; }
void mkadd(int &x, int y) { x = add(x, y); }
void mkdec(int &x, int y) { x = dec(x, y); }

int n, m, c, st[32], g[M + 5], pw[M + 5], C[M + 5][M + 5];
char s[32][32], str[32];
void solve1() {
  static int use[32];
  int ans = 0;
  rep(i, 1, (1 << (n - m + 1)) - 1) {
    rep(j, 1, n) use[j] = 0;
    bool ok = 1;
    rep(j, 1, n - m + 1) if(i >> (j - 1) & 1) {
      rep(k, 0, m - 1) {
        if(!(st[j + k] >> str[k] & 1)) { ok = 0; break ; }
        use[j + k] |= 1 << str[k];
      }
      if(!ok) break ;
    }
    if(!ok) continue ;
    int h = 0;
    rep(j, 1, n) h += ppc(use[j]);
    ans = !(ppc(i) & 1) ? dec(ans, g[h]) : add(ans, g[h]);
  }
  printf("%d\n", ans);
}
void solve2() {
  static int dp[32][M + 5][1 << 10];
  const int U = (1 << (m - 1)) - 1;
  rep(i, 0, n) rep(j, 0, c) rep(k, 0, U) dp[i][j][k] = 0;
  dp[0][0][0] = mod - 1;
  int sc = 0;
  rep(i, 1, n) {
    sc += min(min(i - 1, m), (int)strlen(s[i - 1]));
    rep(k, 0, U) {
      int z = 0;
      rep(j, 0, m - 2) if(k >> j & 1) z |= 1 << str[j + 1];
      if((z & st[i]) != z) continue ;
      int x = ppc(z);
      rep(j, 0, sc) if(dp[i - 1][j][k]) {
        mkadd(dp[i][j + x][(k << 1) & U], dp[i - 1][j][k]);
      }
      if(!(st[i] >> str[0] & 1)) continue ;
      if(!(z >> str[0] & 1)) ++ x;
      rep(j, 0, sc) if(dp[i - 1][j][k]) {
        mkdec(dp[i][j + x][(k << 1 | 1) & U], dp[i - 1][j][k]);
      }
    }
  }
  int ans = 0;
  rep(i, 1, c)
    ans = (ans + (ll)g[i] * dp[n][i][0]) % mod;
  printf("%d\n", ans);
}
int main() {
  rep(i, 0, M) {
    C[i][0] = 1;
    rep(j, 1, i)
      C[i][j] = add(C[i - 1][j - 1], C[i - 1][j]);
  }
  int test;
  scanf("%d", &test);
  while(test --) {
    scanf("%d%d", &n, &m);
    rep(i, 1, n) scanf("%s", s[i]);
    c = 0;
    rep(i, 1, n) {
      st[i] = 0; c += strlen(s[i]);
      for(int j = 0; s[i][j]; j ++)
        st[i] |= 1 << (s[i][j] - 'a');
    }
    scanf("%s", str);
    rep(i, 0, m - 1) str[i] -= 'a';
    bool mark = 0;
    rep(i, 1, n - m + 1) {
      mark = 1;
      rep(j, 0, m - 1) if(!(st[i + j] >> str[j] & 1)) { mark = 0; break ; }
      if(mark) break ;
    }
    if(!mark) { puts("-1"); continue ; }
    pw[1] = 1;
    rep(i, 2, c) pw[i] = (ll)pw[mod % i] * (mod - mod / i) % mod;
    rep(i, 1, c) pw[i] = (ll)pw[i] * c % mod;
    rep(i, 1, c) {
      g[i] = 0;
      rep(k, 1, i) {
        if(!(k & 1)) g[i] = (g[i] + (mod - C[i][k]) * (ll)pw[k]) % mod;
        else g[i] = (g[i] + C[i][k] * (ll)pw[k]) % mod;
      }
    }
    if(n - m + 1 <= 19) solve1(); else solve2();
    // solve2();
  }
  return 0;
}