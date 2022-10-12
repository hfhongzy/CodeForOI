#include <bits/stdc++.h>
using namespace std;
int dir(char c) {
   return c >= 'A' && c <= 'Z' ? c - 'A' : 26 + c - 'a';
}
const int N = 1 << 13;
const int S = 1 << 21;
struct namer {
   int id, ch[S][52], num[S];
   namer() { id = 1; }
   int q(char *s) {
      int u = 1;
      for(; *s; s ++) {
         int &v = ch[u][dir(*s)];
         u = v ? v : v = ++ id;
      }
      if(!num[u]) num[u] = ++ *num;
      return num[u];
   }
} mp;
int n, m;
vector<int> G[N];

stack<int> st;
bool ins[N];
int dfn[N], low[N], bel[N], scc, idx;
void tarjan(int u) {
   st.push(u); ins[u] = 1; dfn[u] = low[u] = ++ idx;
   for(int v : G[u]) {
      if(!dfn[v]) {
         tarjan(v);
         low[u] = min(low[u], low[v]);
      } else if(ins[v]) {
         low[u] = min(low[u], dfn[v]);
      }
   }
   if(low[u] == dfn[u]) {
      scc ++;
      int v = 0;
      do {
         v = st.top(); st.pop(); ins[v] = 0; bel[v] = scc;
      } while(v != u);
   }
}
int main() {
   scanf("%d", &n);
   static char s[16], t[16];
   vector<pair<int, int>> couple;
   for(int i = 0; i < n; i ++) {
      scanf("%s%s", s, t);
      int u = mp.q(s), v = mp.q(t);
      G[u].emplace_back(v);
      couple.emplace_back(u, v);
   }
   scanf("%d", &m);
   for(int i = 0; i < m; i ++) {
      scanf("%s%s", s, t);
      int u = mp.q(s), v = mp.q(t);
      G[v].emplace_back(u);
   }
   for(int i = 1; i <= 2 * n; i ++) if(!dfn[i]) tarjan(i);
   for(auto p : couple) {
      puts(bel[p.second] == bel[p.first] ? "Unsafe" : "Safe");
   }
   return 0;
}