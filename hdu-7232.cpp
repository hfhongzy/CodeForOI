// Problem: Shattrath City
// Contest: Virtual Judge - HDU
// URL: https://vjudge.net/problem/HDU-7232
// Memory Limit: 512 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<stack>
#include<queue>
#include<vector>
#include<cassert>
#define debug(x) cerr << #x << ": " << (x) << endl
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
using namespace std;

const int N = 2e6 + 5, P = 998244353; //模数
using ll = int64_t;
using poly = vector<int>;
void ADD(int &x, int y) { (x += y) %= P; }
void SUB(int &x, int y) { (x += P - y) %= P; }
int MUL(int x, int y) { return (ll)x*y % P; }

ll POW(ll a, ll b = P - 2, ll x = 1) {
    for (; b; b >>= 1, a = MUL(a, a))
        if (b & 1) x = MUL(x, a);
    return x;
}
/*---------------------------------------------------------------------------*/
int add(int x, int y) { return (x += y) >= P ? x - P : x; }
int dec(int x, int y) { return x - y < 0 ? x - y + P : x - y; }
int qpow(int a, int b) {
  int ans = 1;
  for(; b >= 1; b >>= 1, a = (ll)a * a % P)
    if(b & 1) ans = (ll)ans * a % P;
  return ans;
}

int rev[N], W[N], inv[N];
int getn(int len) { int n = 1; while(n < len) n <<= 1; return n; } //[0, len - 1]
void prework(int n) {
  for(int i = 1; i < n; i <<= 1) {
    W[i] = 1;
    int w = qpow(3, (P - 1) / (i << 1));
    for(int j = 1; j < i; j ++)
      W[i + j] = (ll)W[i + j - 1] * w % P;
  }
  inv[1] = 1;
  for(int i = 2; i <= n; i ++) inv[i] = (P - P / i) * (ll)inv[P % i] % P;
}
void NTT(poly &a, int n, int op) {
  a.resize(n);
  for(int i = 1; i < n; i ++)
    if(i < (rev[i] = (rev[i >> 1] >> 1) | (i & 1 ? n >> 1 : 0)))
      swap(a[i], a[rev[i]]);
  for(int i = 1; i < n; i <<= 1) {
    for(int j = 0; j < n; j += i << 1) {
      for(int k = 0; k < i; k ++) {
        int q = 1ll * W[i + k] * a[j + k + i] % P;
        a[j + k + i] = add(a[j + k], P - q); a[j + k] = add(a[j + k], q);
      }
    }
  }
  if(op == 1) return ;
  reverse(a.begin() + 1, a.end());
  int inv = P - (P - 1) / n;
  rep(i, 0, n - 1) a[i] = (ll)a[i] * inv % P;
}
int mysize;
poly operator * (poly a, poly b) {
  int t = min(int(a.size() + b.size()) - 1, mysize), n = getn(t);
  NTT(a, n, 1); NTT(b, n, 1);
  rep(i, 0, n - 1) a[i] = (ll)a[i] * b[i] % P;
  NTT(a, n, -1); a.resize(t);
  return a;
}
int n, m;
int f[N], sum[N];

int INV(int x){
  return POW(x, P-2);
}

int fac[N], pwn[N];

void getFac(int n){
  fac[0]=1;
  for(int i=1; i<=n; i++) fac[i]=1LL*fac[i-1]*i%P;
}

poly A, B;

#define pb push_back

void divi(int l, int r){
    if(l>r) return ;
  if(l==r){
    ADD(f[l], MUL(fac[n], POW(n, l-1)));
    if(l>n){
      SUB(f[l], MUL(MUL(fac[n], pwn[l-n]), sum[l-n]));
    }
    sum[l]=(sum[l-1]+MUL(f[l], INV(pwn[l])))%P;
    return;
  }
  int mid=l+r>>1;
  divi(l, mid);
  
  A.clear(), B.clear();

  int len=min(r-l+1, n);
  A.resize(mid - l + 1);
  B.pb(0);
  rep(i,1,len-1) B.pb(fac[i]);
  rep(i,l,mid) A[i-l]=f[i];
  mysize = r-l+1;
  A = A*B;
  rep(i,mid+1,r) if(i-l<A.size()) SUB(f[i], A[i-l]);
  divi(mid+1, r);
}

signed main(){
    prework(4e5 + 1);
  getFac(N-10);
  int cs; cin>>cs;
  while(cs--){
    cin>>n>>m;
    // cerr << "n = " << n << ", m = " << m << endl;
    pwn[0]=1;
    rep(i,1,m-n+1) f[i]=0, sum[i]=0, pwn[i]=MUL(n, pwn[i-1]);
    divi(1, m-n+1);
    int res=POW(n, m);
    int del=0;
    rep(i,1,m-n+1) ADD(del, MUL(f[i], POW(n, m-n+1 - i)));
    SUB(res, del);
    cout<<res<<endl;
  }
  return 0;
}
/*
4
100000 200000
100000 200000
10 200000
3 4
*/