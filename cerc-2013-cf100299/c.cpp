#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 1<<17;

struct SegTree {
	ll t[2*N];
	
	void build(int n, ll a[]) {
		memset(t, 0, sizeof t);
	}

	int next(int x) {
	}
};

ll arr[N];
SegTree segt;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int T;
	cin >> T;
	while (T--) {
		int n;
		cin >> n;

		for (int i = 0; i < n; i++) {
			cin >> arr[i];
		}
		segt.build(n, arr);

		for (int i = 0; i < n; i++) {
		}
	}

	return 0;
}
