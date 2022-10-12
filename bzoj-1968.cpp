#include <cstdio>
using namespace std;
int m, f[2000011];
int main() {
	scanf("%d", &m);
	int num = 0;
	for(int i = 1; i <= m; i ++)
		num += (m - i) / i + 1;
	printf("%d\n", num);
	return 0;
}