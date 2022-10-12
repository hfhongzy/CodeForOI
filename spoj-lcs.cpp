#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 5e5 + 10;
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
int match(char *s) {
	int ans = 0, u = 0, len = 0;
	while(*s) {
		int c = *s - 'a';
		while(u && -1 == st[u].nxt[c]) {
			u = st[u].link;
			len = st[u].len;
		}
		if(~ st[u].nxt[c]) {
			u = st[u].nxt[c]; len ++;
			ans = max(ans, len);
		}
		s ++;
	}
	return ans;
}

} sam;
char s[N], t[N];
int main() {
	freopen("input", "r", stdin);
	scanf("%s%s", s, t);
	sam.init();
	for(int i = 0; s[i]; i ++) sam.extend(s[i] - 'a');
	printf("%d\n", sam.match(t));
	return 0;
}