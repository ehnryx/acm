#include <bits/stdc++.h>
using namespace std;
#define problem_name "anniversary"

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;



int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
#ifdef ONLINE_JUDGE
	freopen(problem_name ".in", "r", stdin);
	freopen(problem_name ".out", "w", stdout);
#endif

	int w, h, ax, ay, bx, by;
	cin >> w >> h >> ax >> ay >> bx >> by;
	if (ax == bx) {
		cout << 0 << " " << ay << " " << w << " " << by << nl;
	} else {
		cout << ax << " " << 0 << " " << bx << " " << h << nl;
	}

	return 0;
}
