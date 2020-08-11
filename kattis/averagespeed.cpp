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
	cout << fixed << setprecision(2);

	int h = 0;
	int m = 0;
	int c = 0;
	ld dist = 0;
	int speed = 0;
	for(string s; getline(cin, s); ) {
		istringstream in(s);
		vector<string> line;
		for(string t; in >> t; ) {
			line.push_back(t);
		}
		int hh = stoi(line[0].substr(0, 2));
		int mm = stoi(line[0].substr(3, 2));
		int cc = stoi(line[0].substr(6, 2));
		ld dt = (hh - h) + (ld)(mm - m)/60 + (ld)(cc - c)/3600;
		dist += dt * speed;
		if(line.size() == 1) {
			cout << line[0] << " " << dist << " " << "km" << nl;
		} else {
			speed = stoi(line[1]);
		}
		h = hh;
		m = mm;
		c = cc;
	}

	return 0;
}
