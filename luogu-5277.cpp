#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <ctime>
using namespace std;
typedef long long ll;
const int N = 4e5 + 10;
const int mod = 998244353;
const int g = 3;
int rev[N], len;
ll w[N], inv_w[N];
int qpow(int a, int b) {
	int ans = 1;
	for(; b >= 1; b >>= 1, a = (ll) a * a % mod)
		if(b & 1) ans = (ll) ans * a % mod;
	return ans;
}
namespace cipolla {

int a, t;
struct Node {
	int x, y;
	Node operator * (const Node &b) const {
		return (Node) {
			(int) ((1ll * x * b.x % mod + 1ll * y * b.y % mod * t % mod) % mod),
			(int) ((1ll * x * b.y % mod + 1ll * y * b.x % mod) % mod)
		};
	}
};
Node nqpow(Node a, int b) {
	Node ans = (Node) {1, 0};
	for(; b >= 1; b >>= 1, a = a * a)
		if(b & 1) ans = ans * a;
	return ans;
}
int sqrt(int n) {
	if(n == 1) return 1;
	a = 1; srand(time(0));
	while(qpow(((t = (1ll * a * a % mod - n) % mod + mod) % mod), (mod - 1) / 2) != mod - 1)
		a = 1ll * rand() * rand() % mod;
	int res = nqpow((Node) {a, 1}, (mod + 1) / 2).x;
	return min(res, (mod - res) % mod);
}

}
void InitNTT(int n) {
	int k = 0;
	for(len = 1; len <= n; len <<= 1) k ++;
	for(int i = 1; i < len; i ++)
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
	w[0] = inv_w[0] = 1;
	ll v = qpow(g, (mod - 1) / len);
	for(int i = 1; i < len; i ++)
		inv_w[len - i] = w[i] = w[i - 1] * v % mod;
}
void NTT(ll *a, const ll *w) {
	for(int i = 1; i < len; i ++)
		if(i < rev[i]) swap(a[i], a[rev[i]]);
	for(int i = 1; i < len; i <<= 1) {
		for(int j = 0, t = len / (i << 1); j < len; j += i << 1) {
			const ll *wn = w;
			for(int k = j; k < j + i; k ++, wn += t) {
				ll t1 = a[k], t2 = *wn * a[k + i] % mod;
				a[k] = (t1 + t2) % mod; a[k + i] = (t1 - t2) % mod;
			}
		}
	}
	if(w == inv_w)
		for(int i = 0, v = - (mod - 1) / len; i < len; i ++)
			a[i] = a[i] * v % mod;
}
//b[n], b[n + 1], ... will not be modified
void Inv(const ll *a, int n, ll *b) { //AB = 1 (mod x^n)
	if(n == 1) { b[0] = qpow(a[0], mod - 2); return ; }
	int m = (n + 1) >> 1; Inv(a, m, b);
	static ll ta[N], tb[N]; InitNTT(n * 2);
	for(int i = 0; i < n; i ++) ta[i] = a[i];
	for(int i = n; i < len; i ++) ta[i] = 0;
	for(int i = 0; i < m; i ++) tb[i] = b[i];
	for(int i = m; i < len; i ++) tb[i] = 0;
	NTT(ta, w); NTT(tb, w);
	for(int i = 0; i < len; i ++)
		tb[i] = (2 - tb[i] * ta[i] % mod) * tb[i] % mod;
	NTT(tb, inv_w);
	for(int i = 0; i < n; i ++) b[i] = tb[i];
}
void Sqrt(const ll *a, int n, ll *b) { //B^2 = A (mod x^n)
	if(n == 1) { b[0] = cipolla::sqrt(a[0]); return ; }
	int m = (n + 1) >> 1; Sqrt(a, m, b);
	static ll ti[N], ta[N], tb[N];
	for(int i = m; i < n; i ++) b[i] = 0;
	Inv(b, n, ti); InitNTT(n * 2);
	for(int i = n; i < len; i ++) ti[i] = 0;
	for(int i = 0; i < n; i ++) ta[i] = a[i];
	for(int i = n; i < len; i ++) ta[i] = 0;
	for(int i = 0; i < m; i ++) tb[i] = b[i];
	for(int i = m; i < len; i ++) tb[i] = 0;
	NTT(ta, w); NTT(tb, w); NTT(ti, w);
	for(int i = 0, v = (mod + 1) >> 1; i < len; i ++)
		tb[i] = (tb[i] * tb[i] + ta[i]) % mod * v % mod * ti[i] % mod;
	NTT(tb, inv_w);
	for(int i = 0; i < n; i ++) b[i] = tb[i];
}
int read() {
	int x = 0; char c = getchar();
	for(; c < '0' || c > '9'; c = getchar()) ;
	for(; c >= '0' && c <= '9'; c = getchar())
		x = x * 10 + (c & 15);
	return x;
}
int main() {
	static ll A[N], B[N];
	int n = read();
	for(int i = 0; i < n; i ++) A[i] = read();
	Sqrt(A, n, B);
	for(int i = 0; i < n; i ++)
		printf("%lld ", (B[i] + mod) % mod);
	return 0;
}