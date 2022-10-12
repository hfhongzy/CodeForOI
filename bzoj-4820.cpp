#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 305 * 305;
int n, m, ch[N][2], fail[N], bel[N], id = 1;
char s[N];
void insert(int cur) {
	int u = 1;
	for(int i = 1;	i <= m; i ++) {
		int &v = ch[u][s[i] == 'T'];
		u = v ? v : v = ++ id;
	}
	bel[u] = cur;
}
void buildac() {
	static int v, q[N], ql, qr; fail[1] = 1;
	for(int i = 0; i < 2; i ++) if(v = ch[1][i]) {
		q[qr ++] = v; fail[v] = 1;
	} else ch[1][i] = 1;
	while(ql ^ qr) {
		int u = q[ql ++];
		for(int i = 0; i < 2; i ++) if(v = ch[u][i]) {
			q[qr ++] = v; fail[v] = ch[fail[u]][i];
		} else ch[u][i] = ch[fail[u]][i];
	}
}
double dp[N];
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++) {
		scanf("%s", s + 1); insert(i);
	}
	buildac();
	for(int i = 1; i <= n; i ++)
	return 0;
}