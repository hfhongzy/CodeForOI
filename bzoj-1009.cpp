#include <algorithm>
#include <cstdio>
using namespace std;

int n, m, mod, f[22], g[22][10];
struct matrix {
	int a[22][22], n, m;
	matrix operator * (const matrix &b) {
		matrix ans; ans.n = n; ans.m = b.m;
		for(int i = 0; i < ans.n; i ++) {
			for(int j = 0; j < ans.m; j ++) {
				ans.a[i][j] = 0;
				for(int k = 0; k < m; k ++) {
					ans.a[i][j] += a[i][k] * b.a[k][j];
				}
				ans.a[i][j] %= mod;
			}
		}
		return ans;
	}
} tr, st;
matrix mpow(matrix p, int b) {
	matrix ans = p; b --;
	for(; b >= 1; b >>= 1, p = p * p)
		if(b & 1) ans = ans * p;
	return ans;
}
int main() {
	scanf("%d%d%d", &n, &m, &mod);
	static char s[22]; scanf("%s", s + 1);
	if(n < m) {
		int res = 1;
		for(int i = 1; i <= n; i ++)
			res = res * 10ll % mod;
		printf("%d\n", res);
		return 0;
	}
	f[1] = 0;
	for(int i = 2; i <= m; i ++) {
		int j = f[i - 1];
		for(; j && s[j + 1] != s[i]; j = f[j]) ;
		if(s[j + 1] == s[i]) j ++;
		f[i] = j;
	}
	g[0][s[1] - '0'] = 1;
	for(int k = 1; k < m; k ++) {
		for(char ch = '0'; ch <= '9'; ch ++) {
			if(s[k + 1] == ch) {
				g[k][ch - '0'] = k + 1; continue ;
			}
			int j = f[k];
			for(; j && s[j + 1] != ch; j = f[j]) ;
			if(s[j + 1] == ch) j ++;
			g[k][ch - '0'] = j;
		}
	}
	st.n = 1; st.m = m; st.a[0][0] = 1;
	tr.n = tr.m = m;
	for(int i = 0; i < m; i ++) {
		for(int k = 0; k < 10; k ++) {
			if(g[i][k] < m) tr.a[i][g[i][k]] ++;
		}
	}
	st = st * mpow(tr, n);
	int cnt = 0;
	for(int i = 0; i < m; i ++)
		cnt += st.a[0][i];
	printf("%d\n", cnt % mod);
	return 0;
}
/*
dp[i][j] : 前i个字符，匹配到j
dp[0][0] = 1
dp[i][j] = \sum_{k = 0}^j s[j]
dp[n][0 to m - 1]
*/