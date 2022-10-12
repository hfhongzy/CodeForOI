#include <algorithm>
#include <cstdio>
#include <cmath>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef double db;
const int N = 3e6 + 10;
int n, a[N], st[N], top, R[N];
int main() {
   scanf("%d", &n);
   rep(i, 1, n) scanf("%d", a + i);
   per(i, n, 1) {
      while(top && a[st[top]] <= a[i]) {
         top --;
      }
      R[i] = st[top];
      st[++ top] = i;
   }
   rep(i, 1, n) printf("%d ", R[i]);
   return 0;
}