#include <algorithm>
#include <cstdio>
#include <queue>
using namespace std;
typedef long long ll;
const int N = 1e5 + 100;
struct Node {
	ll cnt; int d;
	bool operator < (const Node &b) const {
		return cnt > b.cnt || (cnt == b.cnt && d > b.d);
	}
};
int n, k;
ll a[N];
priority_queue<Node> pq;
int main() {
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i ++) scanf("%lld", a + i);
	if((n - 1) % (k - 1)) n += (k - 1) - ( (n - 1) % (k - 1) );
	for(int i = 1; i <= n; i ++) pq.push((Node) {a[i], 0});
	ll ans = 0;
	while(pq.size() > 1) {
		Node u; u.cnt = u.d = 0;
		for(int i = 1; i <= k; i ++) {
			u.cnt += pq.top().cnt;
			u.d = max(u.d, pq.top().d + 1);
			pq.pop();
		}
		pq.push(u); ans += u.cnt;
	}
	printf("%lld\n%d\n", ans, pq.top().d);
	return 0;
}