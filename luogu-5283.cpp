#include <algorithm>
#include <cstdio>
#include <queue>
using namespace std;
typedef unsigned uint;
typedef unsigned long long ull;
const int N = 5e5 + 10;
const int M = N * 35;
int n, m, k, id, T[N], ch[M][2], sz[M];
uint a[N];
void build(int &u, int d = m) {
	u = ++ id; sz[u] = 1;
	if(d) build(ch[u][0], d - 1);
}
void build(int p, int &u, uint x, int d = m) {
	u = ++ id; sz[u] = sz[p] + 1;
	if(d -- == 0) return ;
	int y = x >> d & 1;
	ch[u][y ^ 1] = ch[p][y ^ 1];
	build(ch[p][y], ch[u][y], x, d);
}
uint kth(int u, uint x, int k) {
	int v = u; uint ans = 0;
	for(int i = m; i >= 1; i --) {
		int y = x >> (i - 1) & 1;
		if(sz[ch[v][y ^ 1]] >= k) {
			ans ^= 1 << (i - 1);
			v = ch[v][y ^ 1];
		} else {
			k -= sz[ch[v][y ^ 1]];
			v = ch[v][y];
		}
	}
	return ans;
}
struct Node {
	int r, k; uint val;
	bool operator < (const Node &b) const {
		return val < b.val;
	}
};
priority_queue<Node> pq;
int main() {
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i ++) scanf("%u", a + i), a[i] ^= a[i - 1];
	uint t = *max_element(a, a + n + 1);
	while(t) { t >>= 1; m ++; }
	build(T[0]);
	for(int i = 1; i <= n; i ++) {
		build(T[i - 1], T[i], a[i]);
		pq.push((Node) {i, 1, kth(T[i], a[i], 1)});
	}
	ull ans = 0;
	for(int i = 0; i < k; i ++) {
		Node u = pq.top(); pq.pop(); ans += u.val;
		if(u.k < u.r) pq.push((Node) {u.r, u.k + 1, kth(T[u.r], a[u.r], u.k + 1)});
	}
	printf("%llu\n", ans);
	return 0;
}