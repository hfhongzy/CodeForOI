#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 1010;
int x, y, z, f[N], sg[N];
bool vis[N];
int main() {
	int n = 1; f[0] = f[1] = 1;
	while(f[n] < 1000) { f[n + 1] = f[n] + f[n - 1]; n ++; }
	sg[0] = 0;
	for(int i = 1; i <= 1000; i ++) {
		for(int j = 1; j <= n && i >= f[j]; j ++) vis[sg[i - f[j]]] = 1;
		sg[i] = 0;
		while(vis[sg[i]]) sg[i] ++;
		for(int j = 1; j <= n && i >= f[j]; j ++) vis[sg[i - f[j]]] = 0;
	}
	while(~ scanf("%d%d%d", &x, &y, &z)) {
		if(x == 0 && y == 0 && z == 0) break ;
		puts((sg[x] ^ sg[y] ^ sg[z]) == 0 ? "Nacci" : "Fibo");
	}
	return 0;
}