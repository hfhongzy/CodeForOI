#include <algorithm>
#include <cstdio>
using namespace std;
int n, x, y, d;
char s[300005];
int main() {
	scanf("%d%d%d%s", &n, &x, &y, s + 1);
	for(int i = 1; i <= n; i ++)
		d += s[i] == '0' && s[i - 1] != '0';
	printf("%lld\n", min((d - 1ll) * x + y, 1ll * y * d));
	return 0;
}