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



int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n, m, k;
	cin >> n >> m >> k;

	unordered_map<int,int> remap;

	int choice[n+1];
	for (int i=1; i<=n; i++) {
		cin >> choice[i];
	}

	int p[m];
	for (int i=0; i<m; i++) {
		cin >> p[i];
	}
	sort(p, p+m);

	for (int i=0; i<m; i++) {
		remap[p[i]] = i;
	}

	for (int i=1; i<=n; i++) {
		choice[i] = remap[choice[i]];
	}

	vector<pii> cts;
	int start = 1;
	for (int i=2; i<=n; i++) {
		if (choice[i]-choice[start] != i-start || i-start == k) {
			cts.push_back(pii(start,i-1));
			start = i;
		}
	}
	cts.push_back(pii(start,n));

	cout << cts.size() << nl;
	for (const pii& it : cts) {
		cout << it.second-it.first+1 << " ";
		for (int i=it.first; i <= it.second; i++) {
			cout << i << " ";
		}
		cout << nl;
	}

	return 0;
}
