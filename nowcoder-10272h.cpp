#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
int qpow(int a, int b) {
  int ans = 1;
  for(; b >= 1; b >>= 1, a = (ll)a * a % mod)
    if(b & 1) ans = (ll)ans * a % mod;
  return ans;
}
int n, m, res, ans[8][8], a[8][8];
void dfs(int x, int y) {
  if(x == n + 1) { res ++; return ; }
  for(int i = 0; i < 3; i ++) {
    bool bad = 0;
    a[x][y] = i;
    for(int u = x - 1; u >= 1; u --) {
      for(int v = y - 1; v >= 1; v --) {
        if((a[u][v] == a[u][y] && a[x][v] == a[x][y]) || (a[u][v] == a[x][v] && a[u][y] == a[x][y])) {
          bad = 1; break ;
        }
      }
      if(bad) break ;
    }
    if(!bad) {
      y == m ? dfs(x + 1, 1) : dfs(x, y + 1);
    } 
  }
}
int main() {
  for(n = 1; n <= 7; n ++) {
    for(m = n; m <= 7; m ++) {
      res = 0; dfs(1, 1);
      ans[n][m] = qpow(3, n * m) - res;
    }
  }
  int test; scanf("%d", &test);
  while(test --) {
    int n, m;
    scanf("%d%d", &n, &m);
    if(n > m) swap(n, m);
    if(n == 1) printf("0\n");
    else if(m > 7) printf("%d\n", qpow(3, n * m));
    else printf("%d\n", ans[n][m]);
  }
  return 0;
}