#include <algorithm>
#include <cstdio>
#include <queue>
using namespace std;
typedef long long ll;
const int N = 2e6 + 10;
int id, lnk[N], len[N], ch[N][26], w[N];
void init() {
   lnk[0] = -1; id = 0; fill(ch[0], ch[0] + 26, -1);
}
int extend(int la, int c) {
   int u = ++ id, p = la;
   fill(ch[u], ch[u] + 26, -1); len[u] = len[la] + 1;
   for(; ~ p && ch[p][c] == -1; p = lnk[p]) ch[p][c] = u;
   if(p == -1) lnk[u] = 0;
   else {
      int q = ch[p][c];
      if(len[q] == len[p] + 1) lnk[u] = q;
      else {
         int q0 = ++ id;
         copy(ch[q], ch[q] + 26, ch[q0]);
         len[q0] = len[p] + 1; lnk[q0] = lnk[q];
         lnk[u] = lnk[q] = q0;
         for(; ~ p && ch[p][c] == q; p = lnk[p])
            ch[p][c] = q0;
      }
   }
   return u;
}
char str[N];
int idx, cnt[N], a[N], son[N][26];
void insert(char *s) {
   int u = 1;
   for(; *s; s ++) {
      int &v = son[u][*s - 'a'];
      u = v ? v : v = ++ idx;
   }
}
void build() {
   static int ID[N], v;
   queue<int> q; q.push(1); init(); ID[1] = 0;
   while(q.size()) {
      int u = q.front(); q.pop();
      for(int i = 0; i < 26; i ++) if(v = son[u][i]) {
         ID[v] = extend(ID[u], i); q.push(v);
      }
   }
}
int main() {
   int n; scanf("%d", &n); idx = 1;
   for(int i = 1; i <= n; i ++) {
      scanf("%s", str); insert(str);
   }
   build();
   ll ans = 0;
   for(int i = 1; i <= id; i ++)
      ans += len[i] - len[lnk[i]];
   printf("%lld\n", ans);
   return 0;
}