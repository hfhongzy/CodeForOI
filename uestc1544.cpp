#include <algorithm>
#include <cstdio>
using namespace std;
typedef long long ll;
const int N = 20;
int n, m;
ll a[N], f[N];
ll C(ll n, ll m) {
	if(n < m) return 0ll;
	ll res = 1;
	for(ll i = n; i > n - m; i --) res *= i;
	for(ll i = 1; i <= m; i ++) res /= i;
	return res;
}
ll gcd(ll a, ll b) {
	return b == 0 ? a : gcd(b, a % b);
}
ll lcm(ll a, ll b) {
	return a / gcd(a, b) * b;
}
int main() {
	int test;
	scanf("%d", &test);
	while(test --) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= m; i ++) scanf("%lld", a + i);
		f[1] = 1;
		for(int i = 2; i <= m; i ++) {
			f[i] = i & 1;
			for(int j = 1; j < i; j ++) f[i] -= C(i, j) * f[j];
		}
		ll ans = 0;
		for(int i = 1; i < (1 << m); i ++) {
			ll x = 1; int sz = 0;
			for(int j = 0; j < m; j ++) if(i >> j & 1) {
				x = lcm(x, a[j + 1]); sz ++;
			}
			ans += f[sz] * (n / x);
		}
		printf("%lld\n", ans);
	}
	return 0;
}