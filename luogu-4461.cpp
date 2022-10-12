#include <algorithm>
#include <complex>
#include <cstdio>
#include <cmath>
using namespace std;
typedef complex<double> comp;
const int N = 80010;
int len, rev[N * 4];
void FFT(comp *a, int t) {
	static const double pi = acos(-1.0);
	for(int i = 0; i < len; i ++)
		if(i < rev[i]) swap(a[i], a[rev[i]]);
	for(int i = 1; i < len; i <<= 1) {
		comp w(cos(pi / i), t * sin(pi / i));
		for(int j = 0; j < len; j += i << 1) {
			comp wn(1, 0);
			for(int k = 0; k < i; k ++, wn *= w) {
				comp p = a[j + k], q = wn * a[j + k + i];
				a[j + k] = p + q; a[j + k + i] = p - q;
			}
		}
	}
}
void Conv(const int *a, const int *b, int n, int m, int *c) {
	int k = 0;
	for(len = 1; len <= n + m; len <<= 1) k ++;
	for(int i = 1; i < len; i ++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
	static comp x[N * 4], y[N * 4];
	for(int i = 0; i < len; i ++) x[i] = comp(i <= n ? a[i] : 0, 0);
	for(int i = 0; i < len; i ++) y[i] = comp(i <= m ? b[i] : 0, 0);
	FFT(x, 1); FFT(y, 1);
	for(int i = 0; i < len; i ++) x[i] *= y[i];
	FFT(x, -1);
	for(int i = 0; i < len; i ++) c[i] = (int) (x[i].real() / len + 0.5);
}
struct node {
	int a[N], n;
	node() {}
	node(int x) { a[0] = x; n = 1; }
	node operator * (const node &b) {
		node c; c.n = n + b.n;
		c.a[c.n - 2] = c.a[c.n - 1] = 0;
		Conv(a, b.a, n - 1, b.n - 1, c.a);
		for(int i = 0; i < c.n - 1; i ++) {
			c.a[i + 1] += c.a[i] / 10; c.a[i] %= 10;
		}
		while(c.n > 1 && c.a[c.n - 1] == 0) c.n --;
		return c;
	}
	void div3() {
		int r = 0;
		for(int i = n - 1; i >= 0; i --) {
			r = r * 10 + a[i];
			a[i] = r / 3; r %= 3;
		}
		while(n > 1 && a[n - 1] == 0) n --;
	}
	void minus() {
		a[0] --;
		for(int i = 0; i < n; i --) {
			if(a[i] < 0) {
				a[i] += 10; a[i - 1] --;
			} else break ;
		}
		while(n > 1 && a[n - 1] == 0) n --;
	}
	void out() {
		printf("%d", a[n - 1]);
		for(int i = n - 2; ~ i; i --)
			printf("%d", a[i]);
		puts("");
	}
};
node qpow(node a, int b) {
	node ans(1);
	for(; b >= 1; b >>= 1, a = a * a)
		if(b & 1) ans = ans * a;
	return ans;
}
int main() {
	int t; scanf("%d", &t);
	while(t --) {
		int n; scanf("%d", &n);
		if(n <= 2) printf("%d\n", n);
		else {
			node x = qpow(node(2), n + 1);
			x.minus();
			if(n % 2 == 0) x.minus();
			x.div3(); x.out();
		}
	}
	return 0;
}