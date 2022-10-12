#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 55, L = 30, mod = 990804011;
int n, m, f[N][N][L][L];
char s[N][L];
int solve(int l, int r, int p, int c) { //s[l..r] suffix p, s[..][p] >= c
   if(l > r) return 1;
   if(c > 26) return 0;
   if(p > m) return l == r;
   int &ans = f[l][r][p][c];
   if(~ ans) return ans;
   ans = solve(l, r, p, c + 1);
   rep(i, l, r) {
      if(s[i][p] <= 26 && s[i][p] != c) break ;
      if(s[i][p] == 27 && !c) break ;
      ans = (ans + 1ll * solve(l, i, p + 1, 0) * solve(i + 1, r, p, c + 1)) % mod;
   }
   return ans;
}
int main() {
   scanf("%d", &n);
   rep(i, 1, n) {
      scanf("%s", s[i] + 1);
      int l = strlen(s[i] + 1); m = max(m, l);
      rep(j, 1, l) s[i][j] = s[i][j] == '?' ? 27 : s[i][j] - 'a' + 1;
   }
   memset(f, -1, sizeof f);
   printf("%d\n", solve(1, n, 1, 0));
   return 0;   
}