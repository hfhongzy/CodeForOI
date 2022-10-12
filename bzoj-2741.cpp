#include <algorithm>
#include <cstdio>
#include <cmath>
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
const int N = 12005, M = 115, S = N * 32;
int n, m, a[N], sz, bit, siz[S], ch[S][2], bn, id, T[N], res[M][N];
void build(int &u, int p, int d, int x) {
	u = ++ id; siz[u] = siz[p] + 1;
	if(d == -1) return ;
	if(x >> d & 1) {
		ch[u][0] = ch[p][0];
		build(ch[u][1], ch[p][1], d - 1, x);
	} else {
		ch[u][1] = ch[p][1];
		build(ch[u][0], ch[p][0], d - 1, x);
	}
}
int query(int ul, int ur, int x) {
	int ans = 0; ul = !ul ? 0 : T[ul - 1]; ur = T[ur];
	for(int i = bit; i >= 0; i --) {
		int d = x >> i & 1;
		if(siz[ch[ur][d ^ 1]] - siz[ch[ul][d ^ 1]] >= 1) {
			ul = ch[ul][d ^ 1]; ur = ch[ur][d ^ 1];
			ans ^= 1 << i;
		} else {
			ul = ch[ul][d]; ur = ch[ur][d];
		}
	}
	return ans;
}
int query(int l, int r) {
	int x = l / sz + 1, y = r / sz + 1, ans = 0;
	if(x == y) {
		for(int i = l; i <= r; i ++) ans = max(ans, query(l, r, a[i]));
	} else {
		ans = res[x + 1][r];
		for(int i = l; i < x * sz; i ++) ans = max(ans, query(l, r, a[i]));
	}
	return ans;
}
int main() {
	// freopen("input", "r", stdin);
	n = read(), m = read();
	for(int i = 1; i <= n; i ++) a[i] = a[i - 1] ^ read();
	sz = max(1, (int) sqrt(n)); //(k - 1) * sz ~ min(n, k * sz - 1)
	bn = n / sz + 1;
	int mx = *max_element(a, a + n + 1);
	for(int i = 0; i < 31; i ++) if(mx >> i & 1) bit = i;
	for(int i = 0; i <= n; i ++) {
		build(T[i], i ? T[i - 1] : 0, bit, a[i]);
	}
	for(int i = 1; i <= bn; i ++) {
		int l = (i - 1) * sz, cur = 0;
		for(int j = l; j <= n; j ++) {
			cur = max(cur, query(l, j, a[j]));
			res[i][j] = cur;
		}
	}
	int lans = 0;
	for(int l, r, i = 1; i <= m; i ++) {
		l = ((long long) read() + lans) % n + 1;
		r = ((long long) read() + lans) % n + 1;
		if(l > r) swap(l, r);
		printf("%d\n", lans = query(l - 1, r));
	}
	return 0;
}