#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 5e5 + 10;
const int mod = 1e9;
int n, a[N], ans, s1[N], s2[N], sl1[N], sl2[N], sm[N], s[N];
int f(int *s, int l, int r) { return (s[r] - s[l - 1] + mod) % mod; }
int g(int l, int r) { return (l + r) * (r - l + 1ll) / 2 % mod; }
void upd(int x) { if((ans += x) >= mod) ans -= mod; }
void solve(int l, int r) {
	if(l > r) return ;
	if(l == r) { upd(1ll * a[l] * a[l] % mod); return ; }
	int mid = (l + r) >> 1, L = a[mid], R = a[mid];
	s1[mid] = s2[mid] = sl1[mid] = sl2[mid] = sm[mid] = s[mid] = 0;
	for(int i = mid + 1; i <= r; i ++) {
		L = min(L, a[i]); R = max(R, a[i]);
		s1[i] = (s1[i - 1] + R) % mod;
		s2[i] = (s2[i - 1] + L) % mod;
		sl1[i] = (sl1[i - 1] + 1ll * R * (i - mid)) % mod;
		sl2[i] = (sl2[i - 1] + 1ll * L * (i - mid)) % mod;
		sm[i] = (sm[i - 1] + 1ll * L * R) % mod;
		s[i] = (s[i - 1] + 1ll * L * R % mod * (i - mid)) % mod;
	}
	L = R = a[mid];
	int m1 = mid, m2 = mid;
	for(int i = mid; i >= l; i --) {
		L = min(L, a[i]); R = max(R, a[i]);
		while(m1 < r && a[m1 + 1] >= L) m1 ++;
		while(m2 < r && a[m2 + 1] <= R) m2 ++;
		int k = mid - i + 1; upd(1ll * L * R % mod * k % mod);
		if(m1 <= m2) {
			if(mid < m1) upd(1ll * L * R % mod * g(k + 1, k + m1 - mid) % mod);
			if(m1 < m2) upd(R * (f(sl2, m1 + 1, m2) + 1ll * k * f(s2, m1 + 1, m2) % mod) % mod);
			if(m2 < r) upd((f(s, m2 + 1, r) + 1ll * k * f(sm, m2 + 1, r)) % mod);
		} else {
			if(mid < m2) upd(1ll * L * R % mod * g(k + 1, k + m2 - mid) % mod);
			if(m2 < m1) upd(L * (f(sl1, m2 + 1, m1) + 1ll * k * f(s1, m2 + 1, m1) % mod) % mod);
			if(m1 < r) upd((f(s, m1 + 1, r) + 1ll * k * f(sm, m1 + 1, r)) % mod);
		}
	}
	solve(l, mid - 1); solve(mid + 1, r);
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++)
		scanf("%d", a + i);
	solve(1, n);
	printf("%d\n", ans);
	return 0;
}