#include <algorithm>
#include <complex>
#include <cstdio>
#include <cmath>
using namespace std;
typedef long long ll;
const int N = 262144 | 5;
const int mod = 3 * (1 << 18) + 1, _g = 10;
int qpow(int a, int b) {
	int ans = 1;
	for(; b >= 1; b >>= 1, a = (ll) a * a % mod)
		if(b & 1) ans = (ll) ans * a % mod;
	return ans;
}
namespace ntt {

int rev[N], len, inv_len, omega[N];
void init(int n) {
	int k = 0;
	for(len = 1; len <= n; len <<= 1) k ++;
	for(int i = 1; i < len; i ++)
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
	omega[0] = 1; omega[1] = qpow(_g, (mod - 1) / len);
	for(int i = 2; i < len; i ++) omega[i] = (ll) omega[i - 1] * omega[1] % mod;
	inv_len = qpow(len, mod - 2);
}
void ntt(int *a, int ty) {
	for(int i = 1; i < len; i ++)
		if(i < rev[i]) swap(a[i], a[rev[i]]);
	for(int i = 1; i < len; i <<= 1) {
		for(int j = 0; j < len; j += i << 1) {
			for(int k = j; k < j + i; k ++) {
				int t = len / (i << 1) * (k - j);
				int t1 = a[k], t2 = omega[ty] * a[k + i] % mod;
				a[k] = (t1 + t2) % mod; a[k + i] = (t1 - t2 + mod) % mod;
			}
		}
	}
	if(ty == -1) {
		for(int i = 0; i < len; i ++)
			a[i] = (ll) a[i] * inv_len % mod;
	}
}

}
int k, n, m, poly[11][N], ans[N], fac[N], fav[N], t[N], cnt0[N], inv[mod];
char g[11][N];
void build(int u) {
	for(int i = 0; i < ntt::len; i ++) poly[u][i] = 0;
	for(int i = 0; i <= n; i ++) if(g[u][i]) poly[u][i] = fav[i];
	ntt::ntt(poly[u], 1);
}
ll Omega(ll k) {
	return ntt::omega[k % ntt::len];
}
int main() {
	const int nn = 14000 * 9;
	fac[0] = 1;
	for(int i = 1; i <= nn; i ++) fac[i] = (ll) fac[i - 1] * i % mod;
	fav[nn] = qpow(fac[nn], mod - 2);
	for(int i = nn; i >= 1; i --) fav[i - 1] = (ll) fav[i] * i % mod;
	inv[1] = 1;
	for(int i = 2; i < mod; i ++) {
		inv[i] = (ll) (mod - mod / i) * inv[mod % i] % mod;
	}
	int test; scanf("%d", &test);
	while(test --) {
		scanf("%d%d%d", &k, &n, &m);
		for(int i = 1; i < k; i ++) {
			scanf("%s", g[i]);
			for(int j = 0; j <= n; j ++)
				g[i][j] ^= '0';
		}
		ntt::init(n * (k - 1));
		for(int i = 1; i < k; i ++) build(i);
		for(int i = 0; i < ntt::len; i ++) {
			t[i] = 1; cnt0[i] = 0;
			for(int j = 1; j < k; j ++) {
				if(!poly[j][i]) cnt0[i] ++;
				else t[i] = (ll) t[i] * poly[j][i] % mod;
			}
			ans[i] = cnt0[i] ? 0 : t[i];
		}
		for(int x, y, i = 1; i <= m; i ++) {
			scanf("%d%d", &x, &y); g[x][y] ^= 1;
			for(int j = 0; j < ntt::len; j ++) {
				if(!poly[x][j]) cnt0[j] --;
				else t[j] = (ll) t[j] * inv[poly[x][j]] % mod;
				if(g[x][y] == 1) {
					poly[x][j] += fav[y] * Omega((ll) j * y) % mod;
				} else {
					poly[x][j] -= fav[y] * Omega((ll) j * y) % mod;
				}
				(poly[x][j] += mod) %= mod;
				if(!poly[x][j]) cnt0[j] ++;
				else t[j] = (ll) t[j] * poly[x][j] % mod;
				(ans[j] += cnt0[j] ? 0 : t[j]) %= mod;
			}
		}
		ntt::ntt(ans, -1);
		int res = 0;
		for(int i = 1; i <= n * (k - 1); i ++) {
			(res += (ll) fac[i] * ans[i] % mod) %= mod;
		}
		printf("%d\n", res);
	}
	return 0;
}
//T O(k^2nlog(nk) + mnk)