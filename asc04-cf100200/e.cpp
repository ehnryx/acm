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

const int N = 2000 + 1;
int dp[N][6][5];
pair<int,int> pre[N][6][5];

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

#ifdef ONLINE_JUDGE
	freopen("dvd.in", "r", stdin);
	freopen("dvd.out", "w", stdout);
#endif

	string line;
	getline(cin, line);
	int n = stoi(line);
	vector<string> name(n+1);
	map<int,map<int,vector<int>>> group;
	for(int i=1; i<=n; i++) {
		getline(cin, line);
		reverse(line.begin(), line.end());
		int first = line.find(' ');
		int second = line.find(' ', first + 1);
		string syear, sregion;
		syear = line.substr(first + 1, second - first - 1);
		name[i] = line.substr(second + 1, (int)line.size() - second - 1);
		reverse(name[i].begin(), name[i].end());
		reverse(syear.begin(), syear.end());
		int year = stoi(syear);
		int region = line[0] - '1';
		group[year][region].push_back(i);
	}

	memset(dp, 0x3f^0xff, sizeof dp);
	for(int j=0; j<=5; j++) {
		for(int r=0; r<5; r++) {
			dp[0][j][r] = 0;
		}
	}

	n = group.size();
	vector<int> year(n+1);
	auto it = group.begin();
	for(int i=1; i<=n; i++, it++) {
		year[i] = it->first;
		auto& cur = it->second;
		for(int j=0; j<=5; j++) {
			for(int r=0; r<5; r++) {
				dp[i][j][r] = dp[i-1][j][r];
				pre[i][j][r] = make_pair(0, r);
				for(int bm=0; bm<1<<5; bm++) {
					int cnt = __builtin_popcount(bm);
					if(!(bm & 1<<r) || cnt > j+1) continue;
					for(int t=0; t<5; t++) {
						if(!(bm & 1<<t) || (t == r && cnt > 1)) continue;
						int val = dp[i-1][j+1-cnt][t];
						for(int k=0; k<5; k++) {
							if(bm & 1<<k) {
								val += cur[k].size();
							}
						}
						if(val > dp[i][j][r]) {
							dp[i][j][r] = val;
							pre[i][j][r] = make_pair(bm, t);
						}
					}
				}
			}
		}
	}

	int region = 0;
	for(int r=1; r<5; r++) {
		if(dp[n][5][r] > dp[n][5][region]) {
			region = r;
		}
	}

	cout << dp[n][5][region] << nl;
	vector<string> ans;
	for(int i=n, j=5, r=region; i>0; i--) {
		auto [bm, nr] = pre[i][j][r];
		if(!bm) continue;
		for(int t : group[year[i]][r]) {
			ans.push_back(name[t]);
		}
		for(int k=0; k<5; k++) {
			if((bm & 1<<k) && k != nr && k != r) {
				for(int t : group[year[i]][k]) {
					ans.push_back(name[t]);
				}
			}
		}
		if(nr != r) {
			for(int t : group[year[i]][nr]) {
				ans.push_back(name[t]);
			}
		}
		j -= __builtin_popcount(bm) - 1;
		r = nr;
	}
	reverse(ans.begin(), ans.end());
	for(const string& s : ans) {
		cout << s << nl;
	}

	assert(ans.size() == dp[n][5][region]);

	return 0;
}
