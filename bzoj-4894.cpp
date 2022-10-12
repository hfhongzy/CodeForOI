#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;
const int N = 310, mod = 1e9 + 7;
int n, a[N][N], b[N][N];
int qpow(int a, int b) {
	int ans = 1;
	for(; b >= 1; b >>= 1, a = 1ll * a * a % mod)
		if(b & 1) ans = 1ll * ans * a % mod;
	return ans;
}
int gauss() {
	int sgn = 1;
	for(int i = 2; i <= n; i ++) {
		int j = i;
		for(int k = i; k <= n; k ++) if(a[k][i]) {
			j = i; break ;
		}
		if(j != i) {
			for(int k = i; k <= n; k ++) swap(a[i][k], a[j][k]);
			sgn *= -1;
		}
		int cur = qpow(a[i][i], mod - 2);
		for(j = i + 1; j <= n; j ++) {
			int t = 1ll * a[j][i] * cur % mod;
			for(int k = i; k <= n; k ++) {
				(a[j][k] += mod - 1ll * a[i][k] * t % mod) %= mod;
			}
		}
	}
	int ans = 1;
	for(int i = 2; i <= n; i ++)
		ans = 1ll * ans * a[i][i] % mod;
	return sgn == 1 ? ans : (mod - ans) % mod;
}
int main() {
	scanf("%d", &n);
	static char s[N];
	for(int i = 1; i <= n; i ++) {
		scanf("%s", s + 1);
		for(int j = 1; j <= n; j ++) if(s[j] == '1') {
			a[i][j] = mod - 1;
			a[j][j] ++;
		}
	}
	printf("%d\n", gauss());
	return 0;
}