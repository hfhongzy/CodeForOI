#include <algorithm>
#include <cstdio>
using namespace std;
int n, k, dp[1 << 21][21], f0[1 << 21], f1[1 << 21];
int main() {
	// freopen("input", "r", stdin);
	scanf("%d%d", &n, &k);
	for(int i = 0; i <= n; i ++) {
		static char s[1 << 21]; scanf("%s", s);
		for(int j = 0; j < (1 << i); j ++) if(s[j] == '1') dp[j | (1 << i)][i] = 1;
	}
	for(int i = 1; i < (1 << (n + 1)); i ++) {
		bool t = 0; f0[i] = f1[i] = -1;
		for(int j = n; j >= 0; j --) {
			bool c = i >> j & 1;
			if(!t) t |= c;
			else {
				if(c && -1 == f1[i]) f1[i] = j;
				if(!c && -1 == f0[i]) f0[i] = j; 
			}
		}
	}
	int ans = 0, len = -1;
	for(int i = (1 << (n + 1)) - 1; i >= 1; i --) {
		int l = 0;
		for(int j = n; j >= 0; j --) if(i >> j & 1) { l = j; break ; }
		for(int j = l; j >= 0; j --) if(dp[i][j]) {
			int t = i & ((1 << j) - 1), s = (i ^ (1 << l)) >> j;
			if(j) dp[s | (1 << (l - j))][0] += dp[i][j];
			int p0 = f0[t | (1 << j)], p1 = f1[t | (1 << j)];
			if(~ p0) dp[(s << (p0 + 1)) | (t & ((1 << p0) - 1)) | (1 << (l - j + p0 + 1))][p0] += dp[i][j];
			if(~ p1) dp[(s << (p1 + 1)) | (1 << p1) | (t & ((1 << p1) - 1)) | (1 << (l - j + p1 + 1))][p1] += dp[i][j];
		}
		if(dp[i][0] >= k && (l > len || (l == len && ans > i))) ans = i, len = l;
	}
	for(int i = n; i >= 0; i --) if(ans >> i & 1) {
		for(int j = i - 1; j >= 0; j --) {
			putchar('0' + (ans >> j & 1));
		}
		break ;
	}
	putchar('\n');
	return 0;
}