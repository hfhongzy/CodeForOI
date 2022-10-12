#include <cstdio>
#include <cstring>
#include <algorithm>
#define fs first
#define sc second
using namespace std;

typedef long long ll;

const int N = 1e6 + 10;

int p[N], c, mu[N];
bool tag[N];
void sieve(int n) {
   mu[1] = 1;
   for(int i = 2; i <= n; i ++) {
      if(!tag[i]) { p[++ c] = i; mu[i] = -1; }
      for(int j = 1; j <= c && i * p[j] <= n; j ++) {
         tag[i * p[j]] = 1;
         if(i % p[j] == 0) break ;
         mu[i * p[j]] = - mu[i];
      }
   }
}
ll solve(ll n) {
   ll ans = 0;
   for(ll x = 1; x * x <= n; x ++) if(mu[x]) {
      ll L = n / (x * x), res = 0;
      for(ll i = 1; i * i * i <= L; i ++) {
         res += 3 * (L / (i * i) - i) + 1; //i = j < k & i = j = k
         for(ll j = i + 1; i * j * j <= L; j ++) {
            res += 6 * (L / (i * j) - j) + 3; //i < j < k & i < j = k
         }
      }
      if(mu[x] > 0) ans += res;
      else ans -= res;
   }
   return (ans + n) / 2;
}
int main() {
   ll a, b, l = 1;
   scanf("%lld%lld", &a, &b);
   while(l * l <= b) l ++;
   sieve(l);
   printf("%lld\n", solve(b) - solve(a - 1));
   return 0;
}