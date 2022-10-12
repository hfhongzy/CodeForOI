#include <algorithm>
#include <cstdio>
using namespace std;
typedef long long ll;
const int N = 1e7 + 10;
int n, p[N], mu[N];
ll f[N];
bool tag[N];
void sieve(int n) {
	mu[1] = 1;
	for(int i = 2; i <= n; i ++) {
		if(!tag[i]) p[++ p[0]] = i, mu[i] = -1;
		for(int j = 1; j <= p[0] && p[j] * i <= n; j ++) {
			int t = i * p[j]; tag[t] = 1;
			if(i % p[j] == 0) { mu[t] = 0; break ; }
			mu[t] = - mu[i];
		}
	}
	f[1] = 1;
	for(int i = 1; i * i <= n; i ++)
		for(int j = i * i; j <= n; j += i * i)
			f[j] -= mu[j / (i * i)];
	for(int i = 2; i <= n; i ++) f[i] += f[i - 1], mu[i] += mu[i - 1];
}
int main() {
	sieve(N - 1);
	int test;
	scanf("%d", &test);
	while(test --) {
		int n, m;
		scanf("%d%d", &n, &m);
		if(n > m) swap(n, m);
		ll ans = 0;
		for(int i = 1, j; i <= n; i = j + 1) {
			j = min(n / (n / i), m / (m / i));
			ans += (f[j] - f[i - 1]) * (n / i) * (m / i);
		}
		printf("%lld\n", ans);
	}
	return 0;
}