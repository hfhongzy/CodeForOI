#include <algorithm>
#include <cstdio>
using namespace std;
typedef long long ll;
const int N = 15;
int a[N], cnt[N], cur[N];
ll ans, c[N][N];
ll work(int sz) {
	int n = 0;
	for(int i = 1; i <= 6; i ++) {
		if(cur[i] % sz) return 0;
		cur[i] /= sz; n += cur[i];
	}
	ll res = 1;
	for(int i = 1; i <= 6; i ++) {
		res *= c[n][cur[i]]; n -= cur[i];
	}
	return res;
}
int main() {
	for(int i = 0; i < N; i ++) {
		c[i][0] = c[i][i] = 1;
		for(int j = 1; j < i; j ++)
			c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
	}
	int test; scanf("%d", &test);
	while(test --) {
		fill(cnt, cnt + 7, 0);
		for(int i = 1; i <= 12; i ++) {
			scanf("%d", a + i); cnt[a[i]] ++;
		}
		ans = 0;
		copy(cnt + 1, cnt + 7, cur + 1); ans += work(1);
		copy(cnt + 1, cnt + 7, cur + 1); ans += 6 * work(4);
		copy(cnt + 1, cnt + 7, cur + 1); ans += 3 * work(2);
		copy(cnt + 1, cnt + 7, cur + 1); ans += 8 * work(3);
		for(int i = 1; i <= 6; i ++) {
			for(int j = 1; j <= 6; j ++) {
				copy(cnt + 1, cnt + 7, cur + 1);
				cur[i] --; cur[j] --;
				if(cur[i] < 0 || cur[j] < 0) continue ;
				ans += 6 * work(2);
			}
		}
		printf("%lld\n", ans / 24);
	}	
	return 0;
}