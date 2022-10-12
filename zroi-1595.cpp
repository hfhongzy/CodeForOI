#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;

typedef long long ll;

const int N = 1e5 + 10;
const int M = 22;
const int INF = 2e9;

template<class T>
void chkmin(T &x, const T &y) { if(x > y) x = y; }

char s[N], t[M];
int n, m, f[N][M][M * 2];
int main() {
   scanf("%s%s", s + 1, t + 1);
   n = strlen(s + 1); m = strlen(t + 1);
   rep(i, 0, n) rep(j, 0, m) rep(k, 0, M * 2 - 1) f[i][j][k] = INF;
   // rep(i, -m, -1) f[0][0][i + m] = -1;
   rep(i, 0, m) f[0][0][i + m] = 0;
   rep(i, 0, n) rep(j, 0, m) if(i || j) {
      // rep(k, -m, -j-1) f[i][j][k + m] = -1;
      f[i][j][-j + m] = 0;
      rep(k, -j + 1, m) {
         f[i][j][k + m] = min(i ? f[i - 1][j][k + m] + 1 : INF,
         min(j ? f[i][j - 1][k + 1 + m] : INF, i && j ? f[i - 1][j - 1][k - (s[i] == t[j]) + m] + 1 : INF));
      }
      // printf("f[%d][%d][%d] = %d\n", i, j, k, f[i][j][k + m]);
   }
   int q; scanf("%d", &q);
   while(q --) {
      int l, r; scanf("%d%d", &l, &r);
      int len = r - l + 1;
      rep(k, -m, m) if(f[r][m][k + m] >= len && (k == m || f[r][m][k + m] < INF)) {
         printf("%d\n", len - k); break ;
      }
   }
   return 0;
}