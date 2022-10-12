#include <algorithm>
#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;
const int N = 1e5 + 10, mod = 1e9 + 7, inv2 = (mod + 1) >> 1;
int n, sq, m, k, w[N], seq[N], c[N], s[N], t[N];
vector<int> G[N], H[N];
int qpow(int a, int b = mod - 2) {
	int ans = 1;
	for(; b >= 1; b >>= 1, a = 1ll * a * a % mod)
		if(b & 1) ans = 1ll * ans * a % mod;
	return ans;
}
int main() {
	scanf("%d%d%d", &n, &m, &k); sq = (int) sqrt(m + 0.5);
	for(int i = 1; i <= n; i ++) scanf("%d", w + i);
	for(int i = 1; i <= k; i ++) scanf("%d", seq + i), c[seq[i]] ++;
	for(int x, y, i = 1; i <= m; i ++) {
		scanf("%d%d", &x, &y);
		G[x].push_back(y);
		G[y].push_back(x);
	}
	for(int i = 1; i <= n; i ++) if(c[i])
		for(int v : G[i]) if(!c[v] && w[v]) {
			puts("-1"); return 0;
		}
	for(int i = 1; i <= n; i ++) if(G[i].size() > sq)
		for(int v : G[i]) H[v].push_back(i);
	for(int i = 1; i <= n; i ++) if(c[i]) 
		w[i] = 1ll * w[i] * qpow(2, c[i]) % mod * qpow(qpow(2, c[i]) - 1) % mod;
	for(int i = 1; i <= n; i ++)
		for(int v : G[i]) (s[i] += w[v]) %= mod;
	int ans = 0;
	for(int i = 1; i <= k; i ++) {
		int u = seq[i];
		for(int v : H[u]) (ans += t[v]) %= mod;
		(ans += s[u]) %= mod;
		int nxt = 1ll * w[u] * inv2 % mod;
		if(G[u].size() > sq) {
			(t[u] += mod - nxt) %= mod;
		} else {
			for(int v : G[u]) (s[v] += mod - nxt) %= mod;
		}
		w[u] = nxt;
	}
	printf("%d\n", ans);
	return 0;
}