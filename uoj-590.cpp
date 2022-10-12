#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 1e6 + 10;
const int INF = 2e9;
struct node {
	int x, y;
} a[N];
int n, m, ans;
int main() {
	scanf("%d%d", &n, &m);
	rep(i, 1, n) scanf("%d%d", &a[i].x, &a[i].y);
	sort(a + 1, a + n + 1, [&](node a, node b) { return a.x < b.x || (a.x == b.x && a.y < b.y); });
	priority_queue< int, vector<int>, greater<int> > q;
	rep(i, 1, n) {
		int j = i;
		while(j < n && a[j + 1].x == a[j].x) j ++;
		rep(k, i, j) q.push(a[k].y);
		for(int t = a[i].x, nt = j == n ? INF : a[j + 1].x; q.size() && t < nt; t ++) {
			rep(k, 1, m) {
				if(!q.size()) break ;
				int u = q.top(); q.pop(); ans = max(ans, t - u);
			}
		}
		i = j;
	}
	printf("%d\n", ans);
	return 0;
}