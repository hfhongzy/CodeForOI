#include <algorithm>
#include <cstdio>
#include <vector>
#include <set>
using namespace std;
const int N = 2e5 + 5;
const int M = 100005;
char str[M];
struct SAM {

int id, la, nxt[N][26], len[N], link[N];
void clr(int x) { fill(nxt[x], nxt[x] + 26, -1); }
void init() {
	link[0] = -1; clr(0);
}
int a[N], cur[N], w[N], pos[N];
void extend(int c) {
	int u = ++ id, p = la;
	len[u] = len[la] + 1; clr(u);
	for(; ~ p && -1 == nxt[p][c]; p = link[p]) {
		nxt[p][c] = u;
	}
	if(p == -1) {
	} else {
		int q = nxt[p][c];
		if(len[p] + 1 == len[q]) {
			link[u] = q;
		} else {
			int q0 = ++ id;
			copy(nxt[q], nxt[q] + 26, nxt[q0]);
			len[q0] = len[p] + 1; link[q0] = link[q];
			link[q] = link[u] = q0;
			for(; ~ p && nxt[p][c] == q; p = link[p]) {
				nxt[p][c] = q0;
			}
		}
	}
	la = u; w[u] = 1; pos[u] = len[la];
}
void tpo() {
	static int cnt[N];
	int n = len[la];
	for(int i = 1; i <= id; i ++) cnt[len[i]] ++;
	for(int i = 1; i <= n; i ++) cnt[i] += cnt[i - 1];
	for(int i = 1; i <= id; i ++) a[cnt[len[i]] --] = i;
}

} sam;
multiset<int> Sr, S;
vector<int> sr[M], s[2][M];
int main() {
	freopen("input", "r", stdin);
	scanf("%s", str);
	sam.init();
	for(int i = 0; str[i]; i ++) sam.extend(str[i] - 'a');
	sam.tpo();
	int n = sam.len[sam.la];
	for(int i = sam.id; i >= 1; i --) {
		int u = sam.a[i], f = sam.link[u];
		sam.w[f] += sam.w[u]; sam.pos[f] ^= sam.pos[u];
		if(sam.w[u] == 1) {
			int r = sam.pos[u], m = r - sam.len[f];
			Sr.insert(r); sr[m + 1].push_back(r);
			if(m ^ r) {
				s[0][m + 1].push_back(r - m + 1);
				s[1][r + 1].push_back(r - m + 1);
			}
		}
	}
	for(int i = 1; i <= n; i ++) {
		for(int u = 0; u < (int) s[0][i].size(); u ++) S.insert(s[0][i][u]);
		for(int u = 0; u < (int) s[1][i].size(); u ++) S.erase(S.lower_bound(s[1][i][u]));
		for(int u = 0; u < (int) sr[i].size(); u ++) Sr.erase(Sr.lower_bound(sr[i][u]));
		int ans = n;
		if(S.size()) ans = min(ans, *S.begin());
		if(Sr.size()) ans = min(ans, *Sr.begin() - i + 1);
		printf("%d\n", ans);
	}
	return 0;
}