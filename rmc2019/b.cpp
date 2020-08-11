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

const int N = 60 + 1;
const int M = 65000 + 1;
queue<int> pref[N];
vector<string> ans[N];
unordered_set<int> have[N];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n, m;
	cin >> n >> m;
	unordered_map<string,int> idx;
	vector<string> name;
	int id = 0;
	for(int i=0; i<n; i++) {
		int k;
		cin >> k;
		for(int j=0; j<k; j++) {
			string s;
			cin >> s;
			if(!idx.count(s)) {
				idx[s] = id++;
				name.push_back(s);
			}
			pref[i].push(idx[s]);
			have[i].insert(idx[s]);
		}
	}
	int k;
	cin >> k;
	for(int i=0; i<k; i++) {
		string s;
		cin >> s;
		if(!idx.count(s)) {
			idx[s] = id++;
			name.push_back(s);
		}
		for(int j=0; j<n; j++) {
			if(!have[j].count(idx[s])) {
				pref[j].push(idx[s]);
			}
		}
	}

	unordered_set<int> vis;
	for(int t=0; t<m; t++) {
		for(int i=0; i<n; i++) {
			while(vis.count(pref[i].front())) {
				pref[i].pop();
			}
			vis.insert(pref[i].front());
			ans[i].push_back(name[pref[i].front()]);
			pref[i].pop();
		}
	}

	for(int i=0; i<n; i++) {
		for(const string& s : ans[i]) {
			cout << s << " ";
		}
		cout << nl;
	}

	return 0;
}
