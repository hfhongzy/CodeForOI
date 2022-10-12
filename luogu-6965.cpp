#include <bits/stdc++.h>
#define pb push_back
#define LOG(...) fprintf(stderr, __VA_ARGS__);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 4e6 + 20;
int n, rt, id, bac[N], ch[N][2];
int dfn[N], low[N], idx, bel[N], scc;
vector<int> G[N];
stack<int> st;
bool ins[N];
void tarjan(int u) {
  dfn[u] = low[u] = ++ idx; st.push(u); ins[u] = 1;
  for(int v : G[u]) {
    if(!dfn[v]) {
      tarjan(v); low[u] = min(low[u], low[v]);
    } else if(ins[v]) {
      low[u] = min(low[u], dfn[v]);
    }
  }
  if(low[u] == dfn[u]) {
    int v = 0; scc ++;
    do {
      v = st.top(); st.pop(); ins[v] = 0; bel[v] = scc;
    } while(v != u);
  }
}
void insert(char *s, int c, int rev_c) {
  int u = rt;
  for(int i = 1; s[i]; i ++) {
    int &v = ch[u][s[i] & 1];
    if(!v) {
      v = ++ id; bac[v] = v;
    }
    u = v;
  }
  ++ id; G[id].pb(bac[u]);
  G[c].pb(bac[u]);
  G[id].pb(rev_c);
  bac[u] = id;
}
void insert2(char *s, int c, int rev_c) {
  int u = rt;
  for(int i = 1; s[i]; i ++) {
    int &v = ch[u][s[i] & 1];
    if(!v) {
      v = ++ id; bac[v] = v;
    }
    u = v;
  }
  ++ id; G[bac[u]].pb(id);
  G[bac[u]].pb(rev_c);
  G[c].pb(id);
  bac[u] = id;
}
void build(int u, int la = -1) {
  if(!u) return ;
  if(~la) G[u].pb(la);
  build(ch[u][0], bac[u]); build(ch[u][1], bac[u]);
}
void build2(int u, int la = -1) {
  if(!u) return ;
  if(~la) G[la].pb(u);
  build2(ch[u][0], bac[u]); build2(ch[u][1], bac[u]);
}
int main() {
  scanf("%d", &n);
  if(n >= int(1e5)) {
    puts("NO"); return 0;
  }
  id = rt = 2 * n + 1; bac[rt] = rt;
  static char s[N];
  vector<string> str(n + 1);
  vector<int> pos(n + 1);
  rep(i, 1, n) {
    scanf("%s", s + 1); str[i] = string(s + 1);
    int p = -1;
    for(int j = 1; s[j]; j ++) if(s[j] == '?') {
      p = j; break ;
    }
    if(!~p) {
      p = 1;
      if(s[1] == '1') G[i].pb(i + n);
      else G[i + n].pb(i);
    }
    pos[i] = p - 1;
    s[p] = '0'; insert(s, i, i + n);
    s[p] = '1'; insert(s, i + n, i);
  }
  build(rt);
  rt = ++ id;
  rep(i, 1, n) {
    int p = pos[i] + 1;
    rep(j, 0, (int)str[i].size() - 1) s[j + 1] = str[i][j];
    s[(int)str[i].size() + 1] = 0;
    s[p] = '0'; insert2(s, i, i + n);
    s[p] = '1'; insert2(s, i + n, i);
  }
  build2(rt);
  rep(i, 1, id) if(!dfn[i]) tarjan(i);
  rep(i, 1, n) if(bel[i] == bel[i + n]) {
    puts("NO"); return 0;
  }
  puts("YES");
  rep(i, 1, n) {
    str[i][pos[i]] = bel[i] < bel[i + n] ? '0' : '1';
    puts(str[i].c_str());
  }
  return 0;
}