#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
const int N = 2e5 + 10;
int n, m, q, eu[N], ev[N], ans[N];
vector<int> bpos[N];

int f[N], cur, sz[N];
void init() {
	cur = n;
	for(int i = 1; i <= n; i ++) {
		sz[i] = 1; f[i] = i;
	}
}
int find(int u) {
	while(u ^ f[u]) u = f[u];
	return u;
}
int st[N][2], tp; //0 : fa
int merge(int u) {
	int x = eu[u], y = ev[u];
	x = find(x); y = find(y);
	if(x == y) return 0;
	if(sz[x] < sz[y]) swap(x, y);
	tp ++; st[tp][0] = x; st[tp][1] = y;
	f[y] = x; sz[x] += sz[y]; cur --; return 1;
}
void pop() {
	int x = st[tp][0], y = st[tp][1];
	tp --; sz[x] -= sz[y]; f[y] = y; cur ++;
}
void solve(int l, int r, vector<int> &vec) {
	if(!vec.size()) {
		for(int i = l; i <= r; i ++) ans[i] = 0;
		return ;
	}
	int mcnt = 0; vector<int> son;
	for(int i = 0; i < (int) vec.size(); i ++) {
		int v = vec[i];
		vector<int>::iterator it = lower_bound(bpos[v].begin(), bpos[v].end(), l);
		if(it == bpos[v].end() || *it > r) {
			mcnt += merge(v);
		} else {
			son.push_back(v);
		}
	}
	if(cur == 1 || l == r) {
		for(int i = l; i <= r; i ++) ans[i] = cur == 1;
	} else {
		int mid = (l + r) >> 1;
		solve(l, mid, son); solve(mid + 1, r, son);
	}
	while(mcnt --) pop();
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i ++)
		scanf("%d%d", eu + i, ev + i);
	scanf("%d", &q);
	for(int i = 1; i <= q; i ++) {
		int sz; scanf("%d", &sz);
		while(sz --) {
			int x; scanf("%d", &x);
			bpos[x].push_back(i);
		}
	}
	init();
	vector<int> vec;
	for(int i = 1; i <= m; i ++) vec.push_back(i);
	solve(1, q, vec);
	for(int i = 1; i <= q; i ++)
		puts(ans[i] ? "Connected" : "Disconnected");
	return 0;
}