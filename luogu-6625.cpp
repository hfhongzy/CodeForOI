#include <bits/stdc++.h>
#define pb push_back
#define LOG(FMT...) fprintf(stderr, FMT);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int n;
ll a[N], ans;
int main() {
  scanf("%d", &n);
  rep(i, 1, n) scanf("%lld", a + i);
  rep(i, 2, n) {
    a[i] += a[i - 1];
    if(a[i] > 0) ans += a[i];
  }
  printf("%lld\n", ans);
  return 0;
}