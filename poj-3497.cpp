#include <algorithm>
#include <cstdio>
#include <queue>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;

const int N = 256;
int n, map1[N], map2[N], ml[N], mr[N];
int v1[N][N], v2[N][N], pos[N];
char c1[N], c2[N];
int main() {
   int test; scanf("%d", &test);
   while(test --) {
      scanf("%d", &n);
      static char str[128];
      rep(i, 1, n) ml[i] = mr[i] = pos[i] = 0;
      rep(i, 1, n) { scanf("%s", str); map1[*str] = i; c1[i] = *str; }
      rep(i, 1, n) { scanf("%s", str); map2[*str] = i; c2[i] = *str; }
      rep(i, 1, n) {
         scanf("%s", str); int u = map1[*str];
         rep(j, 2, n + 1) v1[u][j - 1] = map2[str[j]];
      }
      rep(i, 1, n) {
         scanf("%s", str); int u = map2[*str];
         rep(j, 2, n + 1) v2[u][map1[str[j]]] = j;
      }
      queue<int> q;
      rep(i, 1, n) q.push(i);
      while(q.size()) {
         int u = q.front(), v = v1[u][++ pos[u]];
         if(!mr[v]) { q.pop(); mr[v] = u; ml[u] = v; continue ; }
         if(v2[v][mr[v]] > v2[v][u]) { q.pop(); q.push(mr[v]); mr[v] = u; ml[u] = v; }
      }
      vector< pair<char, char> > ans;
      rep(i, 1, n) ans.pb(make_pair(c1[i], c2[ml[i]]));
      sort(ans.begin(), ans.end());
      for(int i = 0; i < (int) ans.size(); i ++) printf("%c %c\n", ans[i].first, ans[i].second);
      if(test) putchar('\n');
   }
   return 0;
}