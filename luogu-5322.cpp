#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 110, M = 2e4 + 10;
int s, n, m, a[N][N], dp[N][M];
int main() {
	scanf("%d%d%d", &s, &n, &m);
	for(int i = 1; i <= s; i ++)
		for(int j = 1; j <= n; j ++)
			scanf("%d", &a[i][j]);
	for(int i = 1; i <= n; i ++) {
		static int t[N];
		for(int j = 1; j <= s; j ++) t[j] = a[j][i] * 2 + 1;
		sort(t + 1, t + s + 1);
		for(int j = 0; j <= s; j ++) if(j == s || t[j + 1] != t[j]) {
			for(int k = 0; k <= m - t[j]; k ++) {
				dp[i][k + t[j]] = max(dp[i][k + t[j]], dp[i - 1][k] + i * j);
			}
		}
	}
	int ans = 0;
	for(int i = 0; i <= m; i ++)
		ans = max(ans, dp[n][i]);
	printf("%d\n", ans);
	return 0;
}