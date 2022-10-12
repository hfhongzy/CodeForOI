#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;
typedef long long ll;
const int N = 2e5 + 10, mod = 998244353, _g = 3;
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
int fac[N], fav[N], f[N], n = 1e5, A[N], B[N];
void solve(int l, int r) {
	if(l == r) {
		if(l == 0) {
			f[0] = 1;
		} else {
			f[l] = 1ll * f[l] * fac[l - 1] % mod;
		}
		return ;
	}
	int mid = (l + r) >> 1;
	solve(l, mid);
	InitNTT(r - l);
	for(int i = 0; i < len; i ++) A[i] = l + i <= mid ? 1ll * f[l + i] * fav[l + i] % mod : 0;
	for(int i = 0; i < len; i ++) B[i] = i <= r - l ? 1ll * i * i % mod : 0;
	NTT(A, w); NTT(B, w);
	for(int i = 0; i < len; i ++) A[i] = 1ll * A[i] * B[i] % mod;
	NTT(A, inv_w);
	for(int i = mid + 1; i <= r; i ++) (f[i] += A[i - l]) %= mod;
	solve(mid + 1, r);
}
int main() {
	fac[0] = 1;
	for(int i = 1; i <= n; i ++) fac[i] = (ll) fac[i - 1] * i % mod;
	fav[n] = qpow(fac[n], mod - 2);
	for(int i = n; i >= 1; i --) fav[i - 1] = (ll) fav[i] * i % mod;
	solve(0, n);
	while(~ scanf("%d", &n)) {
		printf("%d\n", f[n]);
	}
	return 0;
}
/*
f[n]表示1 ~ n的答案, f[0] = 1
f[n] = fac[n - 1] \sum_{i = 0}^{n - 1} f[i] fav[i] (n - i)^2
f:1 5 31
*/