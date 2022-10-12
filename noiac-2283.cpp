#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 510;
const int M = 1010;
const int S = 5010;
int n, len[12], lenb, m1, m2, q, f[32][M][M], g[32][M][M], fP[M][M], gP[M][M], dp[S][M], lg[1 << 10];
char s[12][N], b[M];
int main() {
  scanf("%d", &n);
  rep(i, 0, n - 1) scanf("%s", s[i]), lg[1 << i] = i;
  scanf("%s%d", b + 1, &q);
  lenb = strlen(b + 1);
  m1 = n >> 1; m2 = n - m1;
  auto chkmax = [](int &x, int y) {
    if(x < y) return x = y, true;
    return false;
  };
  for(int i = 0; i < m1; i ++) {
    len[i] = strlen(s[i]);
    rep(l, 1, lenb) {
      rep(j, 1, len[i]) rep(k, l, lenb) {
        if(s[i][j - 1] == b[k]) dp[j][k - l + 1] = dp[j - 1][k - l] + 1;  
        else dp[j][k - l + 1] = max(dp[j - 1][k - l + 1], dp[j][k - l]);
      }
      rep(r, l, lenb) f[1 << i][l][r] = dp[len[i]][r - l + 1];
    }
  }
  for(int i = 1; i < (1 << m1); i ++) if(i & (i - 1)) {
    int z = i & (-i), c = len[lg[z]];
    rep(l, 1, lenb + 1) fP[l][l - 1] = l - 1;
    per(l, lenb, 1) rep(r, l, lenb) {
      f[i][l][r] = -1;
      rep(k, fP[l][r - 1], fP[l + 1][r])
        if(chkmax(f[i][l][r], f[z][l][k] + f[i ^ z][k + 1][r]))
          fP[l][r] = k;
    }
  }
  for(int i = 0; i < m2; i ++) {
    len[m1+i] = strlen(s[m1+i]);
    rep(l, 1, lenb) {
      rep(j, 1, len[m1+i]) rep(k, l, lenb) {
        if(s[m1+i][j - 1] == b[k]) dp[j][k - l + 1] = dp[j - 1][k - l] + 1;  
        else dp[j][k - l + 1] = max(dp[j - 1][k - l + 1], dp[j][k - l]);
      }
      rep(r, l, lenb) g[1 << i][l][r] = dp[len[m1+i]][r - l + 1];
    }
  }
  for(int i = 1; i < (1 << m2); i ++) if(i & (i - 1)) {
    int z = i & (-i), c = len[m1+lg[z]];
    rep(l, 1, lenb + 1) gP[l][l - 1] = l - 1;
    per(l, lenb, 1) rep(r, l, lenb) {
      g[i][l][r] = -1;
      rep(k, gP[l][r - 1], gP[l + 1][r])
        if(chkmax(g[i][l][r], g[z][l][k] + g[i ^ z][k + 1][r]))
          gP[l][r] = k;
    }
  }
  rep(T, 1, q) {
    int st, l, r, ans = 0;
    scanf("%d%d%d", &st, &l, &r);
    int s1 = st & ((1 << m1) - 1), s2 = st >> m1;
    rep(i, l - 1, r)
      ans = max(ans, f[s1][l][i] + g[s2][i + 1][r]);
    printf("%d\n", ans);
  }
//  cerr << "time: " << clock() / (double) CLOCKS_PER_SEC << endl;
  return 0;
}