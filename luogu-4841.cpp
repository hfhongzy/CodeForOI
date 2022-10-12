#include <algorithm>
#include <cstdio>
using namespace std;
typedef long long ll;
const int N = 1 << 21 | 5;
const int mod = 1004535809;
const int g = 3;
int rev[N], len;
ll w[N], inv_w[N], inv[N], fac[N], fav[N];
ll qpow(ll a, ll b) {
	ll ans = 1;
	for(; b >= 1; b >>= 1, a = (ll) a * a % mod)
		if(b & 1) ans = (ll) ans * a % mod;
	return ans;
}
void Init(int n) {
	fac[0] = fav[0] = 1;
	for(int i = 1; i <= n; i ++) {
		inv[i] = i == 1 ? 1 : ( - (mod / i) * inv[mod % i] % mod );
		fac[i] = fac[i - 1] * i % mod;
		fav[i] = fav[i - 1] * inv[i] % mod;
	}
}
void InitNTT(int n) {
	int k = 0;
	for(len = 1; len <= n; len <<= 1) k ++;
	for(int i = 1; i < len; i ++)
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
	w[0] = inv_w[0] = 1;
	ll v = qpow(g, (mod - 1) / len);
	for(int i = 1; i < len; i ++)
		inv_w[len - i] = w[i] = w[i - 1] * v % mod;
}
void NTT(ll *a, const ll *w) {
	for(int i = 1; i < len; i ++)
		if(i < rev[i]) swap(a[i], a[rev[i]]);
	for(int i = 1; i < len; i <<= 1) {
		for(int j = 0, t = len / (i << 1); j < len; j += i << 1) {
			const ll *wn = w;
			for(int k = j; k < j + i; k ++, wn += t) {
				ll t1 = a[k], t2 = *wn * a[k + i] % mod;
				a[k] = (t1 + t2) % mod; a[k + i] = (t1 - t2) % mod;
			}
		}
	}
	if(w == inv_w)
		for(int i = 0, v = - (mod - 1) / len; i < len; i ++)
			(a[i] *= v) %= mod;
}
void cpyto(const ll *from, ll *to, int n) {
	for(int i = 0; i < n; i ++) to[i] = from[i];
	for(int i = n; i < len; i ++) to[i] = 0;
}
//AB = 1 (mod x^n), b[n], b[n + 1], ... will not be modified
void Inv(const ll *a, int n, ll *b) {
	if(n == 1) { b[0] = qpow(a[0], mod - 2); return ; }
	int m = (n + 1) >> 1; Inv(a, m, b);
	static ll ta[N], tb[N]; InitNTT(n * 2);
	cpyto(a, ta, n); cpyto(b, tb, m);
	NTT(ta, w); NTT(tb, w);
	for(int i = 0; i < len; i ++)
		(tb[i] *= 2 - tb[i] * ta[i] % mod) %= mod;
	NTT(tb, inv_w);
	for(int i = 0; i < n; i ++) b[i] = tb[i];
}
//Ln(A(x)) = B(x) (mod x^n)
void Ln(const ll *a, int n, ll *b) {
	static ll t1[N], t2[N];
	Inv(a, n, t1); InitNTT(n * 2);
	for(int i = n; i < len; i ++) t1[i] = 0;
	for(int i = 1; i < n; i ++) t2[i - 1] = a[i] * i % mod;
	for(int i = n - 1; i < len; i ++) t2[i] = 0;
	NTT(t1, w); NTT(t2, w);
	for(int i = 0; i < len; i ++) (t1[i] *= t2[i]) %= mod;
	NTT(t1, inv_w); b[0] = 0;
	for(int i = 1; i < n; i ++) b[i] = t1[i - 1] * inv[i] % mod;
}
int main() {
	int n;
	static ll F[N], G[N];
	scanf("%d", &n); Init(++ n);
	for(int i = 0; i < n; i ++) G[i] = qpow(2, i * (i - 1ll) / 2) * fav[i] % mod;
	Ln(G, n, F); n --; F[n] = (F[n] + mod) % mod;
	printf("%lld\n", F[n] * fac[n] % mod);
	return 0;
}