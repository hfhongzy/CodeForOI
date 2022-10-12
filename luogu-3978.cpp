#include <cstdio>

int main() {
	int n; scanf("%d", &n);
	long double t = n;
	printf("%.9Lf\n", t * (t + 1) / (4 * t - 2));
	return 0;
}