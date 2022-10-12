#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;
const int N = 1e6 + 10, mod = 998244353;
char a[N], l[N], r[N], s1[N + N], s2[N + N];
int ql[N], qr[N], na, nl, nr, n1, n2, z1[N + N], z2[N + N], p[N], dp[N], nxt[N];
int upd(const int &x) { return x >= mod ? x - mod : x; }
void upd(int &x, const int &y) { (x += y) >= mod ? x -= mod : 0; }
int sumf(int l, int r) { return upd(p[r] + (l == 0 ? 0 : mod - p[l - 1])); }
void init(int *z, char *s, int &n, const int &nl, const char *s0) {
	n = nl + na;
	for(int i = 1; i <= nl; i ++) s[i] = s0[i];
	for(int i = nl + 1; i <= n; i ++) s[i] = a[i - nl];
	for(int i = 2, mid = 0, r = 0; i <= n; i ++) {
		z[i] = i < r ? min(r - i + 1, z[i - mid + 1]) : 0;
		while(s[z[i] + 1] == s[i + z[i]]) z[i] ++;
		if(i + z[i] - 1 > r) { r = i + z[i] - 1; mid = i; }
	}
}
bool limL(int l, int r) {
	l = min(r, nxt[l]);
	if(r - l + 1 != nl) return r - l + 1 > nl;
	int x = min(nl, z1[nl + l]);
	return x == nl ? 1 : a[l + x] >= ::l[x + 1];
}
bool limR(int l, int r) {
	l = min(r, nxt[l]);
	if(r - l + 1 != nr) return r - l + 1 < nr;
	int x = min(nr, z2[nr + l]);
	return x == nr ? 1 : a[l + x] <= ::r[x + 1];
}
int main() {
	scanf("%s%s%s", a + 1, l + 1, r + 1);
	na = strlen(a + 1); nl = strlen(l + 1); nr = strlen(r + 1);
	init(z1, s1, n1, nl, l); init(z2, s2, n2, nr, r);
	for(int i = na; i >= 1; i --) nxt[i] = (i == na || a[i] != '0') ? i : nxt[i + 1];
	ql[0] = N; qr[0] = -1;
	for(int i = 1; i <= na; i ++) {
		if(!limR(i, i)) ql[i] = N;
		else {
			ql[i] = min(ql[i - 1], i);
			while(ql[i] < i && !limR(ql[i], i)) ql[i] ++;
		}
		if(!limL(1, i)) qr[i] = 0;
		else {
			qr[i] = max(qr[i - 1], 1);
			while(qr[i] < i && limL(qr[i] + 1, i)) qr[i] ++;
		}
	}
	dp[0] = p[0] = 1;
	for(int i = 1; i <= na; i ++) {
		if(ql[i] <= qr[i]) dp[i] = sumf(ql[i] - 1, qr[i] - 1);
		if(a[i] == '0' && l[1] == '0') upd(dp[i], dp[i - 1]);
		p[i] = p[i - 1];
		if(a[i + 1] != '0') upd(p[i], dp[i]);
	}
	printf("%d\n", dp[na]);
	return 0;
}