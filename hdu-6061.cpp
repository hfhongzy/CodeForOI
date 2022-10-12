#include <algorithm>
#include <complex>
#include <cstdio>
#include <cmath>
using namespace std;
typedef long long ll;
const int N = 4e5 + 10;
const int mod = 998244353, g = 3;
int qpow(int a, int b) {
	int ans = 1;
	for(; b >= 1; b >>= 1, a = (ll) a * a % mod)
		if(b & 1) ans = (ll) ans * a % mod;
	return ans;
}
int fac[N], fav[N];
namespace poly {

int rev[N], len;
void init(int n) {
	int k = 0;
	for(len = 1; len <= n; len <<= 1) k ++;
	for(int i = 1; i < len; i ++)
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
}
void ntt(int *a, int ty) {
	for(int i = 1; i < len; i ++)
		if(i < rev[i]) swap(a[i], a[rev[i]]);
	for(int i = 1; i < len; i <<= 1) {
		int wn = qpow(g, (mod - 1) / (i << 1));
		if(ty == -1) wn = qpow(wn, mod - 2);
		for(int j = 0; j < len; j += i << 1) {
			for(int k = j, w = 1; k < j + i; k ++, w = (ll) w * wn % mod) {
				int t1 = a[k], t2 = (ll) w * a[k + i] % mod;
				a[k] = (t1 + t2) % mod; a[k + i] = (t1 - t2 + mod) % mod;
			}
		}
	}
	if(ty == -1) {
		ty = qpow(len, mod - 2);
		for(int i = 0; i < len; i ++)
			a[i] = (ll) a[i] * ty % mod;
	}
}

}
int n, m, c[N], a[N], b[N];
int main() {
	fac[0] = 1;
	for(int i = 1; i < N; i ++) fac[i] = (ll) fac[i - 1] * i % mod;
	fav[N - 1] = qpow(fac[N - 1], mod - 2);
	for(int i = N - 1; i >= 1; i --) fav[i - 1] = (ll) fav[i] * i % mod;
	while(~ scanf("%d", &n)) {
		for(int i = 0; i <= n; i ++) scanf("%d", c + i);
		poly::init(n << 1); scanf("%d", &m); int k = 0;
		for(int i = 1; i <= m; i ++) {
			int x; scanf("%d", &x); (k += x) %= mod;
		}
		k = (mod - k) % mod;
		int pwk = 1;
		for(int i = 0; i <= n; i ++) {
			a[i] = (ll) fac[i] * c[i] % mod;
			b[i] = (ll) fav[i] * pwk % mod;
			pwk = (ll) pwk * k % mod;
		}
		reverse(b, b + n + 1);
		for(int i = n + 1; i < poly::len; i ++) a[i] = b[i] = 0;
		poly::ntt(a, 1); poly::ntt(b, 1);
		for(int i = 0; i < poly::len; i ++) a[i] = (ll) a[i] * b[i] % mod;
		poly::ntt(a, -1);
		for(int i = 0; i <= n; i ++) {
			printf("%d%c", int((ll) a[i + n] * fav[i] % mod), ' ');
		}
		puts("");
	}
	return 0;
}
//a[i] b[j] c[i + j]
//b[n - j]