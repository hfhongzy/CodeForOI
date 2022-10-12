#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;
const int N = 1e5 + 10;
int n, z[N + N], Map[N];
char s[N + N], t[N];
int main() {
	int test;
	scanf("%d", &test);
	while(test --) {
		scanf("%s", t + 1);
		for(int i = 1; i <= 26; i ++) {
			Map[t[i]] = 'a' + i - 1;
		}
		scanf("%s", s + 1); n = strlen(s + 1);
		for(int i = n + 1; i <= 2 * n; i ++) {
			s[i] = t[s[i - n] - 'a' + 1];
		}
		n *= 2; s[n + 1] = 0;
		for(int i = 2, mid = 0, r = 0; i <= n; i ++) {
			z[i] = i < r ? min(r - i + 1, z[i - mid + 1]) : 0;
			while(s[z[i] + 1] == s[i + z[i]]) z[i] ++;
			if(i + z[i] - 1 > r) {
				r = i + z[i] - 1; mid = i;
			}
		}
		z[n + 1] = 0;
		for(int i = (n + 3) / 4; i <= n / 2; i ++) {
			if(z[n / 2 + i + 1] + i == n / 2) {
				for(int j = 1; j <= i; j ++) putchar(s[j]);
				for(int j = 1; j <= i; j ++) putchar(Map[s[j]]);
				break ;
			}
		}
		putchar('\n');
	}
	return 0;
}