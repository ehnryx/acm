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

struct Person {
	int bbl, pos, i;
	Person() {}
	bool operator < (const Person& other) const {
		return pos < other.pos;
	}
	operator int() {
		return i;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int sep, n, k;
	cin >> sep;

	cin >> n;
	int d[n+1];
	for (int i = 0; i < n; i++) {
		cin >> d[i+1];
	}

	cin >> k;
	Person a[k];
	for (int i = 0; i < k; i++) {
		cin >> a[i].bbl >> a[i].pos;
		a[i].i = i+1;
	}
	sort(a, a+k);

	vector<int> ans;
	bool shit = true;
	while (shit) {
		shit = false;
		for (int i = 0; i < k; i++) {
			if (a[i].pos != n) {
				if (i+1 < k && a[i+1].pos != n) {
					int diff = d[a[i+1].pos] - d[a[i].pos+1];
					if (diff > sep || diff < max(a[i].bbl, a[i+1].bbl))
						continue;
				}
				if (i > 0) {
					int diff = d[a[i].pos+1] - d[a[i-1].pos];
					if (diff > sep || diff < max(a[i-1].bbl, a[i].bbl))
						continue;
				}
				a[i].pos++;
				ans.push_back(a[i]);
				shit = true;
				break;
			}
		}
	}

	if (a[0].pos == n) {
		for (int it : ans) {
			cout << it << " ";
		}
		cout << nl;
	} 
	else {
		cout << "impossible" << nl;
	}

	return 0;
}
