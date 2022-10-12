#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;
const int N = 3e5 + 10, mod = 1e9 + 7;
char s[N];
int dp[N][3][3];
int main() {
	scanf("%s", s + 1); int n = strlen(s + 1); dp[0][0][0] = 1;
	for(int i = 1; i <= n; i ++) {
		for(int x1 = 0; x1 < 3; x1 ++) {
			for(int x0 = 0; x0 < 3; x0 ++) if(dp[i - 1][x1][x0]) {
				for(int x = 0; x < 2; x ++) {
					if(s[i] != '?' && x != s[i] - '0') continue ;
					int y1 = x1, y0 = x0;
					if(x == 1) {
						if(y0) y0 --;
						else y1 = y1 == 2 ? 2 : y1 + 1;
					} else {
						y0 = y0 == 2 ? 1 : y0 + 1;
					}
					(dp[i][y1][y0] += dp[i - 1][x1][x0]) %= mod;
				}
			}
		}
	}
	int ans = ((long long) dp[n][1][0] + dp[n][2][0] + dp[n][2][1] + dp[n][2][2]) % mod;
	printf("%d\n", ans);
	return 0;
}
/*
优先级：
(1) 000 -> 0
(2) delete 01 / 10
(3) 111 -> 1
维护111..000栈
0 <= 2, 01删
*/