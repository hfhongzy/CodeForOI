#include <algorithm>
#include <cstdio>
#include <set>
using namespace std;
const int N = 2e5 + 10;
int n, p[N], w[N], to[N], nxt[N], hd[N], ec;
multiset<int> f[N];
void add(int u, int v) { to[++ ec] = v; nxt[ec] = hd[u]; hd[u] = ec; }
void merge(int u, int v) {
   if(f[p[u]].size() < f[p[v]].size()) swap(p[u], p[v]);
   u = p[u]; v = p[v];
   for(multiset<int>::iterator it = f[v].begin(); it != f[v].end(); it ++) {
      f[u].insert(* it);
   }
}
void dfs(int u) {
   p[u] = u;
   for(int i = hd[u]; i; i = nxt[i]) { dfs(to[i]); merge(u, to[i]); }
   multiset<int>::iterator it = f[p[u]].lower_bound(w[u]);
   if(it != f[p[u]].begin()) f[p[u]].erase(-- it);
   f[p[u]].insert(w[u]);
}
int main() {
   scanf("%d", &n);
   for(int i = 1; i <= n; i ++) scanf("%d", w + i);
   for(int i = 2, f; i <= n; i ++) { scanf("%d", &f); add(f, i); }
   dfs(1);
   printf("%d\n", (int) f[p[1]].size());
   return 0;
}