#include <algorithm>
#include <cstdio>
using namespace std;
typedef long long ll;
const int N = 2e6 + 10;
int la, id, lnk[N], len[N], ch[N][26], w[N];
void init() {
   lnk[0] = -1; id = la = 0; fill(ch[0], ch[0] + 26, -1);
}
void extend(int c) {
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
   la = u; w[u] = 1;
}
char str[N];
int cnt[N], a[N];
int main() {
   scanf("%s", str + 1); init();
   for(int i = 1; str[i]; i ++) extend(str[i] - 'a');
   int n = len[la];
   for(int i = 1; i <= id; i ++) cnt[len[i]] ++;
   for(int i = 1; i <= n; i ++) cnt[i] += cnt[i - 1];
   for(int i = 1; i <= id; i ++) a[cnt[len[i]] --] = i;
   for(int i = id; i >= 1; i --) w[lnk[a[i]]] += w[a[i]];
   ll ans = 0;
   for(int i = 1; i <= id; i ++) if(w[i] > 1)
      ans = max(ans, (ll) w[i] * len[i]);
   printf("%lld\n", ans);
   return 0;
}