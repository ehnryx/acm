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


int calc(int u, const vector<int>& x, const vector<vector<int>>& adj, const vector<int>& val, const vector<char>& op) {
	if(val[u] != -1) return x[val[u]];
	vector<int> ch;
	for(int w : adj[u]) {
		ch.push_back(calc(w, x, adj, val, op));
	}
	if(ch.size() == 1) return ch[0];
	if(op[u] == '+') return ch[0] + ch[1];
	if(op[u] == '-') return ch[0] - ch[1];
	if(op[u] == '*') return ch[0] * ch[1];
	assert(false);
}

// TODO
// double-check correctness
// read limits carefully
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	for(int n; cin >> n && n; ) {
		vector<int> v(n);
		for(int i=0; i<n; i++) {
			cin >> v[i];
		}
		int res;
		cin >> res;

		string s;
		cin >> s;
		int cid = 0;
		int cur = 0;
		vector<int> par(s.size());
		vector<int> val(s.size(), -1);
		vector<char> op(s.size());
		vector<vector<int>> adj(s.size());
		int vid = 0;
		for(char c : s) {
			if(c == '(') {
				par[++cid] = cur;
				adj[cur].push_back(cid);
				cur = cid;
			} else if(c == ')')  {
				cur = par[cur];
			} else if(isalpha(c)) {
				par[++cid] = cur;
				adj[cur].push_back(cid);
				cur = cid;
				val[cur] = vid++;
				cur = par[cur];
			} else {
				op[cur] = c;
			}
		}


		bool ok = false;
		sort(v.begin(), v.end());
		do {
			if(calc(0, v, adj, val, op) == res) {
				ok = true;
				break;
			}
		} while(next_permutation(v.begin(), v.end()));
		if(ok) {
			cout << "YES" << nl;
		} else {
			cout << "NO" << nl;
		}
	}

	return 0;
}
