#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;
typedef long long ll;
const int N = 15;
int m, n;
ll s[N][N], f[N];
bool G[66][N][N];
void init() {
	s[0][0] = 1;
	for(int i = 1; i <= n; i ++) {
		for(int j = 1; j <= i; j ++) {
			s[i][j] = s[i - 1][j] * j + s[i - 1][j - 1];
		}
	}
	f[1] = 1;
	for(int i = 2; i <= n; i ++) {
		f[i] = 0;
		for(int j = 1; j < i; j ++)
			f[i] -= f[j] * s[i][j];
	}
}
ll ans, a[66];
int bel[N], sz;
void calc() {
	ll cur = 1; fill(a, a + m, 0);
	for(int i = 1; i <= n; i ++) {
		for(int j = i + 1; j <= n; j ++) if(bel[i] ^ bel[j]) {
			ll x = 0;
			for(int k = 1; k <= m; k ++) if(G[k][i][j]) {
				x ^= 1ll << (k - 1);
			}
			for(int k = 0; k < m; k ++) if(x >> k & 1) {
				if(a[k]) x ^= a[k];
				else { a[k] = x; break ; }
			}
		}
	}
	for(int i = 0; i < m; i ++) if(!a[i]) cur <<= 1;
	ans += f[sz] * cur;
}
void dfs(int u) {
	if(u == n + 1) return calc();
	for(int i = 1; i <= sz; i ++) {
		bel[u] = i; dfs(u + 1);
	}
	sz ++; bel[u] = sz; dfs(u + 1); sz --;
}
int main() {
	scanf("%d", &m);
	for(int i = 1; i <= m; i ++) {
		static char str[N * N];
		scanf("%s", str + 1);
		if(!n) {
			int len = strlen(str + 1);
			for(n = 1; n * (n - 1) / 2 < len; n ++) ;
		}
		int pt = 0;
		for(int j = 1; j <= n; j ++)
			for(int k = j + 1; k <= n; k ++)
				G[i][j][k] = str[++ pt] == '1';
	}
	init(); dfs(1);
	printf("%lld\n", ans);
	return 0;
}