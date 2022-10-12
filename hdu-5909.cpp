#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll;
const int N = 1000 + 50, mod = 1e9 + 7;
int n, m, a[N];
vector<int> G[N];
int dp[N][N], ans[N];
//dp'[i] = dp[j] dp[v][k], j ^ k = i;
void fwtxor(int *a) {
   for(int i = 1; i < m; i <<= 1)
      for(int j = 0; j < m; j += i << 1)
         for(int k = 0; k < i; k ++) {
            int p = a[j + k], q = a[j + k + i];
            a[j + k] = (p + q) % mod; a[j + k + i] = (p - q + mod) % mod;
         }
}
void Ifwtxor(int *a) {
   const long long inv2 = (mod + 1) >> 1;
   for(int i = 1; i < m; i <<= 1)
      for(int j = 0; j < m; j += i << 1)
         for(int k = 0; k < i; k ++) {
            int p = a[j + k], q = a[j + k + i];
            a[j + k] = (p + q) * inv2 % mod; a[j + k + i] = (p - q + mod) * inv2 % mod;
         }
}
void dfs(int u, int fa = 0) {
   dp[u][a[u]] = 1;
   for(int i = 0; i < (int) G[u].size(); i ++) {
      int v = G[u][i];
      if(v == fa) continue ;
      dfs(v, u);
      static int A[N], B[N];
      for(int j = 0; j < m; j ++) A[j] = dp[u][j];
      for(int j = 0; j < m; j ++) B[j] = dp[v][j];
      B[0] ++;
      fwtxor(A); fwtxor(B);
      for(int j = 0; j < m; j ++) A[j] = 1ll * A[j] * B[j] % mod;
      Ifwtxor(A);
      for(int j = 0; j < m; j ++) dp[u][j] = A[j];
   }
}
int main() {
   int test; scanf("%d", &test);
   while(test --) {
      scanf("%d%d", &n, &m);
      for(int i = 1; i <= n; i ++) scanf("%d", a + i);
      for(int i = 1; i <= n; i ++) {
         G[i].clear(); fill(dp[i], dp[i] + m, 0);
      }
      for(int u, v, i = 1; i < n; i ++) {
         scanf("%d%d", &u, &v);
         G[u].push_back(v);
         G[v].push_back(u);
      }
      dfs(1);
      for(int i = 0; i < m; i ++) {
         int ans = 0;
         for(int j = 1; j <= n; j ++)
            (ans += dp[j][i]) %= mod;
         printf("%d%c", ans, " \n"[i == m - 1]);
      }
   }
   return 0;
}