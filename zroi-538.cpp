#include <algorithm>
#include <cctype>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
const int N = 1e5 + 10;
namespace io {

char gc() {
	static char *S, *T, buf[1 << 15];
	if(S == T) T = (S = buf) + fread(buf, 1, 1 << 15, stdin);
	return S == T ? EOF : *S ++;
}
int read() {
	int x = 0; char c = gc();
	for(; !isdigit(c); c = gc()) ;
	for(; isdigit(c); c = gc()) 
		x = x * 10 + (c & 15);
	return x;
}

}
using io::read;
int n, m, ans, id[N], d[N];
struct Graph {

struct Edge {
	int v, nxt;
} e[(N + 20) * 2];
int hd[N], ec;
void clr() { fill(hd + 1, hd + n + 1, -1); ec = 0; }
void add(int u, int v) {
	e[ec] = {v, hd[u]}; hd[u] = ec ++;
}

} G1, G2;
void flood(int u, int cur) {
	id[u] = cur;
	for(int i = G1.hd[u]; ~ i; i = G1.e[i].nxt) {
		int v = G1.e[i].v;
		if(!id[v] && d[v] == 2) flood(v, cur);
	}
}
bool ins[N];
void dfs(int u, int pre, int s) {
	if(ins[u]) { ans += u == s; return ; }
	ins[u] = 1;
	for(int i = G2.hd[u]; ~ i; i = G2.e[i].nxt) if(pre != (i ^ 1)) {
		if(G2.e[i].v <= s) dfs(G2.e[i].v, i, s);
	}
	ins[u] = 0;
}
int main() {
	// freopen("input", "r", stdin);
	n = read(); m = read();
	if(m == n - 1) return puts("0"), 0;
	if(m == n) return puts("1"), 0;
	G1.clr();
	for(int u, v, i = 1; i <= m; i ++) {
		u = read(); v = read();
		G1.add(u, v); G1.add(v, u); d[u] ++; d[v] ++;
	}
	queue<int> q;
	for(int i = 1; i <= n; i ++) if(d[i] == 1) q.push(i);
	while(q.size()) {
		int u = q.front(); q.pop();
		for(int i = G1.hd[u]; ~ i; i = G1.e[i].nxt) {
			int v = G1.e[i].v;
			if(d[v] > 1) {
				if(-- d[v] == 1) q.push(v);
			}
		}
	}
	for(int i = 1; i <= n; i ++) if(d[i] == 2 && !id[i]) flood(i, i);
	G2.clr();
	for(int i = 1; i <= n; i ++) if(d[i] > 1) {
		int x = id[i] ? id[i] : i;
		for(int j = G1.hd[i]; ~ j; j = G1.e[j].nxt) {
			int v = G1.e[j].v;
			if(d[v] > 1) {
				int y = id[v] ? id[v] : v;
				if(x >= y) continue ;
				G2.add(x, y); G2.add(y, x);
			}
		}
	}
	for(int i = 1; i <= n; i ++) dfs(i, -1, i);
	printf("%d\n", ans >> 1);
	return 0;
}