#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 2e5 + 5;
char s[100005];
struct SAM {

int id, la, nxt[N][26], len[N], link[N];
void clr(int x) { fill(nxt[x], nxt[x] + 26, -1); }
void init() {
	link[0] = -1; clr(0);
}
void extend(int c) {
	int u = ++ id, p = la;
	len[u] = len[la] + 1; clr(u);
	for(; ~ p && -1 == nxt[p][c]; p = link[p]) {
		nxt[p][c] = u;
	}
	if(p == -1) {
	} else {
		int q = nxt[p][c];
		if(len[p] + 1 == len[q]) {
			link[u] = q;
		} else {
			int q0 = ++ id;
			copy(nxt[q], nxt[q] + 26, nxt[q0]);
			len[q0] = len[p] + 1; link[q0] = link[q];
			link[q] = link[u] = q0;
			for(; ~ p && nxt[p][c] == q; p = link[p]) {
				nxt[p][c] = q0;
			}
		}
	}
	la = u;
}
int a[N], cur[N], ans[N];
void tpo() {
	static int cnt[N];
	int n = len[la];
	for(int i = 1; i <= id; i ++) cnt[len[i]] ++;
	for(int i = 1; i <= n; i ++) cnt[i] += cnt[i - 1];
	for(int i = 1; i <= id; i ++) a[cnt[len[i]] --] = i;
}
int lcs() {
	fill(ans + 1, ans + id + 1, N);
	while(~ scanf("%s", s)) {
		int u = 0, l = 0;
		for(int i = 0; s[i]; i ++) {
			int c = s[i] - 'a';
			while(u && nxt[u][c] == -1) {
				u = link[u];
				l = len[u];
			}
			if(~ nxt[u][c]) {
				u = nxt[u][c]; l ++;
				cur[u] = max(cur[u], l);
			}
		}
		for(int i = id; i >= 1; i --) {
			int u = a[i], f = link[u];
			cur[f] = max(cur[f], min(len[f], cur[u]));
			ans[u] = min(ans[u], cur[u]); cur[u] = 0;
		}
	}
	int res = 0;
	for(int i = 1; i <= id; i ++)
		if(ans[i] < N) res = max(res, ans[i]);
	return res;
}

} sam;
int main() {
	freopen("input", "r", stdin);
	scanf("%s", s);
	sam.init();
	for(int i = 0; s[i]; i ++) sam.extend(s[i] - 'a');
	sam.tpo();
	printf("%d\n", sam.lcs());
	return 0;
}