#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
const int N = 1e5 + 10, S = N * 60;
int q, cur, rt, id, ch[S][10], sz[S];
vector<int> vec[S];
char s[66];
void update(int &u, int d, int cnt) {
	if(!u) u = ++ id;
	sz[u] += cnt;
	if(sz[u] == (int) vec[u].size() + 1) vec[u].push_back(cur);
	if(!s[d]) return ;
	update(ch[u][s[d] - 'a'], d + 1, cnt);
}
int query(int u, int v) {
	for(int d = 1; s[d]; d ++) {
		u = ch[u][s[d] - 'a'];
	}
	return vec[u].size() > v ? vec[u][v] : -1;
}
int main() {
	scanf("%d", &q); rt = id = 1;
	for(int op, lans = 0, t = 1; t <= q; t ++) {
		scanf("%d%s", &op, s + 1); cur = t;
		if(op == 1) update(rt, 1, 1);
		if(op == 2) update(rt, 1, -1);
		if(op == 3) {
			int a, b, c; scanf("%d%d%d", &a, &b, &c);
			int ans = query(1, ((long long) a * lans + b) % c);
			if(ans == -1) {
				lans = 1; puts("-1");
			} else {
				printf("%d\n", lans = ans);
			}
		}
		
	}
	return 0;
}