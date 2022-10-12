#include <algorithm>
#include <cstdio>
using namespace std;
typedef long long ll;
const int N = 5e5 + 10;
int n;
ll mod;
ll mul(ll a, ll b) {
   ll t = a * b - (ll)((long double) a / mod * b + 1e-8) * mod;
   return t < 0 ? t + mod : t;
}
ll phi(ll n) {
	ll ans = n;
	for(ll i = 2; i * i <= n; i ++) if(n % i == 0) {
		ans = ans / i * (i - 1);
		while(n % i == 0) n /= i;
	}
	if(n > 1) ans = ans / n * (n - 1);
	return ans;
}
struct mat {
	ll a[3][3];
	mat operator * (const mat &b) {
		mat ans;
		for(int i = 0; i < 3; i ++) {
			for(int j = 0; j < 3; j ++) {
				ans.a[i][j] = 0;
				for(int k = 0; k < 3; k ++) {
					(ans.a[i][j] += mul(a[i][k], b.a[k][j])) %= mod;
				}
			}
		}
		return ans;
	}
} fir, tr;
mat mpow(mat a, int b) {
	mat ans = a; b --;
	for(; b >= 1; b >>= 1, a = a * a)
		if(b & 1) ans = ans * a;
	return ans;
}
ll solve(ll n) {
	if(n == 1) return 1;
	if(n == 2) return 5;
	mat res = fir * mpow(tr, n - 2);
	return res.a[0][0];
}
int main() {
	while(~ scanf("%d%lld", &n, &mod)) {
		mod *= n;
		fir.a[0][0] = 5; fir.a[0][1] = 1; fir.a[0][2] = 2;
		tr.a[0][0] = 3; tr.a[0][1] = 1; tr.a[1][0] = mod - 1; tr.a[2][0] = tr.a[2][2] = 1;
		ll ans = 0;
		for(int i = 1; i * i <= n; i ++) if(n % i == 0) {
			(ans += mul(phi(n / i), solve(i))) %= mod;
			if(n / i != i) {
				(ans += mul(phi(i), solve(n / i))) %= mod;
			}
		}
		printf("%d\n", (int) (ans / n));
	}
	return 0;
}