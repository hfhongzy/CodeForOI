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
const int N = 5e4 + 10;
int q;
int main() {
	// freopen("input", "r", stdin);
	while(q = read()) {
		static int st[N][2], tg[N]; int top = 0;
		for(int i = 1; i <= q; i ++) {
			int t = read(), x = read(), y = read();
			if(t == 1) {
				st[++ top][0] = x; st[top][1] = y; tg[top] = 1;
			}
			if(t == -1) {
				for(int j = 1; j <= top; j ++) {
					if(tg[j] && st[j][0] == x && st[j][1] == y) {
						tg[j] = 0; break ;
					}
				}
			}
			if(t == 0) {
				long long ans = -1e18;
				for(int j = 1; j <= top; j ++) if(tg[j]) {
					ans = max(ans, 1ll * x * st[j][0] + 1ll * y * st[j][1]);
				}
				printf("%lld\n", ans);
			}
		}
	}
	return 0;
}
/*
左边构成凸包，然后考虑对右边询问的影响
for each (p, q), max(px + qy)
(a, b) is better than (p, q), p < a
ax + by > px + qy
(a - p) x > -(b - q) y
if y = 0 : max-min check
if -y > 0 : - x / y < (b - q) / (a - p)
上凸包。
if -y < 0 : - x / y > (b - q) / (a - p)
下凸包。
*/