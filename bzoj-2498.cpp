#include <algorithm>
#include <complex>
#include <cstdio>
#include <cmath>
using namespace std;
typedef long long ll;
typedef long double db;
typedef complex<db> comp;
const db pi = acos(-1);
const int N = 65536 + 10;
namespace fft {

int rev[N], len;
void init(int n) {
	int k = 0;
	for(len = 1; len <= n; len <<= 1) k ++;
	for(int i = 1; i < len; i ++)
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
}
void fft(comp *a, int ty) {
	for(int i = 1; i < len; i ++)
		if(i < rev[i]) swap(a[i], a[rev[i]]);
	for(int i = 1; i < len; i <<= 1) {
		comp wn(cos(pi / i), ty * sin(pi / i)), w, t1, t2;
		for(int j = 0; j < len; j += i << 1) {
			w = comp(1, 0);
			for(int k = j; k < j + i; k ++, w *= wn) {
				t1 = a[k], t2 = w * a[k + i];
				a[k] = t1 + t2; a[k + i] = t1 - t2;
			}
		}
	}
	if(ty == -1)
		for(int i = 0; i < len; i ++)
			a[i] /= len;
}

}
comp poly[5][N], ans[N];
int m, p, mx, sz, a[N], s[6];
ll f[6], fac[6];
void dfs(int u) {
	if(u == p + 1) {
		ll cur = 1;
		for(int i = 1; i <= sz; i ++) cur *= f[s[i]];
		for(int i = 0; i < fft::len; i ++) {
			comp t = comp(cur, 0);
			for(int j = 1; j <= sz; j ++) {
				t *= poly[s[j] - 1][i];
			}
			ans[i] += t;
		}
		return ;
	}
	for(int i = 1; i <= sz; i ++) {
		s[i] ++; dfs(u + 1); s[i] --;
	}
	sz ++; s[sz] = 1; dfs(u + 1); sz --;
}

int main() {
	f[1] = 1; fac[1] = 1;
	for(int i = 2; i <= 5; i ++) {
		f[i] = f[i - 1] * (1 - i);
		fac[i] = fac[i - 1] * i;
	}
	int test; scanf("%d", &test);
	for(int T = 1; T <= test; T ++) {
		printf("Case #%d:\n", T);
		scanf("%d%d", &m, &p); mx = 0;
		for(int i = 1; i <= m; i ++) {
			scanf("%d", a + i); mx = max(mx, a[i]);
		}
		mx *= p; fft::init(mx);
		fill(ans, ans + fft::len, comp(0, 0));
		for(int i = 1; i <= p; i ++) {
			for(int j = 0; j < fft::len; j ++) {
				poly[i - 1][j] = comp(0, 0);
			}
			for(int j = 1; j <= m; j ++) {
				poly[i - 1][a[j] * i] = comp(1, 0);
			}
			fft::fft(poly[i - 1], 1);
		}
		dfs(1); fft::fft(ans, -1);
		for(int i = 1; i <= mx; i ++) {
			db t = ans[i].real() / fac[p];
			if(t > 0.5) printf("%d: %lld\n", i, (ll) (t + 0.5));
		}
		puts("");
	}
	return 0;
}