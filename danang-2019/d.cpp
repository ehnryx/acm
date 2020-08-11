#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
#define nl '\n'

const int M = 44;
const int HOUR = 60*M;
const int DAY = 12*HOUR;
int valid(int h, int m, int d) {
	if(h>=12) h -= 12;
	int tot = h*60*M + m;
	int diff = abs(m*DAY - tot*HOUR);
	return (diff * 4 == d * HOUR*DAY || diff * 4 == (4-d)%4 * HOUR*DAY);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int T;
	scanf("%d", &T);
	while(T--) {
		int h1, m1, h2, m2, d;
		scanf("%d:%d", &h1, &m1);
		scanf("%d:%d", &h2, &m2);
		scanf("%d", &d);
		d /= 90;
		m1 *= M;
		m2 *= M;
		int ans = 0;
		while(h1 != h2 || m1 != m2) {
			ans += valid(h1, m1, d);
			if(++m1 == 60*M) {
				h1++;
				m1 = 0;
			}
		}
		ans += valid(h2, m2, d);
		cout << ans << nl;
	}

	return 0;
}
