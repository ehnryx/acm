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

	int n, d, k;
	cin >> n >> d >> k;

	string s;
	int a;
	vector<pair<int,string>> vals;
	for (int i = 0; i < n; i++) {
		cin >> s >> a;
		vals.push_back(pair<int,string>(a,s));
	}
	sort(vals.begin(), vals.end(), greater<pair<int,string>>());

	int tot = 0;
	for (int i = 0; i < k; i++) {
		tot += vals[i].first;
	}

	if (tot < d) {
		cout << "impossible" << nl;
	} else {
		cout << k << nl;
		for (int i = 0; i < k; i++) {
			cout << vals[i].second << ", YOU ARE FIRED!" << nl;
		}
	}

	return 0;
}
