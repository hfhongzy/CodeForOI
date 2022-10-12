#include <algorithm>
#include <cstdio>
using namespace std;
const int mod = 1e8 + 7, N = 1010;
int n, a[N], cnt[N], p[N], mu[N], pw[N], f[N];
bool tag[N];
void sieve(int n) {
	mu[1] = 1;
	for(int i = 2; i <= n; i ++) {
		if(!tag[i]) p[++ p[0]] = i, mu[i] = -1;
		for(int j = 1; j <= p[0] && p[j] * i <= n; j ++) {
			tag[i * p[j]] = 1;
			if(i % p[j] == 0) {
				mu[i * p[j]] = 0;
				break ;
			}
			mu[i * p[j]] = - mu[i];
		} 
	}
}
int main() {
	pw[0] = 1;
	for(int i = 1; i < N; i ++)
		pw[i] = (pw[i - 1] + pw[i - 1]) % mod;
	sieve(N - 1);
	int test;
	scanf("%d", &test);
	while(test --) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i ++) {
			scanf("%d", a + i); cnt[a[i]] ++;
		}
		int m = *max_element(a + 1, a + n + 1), ans = 0;
		for(int i = 1; i <= m; i ++) {
			for(int j = i; j <= m; j += i) {
				f[i] += cnt[j];
			}
		}
		for(int i = 1; i <= m; i ++) {
			int r = 0;
			for(int j = 1; i * j <= m; j ++) if(mu[j]) {
				if(mu[j] == 1) r += pw[f[i * j]] - 1;
				else r += mod - pw[f[i * j]] + 1;
				r %= mod;
			}
			(ans += 1ll * r * i % mod) %= mod;
		}
		printf("%d\n", (ans + mod) % mod);
		fill(cnt, cnt + m + 1, 0);
		fill(f, f + m + 1, 0);
	}
	return 0;
}
//\sum_{d = 1} d \sum_{p1, p2, pk} [gcd(a[p1], a[p2], a[pk]) = d]
//\sum_{d = 1} d \sum_{p1, p2, pk} [gcd(a[p1]/d, a[p2]/d, a[pk]/d) = 1]
//\sum_{d = 1} d \sum_{p1, p2, pk} \sum_{d'} \mu(d') [d' | (a[p1]/d), d' | ..]
//\sum_{d = 1} d \sum_{d'} \mu(d') [d' | (a[p1]/d), d' | ..]