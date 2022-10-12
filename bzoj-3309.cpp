#include <algorithm>
#include <cstdio>
using namespace std;
typedef long long ll;
const int N = 1e7 + 5;
int p[N], pc, mu[N], pw[N], pp[N], g[N];
bool tag[N];
void sieve() {
	mu[1] = 1;
	for(int i = 2; i < N; i ++) {
		if(!tag[i]) { p[++ pc] = i; mu[i] = -1; pw[i] = 1; pp[i] = i; }
		if(i == pp[i]) g[i] = 1;
		else if(pw[i / pp[i]] == pw[i]) g[i] = - g[i / pp[i]];
		else g[i] = 0;
		for(int j = 1; j <= pc; j ++) {
			int t = i * p[j];
			if(t >= N) break ;
			tag[t] = 1;
			if(i % p[j] == 0) {
				pw[t] = pw[i] + 1; pp[t] = pp[i] * p[j]; mu[t] = 0;
				break ;
			}
			pw[t] = 1; pp[t] = p[j]; mu[t] = - mu[i];
		}
	}
	for(int i = 1; i < N; i ++) g[i] += g[i - 1];
}
int main() {
	sieve();
	int test; scanf("%d", &test);
	while(test --) {
		int n, m;
		scanf("%d%d", &n, &m);
		if(n > m) swap(n, m);
		ll ans = 0;
		for(int i = 1, j; i <= n; i = j + 1) {
			j = min(n / (n / i), m / (m / i));
			ans += (ll) (g[j] - g[i - 1]) * (n / i) * (m / i);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
/*
\sum T {1 to n} (n/T) (m/T) (f * mu) [T]
g(n) \sum_{d | n} f[d] mu[n / d]
g(n p^k), gcd(n, p) != 1:
g[n] + \sum_{d | n} \sum_{p, .., p^k} f[d p^i] mu[n / d p^{k-i}]
*/