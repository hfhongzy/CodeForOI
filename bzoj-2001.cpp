#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
namespace io {

char *S, *T, buf[1 << 15];
char gc() {
	if(S == T) {
		T = (S = buf) + fread(buf, 1, 1 << 15, stdin);
		if(S == T) return EOF;
	}
	return *S ++;
}

int read() {
	int x = 0; char c = gc(); bool bo = 0;
	for(; c < '0' || c > '9'; c = gc()) bo |= c == '-';
	for(; c >= '0' && c <= '9'; c = gc()) x = x * 10 + (c & 15);
	return bo ? - x : x;
}

}
using io::read;
typedef long long ll;
const int N = 5e4 + 10;
const int INF = 1e9 + 10;
struct edge { int u, v, id; };
int n, m, q, w[N], qa[N], qw[N];
vector<edge> e[20];
ll ans[N];

int f[N];
void clr(int u) { f[u] = u; }
void clr(vector<edge> &e) {
	for(int i = 0; i < (int) e.size(); i ++) {
		clr(e[i].u); clr(e[i].v);
	}
}
int find(int u) {
	return u == f[u] ? u : f[u] = find(f[u]);
}
bool merge(int u, int v) {
	u = find(u); v = find(v); f[u] = v;
	return u == v ? 0 : 1;
}
bool cmp(edge x, edge y) {
	return w[x.id] < w[y.id];
}
void reduct(int l, int r, int dep) {
	static int tmp[N];
	for(int i = l; i <= r; i ++) tmp[i] = w[qa[i]], w[qa[i]] = INF;
	vector<edge> ne;
	clr(e[dep]); sort(e[dep].begin(), e[dep].end(), cmp);
	for(int i = 0; i < (int) e[dep].size(); i ++) {
		edge &ev = e[dep][i];
		if(merge(ev.u, ev.v) || w[ev.id] == INF) {
			ne.push_back(ev);
		}
	}
	for(int i = l; i <= r; i ++) if(tmp[i] != INF) w[qa[i]] = tmp[i];
	e[dep] = ne;
}
void contract(int l, int r, int dep, ll &val) {
	static int tmp[N];
	for(int i = l; i <= r; i ++) tmp[i] = w[qa[i]], w[qa[i]] = -INF;
	vector<edge> ne;
	clr(e[dep]); sort(e[dep].begin(), e[dep].end(), cmp);
	for(int i = 0; i < (int) e[dep].size(); i ++) {
		edge &ev = e[dep][i];
		if(merge(ev.u, ev.v) && w[ev.id] != -INF) {
			ne.push_back(ev);
		}
	}
	clr(e[dep]);
	for(int i = 0; i < (int) ne.size(); i ++) {
		edge &ev = ne[i];
		merge(ev.u, ev.v); val += w[ev.id];
	}
	for(int i = 0; i < (int) e[dep].size(); i ++) {
		edge &ev = e[dep][i];
		ev.u = find(ev.u); ev.v = find(ev.v);
	}
	for(int i = l; i <= r; i ++) if(tmp[i] != -INF) w[qa[i]] = tmp[i];
}
void solve(int l, int r, int dep, ll val) {
	if(l == r) {
		clr(e[dep]); w[qa[l]] = qw[l];
		sort(e[dep].begin(), e[dep].end(), cmp);
		ans[l] = val;
		for(int i = 0; i < (int) e[dep].size(); i ++) {
			edge &ev = e[dep][i];
			if(merge(ev.u, ev.v)) {
				ans[l] += w[ev.id];
			}
		}
		return ;
	}
	reduct(l, r, dep);
	contract(l, r, dep, val);
	reduct(l, r, dep);
	int mid = (l + r) >> 1;
	e[dep + 1] = e[dep]; solve(l, mid, dep + 1, val);
	e[dep + 1] = e[dep]; solve(mid + 1, r, dep + 1, val);
}
int main() {
	// freopen("input", "r", stdin);
	n = read(), m = read(), q = read();
	for(int i = 1; i <= m; i ++) {
		int u = read(), v = read(), w = read();
		e[0].push_back((edge) {u, v, i}); ::w[i] = w;
	}
	for(int i = 1; i <= q; i ++)
		qa[i] = read(), qw[i] = read();
	solve(1, q, 0, 0ll);
	for(int i = 1; i <= q; i ++)
		printf("%lld\n", ans[i]);
	return 0;
}