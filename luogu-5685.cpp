#include <algorithm>
#include <cstdio>
#include <string>
using namespace std;
const int N = 1e5 + 10;
struct pam {
	int fail, len, d, st, nxt[28];
} t[N];
char s[N];
int n, id, la, w[N][2];
void clr(int u) { t[u].st = 0; }
void init() {
	s[0] = -1;
	n = 0; id = 1; la = 0;
	t[0] = (pam) {0, -1, 0};
	t[1] = (pam) {0, 0, 0};
	clr(0); clr(1);
}
int find(int u) {
	while(s[n - t[u].len] != s[n + 1]) u = t[u].fail;
	return u;
}
void insert(int c, int ty) {
	s[n + 1] = c; int u = find(la);
	if(t[u].st >> c & 1) la = t[u].nxt[c];
	else {
		t[u].st ^= 1 << c;
		t[u].nxt[c] = la = ++ id; clr(la);
		t[la].len = t[u].len + 2;
		int v = u ? t[find(t[u].fail)].nxt[c] : 1;
		t[la].fail = v; t[la].d = t[t[la].fail].d + 1;
	}
	n ++;
	if(~ ty) w[la][ty] ++;
}
int main() {
	init(); long long ans = 0;
	static char s[N]; scanf("%s", s + 1);
	for(int i = 1; s[i]; i ++) insert(s[i] - 'A', 0);
	insert(27, -1); insert(26, -1); scanf("%s", s + 1);
	for(int i = 1; s[i]; i ++) insert(s[i] - 'A', 1);
	for(int i = id; i >= 2; i --) {
		w[t[i].fail][0] += w[i][0];
		w[t[i].fail][1] += w[i][1];
		ans += 1ll * w[i][0] * w[i][1];
	}
	printf("%lld\n", ans);
	return 0;
}