#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 1e6 + 10;
int a[N], n;
char s[N];
int main() {
	scanf("%d%s", &n, s); n --;
	for(int i = 0; i <= n; i ++) {
		a[i] = s[i] - '0' - 1;
	}
	int ans = 0;
	for(int i = 0; i <= n; i ++) {
		if((n & i) == i) ans ^= a[i] & 1;
	}
	if(ans == 1) puts("1");
	else {
		for(int i = 0; i <= n; i ++) {
			if(a[i] == 1) { puts("0"); return 0; }
			a[i] >>= 1;
		}
		ans = 0;
		for(int i = 0; i <= n; i ++) {
			if((n & i) == i) ans ^= a[i] & 1;
		}
		printf("%d\n", ans ? 2 : 0);
	}
	return 0;
}