#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 6e4 + 10;
const int INF = 1e8 + 10;
int n, k, a[N], f[10][N], s[N], dp[1 << 17];
void clear() { fill(dp, dp + (1 << 16), INF); }
void insert(int x, int val) {
   for(int i = 0; i < (1 << 8); i ++) {
      int t = ((x >> 8) << 8) | i;
      dp[t] = min(dp[t], ((x & 255) ^ i) + val);
   }
}
int query(int x) {
   int ans = INF;
   for(int i = 0; i < (1 << 8); i ++) {
      ans = min(ans, dp[(i << 8) | (x & 255)] + ( ((x >> 8) ^ i) << 8 ));
   }
   return ans;
}

int main() {
   scanf("%d%d", &n, &k);
   rep(i, 1, n) scanf("%d", a + i), s[i] = s[i - 1] ^ a[i];
   rep(i, 1, n) f[0][i] = INF;
   f[0][0] = 0;
   rep(i, 1, k) {
      clear();
      rep(j, i, n) {
         insert(s[j - 1], f[i - 1][j - 1]);
         f[i][j] = query(s[j]);
      }
   }
   rep(i, k, n) printf("%d%c", f[k][i], " \n"[i == n]);
   return 0;
}