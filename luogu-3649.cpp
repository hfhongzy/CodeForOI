#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 3e5 + 10;
struct pam {
	int fail, len, d, st, nxt[26];
} t[N];
char s[N];
int n, id, la, w[N];
void clr(int u) { t[u].st = 0; }
void init() {
	scanf("%s", s + 1); s[0] = -1;
	n = 0; id = 1; la = 0;
	t[0] = (pam) {0, -1, 0};
	t[1] = (pam) {0, 0, 0};
	clr(0); clr(1);
}
int find(int u) {
	while(s[n - t[u].len] != s[n + 1]) u = t[u].fail;
	return u;
}
void insert(int c) {
	int u = find(la);
	if(t[u].st >> c & 1) la = t[u].nxt[c];
	else {
		t[u].st ^= 1 << c;
		t[u].nxt[c] = la = ++ id; clr(la);
		t[la].len = t[u].len + 2;
		int v = u ? t[find(t[u].fail)].nxt[c] : 1;
		t[la].fail = v; t[la].d = t[t[la].fail].d + 1;
	}
	n ++; w[la] ++;
}
int main() {
	init(); long long ans = 0;
	for(int i = 1; s[i]; i ++) insert(s[i] -= 'a');
	for(int i = id; i >= 1; i --) {
		w[t[i].fail] += w[i];
		ans = max(ans, 1ll * w[i] * t[i].len);
	}
	printf("%lld\n", ans);
	return 0;
}