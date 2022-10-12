#include <algorithm>
#include <vector>
#include <cstdio>
#include <cmath>
#define sgn(x) (x > 0 ? 1 : -1)
#define abs(x) (x > 0 ? x : -x)
using namespace std;
char gc() {
   static char buf[1 << 16], *S, *T;
   if(S == T) T = (S = buf) + fread(buf, 1, 1 << 16, stdin);
   return S == T ? EOF : *S ++;
}
template<class T> void read(T &x) {
   x = 0; bool na = 0; char c = gc();
   for(; c < '0' || c > '9'; c = gc()) na |= c == '-';
   for(; c >= '0' && c <= '9'; c = gc()) x = x * 10 + (c & 15);
   if(na) x = -x;
}
typedef long long ll;
const int N = 1e5 + 10, M = 16*5e5 + 10;
int size;
struct node {
	int l, r, id;
	bool operator < (const node &b) const {
		if(l / size == b.l / size) return r < b.r;
		return l / size < b.l / size;
	}
} qn[M];
int n, logn, m, q, rt = 1, c[N], b[N], a[N], f[N][17], cnt[2][N];
int d[N], dfn[N], dr[N], idx;
vector<int> G[N];
ll ans[M], cur;
bool res[M];
void MoQry(int l1, int r1, int l2, int r2, int id) {
	if(l1 > r1 || l2 > r2) return ;
	qn[++ q] = (node) {r1, r2, id};
	if(l1 != 1) qn[++ q] = (node) {l1 - 1, r2, -id};
	if(l2 != 1) qn[++ q] = (node) {r1, l2 - 1, -id};
	if(l1 != 1 && l2 != 1) qn[++ q] = (node) {l1 - 1, l2 - 1, id};
}
void MoPush(int t, int x) { cnt[t][x] ++; cur += cnt[t ^ 1][x]; }
void MoPop(int t, int x) { cnt[t][x] --; cur -= cnt[t ^ 1][x]; }
void dfs(int u, int fa = 0) {
	dfn[u] = ++ idx; d[u] = d[fa] + 1; f[u][0] = fa;
	for(int i = 1; i < logn; i ++)
		f[u][i] = f[f[u][i - 1]][i - 1];
	for(int i = 0; i < (int) G[u].size(); i ++) {
		int v = G[u][i];
		if(v ^ fa) dfs(v, u);
	}
	dr[u] = idx;
}
int Kth(int u, int k) {
	for(int i = logn - 1; ~ i; i --)
		if(k >> i & 1) u = f[u][i];
	return u;
}
bool Rev(int u) {
	return dfn[u] < dfn[rt] && dfn[rt] <= dr[u];
}
struct Range {
	int l, r; bool rev;
	void get(int u) {
		if(!Rev(u)) {
			l = u == rt ? 1 : dfn[u];
			r = u == rt ? n : dr[u];
			rev = 0;
		} else {
			// puts("!");
			int v = Kth(rt, d[rt] - d[u] - 1);
			l = dfn[v]; r = dr[v]; rev = 1;
		}
	}
	void qwith(const Range &b, int id) {
		if(!rev) {
			if(!b.rev) MoQry(l, r, b.l, b.r, id);
			else {
				MoQry(l, r, 1, b.l - 1, id);
				MoQry(l, r, b.r + 1, n, id);
			}
		} else {
			if(!b.rev) {
				MoQry(1, l - 1, b.l, b.r, id);
				MoQry(r + 1, n, b.l, b.r, id);
			} else {
				MoQry(1, l - 1, 1, b.l - 1, id);
				MoQry(r + 1, n, 1, b.l - 1, id);
				MoQry(1, l - 1, b.r + 1, n, id);
				MoQry(r + 1, n, b.r + 1, n, id);
			}
		}
	}
} T1, T2;
int main() {
	// freopen("input", "r", stdin);
	read(n); read(m);
	for(logn = 1; (1 << logn) <= n; logn ++) ;
	for(int i = 1; i <= n; i ++) { read(c[i]); b[i] = c[i]; }
	for(int i = 1, u, v; i < n; i ++) {
		read(u); read(v); G[u].push_back(v); G[v].push_back(u);
	}
	dfs(1); sort(b + 1, b + n + 1);
	for(int i = 1; i <= n; i ++) a[dfn[i]] = lower_bound(b + 1, b + n + 1, c[i]) - b;
	for(int op, u, v, i = 1; i <= m; i ++) {
		read(op); read(u);
		if(op == 1) rt = u;
		if(op == 2) {
			read(v); res[i] = 1;
			T1.get(u); T2.get(v); T1.qwith(T2, i);
		}
	}
	size = max(1, (int) sqrt(n + 0.5));
	for(int i = 1; i <= q; i ++) if(qn[i].l > qn[i].r) swap(qn[i].l, qn[i].r);
	sort(qn + 1, qn + q + 1);
	int l = 0, r = 0;
	for(int i = 1; i <= q; i ++) {
		while(r < qn[i].r) MoPush(1, a[++ r]);
		while(l < qn[i].l) MoPush(0, a[++ l]);
		while(l > qn[i].l) MoPop(0, a[l --]);
		while(r > qn[i].r) MoPop(1, a[r --]);
		// printf("cur = %lld\n", cur);
		ans[abs(qn[i].id)] += sgn(qn[i].id) * cur;
	}
	for(int i = 1; i <= m; i ++) if(res[i]) printf("%lld\n", ans[i]);
	return 0;
}