#include <bits/stdc++.h>
// #define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int n, k, la, lb, pa, pb, posa[N], posb[N], pla, plb;
ll a[N], A[N], B[N], mxa[N], mxb[N];
bool check(bool rev = 0) {
   if(!la) pa = 0;
   if(!lb) pb = 0;
   ll minv = 0; pla = 0;
   rep(i, 1, la) {
      if((!rev && minv > A[i]) || (rev && minv >= A[i])) {
         minv = A[i];
         posa[++ pla] = i;
      }
   }
   minv = 0; plb = 0;
   rep(i, 1, lb) {
      if((!rev && minv > B[i]) || (rev && minv >= B[i])) {
         minv = B[i];
         posb[++ plb] = i;
      }
   }
   rep(i, 0, pla - 1) mxa[i] = *max_element(A + posa[i], A + posa[i + 1] + 1);
   rep(i, 0, plb - 1) mxb[i] = *max_element(B + posb[i], B + posb[i + 1] + 1);
   int i = 0, j = 0;
   while(i < pla || j < plb) {
      if(i != pla && mxa[i] + B[ posb[j] ] <= 0) {
         i ++;
      } else if(j != plb && mxb[j] + A[ posa[i] ] <= 0) {
         j ++;
      } else return 0;
   }
   return 1;
}
int main() {
   int test; scanf("%d", &test);
   while(test --) {
      scanf("%d%d", &n, &k);
      la = lb = 0;
      rep(i, 1, n) scanf("%lld", a + i);
      rep(i, k + 1, n) A[++ la] = a[i];
      per(i, k, 2) B[++ lb] = a[i];
      rep(i, 1, la) A[i] += A[i - 1];
      rep(i, 1, lb) B[i] += B[i - 1];
      if(A[la] + B[lb] > 0) { puts("No"); continue ; }
      ll minv = 2e18;
      rep(i, 1, la) {
         if(minv > A[i]) {
            minv = A[i]; pa = i;
         }
      }
      minv = 2e18;
      rep(i, 1, lb) {
         if(minv > B[i]) {
            minv = B[i]; pb = i;
         }
      }
      if(!check()) { puts("No"); continue ; }
      reverse(A + 1, A + la + 1); pa = la - pa + 1;
      reverse(B + 1, B + lb + 1); pb = lb - pb + 1;
      puts(check(1) ? "Yes" : "No");
   }
   return 0;
}
/*
2
5 2
2 3 0 -3 1
5 2
2 -4 3 -3 4
*/