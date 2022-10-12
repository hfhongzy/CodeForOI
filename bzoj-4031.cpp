#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;
const int N = 105, mod = 1e9;
int n, a[N][N];
int gauss() {
	int sgn = 1;
	for(int i = 1; i < n; i ++) {
		for(int j = i + 1; j < n; j ++) {
			while(1) {
				int x = a[i][i], y = a[j][i];
				if(y == 0) break ;
				int t = x / y;
				for(int k = i; k < n; k ++) {
					(a[i][k] += mod - 1ll * a[j][k] * t % mod) %= mod;
					swap(a[i][k], a[j][k]);
				}
				sgn *= -1;
			}
		}
	}
	int ans = 1;
	for(int i = 1; i < n; i ++)
		ans = 1ll * ans * a[i][i] % mod;
	return sgn == 1 ? ans : (mod - ans) % mod;
}
char s[N][N];
int id[N][N];
void ins(int u, int v) {
	a[u][v] = mod - 1; a[v][u] = mod - 1;
	a[u][u] ++; a[v][v] ++;
}
int main() {
	int n, m; scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++) {
		scanf("%s", s[i] + 1);
		for(int j = 1; j <= m; j ++) if(s[i][j] == '.') {
			id[i][j] = ++ ::n; 
			if(id[i - 1][j]) ins(id[i - 1][j], id[i][j]);
			if(id[i][j - 1]) ins(id[i][j - 1], id[i][j]);
		}
	}
	printf("%d\n", gauss());
	return 0;
}