#include <algorithm>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;

typedef long long ll;
const int N = 4e5 + 10, mod = 998244353;	

int n;
ll dp[N][3][2][2], g[3][2][2];
vector<int> G[N];
void dfs(int u, int fa = 0) {
	for(int v : G[u]) if(v ^ fa) dfs(v, u);
	dp[u][0][0][0] = dp[u][1][0][0] = dp[u][2][0][0] = 1;
	for(int v : G[u]) if(v ^ fa) {
		memset(g, 0, sizeof g);
		for(int i = 0; i < 3; i ++) {
			for(int j = 0; j < 3; j ++) {
				for(int x = 0; x < 2; x ++) {
					for(int y = 0; y < 2; y ++) {
						for(int z = 0; z < 2; z ++) {
							for(int w = 0; w < 2; w ++) {
								if(i + j != 4 && i && j) (g[i][1][1] += dp[u][i][x][z] * dp[v][j][y][w] % mod) %= mod;
								if(y || !j) (g[i][x][z | w] += dp[u][i][x][z] * dp[v][j][y][w] % mod) %= mod;
							}
						}
					}
				}
			}
		}
		for(int i = 0; i < 3; i ++)
			for(int j = 0; j < 2; j ++)
				for(int k = 0; k < 2; k ++)
					dp[u][i][j][k] = g[i][j][k];
	}
}
int main() {
	scanf("%d", &n);
	for(int i = 1, u, v; i < n; i ++) {
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1);
	ll ans = (dp[1][0][0][1] + dp[1][1][1][1] + dp[1][2][1][1]) % mod;
	printf("%lld\n", (ans + mod) % mod);
	return 0;
}