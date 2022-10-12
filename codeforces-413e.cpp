#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 2e5 + 10;
char s[2][N];
int n, m, mark[N], ban[N];
int cnt, ty[N], sz[N], d[N], dl[N], dr[N], bel[N];
int main() {
	// freopen("input", "r", stdin);
	scanf("%d%d%s%s", &n, &m, s[0] + 1, s[1] + 1);
	for(int i = 1; i <= n; i ++) {
		if(s[0][i] == '.' && s[1][i] == '.') mark[i] = 3;
		else if(s[0][i] == '.') mark[i] = 1;
		else if(s[1][i] == '.') mark[i] = 2;
		else mark[i] = 0;
	}
	ban[n] = 1;
	for(int i = 1; i < n; i ++) {
		if(!mark[i] || !mark[i + 1] || mark[i] + mark[i + 1] == 3) {
			ban[i] = 1;
		}
	}
	ty[0] = -1;
	for(int i = 1; i <= n; i ++) if(mark[i]) {
		if(ty[cnt] != mark[i]) {
			cnt ++; ty[cnt] = mark[i]; dl[cnt] = i;
		}
		sz[cnt] ++; bel[i] = cnt; dr[cnt] = i;
	}
	for(int i = 1; i <= n; i ++) ban[i] += ban[i - 1];
	for(int i = 1; i < cnt; i ++) {
		if(ty[i] + ty[i + 1] == 3) d[i] = 0;
		else {
			if(ty[i] == 3) d[i] = sz[i + 1];
			else d[i] = i + 1 == cnt || ty[i + 2] == ty[i] ? sz[i + 1] : sz[i + 1] + 1;
		}
	}
	for(int i = 1; i <= cnt; i ++) d[i] += d[i - 1];
	for(int x, y, i = 1; i <= m; i ++) {
		scanf("%d%d", &x, &y);
		int x1 = x > n, x2 = y > n;
		int y1 = x1 ? x - n : x, y2 = x2 ? y - n : y;
		if(y1 > y2) { swap(y1, y2); swap(x1, x2); }
		if(ban[y2 - 1] - ban[y1 - 1]) puts("-1");
		else {
			if(bel[y1] == bel[y2]) printf("%d\n", y2 - y1 + (x1 ^ x2));
			else {
				int ans = d[bel[y2] - 2] - d[bel[y1] - 1];
				if(bel[y1] + 1 < bel[y2]) {
					ans += dr[bel[y1]] - y1 + y2 - dl[bel[y2]] + 1;
					if(ty[bel[y1]] == 3) ans += (ty[bel[y1] + 1] - 1) ^ x1;
					if(ty[bel[y2]] == 3) ans += (ty[bel[y2] - 1] - 1) ^ x2;
				} else {
					ans += dr[bel[y1]] - y1 + y2 - dl[bel[y2]] + 1 + (x1 ^ x2);
				}
				printf("%d\n", ans);
			}
		}
	}
	return 0;
}