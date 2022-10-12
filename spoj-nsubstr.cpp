#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 6e5 + 10;
struct SAM {

struct Node {
	int len, link, nxt[26];
	void clr() { fill(nxt, nxt + 26, -1); }
} st[N];
int id, la, w[N];
void init() {
	st[0].len = 0; st[0].link = -1; st[0].clr();
	id = la = 0;
}
void extend(int c) {
	int u = ++ id, p = la;
	st[u].len = st[la].len + 1; st[u].clr();
	for(; ~ p && -1 == st[p].nxt[c]; p = st[p].link) {
		st[p].nxt[c] = u;
	}
	if(p == -1) {
		st[u].link = 0;
	} else {
		int q = st[p].nxt[c];
		if(st[p].len + 1 == st[q].len) {
			st[u].link = q;
		} else {
			int q0 = ++ id;
			st[q0] = st[q]; st[q0].len = st[p].len + 1;
			st[q].link = st[u].link = q0;
			for(; ~ p && st[p].nxt[c] == q; p = st[p].link) {
				st[p].nxt[c] = q0;
			}
		}
	}
	la = u; w[u] = 1;
}
void solve() {
	static int cnt[N], a[N], ans[N];
	int n = st[la].len;
	for(int i = 1; i <= id; i ++) cnt[st[i].len] ++;
	for(int i = 1; i <= n; i ++) cnt[i] += cnt[i - 1];
	for(int i = 1; i <= id; i ++) a[cnt[st[i].len] --] = i;
	for(int i = id; i >= 1; i --) {
		int u = a[i]; w[st[u].link] += w[u];
		ans[st[u].len] = max(ans[st[u].len], w[u]);
	}
	for(int i = 1; i <= n; i ++) printf("%d\n", ans[i]);
}

} sam;
char s[N]; //F[x] : len = x, 次数最多
int main() {
	// freopen("input", "r", stdin);
	scanf("%s", s + 1);
	sam.init();
	for(int i = 1; s[i]; i ++) sam.extend(s[i] - 'a');
	sam.solve();
	return 0;
}