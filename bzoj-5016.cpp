#include <algorithm>
#include <cstdio>
#include <cmath>
#define sgn(x) (x > 0 ? 1 : -1)
#define abs(x) (x > 0 ? x : -x)
using namespace std;
typedef long long ll;
const int N = 5e4 + 10;
int size;
struct node {
	int l, r, id;
	bool operator < (const node &b) const {
		if(l / size == b.l / size) return r < b.r;
		return l / size < b.l / size;
	}
} qn[N * 4];
int n, q, a[N], cnt[2][N];
ll ans[N], cur;
void MoPush(int t, int x) { cnt[t][x] ++; cur += cnt[t ^ 1][x]; }
void MoPop(int t, int x) { cnt[t][x] --; cur -= cnt[t ^ 1][x]; }
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++) scanf("%d", a + i);
	scanf("%d", &q); size = max(1, (int) (n / sqrt(4 * q)));
	for(int l1, r1, l2, r2, i = 1; i <= q; i ++) {
		scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
		qn[i * 4 - 3] = (node) {r1, r2, i};
		qn[i * 4 - 2] = (node) {l1 - 1, r2, -i};
		qn[i * 4 - 1] = (node) {r1, l2 - 1, -i};
		qn[i * 4] = (node) {l1 - 1, l2 - 1, i};
	}
	for(int i = 1; i <= 4 * q; i ++) if(qn[i].l > qn[i].r) swap(qn[i].l, qn[i].r);
	sort(qn + 1, qn + 4 * q + 1);
	int l = 0, r = 0;
	for(int i = 1; i <= 4 * q; i ++) if(qn[i].l && qn[i].r) {
		while(r < qn[i].r) MoPush(1, a[++ r]);
		while(l < qn[i].l) MoPush(0, a[++ l]);
		while(l > qn[i].l) MoPop(0, a[l --]);
		while(r > qn[i].r) MoPop(1, a[r --]);
		ans[abs(qn[i].id)] += sgn(qn[i].id) * cur;
	}
	for(int i = 1; i <= q; i ++)
		printf("%lld\n", ans[i]);
	return 0;
}