#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 1e3+1;
int len[N], rem[N];
bool dp[N][N];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n, p;
	cin >> n >> p;
	FOR(i,1,n-1) {
		cin >> len[i];
	}
	FOR(i,1,n-1) {
		cin >> rem[i];
	}

	ordered_set<int> done;
	dp[1][p] = true;
	FOR(i,1,n-1) {
		FOR(j,1,n-i+1) {
			if (dp[i][j] != true) continue;
			// at position j at time i
			int remove = rem[i] - done.order_of_key(rem[i]);
			int shift = len[i] % (n-i+1);
			int cw = (j-1+shift)%(n-i+1)+1;
			int ccw = (j-1+(n-i+1)-shift)%(n-i+1)+1;
			if (cw != remove) {
				dp[i+1][cw - (remove<cw)] = true;
			}
			if (ccw != remove) {
				dp[i+1][ccw - (remove<ccw)] = true;
			}
			done.insert(rem[i]);
		}
	}

	if (dp[n][1]) {
		cout << "Yes" << nl;
	} else {
		cout << "No" << nl;
	}

	return 0;
}
