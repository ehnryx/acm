//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
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
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n, h;
	cin >> n >> h;
	vector<pair<char,int>> ca, ea;
	for(int i=0; i<n; i++) {
		char c; int v;
		cin >> c >> v;
		ca.push_back(make_pair(c, v));
	}
	for(int i=0; i<n; i++) {
		char c; int v;
		cin >> c >> v;
		ea.push_back(make_pair(c, v));
	}
	ca.push_back(make_pair('D', 0));
	ea.push_back(make_pair('D', 0));

	int ch = h;
	int eh = h;
	int cd = 0;
	bool cdodge = false;
	int ed = 0;
	bool edodge = false;
	for(int i=0; i<=n; i++) {
		if(ca[i].first == 'A') {
			if(!edodge) eh -= ca[i].second;
			if(eh <= 0) {
				cout << "VICTORY" << nl;
				return 0;
			}
		} else {
			cd = ca[i].second;
			eh -= ed;
			if(eh <= 0) {
				cout << "VICTORY" << nl;
				return 0;
			}
			cdodge = true;
		}
		ed = 0;
		edodge = false;
		if(ea[i].first == 'A') {
			if(!cdodge) ch -= ea[i].second;
			if(ch <= 0) {
				cout << "DEFEAT" << nl;
				return 0;
			}
		} else {
			ed = ea[i].second;
			ch -= cd;
			if(ch <= 0) {
				cout << "DEFEAT" << nl;
				return 0;
			}
			edodge = true;
		}
		cd = 0;
		cdodge = false;
	}
	cout << "TIE" << nl;

	return 0;
}
