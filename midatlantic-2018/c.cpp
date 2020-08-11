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

string convert(const string& s) {
	string res;
	for(char c:s) {
		if(isalpha(c)) {
			res.push_back(tolower(c));
		}
	}
	return res;
}

bool contains(const string& s, const string& t) {
	int i = 0;
	for(char c:t) {
		if(i>s.size()) return false;
		while(c!=s[i]) {
			i++;
			if(i>s.size()) return false;
		}
		i++;
	}
	return true;
}

bool similar(string s, const string& t) {
	if(s.size() == t.size()) {
		for(int i=0;i<s.size();i++) {
			if(i>0) {
				swap(s[i],s[i-1]);
				if(s==t) return true;
				swap(s[i],s[i-1]);
			}
			char orig = s[i];
			for(int c=0;c<26;c++) {
				s[i] = c+'a';
				if(s==t) return true;
			}
			s[i] = orig;
		}
		return false;
	} else if(s.size() == t.size()-1) {
		return contains(t,s);
	} else if(t.size() == s.size()-1) {
		return contains(s,t);
	}
	return false;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	set<string> w;
	for(string s; cin>>s && s!="***"; ) {
		string t = convert(s);
		if(!t.empty()) w.insert(t);
	}

	bool out = false;
	for(const string& s:w) {
		vector<string> sim;
		for(const string& t:w) {
			if(s!=t && similar(s,t)) {
				sim.push_back(t);
			}
		}
		if(!sim.empty()) {
			cout<<s<<": ";
			for(const string& t:sim) {
				cout<<t<<" ";
			}
			cout<<nl;
			out = true;
		}
	}
	if(!out) {
		cout<<"***"<<nl;
	}

	return 0;
}
