#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 120;
int n, I, E, A, x[N], y[N];
//A = I + E/2 - 1
int cross(int u, int v) {
	return x[u] * y[v] - x[v] * y[u];
}
int gcd(int x, int y) {
	return y ? gcd(y, x % y) : x;
}
int main() {
	freopen("input", "r", stdin);
	int test, number = 0;
	scanf("%d", &test);
	while(test --) {
		printf("Scenario #%d:\n", ++ number);
		scanf("%d", &n);
		for(int i = 0; i < n; i ++) {
			scanf("%d%d", x + i, y + i);
			if(i) {
				x[i] += x[i - 1];
				y[i] += y[i - 1];
			}
		}
		I = E = A = 0;
		for(int i = 0; i < n; i ++) {
			int r = (i + 1) % n;
			E += gcd(abs(x[i] - x[r]), abs(y[i] - y[r]));
			A += cross(i, r);
		}
		I = (A - E) / 2 + 1;
		printf("%d %d %d.%d\n\n", I, E, A / 2, A % 2 == 1 ? 5 : 0);
	}
	return 0;
}