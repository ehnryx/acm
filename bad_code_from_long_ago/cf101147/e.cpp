#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

///* advent of code
typedef istringstream iss;
#define pb push_back
#define ins insert
#define multiset mset
#define getl(A) getline(cin, A)
//*/

const ll INF = 0x3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;

void bfs(vector<int> a[], int d[], int n, int s) {
	queue<int> next;
	next.push(s);
	d[s] = 0;
	while (!next.empty()) {
		s = next.front();
		next.pop();
		for (int neighbour : a[s]) {
			//cerr << "from " << s << " visit " << neighbour << nl;
			if (d[neighbour] == -1) {
				d[neighbour] = d[s]+1;
				next.push(neighbour);
			}
		}
	}
}

int main() {
	freopen("jumping.in", "r", stdin);
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n, d[100000];
	vector<int> a[100000];

	int T;
	cin >> T;
	while (T--) {
		cin >> n;
		int t;
		for (int i = 0; i < n; i++) {
			a[i].clear();
		}
		for (int i = 0; i < n; i++) {
			cin >> t;
			if (i+t < n) a[i+t].push_back(i);
			if (i-t >= 0) a[i-t].push_back(i);
		}
		memset(d, -1, sizeof(d));
		bfs(a, d, n, n-1);
		for (int i = 0; i < n; i++) {
			cout << d[i] << nl;
		}
	}

	return 0;
}
