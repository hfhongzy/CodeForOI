#include <algorithm>
#include <cstdio>
using namespace std;
 
const int N = 5e5 + 10, mod = 998244353;
 
struct Node {
	int l, r, x;
} a[N];
 
int n, m, k, f[N], s[N], L[N];
int solve(int t) {
	for(int i = 0; i <= n + 1; i ++) s[i] = f[i] = L[i] = 0;
	for(int i = 1; i <= m; i ++)
		if(a[i].x & (1 << t)) s[a[i].l] ++, s[ a[i].r + 1 ] --;
		else L[a[i].r] = max(L[a[i].r], a[i].l);
	int sum = 1, now = 0; f[0] = 1;
	for(int i = 1; i <= n; i ++) {
		s[i] += s[i - 1];
		if(!s[i]) f[i] = sum, sum = (sum + f[i]) % mod;
		while(now < L[i]) sum = (sum + mod - f[now]) % mod, now ++;
	}
	return sum;
}
 
int main() {
	scanf("%d%d%d", &n, &k, &m);
	for(int i = 1; i <= m; i ++)
		scanf("%d%d%d", &a[i].l, &a[i].r, &a[i].x);
	int ans = 1;
	for(int i = 0; i < k; i ++) ans = 1ll * ans * solve(i) % mod;
	printf("%d\n", ans);
	return 0;
}