#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int la, id, ch[N][26], lnk[N], len[N], w[N];
void init() { id = la = 0; fill(ch[0], ch[0] + 26, -1); lnk[0] = -1; }
void extend(int c) {
  int u = ++ id, p = la;
  len[u] = len[la] + 1; fill(ch[u], ch[u] + 26, -1);
  for(; ~p && !~ch[p][c]; p = lnk[p]) ch[p][c] = u;
  if(!~p) lnk[u] = 0;
  else {
    int q = ch[p][c];
    if(len[q] == len[p] + 1) lnk[u] = q;
    else {
      int q0 = ++ id; w[id] = 0;
      len[q0] = len[p] + 1; copy(ch[q], ch[q] + 26, ch[q0]);
      lnk[q0] = lnk[q]; lnk[q] = lnk[u] = q0;
      for(; ~p && ch[p][c] == q; p = lnk[p]) ch[p][c] = q0;
    }
  }
  la = u; w[u] = 1;
}
int c[N], k, n;
char s[N];
int main() {
  int test; scanf("%d", &test);
  while(test --) {
    init();
    scanf("%s%d", s + 1, &k);
    n = strlen(s + 1);
    rep(i, 1, n) extend(s[i] - 'a');
    static int cnt[N], ord[N], u;
    rep(i, 0, n) cnt[i] = 0;
    rep(i, 1, id) cnt[len[i]] ++;
    rep(i, 1, n) cnt[i] += cnt[i - 1];
    rep(i, 1, id) ord[cnt[len[i]] --] = i;
    per(i, id, 1) u = ord[i], w[lnk[u]] += w[u];
    rep(i, 0, n) cnt[i] = 0;
    rep(i, 1, id) {
      u = ord[i];
      if(w[u] == k) {
        cnt[len[u]] ++;
        cnt[len[lnk[u]]] --;
      }
    }
    per(i, n - 1, 1) cnt[i] += cnt[i + 1];
    int res = -1;
    rep(i, 1, n) if(cnt[i] && (!~res || cnt[res] <= cnt[i])) res = i;
    printf("%d\n", res);
  }
  return 0;
} 