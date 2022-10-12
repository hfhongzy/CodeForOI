#include <algorithm>
#include <cstdio>
using namespace std;
namespace io {

char *S, *T, buf[1 << 15];
char gc() {
	if(S == T) {
		T = (S = buf) + fread(buf, 1, 1 << 15, stdin);
		if(S == T) return EOF;
	}
	return *S ++;
}

int read() {
	int x = 0; char c = gc(); bool bo = 0;
	for(; c < '0' || c > '9'; c = gc()) bo |= c == '-';
	for(; c >= '0' && c <= '9'; c = gc()) x = x * 10 + (c & 15);
	return bo ? - x : x;
}

}
using io::read;
const int N = 1e5 + 10;
struct node {
	int x, y, z, op, id;
} a[N * 5], t[N * 5];
int n, k, m, q, b[N], bit[N];
long long ans;
void insert(int u, int val) {
	for(; u <= m; u += u & (-u)) {
		bit[u] += val;
	}
}
int query(int u) {
	int ans = 0;
	for(; u >= 1; u &= u - 1) {
		ans += bit[u];
	}
	return ans;
}
bool cmp(node a, node b) {
	if(a.y ^ b.y) return a.y > b.y;
	if(a.id ^ b.id) return a.id < b.id;
	return (a.op == 0) < (b.op == 0);
}
void cdq(int l, int r) {
	if(l >= r) return ;
	int mid = (l + r) >> 1;
	cdq(l, mid); cdq(mid + 1, r);
	int p = l, tp = l - 1;
	for(int i = mid + 1; i <= r; i ++) {
		for(; p <= mid && a[p].x <= a[i].x; p ++) {
			if(!a[p].op) insert(a[p].z, 1);
			t[++ tp] = a[p];
		}
		if(a[i].op) ans += a[i].op * query(a[i].z);
		t[++ tp] = a[i];
	}
	for(int i = p; i <= mid; i ++) t[++ tp] = a[i];
	while(-- p >= l) if(!a[p].op) insert(a[p].z, -1);
	copy(t + l, t + r + 1, a + l);
}
int main() {
	// freopen("input", "r", stdin);
	n = read(), k = read();
	for(int i = 1; i <= n; i ++) {
		a[i].x = read(), a[i].y = read(), a[i].z = read();
		b[i] = a[i].z; a[i].id = i;
	}
	sort(b + 1, b + n + 1);
	m = unique(b + 1, b + n + 1) - b - 1;
	q = n;
	for(int i = 1; i <= n; i ++) {
		int z = lower_bound(b + 1, b + m + 1, a[i].z) - b;
		int zl = lower_bound(b + 1, b + m + 1, a[i].z - k) - b;
		int zr = upper_bound(b + 1, b + m + 1, a[i].z + k) - b - 1;
		a[i].z = z;
		a[++ q] = {a[i].x + a[i].y, a[i].y, zr, 1, i};
		a[++ q] = {a[i].x - a[i].y - 1, a[i].y, zr, -1, i};
		a[++ q] = {a[i].x + a[i].y, a[i].y, zl - 1, -1, i};
		a[++ q] = {a[i].x - a[i].y - 1, a[i].y, zl - 1, 1, i};
	}
	sort(a + 1, a + q + 1, cmp);
	cdq(1, q);
	printf("%lld\n", ans - 0*n);
	return 0;
}
/*
rj <= ri
xi - ri <= xj <= xi + ri
zi - k <= zj <= zi + k

yj <= yi
xi - ri <= xj <= xi + ri
zi - k <= zj <= zi + k
*/