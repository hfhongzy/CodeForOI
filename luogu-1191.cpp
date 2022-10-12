#include <bits/stdc++.h>
#define pb push_back
#define debug(...) fprintf(stderr, __VA_ARGS__);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 156;
int n, up[N][N];
char s[N][N];
int main() {
  scanf("%d", &n);
  rep(i, 1, n) scanf("%s", s[i] + 1);
  rep(i, 1, n) rep(j, 1, n) {
    up[i][j] = s[i][j] == 'B' ? 0 : 1 + up[i - 1][j];
  }
  int ans = 0;
  rep(i, 1, n) rep(j, 1, n) {
    int h = n;
    rep(k, j, n) {
      h = min(h, up[i][k]);
      if(!h) break ;
      ans += h;
    }
  }
  printf("%d\n", ans);
  return 0;
}