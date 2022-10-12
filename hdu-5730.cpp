#include <algorithm>
#include <complex>
#include <cstdio>
#include <cmath>
using namespace std;
typedef long long ll;
typedef long double db;
typedef complex<db> comp;
const db pi = acos(-1);
const int N = 4e5 + 10;
namespace fft {

int rev[N], len;
void init(int n) {
	int k = 0;
	for(len = 1; len <= n; len <<= 1) k ++;
	for(int i = 1; i < len; i ++)
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
}
void fft(comp *a, int ty) {
	for(int i = 1; i < len; i ++)
		if(i < rev[i]) swap(a[i], a[rev[i]]);
	for(int i = 1; i < len; i <<= 1) {
		comp wn(cos(pi / i), ty * sin(pi / i)), w, t1, t2;
		for(int j = 0; j < len; j += i << 1) {
			w = comp(1, 0);
			for(int k = j; k < j + i; k ++, w *= wn) {
				t1 = a[k], t2 = w * a[k + i];
				a[k] = t1 + t2; a[k + i] = t1 - t2;
			}
		}
	}
	if(ty == -1) for(int i = 0; i < len; i ++)
		a[i] /= len;
}

}
int a, b, c;
comp A[4][N];
int p[N], pc, np[N], npc;
bool tag[N];
pair<int, int> scan(char *s) {
	int x = 0, y = 0;
	for(; *s; s ++) {
		if(*s == 'S') y = 0;
		else if(*s == 'H') y = 1;
		else if(*s == 'C') y = 2;
		else if(*s == 'D') y = 3;
		else x = x * 10 + *s - '0';
	}
	return pair<int, int>(x, y);
}
void sieve(int n) {
	for(int i = 2; i <= n; i ++) {
		if(!tag[i]) p[++ pc] = i;
		else np[++ npc] = i;
		for(int j = 1; j <= pc && i * p[j] <= n; j ++) {
			tag[i * p[j]] = 1;
			if(i % p[j] == 0) break ;
		}
	}
}
int main() {
	char op[10]; sieve(N - 1);
	while(scanf("%d%d%d", &a, &b, &c), a | b | c) {
		fft::init(b << 2);
		for(int i = 0; i < 4; i ++) {
			for(int j = 0; j < fft::len; j ++) {
				A[i][j] = comp(0, 0);
			}
			for(int j = 1; j <= npc && np[j] <= b; j ++) {
				A[i][np[j]] = comp(1, 0);
			}
		}
		for(int i = 1; i <= c; i ++) {
			scanf("%s", op);
			pair<int, int> ban = scan(op);
			A[ban.second][ban.first] = comp(0, 0);
		}
		for(int i = 0; i < 4; i ++) {
			fft::fft(A[i], 1);
		}
		for(int i = 0; i < fft::len; i ++) A[0][i] *= A[1][i] * A[2][i] * A[3][i];
		fft::fft(A[0], -1);
		for(int i = a; i <= b; i ++)
			printf("%lld\n", (long long) (A[0][i].real() + 0.1));
		puts("");
	}
	return 0;
}