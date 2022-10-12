#include <algorithm>
#include <cstdio>
using namespace std;
typedef long long ll;
const int p = 1e9 + 9, p1 = 998244353, N = 1e6 + 10;
int n, m, ans[N];
char str[N];
ll a[N];
ll _10(ll x) {
	const ll mod = (ll) p * p1;
	ll y = x * 5ll % mod;
	return (y + y) % mod;
}
ll read() {
	const ll mod = (ll) p * p1;
	ll x = 0; bool mark = 0;
	for(int i = 1; str[i]; i ++) {
		if(str[i] == '-') mark = 1;
		else x = (x * 10 + str[i] - '0') % p;
	}
	return mark ? mod - x : x;
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i <= n; i ++) {
		scanf("%s", str + 1); a[i] = read();
	}
	for(int x = 1; x <= m; x ++) {
		ll h1 = 0, h2 = 0;
		for(int i = n; i >= 1; i --)
			h1 = (h1 + a[i]) * x % p;
		h1 = (h1 + a[0]) % p;
		if(h1 == 0) ans[++ ans[0]] = x;
		if(1) continue ;
		for(int i = n; i >= 1; i --)
			h2 = (h2 + a[i]) % p1 * x % p1;
		h2 = (h2 + ans[0]) % p1;
		if(!h2) ans[++ ans[0]] = x;
	}
	printf("%d\n", ans[0]);
	for(int i = 1; i <= ans[0]; i ++)
		printf("%d\n", ans[i]);
	return 0;
}