#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;
typedef long long ll;
const int N = 2e6 + 10, mod = 1e9 + 7, inv4 = (mod + 1) >> 2;
char s[N >> 1], t[N];
int n, f[N], c[N], l[N], r[N];
void upd(int &x, const int &y) {
	(x += y) >= mod ? x -= mod : 0;
}
void clr() { fill(c, c + n + 1, 0); }
void add(int l, int r, int v) {
	if(l > r) return ;
	upd(c[l], v); upd(c[r + 1], mod - v);
}
void getseq(int *arr) {
	for(int i = 1; i <= n; i ++) {
		arr[i] = arr[i - 1] + c[i];
		if(arr[i] >= mod) arr[i] -= mod;
	}
}
int main() {
	while(~ scanf("%s", s + 1)) {
		n = strlen(s + 1); t[1] = '#';
		for(int i = 1; i <= n; i ++) {
			t[i << 1] = s[i]; t[i << 1 | 1] = '#';
		}
		n = n << 1 | 1; t[n + 1] = '?';
		int mr = 0, mid = 0;
		for(int i = 1; i <= n; i ++) {
			f[i] = i < mr ? min(mr - i, f[2 * mid - i]) : 1;
			while(t[i + f[i]] == t[i - f[i]]) f[i] ++;
			if(f[i] + i > mr) { mr = i + f[i]; mid = i; }
		}
		clr();
		for(int i = 1; i <= n; i ++) if(f[i] ^ 1) {
			add(i - f[i] + 1, i - f[i] + 1, i + f[i] - 1);
			add(i - f[i] + 2, i, mod - 1);
			add(i + 1, i + 1, mod - i);
		}
		getseq(l);
		for(int i = 1; i <= n; i ++) upd(l[i], l[i - 1]);
		clr();
		for(int i = 1; i <= n; i ++) if(f[i] ^ 1) {
			add(i, i, i);
			add(i + 1, i + f[i] - 1, mod - 1);
			add(i + f[i], i + f[i], mod - (i - f[i] + 1));
		}
		getseq(r);
		for(int i = 1; i <= n; i ++) upd(r[i], r[i - 1]);
		int ans = 0;
		for(int i = 2; i <= n - 2; i += 2) {
			upd(ans, (ll) r[i] * l[i + 2] % mod * inv4 % mod);
		}
		printf("%d\n", ans);
	}
	return 0;
}