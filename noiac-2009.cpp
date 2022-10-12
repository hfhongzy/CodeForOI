#include <algorithm>
#include <cstdio>
#include <vector>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
template<typename T> inline void chkmin(T &a, const T &b) { if(a > b) a = b; }
template<typename T> inline void chkmax(T &a, const T &b) { if(a < b) a = b; }
using namespace std;
int n, m;
int main() {
   //freopen("ex_light1.in", "r", stdin);
   //freopen("qwq.out", "w", stdout);
   scanf("%d%d", &n, &m);
   printf("%d\n", max(m - 1, m == 1 ? n / 2 : (n + 1) / 2));
   return 0;
}