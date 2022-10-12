#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;
const int mod = 1e9 + 7, N = 20, M = 1 << 15;
char s[N];
int n, m, dp[2][M], cnt[M], tr[M][4], ans[N], t[N], t2[N];
int main() {
	for(int i = 1; i < (1 << 15); i ++)
		cnt[i] = cnt[i & (i - 1)] + 1;
	int test;
	scanf("%d", &test);
	while(test --) {
		scanf("%s%d", s + 1, &m); n = strlen(s + 1);
		for(int i = 1; i <= n; i ++) {
			if(s[i] == 'A') s[i] = 0;
			if(s[i] == 'C') s[i] = 1;
			if(s[i] == 'G') s[i] = 2;
			if(s[i] == 'T') s[i] = 3;
		}
		for(int i = 0; i < (1 << n); i ++) {
			for(int c = 0; c < 4; c ++) {
				tr[i][c] = 0;
				for(int j = 1; j <= n; j ++) {
					t[j] = t[j - 1] + (i >> (j - 1) & 1); //f[i - 1][j]
				}
				for(int j = 1; j <= n; j ++) {
					t2[j] = s[j] == c ? t[j - 1] + 1 : max(t2[j - 1], t[j]);
					if(t2[j] != t2[j - 1]) tr[i][c] ^= 1 << (j - 1);
				}
			}
		}
		fill(dp[0], dp[0] + (1 << n), 0);
		dp[0][0] = 1; int cur = 0;
		for(int i = 1; i <= m; i ++) {
			cur ^= 1;
			fill(dp[cur], dp[cur] + (1 << n), 0);
			for(int S = 0; S < (1 << n); S ++) if(dp[cur ^ 1][S]) {
				for(int c = 0; c < 4; c ++) {
					(dp[cur][tr[S][c]] += dp[cur ^ 1][S]) %= mod;
				}
			}
		}
		fill(ans, ans + n + 1, 0);
		for(int S = 0; S < (1 << n); S ++) {
			(ans[cnt[S]] += dp[cur][S]) %= mod;
		}
		for(int i = 0; i <= n; i ++) {
			printf("%d\n", ans[i]);
		}
		//dp[i][S] : T前i位，S的前缀和[k]表示f[k][i]
	}
	return 0;
}