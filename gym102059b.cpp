#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 53;
const int M = 1e4 + 20;
int n, m, id, idx[N][N], idy[N][N];
char s[N][N];
vector<int> G[M];
bitset<M> p[M];
bool va(int x, int y) {
  return 1 <= x && x <= n && 1 <= y && y <= m && s[x][y] != '#';
}
namespace _2SAT {

int dfn[M], low[M], bel[M], scc; 
vector<int> G[M];
stack<int> st;
bool ins[M];
void add(int u, int v) { G[u].pb(v); }
void tarjan(int u) {
  low[u] = dfn[u] = ++ *dfn; st.push(u); ins[u] = 1;
  for(int v : G[u]) {
    if(!dfn[v]) {
      tarjan(v);
      low[u] = min(low[u], low[v]);
    } if(ins[v]) {
      low[u] = min(low[u], dfn[v]);
    }
  }
  if(dfn[u] == low[u]) {
    int v = 0; scc ++;
    do {
      v = st.top(); st.pop(); ins[v] = 0;
      bel[v] = scc;
    } while(v != u);
  }
}
bool work(int id) {
  rep(i, 1, id * 2) dfn[i] = 0;
  rep(i, 1, id * 2) if(!dfn[i]) tarjan(i);
  rep(i, 1, id) if(bel[i] == bel[i + id]) return 0;
  return 1;
}

}
int main() {
  scanf("%d%d", &n, &m);
  rep(i, 1, n) scanf("%s", s[i] + 1);
  rep(i, 1, n) rep(j, 1, m) if(s[i][j] != '#') {
    if(j == 1 || s[i][j - 1] == '#') ++ id;
    idy[i][j] = id;
  }
  rep(j, 1, m) rep(i, 1, n) if(s[i][j] != '#') {
    if(i == 1 || s[i - 1][j] == '#') ++ id;
    idx[i][j] = id;
  }
  int sx = 0, sy = 0;
  rep(i, 1, n) rep(j, 1, m) {
    if(!va(i - 1, j) || !va(i + 1, j)) G[idx[i][j]].pb(idy[i][j]);
    if(!va(i, j - 1) || !va(i, j + 1)) G[idy[i][j]].pb(idx[i][j]);
    if(s[i][j] == 'O') { sx = idx[i][j]; sy = idy[i][j]; }
  }
  queue<int> q;
  rep(i, 1, id) {
    q.push(i);
    p[i][i] = 1;
    while(q.size()) {
      int u = q.front(); q.pop();
      for(int v : G[u]) if(!p[i][v]) {
        p[i][v] = 1; q.push(v);
      }
    }
  }
  for(auto s : {sx, sy}) {
    rep(i, 1, 2 * id) _2SAT::G[i].clear();
    rep(i, 1, id) {
      if(!p[s][i]) _2SAT::add(id + i, i);
      rep(j, i + 1, id) {
        if(!p[i][j] && !p[j][i]) {
          _2SAT::add(id + i, j);
          _2SAT::add(id + j, i);
        }
      }
    }
    rep(i, 1, n) rep(j, 1, m) if(::s[i][j] == '*') {
      _2SAT::add(idx[i][j], id + idy[i][j]);
      _2SAT::add(idy[i][j], id + idx[i][j]);
    }
    if(_2SAT::work(id)) { puts("YES"); return 0; }
  }
  puts("NO");
  return 0;
}