#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using pii = pair<int,int>;
using ll = long long;
using ld = long double;
const char nl = '\n';

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n; cin >> n;
	if (n == 2) {
		cout << "4 5" << nl;
		cout << "2 1 2" << nl;
		cout << "1 2" << nl;
		cout << "3 5 1 3" << nl;
		cout << "2 2 3" << nl;
	} else {
		cout << "5462 105" << nl;
		cout << "2 1 2" << nl;
		cout << "1 2" << nl;
		cout << "1 2" << nl;
		int cnt = 3;
		for (int i = 3; i <= 105; i++) {
			for (int j = 0; j < i-1; j++) {
				cnt++;
				if (!j) {
					cout << "2 " << i << " 2" << nl;
				} else {
					cout << "1 " << i << nl;
				}
			}
		}
		cerr << "cnt: " << cnt << nl;
		assert(cnt == 5462);
	}

	return 0;
}

