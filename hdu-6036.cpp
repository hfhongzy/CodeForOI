#include <algorithm>
#include <complex>
#include <cstdio>
#include <cmath>
using namespace std;
typedef long long ll;
const int N = 262144 | 5;
const int mod = 235 * (1 << 22) + 1, _g = 3;
int qpow(int a, int b) {
	int ans = 1;
	for(; b >= 1; b >>= 1, a = (ll) a * a % mod)
		if(b & 1) ans = (ll) ans * a % mod;
	return ans;
}
int rev[N], len;
ll w[N], inv_w[N];
void InitNTT(int n) {
	int k = 0;
	for(len = 1; len <= n; len <<= 1) k ++;
	for(int i = 1; i < len; i ++)
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
	w[0] = inv_w[0] = 1;
	ll v = qpow(_g, (mod - 1) / len);
	for(int i = 1; i < len; i ++)
		inv_w[len - i] = w[i] = w[i - 1] * v % mod;
}
void NTT(int *a, const ll *w) {
	for(int i = 1; i < len; i ++)
		if(i < rev[i]) swap(a[i], a[rev[i]]);
	for(int i = 1; i < len; i <<= 1) {
		for(int j = 0, t = len / (i << 1); j < len; j += i << 1) {
			const ll *wn = w;
			for(int k = j; k < j + i; k ++, wn += t) {
				ll t1 = a[k], t2 = *wn * a[k + i] % mod;
				a[k] = (t1 + t2) % mod; a[k + i] = (t1 - t2 + mod) % mod;
			}
		}
	}
	if(w == inv_w) {
		ll v = mod - (mod - 1) / len;
		for(int i = 0; i < len; i ++)
			a[i] = a[i] * v % mod;
	}
}
int fac[N], fav[N];
int s, m, n, a[N], A[N], B[N], f[N], g[N], ans[N];
int C(int n, int m) {
	return n < m ? 0 : (ll) fac[n] * fav[m] % mod * fav[n - m] % mod;
}
int _pw(int n) {
	return n & 1 ? mod - 1 : 1;
}
int main() {
	fac[0] = 1;
	for(int i = 1; i < N; i ++) fac[i] = (ll) fac[i - 1] * i % mod;
	fav[N - 1] = qpow(fac[N - 1], mod - 2);
	for(int i = N - 1; i >= 1; i --) fav[i - 1] = (ll) fav[i] * i % mod;
	int cas = 0;
	while(~ scanf("%d%d", &m, &n)) {
		s = 0;
		for(int i = 1; i <= m; i ++) {
			scanf("%*d%d", a + i); s += a[i];
		}
		g[0] = 0;
		for(int i = 1; i <= s; i ++) {
			g[i] = 1;
			for(int j = 1; j <= m; j ++) {
				g[i] = (ll) g[i] * C(a[j] + i - 1, i - 1) % mod;
			}
		}
		for(int i = 0; i <= s; i ++) A[i] = (ll) fav[i] * g[i] % mod;
		for(int i = 0; i <= s; i ++) B[i] = (ll) fav[i] * _pw(i) % mod;
		InitNTT(s + s);
		for(int i = s + 1; i < len; i ++) A[i] = B[i] = 0;
		NTT(A, w); NTT(B, w);
		for(int i = 0; i < len; i ++) A[i] = (ll) A[i] * B[i] % mod;
		NTT(A, inv_w);
		for(int i = 0; i <= s; i ++) f[i] = (ll) A[i] * fac[i] % mod;
		fill(ans, ans + n + 1, 0); f[s + 1] = 0;
		for(int i = 1; i <= s; i ++) {
			int inv = qpow(f[i], mod - 2);
			int t1 = 1, t2 = qpow(f[i], n);
			for(int j = 1; j <= n; j ++) {
				(ans[j] += (ll) t1 * t2 % mod) %= mod;
				t1 = (ll) t1 * f[i + 1] % mod;
				t2 = (ll) t2 * inv % mod;
			}
		}
		printf("Case #%d:", ++ cas);
		for(int i = 1; i <= n; i ++)
			printf(" %d", ans[i]);
		puts("");
	}
	return 0;
}
