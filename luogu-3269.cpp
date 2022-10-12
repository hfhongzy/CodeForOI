#include <algorithm>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;
const int N = 1e4 + 10, INF = 1e9 + 10;
char s[N], t[4][N];
int m, n, nxt[N], len[4], f[N][16], g[N][16], pos[4][N];
bool hd[4][N];
void upmax(int &x, const int &y) { if(x < y) x = y; }
void upmin(int &x, const int &y) { if(x > y) x = y; }
bool match(int u, int v) {
	nxt[1] = 0;
	for(int i = 2; i <= len[u]; i ++) {
		int j = nxt[i - 1];
		for(; j && t[u][j + 1] != t[u][i]; j = nxt[j]) ;
		if(t[u][j + 1] == t[u][i]) j ++;
		nxt[i] = j;
	}
	int j = 0;
	for(int i = 1; i <= len[v]; i ++) {
		for(; j && t[u][j + 1] != t[v][i]; j = nxt[j]) ;
		if(t[u][j + 1] == t[v][i]) j ++;
		if(j == len[u]) return 1;
	}
	return 0;
}
int main() {
	// freopen("input", "r", stdin);
	int test;
	scanf("%d", &test);
	while(test --) {
		scanf("%s%d", s + 1, &m);
		n = strlen(s + 1);
		for(int i = 0; i < m; i ++) {
			scanf("%s", t[i] + 1);
			len[i] = strlen(t[i] + 1);
			fill(hd[i], hd[i] + n + 1, 0);
			nxt[1] = 0;
			for(int j = 2; j <= len[i]; j ++) {
				int k = nxt[j - 1];
				for(; k && t[i][k + 1] != t[i][j]; k = nxt[k]) ;
				if(t[i][k + 1] == t[i][j]) k ++;
				nxt[j] = k;
			}
			int k = 0;
			for(int j = 1; j <= n; j ++) {
				for(; k && t[i][k + 1] != s[j]; k = nxt[k]) ;
				if(t[i][k + 1] == s[j]) k ++;
				if(k == len[i]) hd[i][j - len[i] + 1] = 1;
			}
			pos[i][n + 1] = -1;
			for(int j = n; j >= 1; j --) {
				pos[i][j] = j >= len[i] && hd[i][j - len[i] + 1] ? j : pos[i][j + 1];
			}
		}
		int st = 0;
		for(int i = 0; i < m; i ++) {
			for(int j = 0; j < m; j ++) if(len[j] >= len[i] && j != i) {
				if(match(i, j) && (len[i] != len[j] || i < j)) {
					st ^= 1 << i; break ;
				}
			}
		}
		g[0][0] = 0;
		for(int i = 1; i <= n; i ++) {
			for(int j = 0; j < (1 << m); j ++) {
				g[i][j] = g[i - 1][j];
				for(int k = 0; k < m; k ++) if(j >> k & 1) {
					int r = pos[k][i], l = max(1, r - len[k] + 1);
					if(r == -1 || l > i) continue ;
					upmax(g[i][j], g[l - 1][j ^ (1 << k)] + i - l + 1);
				}
			}
		}
		for(int i = 0; i <= n; i ++) fill(f[i], f[i] + (1 << m), INF);
		f[0][0] = 0; int pre[4][16];
		for(int i = 0; i < m; i ++) fill(pre[i], pre[i] + (1 << m), INF);
		for(int i = 0; i < m; i ++) pre[i][0] = 0;
		deque<int> q[4][16];
		for(int i = 1; i <= n; i ++) {
			for(int k = 0; k < m; k ++) if(!(st >> k & 1)) {
				for(int j = 0; j < (1 << m); j ++) if(!(j & st)) {
					if(i - len[k] - 1 >= 0) {
						upmin(pre[k][j], f[i - len[k] - 1][j]);
					}
					deque<int> &cur = q[k][j];
					while(cur.size() && cur.front() < i - len[k]) cur.pop_front();
					if(f[i - 1][j] >= INF) continue ;
					while(cur.size()) {
						int u = cur.back();
						if(f[i - 1][j] - (i - 1) <= f[u][j] - u) cur.pop_back();
						else break ;
					}
					cur.push_back(i - 1);
				}
			}
			for(int j = 0; j < (1 << m); j ++) if(!(j & st)) {
				for(int k = 0; k < m; k ++) if(j >> k & 1) {
					if(i < len[k] || !hd[k][i - len[k] + 1]) continue ;
					upmin(f[i][j], pre[k][j ^ (1 << k)] + len[k]);
					deque<int> &cur = q[k][j ^ (1 << k)];
					if(cur.size()) {
						int u = cur.front();
						upmin(f[i][j], i - u + f[u][j ^ (1 << k)]);
					}
				}
			}
		}
		int mn = INF, mx = 0;
		for(int i = 1; i <= n; i ++) upmin(mn, f[i][st ^ ((1 << m) - 1)]);
		for(int i = 0; i < (1 << m); i ++) upmax(mx, g[n][i]);
		printf("%d %d\n", mn, mx);
	}
	return 0;
}