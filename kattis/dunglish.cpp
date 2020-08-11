//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



// TODO
// double-check correctness
// read limits carefully
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n;
	cin >> n;
	vector<string> line;
	for(int i=0; i<n; i++) {
		string s;
		cin >> s;
		line.push_back(s);
	}

	int m;
	cin >> m;
	unordered_map<string,int> yes, all;
	unordered_map<string,string> only;
	for(int i=0; i<m; i++) {
		string a, b, c;
		cin >> a >> b >> c;
		only[a] = b;
		if(c == "correct") {
			yes[a]++;
		}
		all[a]++;
	}

	ll correct = 1;
	ll incorrect = 1;
	for(string& s : line) {
		correct *= yes[s];
		incorrect *= all[s];
		s = only[s];
	}

	if(incorrect == 1) {
		for(const string& s : line) {
			cout << s << " ";
		}
		cout << nl;
		cout << (correct ? "correct" : "incorrect") << nl;
	} else {
		cout << correct << " correct" << nl;
		cout << incorrect - correct << " incorrect" << nl;
	}

	return 0;
}
