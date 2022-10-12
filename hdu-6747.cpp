#include <bits/stdc++.h>
using namespace std;

inline void ucin() {
   ios::sync_with_stdio(0); cin.tie(0);
}

const int mod = 1e9 + 7;

int main() {
    ucin(); int T, n; cin >> T;
    while(T --) {
        cin >> n;
        int a, b; cin >> a;
        if(n == 1) {
            cout << a / 2 << endl;
            continue ;
        }
        for(int i = 2; i <= n; i ++) {
            cin >> b;
        }
        cout << (a + b) / 2 * ((mod + 1ll) / 2) % mod << "\n";
    }
   return 0;
}