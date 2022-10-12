#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 2020;
struct SAM {

struct Node {
	int len, link, nxt[26];
	void clr() { fill(nxt, nxt + 26, -1); }
} st[N * 2];
int id, la;
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
	la = u;
}
int substr() {
	int ans = 0;
	for(int i = 1; i <= id; i ++) {
		ans += st[i].len - st[st[i].link].len;
	}
	return ans;
}

} sam;
int ans[N][N];
char s[N];
int main() {
	freopen("input", "r", stdin);
	int test;
	scanf("%d", &test);
	while(test --) {
		scanf("%s", s + 1);
		int q; scanf("%d", &q);
		while(q --) {
			int l, r;
			scanf("%d%d", &l, &r);
			sam.init();
			while(l != r + 1) {
				sam.extend(s[l ++] - 'a');
			}
			printf("%d\n", sam.substr());
		}
	}
	return 0;
}