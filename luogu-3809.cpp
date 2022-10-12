#include <algorithm>
#include <cstring>
#include <cstdio>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 1e6 + 10;
char s[N];
int n, rk[N], sa[N], cnt[N], t[N];
void build() {
   int c = *max_element(s + 1, s + n + 1);
   fill(cnt + 1, cnt + c + 1, 0);
   rep(i, 1, n) cnt[rk[i] = s[i]] ++;
   rep(i, 1, c) cnt[i] += cnt[i - 1];
   rep(i, 1, n) sa[cnt[s[i]] --] = i;
   for(int num = 0, k = 1; k <= n; k <<= 1, c = num, num = 0) {
      rep(i, n - k + 1, n) t[++ num] = i;
      rep(i, 1, n) if(sa[i] > k) t[++ num] = sa[i] - k;
      fill(cnt + 1, cnt + c + 1, 0);
      rep(i, 1, n) cnt[rk[i]] ++;
      rep(i, 1, c) cnt[i] += cnt[i - 1];
      per(i, n, 1) sa[cnt[rk[t[i]]] --] = t[i];
      copy(rk + 1, rk + n + 1, t + 1); rk[sa[1]] = num = 1;
      rep(i, 2, n) {
         int u = sa[i - 1] + k <= n ? t[sa[i - 1] + k] : 0;
         int v = sa[i] + k <= n ? t[sa[i] + k] : 0;
         if(!(t[sa[i - 1]] == t[sa[i]] && u == v)) num ++;
         rk[sa[i]] = num;
      }
      if(num == n) break ;
   }
}
int main() {
   scanf("%s", s + 1); n = strlen(s + 1);
   build();
   rep(i, 1, n) printf("%d ", sa[i]);
   return 0;
}