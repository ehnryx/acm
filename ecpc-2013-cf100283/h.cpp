#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define TESTFILE "dice"

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

const int N = 36;
const int M = 2000+1;
int vals[N];
bool seen[M], left[M];

void solve() {
	memset(seen, 0, sizeof seen);
	memset(left, 0, sizeof left);

	int n;
	cin >> n;
	for (int i=0; i<n; i++) {
		cin >> vals[i];
		seen[vals[i]] = left[vals[i]] = true;
	}

	for (int i=1; i<n-4; i++) {
		for (int j=i+1; j<n-4; j++) {
			for (int k=j+1; k<n-4; k++) {
				for (int l=k+1; l<n-4; l++) {
					for (int m=l+1; m<n-4; m++) {
						for (int v=1; v<vals[0]; v++) {
							for (int s=0; s<n; s++) {
							}
						}
					}
				}
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef ONLINE_JUDGE
	freopen(TESTFILE ".in", "r", stdin);
#endif

	int T;
	cin >> T;

	for (int tt=1; tt<=T; tt++) {
		cout << "Case " << tt << ": ";
		solve();
	}

	return 0;
}
