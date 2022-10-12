#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;

typedef long long ll;

const int N = 1e5 + 10;

int x, y, n, p, dp[320][N];
bool fir = 1;
void add(int &x, int y) { (x += y) >= p ? x -= p : 0; }
int add2(int x, int y) { return x + y >= p ? x + y - p : x + y; }
int solve(int n, int x) {
   if(x > n) return 0;
   int ans = 0, m = (int)sqrt(n - x), mx = min(n, x + m), t = n / (mx + 1);
   if(!fir) rep(i, 0, n) dp[0][i] = 0;
   fir = 0;
   dp[0][0] = 1;
   rep(i, x, mx) rep(j, i, n) add(dp[0][j], dp[0][j - i]);
   rep(i, 1, t) rep(j, 0, n) dp[i][j] = add2(j >= mx + 1 ? dp[i - 1][j - (mx + 1)] : 0, j >= i ? dp[i][j - i] : 0);
   rep(i, 0, t) add(ans, dp[i][n]);
   return ans;
}
int main() {
   scanf("%d%d%d%d", &x, &y, &n, &p);
   printf("%d\n", (solve(n, x) - solve(n, y + 1) + p) % p);
   return 0;
}