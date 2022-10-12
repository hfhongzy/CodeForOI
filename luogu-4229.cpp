#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 2020, mod = 998244353;
struct node {
	int l, r, h;
	bool operator < (const node &b) const {
		if(h != b.h) return h < b.h;
		return r < b.r || (r == b.r && l > b.l);
	}
} a[N];
int n, q, A, t, set_p[N], p, pos[N], sz[N], up[N], set_h[N];
int dp[N][N], sum[N];
int qpow(int a, int b) {
	int ans = 1;
	for(; b >= 1; b >>= 1, a = 1ll * a * a % mod)
		if(b & 1) ans = 1ll * ans * a % mod;
	return ans;
}
int main() {
	int test; scanf("%d", &test);
	while(test --) {
		scanf("%d%d%d", &n, &q, &A); t = p = 0;
		for(int i = 1; i <= q; i ++) {
			scanf("%d%d%d", &a[i].l, &a[i].r, &a[i].h);
			set_p[++ t] = a[i].l; set_p[++ t] = a[i].r;
		}
		set_p[++ t] = 1; set_p[++ t] = n;
		sort(set_p + 1, set_p + t + 1);
		t = unique(set_p + 1, set_p + t + 1) - set_p - 1;
		for(int i = 1; i <= t; i ++) {
			pos[++ p] = set_p[i]; sz[p] = 1;
			if(i != t && set_p[i] + 1 < set_p[i + 1]) {
				pos[++ p] = set_p[i] + 1;
				sz[p] = set_p[i + 1] - set_p[i] - 1;
			}
		}

		n = p;
		for(int i = 1; i <= n; i ++) up[i] = A;
		for(int i = 1; i <= q; i ++) {
			a[i].l = lower_bound(pos + 1, pos + n + 1, a[i].l) - pos;
			a[i].r = lower_bound(pos + 1, pos + n + 1, a[i].r) - pos;
			for(int j = a[i].l; j <= a[i].r; j ++) up[j] = min(up[j], a[i].h);
		}
		for(int i = 1; i <= n; i ++) set_h[i] = up[i];
		int cur = 1, res = 1;
		for(int i = 1; i <= q; i ++) {
			while(a[i].l <= a[i].r && up[a[i].l] != a[i].h) a[i].l ++;
			while(a[i].l <= a[i].r && up[a[i].r] != a[i].h) a[i].r --;
			if(a[i].l > a[i].r) res = 0;
		}
		if(res == 0) {
			puts("0"); continue ;
		}
		sort(a + 1, a + q + 1);
		sort(set_h + 1, set_h + n + 1);
		for(int i = 1; i <= n; i ++) if(i == 1 || set_h[i] != set_h[i - 1]) {
			for(int j = 0; j <= n; j ++) dp[0][j] = 0;
			dp[0][0] = 1; sum[0] = 1; int row = 0;
			for(int j = 1; j <= n; j ++) if(up[j] == set_h[i]) {
				row ++; sum[row] = 0; 
				while(cur <= q && a[cur].h < set_h[i]) cur ++;
				while(cur <= q && a[cur].h == set_h[i] && a[cur].r < j) cur ++;
				int l = 0;
				if(cur <= q && a[cur].h == set_h[i] && a[cur].r == j) {
					l = a[cur].l;
				}
				int iv = qpow(set_h[i] - 1, sz[j]);
				int va = (qpow(set_h[i], sz[j]) - iv + mod) % mod;
				for(int k = 0; k <= n; k ++) {
					dp[row][k] = 0;
					if(k >= l && k <= j) {
						if(k == j) dp[row][k] = 1ll * sum[row - 1] * va % mod;
						else dp[row][k] = 1ll * dp[row - 1][k] * iv % mod;
						(sum[row] += dp[row][k]) %= mod;
					}
				}
			}
			res = 1ll * sum[row] * res % mod;
		}
		printf("%d\n", res);
	}
	return 0;
}