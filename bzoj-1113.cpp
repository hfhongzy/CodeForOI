#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 250010;
int a[N], n, ans, st[N], top;
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++) scanf("%*d%d", a + i);
	for(int i = 1; i <= n; i ++) {
		while(top && st[top] >= a[i]) ans += st[top --] == a[i];
		st[++ top] = a[i];
	}
	printf("%d\n", n - ans);
	return 0;
}