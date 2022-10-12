#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e7 + 10;
char s[N], t[N];
int n, m, cnt[256];
ll ans;
int main() {
   scanf("%s%s", s + 1, t + 1);
   n = strlen(s + 1); m = strlen(t + 1);
   s[n + 1] = '$'; t[m + 1] = '%';
   ans = (n + 1ll) * (m + 1);
   rep(i, 1, n + 1) cnt[ s[i] ] ++;
   rep(i, 1, m + 1) ans -= cnt[ t[i] ];
   printf("%lld\n", ans);
   return 0;
}
