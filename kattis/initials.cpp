#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/rope>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_cxx;
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

string get_name(string s, string t, int n) {
	string res;
	res.push_back(tolower(s[0]));
	for(int i=1;i<s.size();i++) {
		if(n>0) {
			res.push_back(tolower(s[i]));
			n--;
		}
	}
	res.push_back(tolower(t[0]));
	for(int i=1;i<t.size();i++) {
		if(n>0) {
			res.push_back(tolower(t[i]));
			n--;
		}
	}
	return res;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n;
	cin>>n;
	string a[n],b[n];
	vector<string> s[n];
	vector<pair<string,int>> name;
	for(int i=0;i<n;i++) {
		cin>>a[i]>>b[i];
		string cat;
		for(char c:b[i]+a[i]) cat.push_back(tolower(c));
		name.push_back(make_pair(cat,i));
		for(int j=0;j<=a[i].size()+b[i].size()-2;j++) {
			s[i].push_back(get_name(b[i], a[i], j));
		}
	}
	sort(name.begin(),name.end());

	int dp[n][80];
	memset(dp,INF,sizeof dp);
	for(int i=0;i<n;i++) {
		int id = name[i].second;
		if(i==0) {
			for(int j=0;j<s[id].size();j++) {
				dp[i][j] = j;
				//cerr<<"set "<<dp[i][j]<<" to "<<j<<nl;
			}
		} else {
			int jd = name[i-1].second;
			for(int j=0;j<s[id].size();j++) {
				for(int k=0;k<s[jd].size();k++) {
					if(s[id][j] > s[jd][k]) {
						//cerr<<"can put "<<s[id][j]<<" after "<<s[jd][k]<<nl;
						dp[i][j] = min(dp[i][j], dp[i-1][k] + j);
					}
				}
				//cerr<<"dp "<<i<<" "<<j<<" = "<<dp[i][j]<<nl;
			}
		}
	}

	int ans = INF;
	for(int i=0;i<80;i++) {
		ans = min(ans, dp[n-1][i]);
	}
	cout<<ans<<nl;

	return 0;
}
