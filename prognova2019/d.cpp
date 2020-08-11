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
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
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

	int n;
	cin >> n;
	string all[n];
	for(int i=0; i<n; i++) {
		cin >> all[i];
	}
	sort(all, all+n);

	int m;
	cin >> m;
	for(int j=0; j<m; j++) {
		string s;
		cin >> s;
		string res;
		for(int i=0; i<s.size(); i++) {
			if(s[i] != '#') {
				res.push_back(s[i]);
			} else {
				auto lb = lower_bound(all, all+n, res + " ");
				auto rb = upper_bound(all, all+n, res + "|");
				if(lb == rb) {
					for(; i<s.size(); i++) {
						if(s[i] != '#') {
							res.push_back(s[i]);
						}
					}
					break;
				} else {
					int cnt = rb - lb;
					int tabs = 0;
					for(; i<s.size() && s[i]=='#'; i++) {
						tabs++;
					}
					assert(tabs > 0);
					tabs = (tabs-1) % cnt;
					res = *(lb + tabs);
					--i;
				}
			}
		}
		cout << res << nl;
	}

	return 0;
}
