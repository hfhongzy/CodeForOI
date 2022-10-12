#include <bits/stdc++.h>
#include "meeting.h"
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
unsigned seed = chrono::system_clock::now().time_since_epoch().count();
mt19937 mt(seed);
uniform_int_distribution<int> ran(0, 1 << 30);
int rd(int i) { return ran(mt) % i; }

const int N = 1024;
int p[N];
vector<pair<int, int>> solve2(int n) {
  vector<pair<int, int>> ans;
  rep(i, 0, n - 2) rep(j, i + 1, n - 1) {
    if(!meeting(vector<int>{i, j})) {
      ans.pb({i, j});
    }
  }
  return ans;
}
vector<pair<int, int>> solve(int n) {
  if(n * (n - 1) / 2 < 50000) {
    return solve2(n);
  }
  rep(i, 0, n - 1) p[i] = i;
  random_shuffle(p, p + n, rd);
}