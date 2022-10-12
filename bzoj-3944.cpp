#include <algorithm>
#include <cstdio>
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;
int p[N], pc;
ll mu[N], phi[N], mu2[N], phi2[N];
bool tag[N];
void sieve() {
	mu[1] = phi[1] = 1;
	for(int i = 2; i < N; i ++) {
		if(!tag[i]) { p[++ pc] = i; mu[i] = -1; phi[i] = i - 1; }
		for(int j = 1; j <= pc; j ++) {
			int t = i * p[j];
			if(t >= N) break ;
			tag[t] = 1;
			if(i % p[j] == 0) { phi[t] = phi[i] * p[j]; break ; }
			phi[t] = phi[i] * (p[j] - 1); mu[t] = - mu[i];
		}
		mu[i] += mu[i - 1]; phi[i] += phi[i - 1];
	}
}
int st[N], m, cur_n;
ll Phi(int n) {
	return n < N ? phi[n] : phi2[cur_n / n];
}
ll Mu(int n) {
	return n < N ? mu[n] : mu2[cur_n / n];
}
int main() {
	sieve();
	int test; scanf("%d", &test);
	while(test --) {
		int n; scanf("%d", &n); cur_n = n; m = 0;
		for(int i = 1; i <= n; i ++) {
			if(n / i < N) break ;
			st[++ m] = n / i;
		}
		ll ans1 = 0, ans2 = 0;
		for(int i = m; i >= 1; i --) {
			int nn = st[i];
			ll res1 = nn * (nn + 1ll) / 2, res2 = 1;
			for(ll i = 2, j; i <= nn; i = j + 1) {
				j = nn / (nn / i);
				res1 -= Phi(nn / i) * (j - i + 1);
				res2 -= Mu(nn / i) * (j - i + 1);
			}
			phi2[n / nn] = res1; mu2[n / nn] = res2;
		}
		printf("%lld %d\n", Phi(n), (int) Mu(n));
	}
	return 0;
}