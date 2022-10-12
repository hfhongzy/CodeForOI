#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 510;
int n, m, len;
char s[N * 2][N * 2], a[N][N];
void rotate() {
	static char t[N * N];
	int c = 0;
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			t[++ c] = a[i][j];
	c = 0;
	for(int j = n; j >= 1; j --)
		for(int i = 1; i <= m; i ++)
			a[i][j] = t[++ c];
	swap(n, m);
}
int g[N * 2][N * 2], px[N * 4], py[N * 4], ps[N * 4], f[N * 4];
void solve() {
	for(int i = 1; i <= 2 * n + 1; i ++) {
		if(i & 1) {
			for(int j = 1; j <= 2 * m + 1; j ++) s[i][j] = '#';
		} else {
			for(int j = 1; j <= 2 * m + 1; j += 2) s[i][j] = '#';
			for(int j = 2; j <= 2 * m; j += 2) s[i][j] = a[i >> 1][j >> 1];
		}
	}
	n = 2 * n + 1; m = 2 * m + 1;
	for(int k = 2; k <= n + m; k ++) {
		int sx = 0, sy = 0;
		if(k <= n) sx = k - 1, sy = 1;
		else sx = n, sy = k - n;
		// assert(sx >= 1 && sx <= n && sy >= 1 && sy <= m);
		int cur = 0;
		for(int x = sx, y = sy; x >= 1 && y <= m; x --, y ++) {
			cur ++; px[cur] = x; py[cur] = y; ps[cur] = s[x][y];
		}
		ps[cur + 1] = -1;
		for(int i = 1, mid = 0, r = 0; i <= cur; i ++) {
			f[i] = i < r ? min(r - i, f[2 * mid - i]) : 1;
			while(ps[i + f[i]] == ps[i - f[i]]) f[i] ++;
			if(i + f[i] > r) { r = i + f[i]; mid = i; }
			g[px[i]][py[i]] = f[i];
		}
	}
	for(int i = 2; i <= n; i += 2) {
		for(int j = 2; j <= m; j += 2) {
			int l = 0;
			for(int x = i, y = j; x <= n && y <= m; x ++, y ++) {
				if(g[x][y] >= l + 1) l ++; else break ;
			}
			len = max(len, l);
		}
	}
	n /= 2; m /= 2;
}
int main() {
	int test; scanf("%d", &test);
	while(test --) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i ++)
			scanf("%s", a[i] + 1);
		len = 0;
		for(int i = 0; i < 4; i ++) {
			solve(); if(i ^ 3) rotate();
		}
		printf("%d\n", len * (len + 1) >> 1);
	}
	return 0;
}
/*
# # # # # # # # #
# a # b # b # a #
# # # # # # # # #
# b # a # a # # #
# # # # # # # # #
# b # a # # # # # 
# # # # # # # # #
# a # # # # # # #
# # # # # # # # #
*/