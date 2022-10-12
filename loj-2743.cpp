#include <algorithm>
#include <cstdio>
#define rep(i, l, r) for(int i = l; i <= r; i ++)
using namespace std;
typedef long long ll;
const int N = 110, mod = 1e9 + 7;
int n, l, a[N], dp[N][N][N * 10][2][2];
inline void upd(int &x, const int &y) {
	(x += y) >= mod ? x -= mod : 0;
}
int main() {
	scanf("%d%d", &n, &l);
	if(n == 1) { puts("1"); return 0; }
	for(int i = 1; i <= n; i ++) scanf("%d", a + i);
	sort(a + 1, a + n + 1);
	for(int i = n; i >= 1; i --) a[i] -= a[i - 1];
	a[1] = 0; dp[0][0][0][0][0] = 1;
	rep(i, 1, n) rep(j, 0, i - 1) rep(s, 0, l) rep(x, 0, 1) rep(y, 0, 1) {
		ll cur = dp[i - 1][j][s][x][y];
		if(!cur) continue ;
		int t = s + (2 * j - x - y) * a[i];
		//独立点
		if(t > l) continue ;
		upd(dp[i][j + 1][t][x][y], cur * (j + 1 - x - y) % mod);
		if(!x) upd(dp[i][j + 1][t][1][y], cur);
		if(!y) upd(dp[i][j + 1][t][x][1], cur);

		//贴着段
		if(j) upd(dp[i][j][t][x][y], cur * (j * 2 - x - y) % mod);
		if(j && !x) upd(dp[i][j][t][1][y], cur);
		if(j && !y) upd(dp[i][j][t][x][1], cur);

		//合并段
		if(j >= 2) upd(dp[i][j - 1][t][x][y], cur * (j - 1) % mod);
	}
	int ans = 0;
	rep(i, 0, l) upd(ans, dp[n][1][i][1][1]);
	printf("%d\n", ans);
	return 0;
}