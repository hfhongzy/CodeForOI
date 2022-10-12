#include <algorithm>
#include <cstdio>
#include <vector>
#define fs first
#define sc second
#define mp make_pair
#define all(x) x.begin(), x.end()
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
int n, m, a[N], b[N], f[N];
ll mx[N], mn[N], ans[N];
vector< pair< int, pair<int, int> > > e;
int find(int u) { return u == f[u] ? u : f[u] = find(f[u]); }
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++) {
		scanf("%d%d", a + i, b + i);
	}
	e.resize(m);
	for(int i = 1; i <= m; i ++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		e[i - 1] = mp(w, mp(u, v));
	}
	sort(all(e));
	for(int i = 1; i <= n; i ++) {
		mx[i] = a[i]; mn[i] = b[i]; f[i] = i; ans[i] = mx[i] * mn[i];
	}
	for(int i = 0; i < (int) e.size(); i ++) {
		int x = find(e[i].sc.fs), y = find(e[i].sc.sc);
		if(x != y) {
			ll _ans = min(ans[x] + ans[y], max((ll) e[i].fs, max(mx[x], mx[y])) * min(mn[x], mn[y]));
			ll _mx = max(mx[x], mx[y]), _mn = min(mn[x], mn[y]);
			ans[x] = _ans; mx[x] = _mx; mn[x] = _mn; f[y] = x;
		}
	}
	ll res = 0;
	for(int i = 1; i <= n; i ++)
		if(find(i) == i) res += ans[i];
	printf("%lld\n", res);
	return 0;
}