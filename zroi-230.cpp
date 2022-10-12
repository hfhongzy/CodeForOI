#include <algorithm>
#include <cstdio>
using namespace std;

const int N = 5005;
int n, a[N], b[N], ans[N][N];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++) {
		scanf("%d", a + i);
		b[i] = b[i - 1] ^ a[i];
		ans[i][i] = a[i];
	}
	for(int i = n; i >= 1; i --)
		for(int j = i + 1; j <= n; j ++)
			ans[i][j] = ans[i + 1][j] ^ ans[i][j - 1];
	for(int i = n; i >= 1; i --)
		for(int j = i + 1; j <= n; j ++)
			ans[i][j] = max(ans[i][j], max(ans[i + 1][j], ans[i][j - 1]));
	int q; scanf("%d", &q);
	while(q --) {
		int l, r;
		scanf("%d%d", &l, &r);
		printf("%d\n", ans[l][r]);
	}
	return 0;
}