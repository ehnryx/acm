#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

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

//#define DEBUG

const int V = 1e6+1;
const int M = 1e3+1;
bitset<V> np;

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	np[0] = np[1] = true;
	for (int i=2; i<M; i++) {
		if (!np[i]) {
			for (int j=i*i; j<V; j+=i) {
				np[j] = true;
			}
		}
	}

	int n;
	cin >> n;

	if (n <= 5) {
		cout << 2 << nl;
		cout << 2 << " " << 4 << nl;
		return 0;
	}

	vector<int> two, three, four;
	FOR(i,3,V) {
		if (!np[i]) {
			if (4*i <= n) {
				four.push_back(i);
			} else if (3*i <= n) {
				three.push_back(i);
			} else if (2*i <= n) {
				two.push_back(i);
			}
		}
	}

	reverse(three.begin(), three.end());
	//reverse(four.begin(), four.end());

	unordered_set<int> used;
	vector<int> ans;

	int tog = 0;
	if (!two.empty()) {
		ans.push_back(two[0]);
		used.insert(two[0]);
		ans.push_back(2*two[0]);
		used.insert(2*two[0]);
	}

#ifdef DEBUG
	ans.push_back(0);
#endif

	FOR(i,2,n) {
		if (__builtin_popcount(i)==1) {
			ans.push_back(i);
			used.insert(i);
		}
	}

#ifdef DEBUG
	ans.push_back(0);
#endif

	for (int i : three) {
		if (tog == 0) {
			if (!used.count(2*i)) {
				ans.push_back(2*i);
				used.insert(2*i);
			}
			if (!used.count(i)) {
				ans.push_back(i);
				used.insert(i);
			}
			if (!used.count(3*i)) {
				ans.push_back(3*i);
				used.insert(3*i);
			}
		} else {
			if (!used.count(3*i)) {
				ans.push_back(3*i);
				used.insert(3*i);
			}
			if (!used.count(i)) {
				ans.push_back(i);
				used.insert(i);
			}
			if (!used.count(2*i)) {
				ans.push_back(2*i);
				used.insert(2*i);
			}
		}
		tog ^= 1;
	}

#ifdef DEBUG
	ans.push_back(0);
#endif

	for (int i : four) {
		if (!used.count(2*i)) {
			ans.push_back(2*i);
			used.insert(2*i);
		}
		for (int j=1; j*i<=n; j++) {
			if (j == 4) continue;
			if (!used.count(j*i)) {
				ans.push_back(j*i);
				used.insert(j*i);
			}
		}
		if (!used.count(4*i)) {
			ans.push_back(4*i);
			used.insert(4*i);
		}
	}

#ifdef DEBUG
	ans.push_back(0);
#endif

	int o = (two.empty() ? -1 : two.back());
	FOR(i,2,n) {
		if (i%2 == 0 && i != o*2 && !used.count(i)) {
			ans.push_back(i);
			used.insert(i);
		}
	}

#ifdef DEBUG
	ans.push_back(0);
#endif

	if (two.size() > 1) {
		if (!used.count(two.back()*2)) {
			ans.push_back(two.back()*2);
		}
		if (!used.count(two.back())) {
			ans.push_back(two.back());
		}
	}

	cout << ans.size() << nl;
	for (int it : ans) {
		cout << it << " ";
	}
	cout << nl;

	return 0;
}
