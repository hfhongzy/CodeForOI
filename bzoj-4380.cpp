#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 4020, M = 52;
int n, m, a[N], b[N], w[N], val[N];
int dp[M][M][N], cost[M][N];
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i ++) {
		scanf("%d%d%d", a + i, b + i, w + i);
		val[i] = w[i];
	}
	sort(val + 1, val + m + 1);
	w[0] = unique(val + 1, val + m + 1) - val - 1;
	for(int i = 1; i <= m ; i++) {
		w[i] = lower_bound(val + 1, val + w[0] + 1, w[i]) - val;
	}
	for(int i = 1; i <= n + 1; i ++) dp[i][i - 1] = 0;
	for(int i = n; i >= 1; i --) {
		for(int j = i; j <= n; j ++) {
			for(int k = 1; k <= m; k ++) if(i <= a[k] && b[k] <= j) {
				for(int u = a[k]; u <= b[k]; j ++) {
					cost[u][w[k]] ++;
				}
			}
			for(int k = i; k <= j; k ++) {
				for(int u = w0 - 1; u >= 1; u --) {
					cost[k][u] += cost[k][u + 1];
				}
			}
			for(int v = w[0]; v >= 1; v --) {
				dp[i][j][v] = dp[i][j][v + 1];		
				for(int k = i; k <= j; k ++) {
					dp[i][j][v] = max(dp[i][j][v], dp[i][k - 1] + dp[k + 1][j] + cost[k][v]);
				}
			}
			for(int k = i; k <= j; k ++) {
				for(int u = w0; u >= 1; u --) {
					cost[k][u] = 0;
				}
			}
		}
	}
	printf("%d\n", dp[1][n][1]);
	return 0;
}