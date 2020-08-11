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



//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int n;
	cin >> n;

	set<int> a, b;
	vector<int> va, vb;
	for (int i=0; i<n; i++) {
		int aa;
		cin >> aa;
		a.insert(aa);
		va.push_back(aa);
	}
	for (int i=0; i<n; i++) {
		int bb;
		cin >> bb;
		b.insert(bb);
		vb.push_back(bb);
	}

	int wa = 0;
	for (int i : va) {
		auto it = b.lower_bound(i);
		if (it != b.begin()) {
			wa++;
			b.erase(prev(it));
		}
	}

	int wb = 0;
	for (int i : vb) {
		auto it = a.lower_bound(i);
		if (it != a.begin()) {
			wb++;
			a.erase(prev(it));
		}
	}

	if (2*wa>n && 2*wb>n) {
		cout << "Both" << nl;
	} else if (2*wa>n) {
		cout << "First" << nl;
	} else if (2*wb>n) {
		cout << "Second" << nl;
	} else {
		cout << "None" << nl;
	}

	return 0;
}
