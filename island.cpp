#include <bits/stdc++.h>
#define pb push_back
#define LOG(FMT...) fprintf(stderr, FMT);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 1e5 + 10;
int n, q;
namespace task {

const int N = 1e4 + 10;
int a[N], b[N];
void main() {
  rep(i, 1, n) {
    scanf("%d%d", a + i, b + i);
  }
  int l, r, c, d;
  rep(i, 1, q) {
    scanf("%d%d%d%d", &l, &r, &c, &d);
    int z = 0;
    rep(j, l, r) {
      if((a[j] ^ c) <= min(b[j], d)) {
        z ++;
      }
    }
    printf("%d\n", z);
  }
}

}
struct node {
  int l, r, c, d;
} qs[N];
int p[N], x[N], y[N], ans[N];
vector<int> vec[N * 4];
bool cmp_qry(int x, int y) {
  return qs[x].d < qs[y].d }
bool cmp_node(int a, int b) {
  return y[a] < y[b];
}
void upload(int l, int r) {
  static int tmp[N];
  int mid = (l + r) >> 1;
  int p1 = l, p2 = mid + 1;
  rep(i, l, r) {
    if(p1 <= mid && (p2 > r || cmp_node(p[p1], p[p2]))) tmp[i] = p[p1 ++];
    else tmp[i] = p[p2 ++];
  }
  copy(tmp + l, tmp + r + 1, p + l);
}
void addq(int u, int l, int r, int ql, int qr, int v) {
  if(l == ql && r == qr) { vec[u].pb(v); return ; }
  int mid = (l + r) >> 1;
  if(qr <= mid) return addq(u << 1, l, mid, ql, qr, v);
  if(ql > mid) return addq(u << 1 | 1, mid + 1, r, ql, qr, v);
  else {
    addq(u << 1, l, mid, ql, mid, v);
    addq(u << 1 | 1, mid + 1, r, mid + 1, qr, v);
  }
}
int ch[N * 27][2], w[N * 27], id = 1;
void clean(int u) {
  ch[u][0] = ch[u][1] = w[u] = 0;
}
void solve(int u, int l, int r) {
  if(l == r) {
    p[l] = l;
  } else {
    int mid = (l + r) >> 1;
    solve(u << 1, l, mid);
    solve(u << 1 | 1, mid + 1, r);
  }
  upload(l, r);
  int j = l;
  for(int i = 0; i < int(vec[u].size()); i ++) {
    int qid = vec[u][i];
    while(j <= r && y[p[j]] <= qs[qid].d) {
      int x0 = x[p[j]], y0 = y[p[j]], u = 1;
      for(int k = 23; ~k; k --) {
        int xi = x0 >> k & 1, yi = y0 >> k & 1;
        if(yi) {
          int &v = ch[u][xi ? 1 : 0];
          if(!v) v = ++ id;
          w[v] ++;
        }
        int &nx = ch[u][xi ^ yi];
        if(!nx) nx = ++ id;
        u = nx;
      }
      w[u] ++;
      j ++;
    }
    int res = w[1];
    for(int u = 1, k = 23; ~k; k --) {
      u = ch[u][qs[qid].c >> k & 1];
      if(!u) break ;
      res += w[u];
    }
    ans[qid] += res;
  }
  // printf("id = %d\n", id);
  rep(i, 1, id) clean(i);
  id = 1;

  j = r;
  for(int i = int(vec[u].size()) - 1; i >= 0; i --) {
    int qid = vec[u][i];
    while(j >= l && y[p[j]] > qs[qid].d) {
      int x0 = x[p[j]], u = 1;
      w[1] ++;
      for(int k = 23; ~k; k --) {
        int xi = x0 >> k & 1;
        int &nx = ch[u][xi];
        if(!nx) nx = ++ id;
        u = nx;
        w[u] ++;
      }
      j --;
    }
    int res = 0;
    int x0 = qs[qid].c, y0 = qs[qid].d, u = 1;
    for(int k = 23; ~k; k --) {
      int xi = x0 >> k & 1, yi = y0 >> k & 1;
      if(yi) {
        int v = ch[u][xi ? 1 : 0];
        if(v) res += w[v];
      }
      u = ch[u][xi ^ yi];
      if(!u) break ;
    }
    if(u) res += w[u];
    ans[qid] += res;
  }

  rep(i, 1, id) clean(i);
  id = 1;
}
int main() {
  freopen("island.in", "r", stdin);
  freopen("island.out", "w", stdout);
  scanf("%d%d", &n, &q);
  if(max(n, q) <= 5000) {
    task::main();
    return 0;
  }
  rep(i, 1, n) scanf("%d%d", x + i, y + i);
  rep(i, 1, q) {
    int l, r, c, d;
    scanf("%d%d%d%d", &l, &r, &c, &d);
    qs[i] = (node){l, r, c, d};
  }
  static int qid[N];
  rep(i, 1, q) qid[i] = i;
  sort(qid + 1, qid + q + 1, cmp_qry);
  rep(i, 1, q) {
    int u = qid[i];
    addq(1, 1, n, qs[u].l, qs[u].r, u);
  }
  solve(1, 1, n);
  rep(i, 1, q) {
    printf("%d\n", ans[i]);
  }
  return 0;
}
/*
4 2
1 1
4 2
5 1
2 7
1 4 6 5
2 4 3 3

20 10
215 144
2 110
174 132
214 142
116 108
155 192
236 208
216 214
99 220
236 118
190 81
230 131
10 238
189 198
183 13
45 193
14 234
208 192
126 19
49 38
7 14 251 184
2 18 89 76
11 15 49 196
8 11 83 139
10 15 119 239
9 16 148 120
11 17 225 34
15 16 3 46
14 15 86 227
7 18 252 103
*/