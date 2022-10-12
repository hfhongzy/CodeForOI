#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 2*1e6 + 10;
char s[N];
int n, cnt[N], t[N], sa[N], rk[N];
void build() {
   int m = *max_element(s + 1, s + n + 1);
   rep(i, 1, n) cnt[rk[i] = s[i]] ++;
   rep(i, 1, m) cnt[i] += cnt[i - 1];
   rep(i, 1, n) sa[cnt[s[i]] --] = i;
   for(int k = 1, num = 0; k < n; k <<= 1, m = num, num = 0) {
      rep(i, n - k + 1, n) t[++ num] = i;
      rep(i, 1, n) if(sa[i] > k) t[++ num] = sa[i] - k;
      rep(i, 1, m) cnt[i] = 0;
      rep(i, 1, n) cnt[rk[i]] ++;
      rep(i, 1, m) cnt[i] += cnt[i - 1];
      per(i, n, 1) sa[cnt[rk[t[i]]] --] = t[i];
      copy(rk + 1, rk + n + 1, t + 1); rk[sa[1]] = num = 1;
      rep(i, 2, n) {
         if(t[sa[i]] != t[sa[i - 1]] || t[sa[i] + k] != t[sa[i - 1] + k]) num ++;
         rk[sa[i]] = num;
      }
      if(num == n) break ;
   }

}
int main() {
   scanf("%s", s + 1); n = strlen(s + 1); build();
   rep(i, 1, n) printf("%d%c", sa[i], " \n"[i == n]);
   return 0;
}