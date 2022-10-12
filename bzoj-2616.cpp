#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 510, M = 1e6 + 10, mod = 1e9 + 7;
int n, m, k, h[N], dp[N][N], g[N];
int fac[M], fav[M];
int qpow(int a, int b) {
	int ans = 1;
	for(; b >= 1; b >>= 1, a = 1ll * a * a % mod)
		if(b & 1) ans = 1ll * ans * a % mod;
	return ans;
}
int C(int x, int y) {
	return x < y ? 0 : 1ll * fac[x] * fav[y] % mod * fav[x - y] % mod;
}
int solve(int l, int r, int fah = 0) {
	if(l > r) return 0;
	int u = min_element(h + l, h + r + 1) - h;
	// printf("%d!\n", u);
	int row = h[u] - fah, col = r - l + 1;
	int ls = solve(l, u - 1, h[u]);
	int rs = solve(u + 1, r, h[u]);
	// printf("[%d] : ls = [%d], rs = [%d]\n", u, ls, rs);
	for(int i = 0; i <= min(col, k); i ++) {
		g[i] = 0;
		for(int j = 0; j <= i; j ++) {
			(g[i] += 1ll * dp[ls][j] * dp[rs][i - j] % mod) %= mod;
		}
	}
	for(int i = 0; i <= min(col, k); i ++) {
		for(int j = 0; j <= i; j ++) {
			(dp[u][i] += 1ll * g[j] * C(col - j, i - j) % mod * C(row, i - j) % mod * fac[i - j] % mod) %= mod;
		}
	}
	return u;
}
int main() {
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i ++) scanf("%d", h + i);
	m = max(n, *max_element(h + 1, h + n + 1)) + 1;
	fac[0] = 1;
	for(int i = 1; i <= m; i ++) fac[i] = 1ll * fac[i - 1] * i % mod;
	fav[m] = qpow(fac[m], mod - 2);
	for(int i = m; i >= 1; i --) fav[i - 1] = 1ll * fav[i] * i % mod;
	dp[0][0] = 1;
	printf("%d\n", dp[solve(1, n)][k]);
	return 0;
}