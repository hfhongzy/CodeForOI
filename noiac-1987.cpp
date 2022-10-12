#include <cstdio>
#define rep(i, j, k) for(int i = j; i <= k; i ++)
using namespace std;
const int N = 2e6 + 10;
int n, k, a[N], la[N], q[N], l;
bool inq[N];
int main() {
   scanf("%d%d", &n, &k);
   rep(i, 1, n) { scanf("%d", a + i); la[a[i]] = i; }
   rep(i, 1, n) if(!inq[a[i]]) {
      while(l >= 1 && la[q[l]] > i && q[l] > a[i]) {
         inq[q[l --]] = 0;
      }
      inq[a[i]] = 1; q[++ l] = a[i];
   }
   rep(i, 1, k) printf("%d ", q[i]);
   return 0;
}