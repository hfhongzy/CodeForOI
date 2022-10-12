#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 1e5 + 20;
struct pam {
	int fail, len, st, d, nxt[26];
} t[N];
int id, nl, nr, ml, mr;
char str[N + N], *s = str + N;
long long ans;
void init() {
	t[0] = (pam) {0, -1, 0, 0}; t[1] = (pam) {0, 0, 0, 0};
	id = 1; nl = 1; nr = ml = mr = 0; s[0] = s[1] = -1;
}
int findl(int u) {
	while(nl + t[u].len > nr || s[nl + t[u].len] != s[nl - 1])
		u = t[u].fail;
	return u;
}
int findr(int u) {
	while(nr - t[u].len < nl || s[nr - t[u].len] != s[nr + 1])
		u = t[u].fail;
	return u;
}
void pushback(int c) {
	s[nr + 1] = c;
	int u = findr(mr);
	if(t[u].st >> c & 1) mr = t[u].nxt[c];
	else {
		t[u].st ^= 1 << c;
		t[u].nxt[c] = mr = ++ id; t[mr].st = 0;
		t[mr].len = t[u].len + 2;
		int v = u ? t[findr(t[u].fail)].nxt[c] : 1;
		t[mr].fail = v; t[mr].d = t[v].d + 1;
	}
	nr ++; ans += t[mr].d;
	if(nr - nl + 1 == t[mr].len) ml = mr;
}
void pushfront(int c) {
	s[nl - 1] = c;
	int u = findl(ml);
	if(t[u].st >> c & 1) ml = t[u].nxt[c];
	else {
		t[u].st ^= 1 << c;
		t[u].nxt[c] = ml = ++ id; t[ml].st = 0;
		t[ml].len = t[u].len + 2;
		int v = u ? t[findl(t[u].fail)].nxt[c] : 1;
		t[ml].fail = v; t[ml].d = t[v].d + 1;
	}
	nl --; ans += t[ml].d;
	if(nr - nl + 1 == t[ml].len) mr = ml;
}
int main() {
	for(int q; ~ scanf("%d", &q); ) {
		init(); char s[5]; ans = 0;
		for(int op, i = 1; i <= q; i ++) {
			scanf("%d", &op);
			if(op == 1) scanf("%s", s), pushfront(*s - 'a');
			if(op == 2) scanf("%s", s), pushback(*s - 'a');
			if(op == 3) printf("%d\n", id - 1);
			if(op == 4) printf("%lld\n", ans);
		}
	}
	return 0;
}