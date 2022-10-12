#include <algorithm>
#include <cstdio>
using namespace std;
typedef long long ll;
const int N = 4e5 + 10;
struct point {
	ll x, y;
	void read() { int xx, yy; scanf("%d%d", &xx, &yy); x = xx; y = yy; }
	point operator - (const point &b) { return (point) {x - b.x, y - b.y}; }
	ll length() { return x * x + y * y; }
	ll det(const point &b) { return x * b.y - y * b.x; }
} a[N];
int n, f[N];
ll b[N];
int main() {
	int test;
	scanf("%d", &test);
	while(test --) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i ++) a[i].read();
		a[0] = a[n]; a[n + 1] = a[1];
		for(int i = 1; i <= n; i ++) b[i * 2 - 1] = (a[i + 1] - a[i]).det(a[i - 1] - a[i]);
		for(int i = 1; i <= n; i ++) b[i * 2] = (a[i] - a[i + 1]).length();
		for(int i = 1; i <= 2 * n; i ++) b[i + 2 * n] = b[i];
		for(int i = 1, mid = 0, r = 0; i <= 4 * n; i ++) {
			f[i] = i < r ? min(r - i, f[2 * mid - i]) : 1;
			while(i + f[i] <= 4 * n && i - f[i] >= 1 && b[i + f[i]] == b[i - f[i]]) f[i] ++;
			if(i + f[i] > r) { r = i + f[i]; mid = i; }
		}
		int ans = 0;
		for(int i = n + 1; i <= 3 * n; i ++) if(f[i] > n) ans ++;
		printf("%d\n", ans >> 1);
	}
	return 0;
}
//1 (1->2) 2 (2->3) .. n (n -> 1)