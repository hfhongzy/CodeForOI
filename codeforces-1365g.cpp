#include <algorithm>
#include <vector>
#include <cstdio>
#define rep(i, j, k) for(int i = j; i <= k; i ++)
#define per(i, j, k) for(int i = j; i >= k; i --)
using namespace std;
typedef long long ll;
const int N = 1005;
int n, idx[N];
ll f[15], ans[N];
vector<int> cur;
const int sam[10] = {0, 1, 2, 4};
ll query(vector<int> &a) {
   printf("? %d", (int) a.size());
   for(int &v: a) printf(" %d", v);
   puts(""); fflush(stdout);
   ll x; scanf("%lld", &x); return x;
}
int main() {
   scanf("%d", &n);
   int id = 0;
   rep(i, 1, n) {
      while(__builtin_popcount(id) != 6) id ++;
      idx[i] = id; id ++;
   }
   rep(i, 0, 12) {
      cur.clear();
      rep(j, 1, n) if(idx[j] >> i & 1) cur.push_back(j);
      f[i] = cur.size() ? query(cur) : 0;
   }
   rep(i, 1, n) {
      rep(j, 0, 12) if(!(idx[i] >> j & 1)) {
         ans[i] |= f[j];
      }
   }
   printf("!");
   rep(i, 1, n) printf(" %lld", ans[i]);
   puts(""); fflush(stdout);
   return 0;
}