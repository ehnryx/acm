#include <bits/stdc++.h>
using namespace std;
//#define _USE_MATH_DEFINES

typedef int ll;
typedef double ld;
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

#undef M_PI
const ld M_PI = 3.1415926535897932384626;
const ld EPS = 1e-12;
const int shift = 5e8;

struct cmphash {
	int operator() (const ld& a) const {
		return hash<long long>{}(llround(shift*a));
	}
};

struct cmpequals {
	bool operator() (const ld& a, const ld& b) const {
		return abs(a - b) <= EPS;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	unordered_map<ld, int, cmphash, cmpequals> count[300];

	ll ans = 0;
	int k;
	cin >> k;
	int k2 = 2*k;

	ld sins[300];
	ld diff[300][300];
	ld num = M_PI;
	for (int i = 1; i < k2; i++) {
		sins[i] = sin(num/(k2));
		num += M_PI;
	}
	for (int i = 1; i < k2; i++) {
		for (int j = 1; j < k2; j++) {
			diff[i][j] = sins[i] / sins[j];
		}
	}

	for (int i = 1; i < k; i++) {
		int lim = min(i, k2-i);
		for (int j = 1; j < lim; j++) {
			int end = k2 - i - j;
			ld left = 2 * diff[j][end];
			for (int e = 1; e < end; e++) {
				int mid = k2 - i - e;
				ld first = left * diff[e][mid];
				count[mid][first]++;
				count[k2-mid][2-first]++;
			}
		}
		int end = k2 - 2*i;
		ld left = 2 * diff[i][end];
		for (int e = 1; e < end; e++) {
			int mid = k2 - i - e;
			ld first = left * diff[e][mid];
			count[mid][first]++;
		}
	}
	for (int i = k; i < k2; i++) {
		int lim = min(i, k2-i);
		for (int j = 1; j < lim; j++) {
			int end = k2 - i - j;
			ld left = 2 * diff[j][end];
			for (int e = 1; e < end; e++) {
				int mid = k2 - i - e;
				ld first = left * diff[e][mid];
				count[mid][first]++;
				count[k2-mid][2-first]++;
			}
		}
	}

	for (int i = 1; i < k; i++) {
		for (const auto& it : count[i]) {
			ans += 2*it.second * count[k2-i][2-it.first];
		}
	}
	for (const auto& it : count[k]) {
		ans += it.second * it.second;
	}

	cout << ans << nl;

	return 0;
}
