#include <algorithm>
#include <cstdio>
#include <vector>
#define rep(i, j, k) for(int i = j; i <= (int) k; i ++)
#define repv(i, v) for(int i = 0; i < (int) v.size(); i ++)
using namespace std;
typedef long long ll;
const int N = 102, mod = 65521;
struct mat {
	int a[N][N], n, m;
	mat operator * (const mat &b) {
		mat ans; ans.n = n; ans.m = b.m;
		rep(i, 1, ans.n) rep(j, 1, ans.m) {
			ans.a[i][j] = 0;
			rep(k, 1, m) {
				ans.a[i][j] += 1ll * a[i][k] * b.a[k][j] % mod;
			}
			ans.a[i][j] %= mod;
		}
		return ans;
	}
} tr, fir;
mat mpow(mat a, ll b) {
	mat ans = a; b --;
	for(; b >= 1; b >>= 1, a = a * a)
		if(b & 1) ans = ans * a;
	return ans;
}
int qpow(int a, int b) {
	int ans = 1;
	for(; b >= 1; b >>= 1, a = 1ll * a * a % mod)
		if(b & 1) ans = 1ll * ans * a % mod;
	return ans;
}
int k, m, sta[N], Map[1000000], tot[N];
ll n;
void dfs(int u, int cur) {
	static int sz;
	if(u == k + 1) { sta[++ m] = cur; Map[cur] = m; return ; }
	for(int i = 1; i <= sz; i ++) dfs(u + 1, cur * 10 + i);
	sz ++; dfs(u + 1, cur * 10 + sz); sz --;
}
vector<int> digit(int st) {
	vector<int> ans;
	for(; st; st /= 10) ans.push_back(st % 10);
	reverse(ans.begin(), ans.end());
	return ans;
}
int encode(vector<int> &d) {
	int ans = 0;
	repv(i, d) ans = ans * 10 + d[i];
	return ans;
}
int calc(int st) {
	static int cnt[10];
	vector<int> d = digit(st);
	int ans = 1;
	repv(i, d) cnt[d[i]] ++;
	repv(i, d) {
		if(cnt[d[i]]) {
			ans = 1ll * ans * qpow(cnt[d[i]], cnt[d[i]] - 2) % mod;
			cnt[d[i]] = 0;
		}
	}
	return ans;
}
struct Ufs {
	int f[N];
	void init(int n) {
		rep(i, 1, n) f[i] = i;
	}
	int find(int u) {
		return u == f[u] ? u : f[u] = find(f[u]);
	}
	bool unite(int u, int v) {
		u = find(u); v = find(v);
		if(u == v) return 0;
		f[u] = v; return 1;
	}
} ufs;
int main() {
	scanf("%d%lld", &k, &n);
	if(n <= 2) return puts("1"), 0;
	if(k == n) k --;
	dfs(1, 0);

	fir.n = 1; fir.m = m;
	rep(i, 1, m) fir.a[1][i] = calc(sta[i]);

	tr.n = tr.m = m;
	rep(i, 1, m) {
		vector<int> d = digit(sta[i]);

		bool out = 1;
		rep(j, 1, d.size() - 1)
			if(d[j] == 1) { out = 0; break ; }

		for(int l = 0; l < (1 << k); l ++) {
			if(out && !(l & 1)) continue ;
			ufs.init(k + 2);
			rep(u, 0, d.size() - 1) rep(v, u + 1, d.size() - 1)
				if(d[u] == d[v]) ufs.unite(v + 1, u + 1);
			bool ntree = 0;
			for(int u = 0; u < k; u ++) if(l >> u & 1) {
				if(!ufs.unite(1 + u, k + 1)) {
					ntree = 1; break ;
				}
			}
			if(ntree) continue ;

			static int col[N];
			fill(col + 1, col + k + 1 + 1, 0);
			int c = 0, nxt = 0;
			for(int j = 2; j <= k + 1; j ++) {
				if(!col[ufs.find(j)]) col[ufs.find(j)] = ++ c;
				nxt = nxt * 10 + col[ufs.find(j)];
			}
			tr.a[i][Map[nxt]] ++;
		}
	}
	// printf("%d !!\n", sta[1]);
	fir = fir * mpow(tr, n - k);
	printf("%d\n", fir.a[1][1]);
	return 0;
}