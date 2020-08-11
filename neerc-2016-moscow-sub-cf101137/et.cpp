#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;




int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	mt19937 rng;
	uniform_int_distribution<int> a(1, (int)1e9);
	cout << (int) 2e5 << nl;
	set<int> s;
	while (s.size() < 2e5) {
		int x = a(rng);
		while (s.count(x)) {
			x = a(rng);
		}
		s.insert(x);
	}
	for (int i : s) cout << i << " "; cout << nl;

	return 0;
}
