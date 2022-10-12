#include <algorithm>
#include <complex>
#include <cstdio>
#include <cmath>
using namespace std;
typedef long long ll;
const int N = 262144 | 5;
const int mod = 998244353, _g = 3;
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
int fac[N], fav[N], bin[N];
int n, a[N], ans[N], A[N], B[N];
int C(int n, int m) {
	return n < m ? 0 : (ll) fac[n] * fav[m] % mod * fav[n - m] % mod;
}
int main() {
	fac[0] = 1;
	for(int i = 1; i < N; i ++) fac[i] = (ll) fac[i - 1] * i % mod;
	fav[N - 1] = qpow(fac[N - 1], mod - 2);
	for(int i = N - 1; i >= 1; i --) fav[i - 1] = (ll) fav[i] * i % mod;
	bin[0] = 1;
	for(int i = 1; i < N; i ++) bin[i] = (bin[i - 1] << 1) % mod;
	int test; scanf("%d", &test);
	while(test --) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i ++) scanf("%d", a + i);
		sort(a + 1, a + n + 1);
		reverse(a + 1, a + n + 1);
		InitNTT(n + n);
		A[0] = 0; B[0] = 1;
		for(int i = 1; i <= n; i ++) {
			A[i] = (ll) a[i] * fac[i - 1] % mod * bin[n - i] % mod;
			B[i] = fav[i];
		}
		reverse(B, B + n + 1);
		for(int i = n + 1; i < len; i ++) A[i] = B[i] = 0;
		NTT(A, w); NTT(B, w);
		for(int i = 0; i < len; i ++) A[i] = (ll) A[i] * B[i] % mod;
		NTT(A, inv_w);
		for(int i = 1; i <= n; i ++) ans[i] = (ans[i - 1] + (ll) A[i + n] * fav[i - 1]) % mod;
		for(int i = 1; i <= n; i ++) {
			printf("%d ", ans[i]);
		}
		puts("");
	}
	return 0;
}
