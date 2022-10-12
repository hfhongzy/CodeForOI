#include <algorithm>
#include <cstdio>
using namespace std;
const int mod = 1e9 + 7, N = 1e5 + 10;
int lim, n, m, A[N];
void fwtxor(int *a) {
	for(int i = 1; i < lim; i <<= 1)
		for(int j = 0; j < lim; j += i << 1)
			for(int k = 0; k < i; k ++) {
				int p = a[j + k], q = a[j + k + i];
				a[j + k] = (p + q) % mod; a[j + k + i] = (p - q + mod) % mod;
			}
}
void Ifwtxor(int *a) {
	const long long inv2 = (mod + 1) >> 1;
	for(int i = 1; i < lim; i <<= 1)
		for(int j = 0; j < lim; j += i << 1)
			for(int k = 0; k < i; k ++) {
				int p = a[j + k], q = a[j + k + i];
				a[j + k] = (p + q) * inv2 % mod; a[j + k + i] = (p - q + mod) * inv2 % mod;
			}
}
int p[N], c;
bool tag[N];
void sieve(int n) {
	for(int i = 2; i <= n; i ++) {
		if(!tag[i]) p[++ c] = i;
		for(int j = 1; j <= c && i * p[j] <= n; j ++) {
			tag[i * p[j]] = 1;
			if(i % p[j] == 0) break ;
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
	sieve(5e4);
	while(~ scanf("%d%d", &n, &m)) {
		for(lim = 1; lim <= m; lim <<= 1) ;
		fill(A, A + lim, 0);
		for(int i = 1; i <= c && p[i] <= m; i ++) A[p[i]] = 1;
		fwtxor(A);
		for(int i = 0; i < lim; i ++) A[i] = qpow(A[i], n);
		Ifwtxor(A);
		printf("%d\n", A[0]);
	}
	return 0;
}