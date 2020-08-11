#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
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



int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	set<int> seen;
	int n, a;
	cin >> n;
	int ans = 0;
	for (int i = 0; i < n; i++) {
		cin >> a;
		if (seen.count(a)) {
			ans++;
		} else {
			seen.insert(a);
		}
	}
	cout << ans << nl;


	return 0;
}
