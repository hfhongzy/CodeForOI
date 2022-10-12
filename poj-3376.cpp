#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 2e6 + 5;
int n, m, cnt[N], len[N], pos[N], fa[N], p[N];
char s[N], dir[N];

bool mark[N];
int maxl;
void Mark(const char *ss, int n, bool rev = 0) {
	static char s[N + N];
	static int f[N + N]; maxl = 0;
	s[1] = '%';
	for(int i = 1; i <= n; i ++) {
		s[i << 1] = ss[i - 1];
		s[i << 1 | 1] = '%';
	}
	n = n << 1 | 1; s[n + 1] = '!';
	for(int i = 1, r = 0, mid = 0; i <= n; i ++) {
		f[i] = i < r ? min(r - i, f[2 * mid - i]) : 1;
		while(s[i + f[i]] == s[i - f[i]]) f[i] ++;
		if(i + f[i] > r) { r = i + f[i]; mid = i; }
		maxl = max(maxl, f[i] - 1);
	}
	if(!rev) {
		for(int i = 2; i < n; i += 2) {
			int mid = (i + 1 + n) >> 1;
			mark[i >> 1] = mid - f[mid] <= i;
		}
	} else {
		for(int i = 2; i < n; i += 2) {
			mark[i >> 1] = (i >> 1) + f[i >> 1] >= i;
		}
	}
}

int id = 1, ch[N][26], tag[N];
int query(const char *ss, int n, bool rev = 0) {
	int u = 1;
	if(rev) {
		for(int i = n; i >= 1 && u; i --)
			u = ch[u][ss[i - 1] - 'a'];
	} else {
		for(int i = 1; i <= n && u; i ++)
			u = ch[u][ss[i - 1] - 'a'];
	}
	return tag[u];
}
void insert(const char *ss, int n, bool rev = 0) {
	int u = 1;
	if(rev) {
		for(int i = n; i >= 1; i --) {
			int &v = ch[u][ss[i - 1] - 'a'];
			if(v) u = v;
			else {
				v = ++ id; fa[v] = u; dir[v] = ss[i - 1] - 'a'; u = v;
			}
			if(mark[i]) tag[u] ++;
		}
	} else {
		for(int i = 1; i <= n; i ++) {
			int &v = ch[u][ss[i - 1] - 'a'];
			if(v) u = v;
			else {
				v = ++ id; fa[v] = u; dir[v] = ss[i - 1] - 'a'; u = v;
			}
			if(mark[i]) tag[u] ++;
		}
	}
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++) {
		scanf("%d%s", len + i, s + pos[i]);
		m = max(m, len[i]);
		pos[i + 1] = pos[i] + len[i];
	}
	for(int i = 1; i <= n; i ++) cnt[len[i]] ++;
	for(int i = 1; i <= m; i ++) cnt[i] += cnt[i - 1];
	for(int i = 1; i <= n; i ++) p[cnt[len[i]] --] = i;
	long long ans = 0;
	for(int i = n; i >= 1; i --) {
		int u = p[i];
		ans += query(&s[pos[u]], len[u], 1);
		Mark(&s[pos[u]], len[u]);
		insert(&s[pos[u]], len[u]);
		if(maxl == len[u]) ans ++;
	}
	for(int i = 1; i <= id; i ++) tag[i] = ch[fa[i]][dir[i]] = 0;
	id = 1;
	for(int i = n; i >= 1; i --) {
		int u = p[i];
		ans += query(&s[pos[u]], len[u]);
		Mark(&s[pos[u]], len[u], 1);
		insert(&s[pos[u]], len[u], 1);
	}
	printf("%lld\n", ans);
	return 0;
}