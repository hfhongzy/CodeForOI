#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 1e5 + 10;
int n, a[N];
int main() {
  scanf("%d", &n);
  rep(i, 1, n) scanf("%d", a + i);
  sort(a + 1, a + n + 1, greater<int>());
  int x = n - 1;
  rep(i, 1, n - 1)
    if(a[i + 1] <= i) { x = i - 1; break ; }
  int y = x + 1;
  for(; y; y ++)
    if(y == n || a[y + 1] <= x) break ;
  if((a[x + 1] - x) % 2 == 0 || (y - x) % 2 == 0) puts("First");
  else puts("Second");
  return 0;
}