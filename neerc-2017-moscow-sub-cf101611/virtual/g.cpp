#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;




int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int n, m;
	cin >> n >> m;

	ll val[n][2*m];
	for (int i=0; i<n; i++) {
		for (int j=0; j<2*m; j++) {
			cin >> val[i][j];
		}
	}

	for (int i=0; i<n; i++) {
		for (int j=0; j<2*m; j+=2) {
			if (val[i][j] != 0) {
				ll fix = val[i][j];
				val[i][j] -= fix;
				val[i][(j+1)%(2*m)] += fix;
				val[i][(j+3)%(2*m)] -= fix;
				val[(i+1)%n][j] += fix;
			}
		}
	}

	for (int j=0; j<2*m; j+=2) {
		if (val[0][j] != 0) {
			//cerr << "can't kill horizontal" << nl;
			cout << "No" << nl;
			return 0;
		}
	}

	ll tot = 0;
	for (int j=1; j<2*m; j+=2) {
		tot += val[0][j];
		for (int i=1; i<n; i++) {
			if (val[i][j] != val[0][j]) {
				//cerr << "vertical is broken" << nl;
				cout << "No" << nl;
				return 0;
			}
		}
	}

	if (tot == 0) {
		cout << "Yes" << nl;
	} else {
		cout << "No" << nl;
	}

	return 0;
}
