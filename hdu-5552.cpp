#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;
typedef long long ll;
const int N = 2e4 + 10, mod = 152076289, _g = 106;
int qpow(int a, int b) {
	int ans = 1;
	for(; b >= 1; b >>= 1, a = (ll) a * a % mod)
		if(b & 1) ans = (ll) ans * a % mod;
	return ans;
}
int rev[N], len, w[N], inv_w[N];
void InitNTT(int n) {
	int k = 0;
	for(len = 1; len <= n; len <<= 1) k ++;
	for(int i = 1; i < len; i ++)
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
	w[0] = inv_w[0] = 1;
	int v = qpow(_g, (mod - 1) / len);
	for(int i = 1; i < len; i ++)
		inv_w[len - i] = w[i] = 1ll * w[i - 1] * v % mod;
}
void NTT(int *a, const int *w) {
	for(int i = 1; i < len; i ++)
		if(i < rev[i]) swap(a[i], a[rev[i]]);
	for(int i = 1; i < len; i <<= 1) {
		for(int j = 0, t = len / (i << 1); j < len; j += i << 1) {
			const int *wn = w;
			for(int k = j; k < j + i; k ++, wn += t) {
				int t1 = a[k], t2 = 1ll * *wn * a[k + i] % mod;
				a[k] = (t1 + t2) % mod; a[k + i] = (t1 - t2 + mod) % mod;
			}
		}
	}
	if(w == inv_w) {
		int v = mod - (mod - 1) / len;
		for(int i = 0; i < len; i ++)
			a[i] = 1ll * a[i] * v % mod;
	}
}
int fac[N], fav[N], f[N], n = 1e4, m, A[N], B[N];
int C2(int n) { return n * (n - 1) / 2; }

void solve(int l, int r) {
	if(l == r) {
		f[l] = (1ll * f[l] * fac[l - 1] + qpow(m + 1, C2(l))) % mod;
		return ;
	}
	int mid = (l + r) >> 1;
	solve(l, mid);
	InitNTT(r - l);
	for(int i = 0; i < len; i ++) A[i] = l + i <= mid ? 1ll * f[l + i] * fav[l + i - 1] % mod : 0;
	for(int i = 0; i < len; i ++) B[i] = i <= r - l ? 1ll * qpow(m + 1, C2(i)) * fav[i] % mod : 0;
	NTT(A, w); NTT(B, w);
	for(int i = 0; i < len; i ++) A[i] = 1ll * A[i] * B[i] % mod;
	NTT(A, inv_w);
	for(int i = mid + 1; i <= r; i ++) (f[i] += mod - A[i - l]) %= mod;
	solve(mid + 1, r);
}
int main() {
	fac[0] = 1;
	for(int i = 1; i <= n; i ++) fac[i] = (ll) fac[i - 1] * i % mod;
	fav[n] = qpow(fac[n], mod - 2);
	for(int i = n; i >= 1; i --) fav[i - 1] = (ll) fav[i] * i % mod;
	int test; scanf("%d", &test);
	for(int t = 1; t <= test; t ++) {
		scanf("%d%d", &n, &m); m %= mod;
		if(n < 3) {
			printf("Case #%d: %d\n", t, 0);
			continue ;
		}
		for(int i = 0; i <= n; i ++) f[i] = 0;
		solve(1, n);
		// printf("f = %d\n", f[n]);
		printf("Case #%d: %d\n", t, (f[n] - 1ll * qpow(n, n - 2) * qpow(m, n - 1) % mod + mod) % mod);
	}
	return 0;
}