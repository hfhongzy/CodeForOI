#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;
typedef long long ll;
const int N = 3e4 + 10;
char str[N], sr[N];
int n;
struct SA {
	int cnt[N], sa[N], rk[N], t[N], h[N], st[N][15], lg[N];
	void build(char *s) {
		int m = *max_element(s + 1, s + n + 1);
		fill(cnt + 1, cnt + m + 1, 0);
		for(int i = 1; i <= n; i ++) cnt[s[i]] ++;
		for(int i = 1; i <= m; i ++) cnt[i] += cnt[i - 1];
		for(int i = 1; i <= n; i ++) rk[i] = cnt[s[i] - 1] + 1;
		for(int i = 1; i <= n; i ++) sa[cnt[s[i]] --] = i;
		m = n;
		for(int k = 1, num = 0; k <= n; k <<= 1, num = 0) {
			for(int i = n - k + 1; i <= n; i ++) t[++ num] = i;
			for(int i = 1; i <= n; i ++) if(sa[i] > k) t[++ num] = sa[i] - k;
			fill(cnt + 1, cnt + m + 1, 0);
			for(int i = 1; i <= n; i ++) cnt[rk[i]] ++;
			for(int i = 1; i <= m; i ++) cnt[i] += cnt[i - 1];
			for(int i = n; i >= 1; i --) sa[cnt[rk[t[i]]] --] = t[i];
			copy(rk + 1, rk + n + 1, t + 1); rk[sa[1]] = num = 1;
			for(int i = 2; i <= n; i ++) {
				int u = sa[i - 1] + k <= n ? t[sa[i - 1] + k] : 0;
				int v = sa[i] + k <= n ? t[sa[i] + k] : 0;
				if(t[sa[i - 1]] == t[sa[i]] && u == v) rk[sa[i]] = num;
				else rk[sa[i]] = ++ num;
			}
			m = num;
			if(num == n) break ;
		}
		s[n + 1] = h[1] = 0;
		for(int i = 1, k = 0; i <= n; i ++) {
			if(rk[i] == 1) { k = 0; continue ; }
			if(k) k --;
			int u = sa[rk[i] - 1];
			for(; s[u + k] == s[i + k]; k ++) ;
			h[rk[i]] = k;
		}
		lg[1] = 0;
		for(int i = 2; i <= n; i ++) lg[i] = lg[i >> 1] + 1;
		for(int i = 1; i <= n; i ++) st[i][0] = h[i];
		for(int j = 1; j <= lg[n]; j ++)
			for(int i = 1; i + (1 << j) - 1 <= n; i ++)
				st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
	}
	int lcp(int a, int b) {
		a = rk[a]; b = rk[b];
		if(a > b) swap(a, b);
		int k = lg[b - a];
		return min(st[a + 1][k], st[b - (1 << k) + 1][k]);
	}
} s, sR;
ll f[N], g[N];
int main() {
	int test;
	scanf("%d", &test);
	while(test --) {
		scanf("%s", str + 1); n = strlen(str + 1);
		for(int i = 1; i <= n; i ++) sr[i] = str[n - i + 1];
		s.build(str); sR.build(sr);
		fill(f, f + n + 1, 0); fill(g, g + n + 1, 0);
		for(int l = 1; l * 2 <= n; l ++) {
			for(int i = 1; i + l <= n; i += l) if(str[i] == str[i + l]) {
				int rlen = min(l, s.lcp(i, i + l)), llen = min(l, sR.lcp(n - i + 1, n - i - l + 1));
				int lp = i - llen + 1, rp = i + rlen - l;
				if(lp > rp) continue ;
				f[lp] ++; f[rp + 1] --;
				g[lp + 2 * l - 1] ++; g[rp + 2 * l] --;
			}
		}
		for(int i = 1; i <= n; i ++) f[i] += f[i - 1];
		for(int i = 1; i <= n; i ++) g[i] += g[i - 1];
		ll ans = 0;
		for(int i = 1; i < n; i ++) ans += g[i] * f[i + 1];
		printf("%lld\n", ans);
	}
	return 0;
}