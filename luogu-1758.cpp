#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
// typedef long long ll;
const int N = 512;
const int mod = 1024523;
int n, m, f[2][N][N];
char s[N], t[N];
int main() {
  scanf("%d%d%s%s", &n, &m, s + 1, t + 1);
  reverse(s + 1, s + n + 1);
  reverse(t + 1, t + m + 1);
  int c = 0; f[c][0][0] = 1;
  rep(i, 0, n) {
    rep(j, 0, m) {
      rep(k, 0, n) {
        if(!(i || j || k)) continue ;
        int l = i + j - k;
        int z = 0;
        if(i && k && s[i] == s[k]) z += f[c ^ 1][j][k - 1];
        if(i && l && s[i] == t[l]) z += f[c ^ 1][j][k];
        if(j && k && t[j] == s[k]) z += f[c][j - 1][k - 1];
        if(j && l && t[j] == t[l]) z += f[c][j - 1][k];
        f[c][j][k] = z >= mod ? z % mod : z;
      }
    }
    c ^= 1;
  }
  printf("%d\n", f[c ^ 1][m][n]);
  return 0;
}