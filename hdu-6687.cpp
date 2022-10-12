#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e5 + 10, L = 33;
int n, k, a[N], b[N];
struct trie {
   int ch[N * L][2], sz[N * L], id;
   int newnode() { id ++; ch[id][0] = ch[id][1] = sz[id] = 0; return id; }
   void init() { id = 0; newnode(); }
   void insert(int x) {
      int u = 1; sz[1] ++;
      per(i, k, 0) {
         int &v = ch[u][x >> i & 1];
         u = v ? v : v = newnode(); sz[u] ++;
      }
   }
   void upd(int u) { sz[u] = sz[ch[u][0]] + sz[ch[u][1]]; }
} A, B;
ll ans;
void dfs(int u, int v, int d, int val) {
   if(!A.sz[u] || !B.sz[v]) return ;
   if(d == -1) {
      A.sz[u] --; B.sz[v] --; ans += val;
      return ;
   }
   dfs(A.ch[u][0], B.ch[v][1], d - 1, val ^ (1 << d));
   dfs(A.ch[u][1], B.ch[v][0], d - 1, val ^ (1 << d));
   dfs(A.ch[u][0], B.ch[v][0], d - 1, val);
   dfs(A.ch[u][1], B.ch[v][1], d - 1, val);
   A.upd(u); B.upd(v);
}
int main() {
   int test; scanf("%d", &test);
   while(test --) {
      scanf("%d", &n);
      int w = 0;
      rep(i, 1, n) scanf("%d", a + i), w = max(w, a[i]);
      rep(i, 1, n) scanf("%d", b + i), w = max(w, b[i]);
      k = 1;
      rep(i, 2, 30) if((1 << i) <= w) k = i; else break ;
      A.init(); B.init();
      rep(i, 1, n) A.insert(a[i]);
      rep(i, 1, n) B.insert(b[i]);
      ans = 0; dfs(1, 1, k, 0);
      printf("%lld\n", ans);
   }
   return 0;
}