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
const ld EPS = 1e-10;
const int shift = 1e8;

ostream& operator << (ostream& os, pair<int,ld> p) {
	os << "(" << p.first << "," << p.second << ")"; return os;
}

struct cmphash {
	int operator() (const pair<int,ld>& a) const {
		return hash<int>{}(a.first) ^ hash<long long>{}(llround(shift*a.second));
	}
};

struct cmpequals {
	bool operator() (const pair<int,ld>& a, const pair<int,ld>& b) const {
		return a.first == b.first && abs(a.second - b.second) <= EPS;
	}
};

struct cmp {
	bool operator () (const pair<int,ld>& a, const pair<int,ld>& b) {
		if (a.first == b.first) return a.second < b.second-EPS;
		else return a.first < b.first;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	//map<pair<int,ld>, int, cmp> count;
	unordered_map<pair<int,ld>, int, cmphash, cmpequals> count;

	ll ans = 0;
	int k;
	cin >> k;
	int k2 = 2*k;

	ld sins[300];
	for (int i = 1; i < k2; i++) {
		sins[i] = sin(M_PI*i/(k2));
	}

	for (int i = 1; i < k2; i++) {
		int lim = k2-i;
		for (int j = 1; j < lim; j++) {
			int end = k2 - i - j;
			ld left = 2 * sins[j] / sins[end];
			for (int e = 1; e < end; e++) {
				int mid = k2 - i - e;
				ld first = left * sins[e] / sins[mid];
				count[pair<int,ld>(mid,first)]++;
			}
		}
	}

	for (const auto& key : count) {
		int angle = k2 - key.first.first;
		ld other = 2 - key.first.second;
		ans += key.second * count[pair<int,ld>(angle,other)];
	}

	cout << ans << nl;

	return 0;
}
