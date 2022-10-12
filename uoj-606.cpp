#include <bits/stdc++.h>
#include "head.h"
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
void work(int n, int tp, int &a, int &b, int &c) {
  if(tp == 1 || 1) {
    rep(i, 0, n) rep(j, 0, n) rep(k, 0, n) {
      if(!query(i, j, k)) {
        a = i; b = j; c = k;
        return ;
      }
    }
  }
}