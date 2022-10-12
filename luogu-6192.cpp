#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
#define queue STL_queue_Always_MLE
using namespace std;
const int N = 105, INF = 1e9 + 10;
template <class T>
struct queue {
   T q[1 << 18], *l, *r;
   queue() { l = r = q; }
   inline int get() { return *l ++; }
   inline void push(T x) { *r ++ = x; }
   inline void clear() { l = r = q; }
   inline bool empty() { return l == r; }
};
int n, m, k, dp[N][1 << 10];
struct Edge { int v, w; };
vector<Edge> G[N];
queue<int> q;
bool use[N];
void spfa(int s) {
   while(!q.empty()) {
      int u = q.get(); use[u] = 0;
      for(auto e : G[u]) if(dp[e.v][s] > e.w + dp[u][s]) {
         dp[e.v][s] = e.w + dp[u][s];
         if(!use[e.v]) { use[e.v] = 1; q.push(e.v); }
      }
   }
}
int main() {
   scanf("%d%d%d", &n, &m, &k);
   int u, v, w;
   rep(i, 1, m) {
      scanf("%d%d%d", &u, &v, &w);
      G[u].push_back({v, w});
      G[v].push_back({u, w});
   }
   memset(dp, 0x3f, sizeof dp);
   rep(i, 1, k) {
      scanf("%d", &u);
      dp[u][1 << (i - 1)] = 0;
   }
   rep(i, 1, (1 << k) - 1) {
      q.clear();
      rep(j, 1, n) {
         for(int s = i; s; s = (s - 1) & i) {
            dp[j][i] = min(dp[j][i], dp[j][s] + dp[j][i ^ s]);
         }
         if(dp[j][i] < INF) {
            q.push(j); use[j] = 1;
         }
      }
      spfa(i);
   }
   int ans = INF;
   rep(i, 1, n) ans = min(ans, dp[i][(1 << k) - 1]);
   printf("%d\n", ans);
   return 0;
}