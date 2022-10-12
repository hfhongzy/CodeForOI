#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 1005, mod = 998244353;
int n, m, q, a[N][N], s[N][N], b[N][N], c[N][N];
inline int upd(const int &x) {
	return x >= mod ? x - mod : x;
}
inline void upd(int &x, const int &y) {
	(x += y) >= mod ? x -= mod : 0;
}
inline int qry(int b[N][N], int xl, int xr, int yl, int yr) {
	return upd(upd(upd(b[xr][yr] + mod - b[xl - 1][yr]) + mod - b[xr][yl - 1]) + b[xl - 1][yl - 1]);
}
int main() {
	// freopen("input", "r", stdin);
	scanf("%d%d%d", &n, &m, &q);
	for(int i = 1; i <= n; i ++) {
		for(int j = 1; j <= m; j ++) {
			scanf("%d", &a[i][j]);
			upd(a[i][j], upd(upd(a[i - 1][j] + a[i][j - 1]) + mod - a[i - 1][j - 1]));
			s[i][j] = a[i][j];
			upd(s[i][j], upd(upd(s[i - 1][j] + s[i][j - 1]) + mod - s[i - 1][j - 1]));
		}
	}
	for(int i = 1; i <= n; i ++) {
		for(int j = 1; j <= m; j ++) {
			c[i][j] = upd(upd(qry(s, i, n, j, m) + mod - qry(s, i, n, 1, m - j)) + mod - qry(s, 1, n - i, j, m));
			upd(c[i][j], qry(s, 1, n - i, 1, m - j));
		}
	}
	for(int i = 1; i <= n; i ++) {
		for(int j = 1; j <= m; j ++) {
			b[i][j] = upd(upd(upd(b[i - 1][j] + b[i][j - 1]) + mod - b[i - 1][j - 1]) + c[i][j]);
		}
	}
	for(int xl, xr, yl, yr, i = 1; i <= q; i ++) {
		scanf("%d%d%d%d", &xl, &xr, &yl, &yr);
		printf("%d\n", qry(b, xl, xr, yl, yr));
	}
	return 0;
}