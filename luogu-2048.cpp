#include <algorithm>
#include <cstdio>
#include <queue>
using namespace std;
typedef long long ll;
const int N = 5e5 + 10;
struct Uni {
	int b[N], m;
	void init(int *a, int n) {
		copy(a + 1, a + n + 1, b + 1);
		sort(b + 1, b + n + 1);
		m = unique(b + 1, b + n + 1) - b - 1;
		for(int i = 1; i <= n; i ++)
			a[i] = lower_bound(b + 1, b + m + 1, a[i]) - b;	
	}
	int &operator [] (int x) { return b[x]; }
} uni;
ll ans;
struct Node {
	int st, x, val;
	bool operator < (const Node &b) const {
		return val < b.val;
	}
};
int n, k, l, r, id, a[N], rt[N], sz[N * 21], ch[N * 21][2];
void update(int &u, int p, int l, int r, int x) {
	u = ++ id; sz[u] = sz[p] + 1;
	if(l == r) return ;
	int mid = (l + r) >> 1;
	if(x <= mid) {
		ch[u][1] = ch[p][1];
		update(ch[u][0], ch[p][0], l, mid, x);
	} else {
		ch[u][0] = ch[p][0];
		update(ch[u][1], ch[p][1], mid + 1, r, x);
	}
}
int query(int u, int v, int l, int r, int x) {
	if(l == r) return l;
	int mid = (l + r) >> 1, rsz = sz[ch[u][1]] - sz[ch[v][1]];
	if(rsz >= x) return query(ch[u][1], ch[v][1], mid + 1, r, x);
	return query(ch[u][0], ch[v][0], l, mid, x - rsz);
}
int main() {
	scanf("%d%d%d%d", &n, &k, &l, &r);
	for(int i = 1; i <= n; i ++) {
		scanf("%d", a + i); a[i] += a[i - 1];
	}
	uni.init(a, n);
	for(int i = n; i >= 1; i --) update(rt[i], rt[i + 1], 1, uni.m, a[i]);
	priority_queue<Node> pq;
	for(int i = 1; i <= n - l + 1; i ++) {
		int _l = i + l - 1, _r = min(n, i + r - 1);
		pq.push((Node) {i, 1, uni[query(rt[_l], rt[_r + 1], 1, uni.m, 1)] - uni[a[i - 1]]});
	}
	for(int i = 1; i <= k; i ++) {
		Node u = pq.top(); pq.pop(); ans += u.val;
		int _l = u.st + l - 1, _r = min(n, u.st + r - 1);
		if(_r - _l + 1 != u.x)
			pq.push((Node) {u.st, u.x + 1, uni[query(rt[_l], rt[_r + 1], 1, uni.m, u.x + 1)] - uni[a[u.st - 1]]});
	}
	printf("%lld\n", ans);
	return 0;
} 