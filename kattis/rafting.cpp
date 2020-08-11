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
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
ld dp(const pt& a, const pt& b) { return real(conj(a)*b); }
inline ld lp_dist(const pt &a, const pt &b, const pt &p) {
  return cp(b - a, p - a) / abs(b - a); }
inline ld lsp_dist(const pt &a, const pt &b, const pt &p) {
  return dp(b - a, p - a) > 0 && dp(a - b, p - b) > 0 ?
    abs(cp(b - a, p - a) / abs(b - a)) : min(abs(a - p), abs(b - p)); }

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int T;
	cin>>T;
	while(T--) {
		int n;
		cin>>n;
		vector<pt> in;
		for(int i=0;i<n;i++) {
			int x,y;
			cin>>x>>y;
			in.push_back(pt(x,y));
		}
		int m;
		cin>>m;
		vector<pt> out;
		for(int i=0;i<m;i++) {
			int x,y;
			cin>>x>>y;
			out.push_back(pt(x,y));
		}

		ld ans = 1e19;
		for(int i=0;i<n;i++) {
			for(int j=0;j<m;j++) {
				ans = min(ans, lsp_dist(out[j],out[(j+1)%m],in[i]));
				ans = min(ans, lsp_dist(in[i],in[(i+1)%n],out[j]));
			}
		}
		cout<<ans/2<<nl;
	}

	return 0;
}
