#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;
typedef long long db;
const int N = 1e6 + 8;
struct point {
	db x, y;
	db det(point b) { return x * b.y - y * b.x; }
};
int gcd(int x, int y) {
	return y == 0 ? x : gcd(y, x % y);
}
int main() {
	int x1, y1, x2, y2, x3, y3;
	while(~ scanf("%d%d%d%d%d%d", &x1, &y1, &x2, &y2, &x3, &y3)) {
		if(!(x1 | y1 | x2 | y2 | x3 | y3)) return 0;
		point A = (point) {x2 - x1, y2 - y1};
		point B = (point) {x3 - x1, y3 - y1};
		db S = llabs(A.det(B));
		S -= gcd(abs(x1 - x2), abs(y1 - y2));
		S -= gcd(abs(x1 - x3), abs(y1 - y3));
		S -= gcd(abs(x3 - x2), abs(y3 - y2));
		//(2S - b)/2 + 1 = I
		printf("%lld\n", S / 2 + 1);
	}
	return 0;
}