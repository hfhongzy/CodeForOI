#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 8e5 + 10;
char str[N];
int id, n, ql[N], qr[N], la, nxt[N][27], len[N], lnk[N], a[N], c[N][2];
void clr(int x) { fill(nxt[x], nxt[x] + 27, -1); }
void init() { lnk[0] = -1; clr(0); }
void extend(int c, int bel) {
	int u = ++ id, p = la;
	len[u] = len[la] + 1; clr(u);
	for(; ~ p && -1 == nxt[p][c]; p = lnk[p]) {
		nxt[p][c] = u;
	}
	if(p == -1) ;
	else {
		int q = nxt[p][c];
		if(len[p] + 1 == len[q]) {
			lnk[u] = q;
		} else {
			int q0 = ++ id;
			copy(nxt[q], nxt[q] + 27, nxt[q0]);
			len[q0] = len[p] + 1; lnk[q0] = lnk[q];
			lnk[q] = lnk[u] = q0;
			for(; ~ p && nxt[p][c] == q; p = lnk[p]) {
				nxt[p][c] = q0;
			}
		}
	}
	la = u;
	if(~ bel) ::c[u][bel] = 1;
}
void tpo() {
	static int cnt[N];
	int n = len[la];
	for(int i = 1; i <= id; i ++) cnt[len[i]] ++;
	for(int i = 1; i <= n; i ++) cnt[i] += cnt[i - 1];
	for(int i = 1; i <= id; i ++) a[cnt[len[i]] --] = i;
}
int main() {
	freopen("input", "r", stdin);
	scanf("%s", str); init();
	for(int i = 0; str[i]; i ++) extend(str[i] - 'a', 0);
	scanf("%s", str); extend(26, -1);
	for(int i = 0; str[i]; i ++) extend(str[i] - 'a', 1);
	tpo();
	long long ans = 0;
	for(int i = id; i >= 1; i --) {
		int u = a[i], f = lnk[u];
		c[f][0] += c[u][0]; c[f][1] += c[u][1];
		ans += 1ll * c[u][1] * c[u][0] * (len[u] - len[f]);
	}
	printf("%lld\n", ans);
	return 0;
}