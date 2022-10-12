#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 405;
int test, n, m, v1[N][N], rnk[N][N], pos[N], ml[N], mr[N];
int main() {
   scanf("%d", &test);
   while(test --) {
      scanf("%d%d", &n, &m);
      rep(i, 1, n) {
         int c = 0, x = 0;
         rep(j, 1, m) {
            scanf("%d", &x);
            if(x) {
               v1[i][++ c] = x;
               rnk[x][i] = j;
            }
         }
      }
      rep(i, 1, n) pos[i] = mr[i] = ml[i] = 0;
      queue<int> q;
      rep(i, 1, n) q.push(i);
      while(q.size()) {
         int u = q.front(), v = v1[u][++ pos[u]];
         if(rnk[v][mr[v]] < rnk[v][u]) { q.pop(); if(mr[v]) q.push(mr[v]); mr[v] = u; ml[u] = v; }
      }
      rep(i, 1, n) printf("%d%c", ml[i], " \n"[i == n]);
   }
   return 0;
}