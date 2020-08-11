#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("amplifiers.in", "r", stdin);
	freopen("amplifiers.out", "w", stdout);
#endif
	
	int n;
	cin >> n;

	if (n % 2 == 0) {
		cout << "No solution" << nl;
		return 0;
	}

	vector<int> ans;
	while (n != 1) {
		if ((n+1)/2 % 2 == 1) {
			ans.push_back(1);
			n = (n+1)/2;
		}
		else {
			ans.push_back(2);
			n = (n-1)/2;
		}
	}
	reverse(ans.begin(), ans.end());

	cout << ans.size() << nl;
	for (int it : ans) {
		cout << it << " ";
	}
	cout << nl;

	return 0;
}
