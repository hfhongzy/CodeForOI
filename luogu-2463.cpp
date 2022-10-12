#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 1e5 + 2005;
int crd, a[N], minl, maxc, bel[N], s[N], n;
void pushback(int x, int y) {
	maxc = max(maxc, x); bel[++ n] = y; s[n] = x;
}
int cnt[N], sa[N], rk[N], height[N];
void build() {
	int m = maxc + 2000;
	fill(cnt, cnt + m + 1, 0);
	for(int i = 1; i <= n; i ++) cnt[s[i] += 2000] ++;
	for(int i = 1; i <= m; i ++) cnt[i] += cnt[i - 1];
	for(int i = 1; i <= n; i ++) rk[i] = cnt[s[i] - 1] + 1;
	for(int i = 1; i <= n; i ++) sa[cnt[s[i]] --] = i;
	m = n;
	for(int k = 1; k <= n; k <<= 1) {
		int c = 0;
		for(int i = n - k + 1; i <= n; i ++) a[++ c] = i;
		for(int i = 1; i <= n; i ++) if(sa[i] > k) a[++ c] = sa[i] - k;
		fill(cnt, cnt + m + 1, 0);
		for(int i = 1; i <= n; i ++) cnt[rk[i]] ++;
		for(int i = 1; i <= m; i ++) cnt[i] += cnt[i - 1];
		for(int i = n; i >= 1; i --) sa[cnt[rk[a[i]]] --] = a[i];
		copy(rk + 1, rk + n + 1, a + 1); rk[sa[1]] = c = 1;
		for(int i = 2; i <= n; i ++) {
			int u = sa[i - 1] + k <= n ? a[sa[i - 1] + k] : 0;
			int v = sa[i] + k <= n ? a[sa[i] + k] : 0;
			rk[sa[i]] = a[sa[i]] == a[sa[i - 1]] && u == v ? c : ++ c;
		}
		if(c == n) break ; m = rk[sa[n]];
	}
}
bool check(int mid) {
	static bool vis[N];
	static int st[N];
	int cnt = 0; bool tag = 0;
	for(int i = 2; i <= n; i ++) if(height[i] >= mid) {
		if(cnt == 0) {
			if(~ bel[sa[i - 1]] && !vis[bel[sa[i - 1]]]) {
				st[++ cnt] = bel[sa[i - 1]]; vis[st[cnt]] = 1;
				if(cnt == crd) { tag = 1; break ; }
			}
		}
		if(~ bel[sa[i]] && !vis[bel[sa[i]]]) {
			st[++ cnt] = bel[sa[i]]; vis[st[cnt]] = 1;
			if(cnt == crd) { tag = 1; break ; }
		}
	} else {
		while(cnt >= 1) vis[st[cnt --]] = 0;
	}
	while(cnt >= 1) vis[st[cnt --]] = 0;
	return tag;
}
int solve() {
	int l = 0, r = minl - 1;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(check(mid)) l = mid + 1;
		else r = mid - 1;
	}
	return l - 1;
}
int main() {
	freopen("input", "r", stdin);
	scanf("%d", &crd); minl = N; maxc = 1888;
	for(int i = 1; i <= crd; i ++) {
		int x, z = 0; scanf("%d", &x);
		for(int j = 1; j <= x; j ++) {
			int y; scanf("%d", &y);
			if(j ^ 1) pushback(y - z, i);
			z = y;
		}
		minl = min(minl, x);
		if(i ^ crd) pushback(1888, -1);
	}
	build();
	for(int i = 1, k = 0; i <= n; i ++) {
		if(rk[i] == 1) { k = 0; continue ; }
		if(k) k --;
		int u = sa[rk[i] - 1], lim = n - max(u, i) + 1;
		for(; k < lim && s[u + k] == s[i + k]; k ++) ;
		height[rk[i]] = k;
	}
	printf("%d\n", 1 + solve());
	return 0;
}
