#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 5e5 + 10;
struct opt {
	int l, r, id;
	bool operator < (const opt &b) const {
		return r < b.r;
	}
} b[N];
struct num {
	int x, id;
	bool operator < (const num &b) const {
		return x < b.x;
	}
} t[N];
int n, m, q, a[N], s[N], ans[N], pre[N], bit[N];
void insert(int u, int val) {
	for(; u <= n; u += u & (-u))
		bit[u] ^= val;
}
int query(int u) {
	int ans = 0;
	for(; u >= 1; u &= u - 1)
		ans ^= bit[u];
	return ans;
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++) {
		scanf("%d", a + i);
		s[i] = s[i - 1] ^ a[i];
		t[i] = (num) {a[i], i};
	}
	for(int op, l, r, i = 1; i <= m; i ++) {
		scanf("%d%d%d", &op, &l, &r);
		if(op < 3) ans[i] = s[l - 1] ^ s[r];
		else b[++ q] = (opt) {l, r, i};
	}
	sort(b + 1, b + q + 1);
	stable_sort(t + 1, t + n + 1);
	for(int i = 1; i <= n; i ++)
		pre[t[i].id] = t[i - 1].x == t[i].x ? t[i - 1].id : 0;
	for(int p = 1, i = 1; i <= n && p <= q; i ++) {
		insert(pre[i] + 1, a[i]); insert(i + 1, a[i]);
		for(; p <= q && b[p].r == i; p ++) {
			ans[b[p].id] = s[b[p].l - 1] ^ s[i] ^ query(b[p].l);
		}
	}
	for(int i = 1; i <= m; i ++)
		printf("%d\n", ans[i]);
	return 0;
}