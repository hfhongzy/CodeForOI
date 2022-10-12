#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 5e5 + 10, mod = 1e9 + 7;
int n, m, pc, p[N], mu[N], pw[N], pws[N];
bool tag[N];
void sieve(int n) {
	mu[1] = 1;
	for(int i = 2; i <= n; i ++) {
		if(!tag[i]) { p[++ pc] = i; mu[i] = -1; }
		for(int j = 1; j <= pc && p[j] * i <= n; j ++) {
			int t = i * p[j]; tag[t] = 1;
			if(i % p[j] == 0) { mu[t] = 0; break ; }
			mu[t] = - mu[i];
		}
	}
}
int qpow(int a, int b) {
	int ans = 1;
	for(; b >= 1; b >>= 1, a = 1ll * a * a % mod)
		if(b & 1) ans = 1ll * ans * a % mod;
	return ans;
}
int main() {
	scanf("%d%d", &n, &m);
	if(n > m) swap(n, m);
	sieve(m);
	int ans = 0;
	for(int i = 1; i <= m; i ++) pw[i] = 1;
	for(int i = 1; i <= n; i ++) {
		for(int j = 1; j <= m / i; j ++) {
			pw[j] = 1ll * pw[j] * j % mod;
			pws[j] = (pws[j - 1] + pw[j]) % mod;
		}
		int r = 0;
		for(int j = 1; j <= n / i; j ++) if(mu[j]) {
			int t1 = 1ll * pws[n / i / j] * pw[j] % mod;
			int t2 = 1ll * pws[m / i / j] * pw[j] % mod;
			if(mu[j] == 1) (r += 1ll * t1 * t2 % mod) %= mod;
			else (r -= 1ll * t1 * t2 % mod) %= mod;
		}
		(ans += 1ll * r * qpow(i, i) % mod) %= mod;
	}
	printf("%d\n", (ans + mod) % mod);
	return 0;
}