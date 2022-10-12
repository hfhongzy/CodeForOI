#include <cstdio>
typedef long long ll;
const int N = 55;
int n, k;
ll a[N], f[N];
bool chk(ll x) {
	if(x > a[n]) return 0;
	f[0] = 1;
	for(int i = 1; i <= n; i ++) {
		f[i] = 0;
		for(int j = 0; j < i; j ++) if(((a[i] - a[j]) & x) == x) {
			f[i] |= f[j] << 1;
		}
	}
	return f[n] >> k & 1;
}
int main() {
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i ++) {
		scanf("%lld", a + i); a[i] += a[i - 1];
	}
	ll ans = 0;
	for(int i = 60; i >= 0; i --)
		if(chk(ans ^ (1ll << i))) ans ^= 1ll << i;
	printf("%lld\n", ans);
	return 0;
}