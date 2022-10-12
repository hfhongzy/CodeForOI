#include <algorithm>
#include <cstdio>
using namespace std;
const int n = 26;
char p[n + 10];
bool vis[n + 10];
int cnt[n + 10];
int main() {
	int t; scanf("%d", &t);
	while(t --) {
		scanf("%s", p + 1);
		for(int i = 1; i <= n; i ++) p[i] = p[i] - 'A' + 1, cnt[i] = vis[i] = 0;
		for(int i = 1; i <= n; i ++) if(!vis[i]) {
			int u = i, sz = 0;
			while(!vis[u]) { vis[u] = 1; sz ++; u = p[u]; }
			cnt[sz] ++;
		}
		bool tag = 1;
		for(int i = 2; i <= n; i += 2)
			if(cnt[i] & 1) tag = 0;
		puts(tag ? "Yes" : "No");
	}
	return 0;
}