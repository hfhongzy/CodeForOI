#include <algorithm>
#include <cstdio>
#include <vector>
#define fs first
#define sc second
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int n, sz[N];
pair<ll, int> d[N];
vector<int> G[N];
ll dfs(int u, int d = 0) {
   ll ans = d;
   for(int v : G[u]) ans += dfs(v, d + 1);
   return ans;
}
int main() {
   scanf("%d", &n);
   rep(i, 1, n) scanf("%lld", &d[i].fs), d[i].sc = i, sz[i] = 1;
   sort(d + 1, d + n + 1);
   per(i, n, 2) {
      ll fd = d[i].fs - n + 2 * sz[i];
      int pos = lower_bound(d + 1, d + n + 1, make_pair(fd, 0)) - d;
      if(d[pos].fs != fd) { puts("-1"); return 0; }
      sz[pos] += sz[i]; G[d[pos].sc].pb(d[i].sc);
   }
   if(dfs(d[1].sc) != d[1].fs) puts("-1");
   else {
      rep(i, 1, n) for(int v : G[i]) printf("%d %d\n", i, v);
   }
   return 0;
}