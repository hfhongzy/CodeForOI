#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;
typedef long long db;
const int N = 1e6 + 8;
struct point {
	db x, y;
	db det(point b) { return x * b.y - y * b.x; }
} last, now;
int main() {
	freopen("input", "r", stdin);
	int test; scanf("%d", &test);
	while(test --) {
		db x = 0, y = 0;
		static char s[N];
		scanf("%s", s + 1); db sum = 0;
		for(int i = 1; s[i]; i ++) if(s[i] != '5') {
			last = (point) {x, y};
			if(s[i] == '8') y ++;
			if(s[i] == '2') y --;
			if(s[i] == '4') x --;
			if(s[i] == '6') x ++;
			if(s[i] == '9') y ++, x ++;
			if(s[i] == '7') y ++, x --;
			if(s[i] == '3') y --, x ++;
			if(s[i] == '1') y --, x --;
			now = (point) {x, y};
			sum += now.det(last);
		}
		sum = sum > 0 ? sum : -sum;
		if(sum & 1) printf("%lld.5\n", sum / 2);
		else printf("%lld\n", sum / 2);
	}
	return 0;
}