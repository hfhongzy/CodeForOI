#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 4040;
int n;
namespace force {

int mx[N], my[N], a[N], b[N], pos[N];
ll work(int *p) {
   copy(a + 1, a + n + 1, b + 1);
   for(int i = 1; i < n; i ++) {
      int x = p[i];
      swap(b[mx[x]], b[my[x]]);
   }
   ll res = 0;
   for(int i = 1; i <= n; i ++) pos[b[i]] = i;
   for(int i = 1; i <= n; i ++) res = res * 10 + pos[i] - 1;
   return res;
}
void main() {
   for(int i = 1, x; i <= n; i ++) {
      scanf("%d", &x); a[x] = i;
   }  
   for(int i = 1; i < n; i ++) {
      scanf("%d%d", mx + i, my + i);   
   }
   static int p[N];
   for(int i = 1; i < n; i ++) p[i] = i;
   ll ans = 1e18 + 10;
   do {
      ans = min(ans, work(p));
   } while(next_permutation(p + 1, p + n));
   static int pr[N];
   for(int i = n; i >= 1; i --) pr[i] = ans % 10 + 1, ans /= 10;
   for(int i = 1; i <= n; i ++) printf("%d ", pr[i]);
   printf("\n");
}

}
namespace sub {

int p[N], f[N], ans[N];
bool use[N];
int find(int u) {
   return u == f[u] ? u : f[u] = find(f[u]);
}
void unite(int u, int v) {
   f[find(u)] = find(v);
}
void main() {
   int x;
   rep(i, 1, n) {
      scanf("%d", &x);
      p[x] = i;
      f[i] = i;
      use[i] = 0;
   }
   rep(i, 1, n - 1) scanf("%*d%*d");
   rep(i, 1, n) {
      rep(j, 1, n) if(!use[j] && (i == n || find(p[i]) != find(j))) {
         unite(p[i], j); ans[i] = j; use[j] = 1; break ;
      }
   }
   rep(i, 1, n) printf("%d%c", ans[i], " \n"[i == n]);
}

}
int main() {
// freopen("tree.in", "r", stdin);
// freopen("tree.out", "w", stdout);
   int t; scanf("%d", &t);
   while(t --) {
      scanf("%d", &n);
      if(n <= 10) { force::main(); continue ; }
      else sub::main();
   }
   return 0;
}
/*
1
5
1 2 5 3 4
1 2
1 3
1 4
1 5
*/