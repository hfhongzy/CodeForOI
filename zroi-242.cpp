#include <algorithm>
#include <cstdio>
#define id(x, y) (x - 1) * m + y
using namespace std;
const int N = 3010;
int n, m, ans, f[N * N], cnt[N];
char s[N * N];
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++)
		scanf("%s", &s[id(i, 1)]);
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			f[id(i, j)] = s[id(i, j)] == '1' ? 0 : 1 + f[max(0, id(i - 1, j))];
	for(int i = 1; i <= n; i ++) {
		int h = 0;
		for(int j = 1; j <= m; j ++) {
			cnt[f[id(i, j)]] ++; h = max(h, f[id(i, j)]);
		}
		for(int j = h - 1; j >= 1; j --) cnt[j] += cnt[j + 1];
		for(int j = h; j >= 1; j --) ans = max(ans, cnt[j] * j);
		fill(cnt, cnt + h + 1, 0);
	}
	printf("%d\n", ans);
	return 0;
}