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

bool match(int a, int b) {
	if(a>b) return match(b,a);
	if(a==2 && b==3) return true;
	if(a==3 && b==5) return true;
	if(a==6 && b==9) return true;
	if(a==0 && b==9) return true;
	if(a==0 && b==6) return true;
	return false;
}

bool add(int a, int b) {
	if(a==0 && b==8) return true;
	if(a==6 && b==8) return true;
	if(a==9 && b==8) return true;
	if(a==1 && b==7) return true;
	if(a==5 && b==6) return true;
	if(a==5 && b==9) return true;
	if(a==3 && b==9) return true;
	return false;
}

bool sub(int a, int b) {
	return add(b, a);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	string s, t;
	cin >> s >> t;
	int n = s.size();
	string a, b;
	for(int i=0; i<n; i++) {
		if(s[i] != t[i]) {
			a.push_back(s[i]);
			b.push_back(t[i]);
		}
	}
	if(a.size() == 1 && match(a[0]-'0', b[0]-'0')) {
		cout << "yes" << nl;
	} else if(a.size() == 2 && add(a[0]-'0', b[0]-'0') && sub(a[1]-'0', b[1]-'0')) {
		cout << "yes" << nl;
	} else if(a.size() == 2 && sub(a[0]-'0', b[0]-'0') && add(a[1]-'0', b[1]-'0')) {
		cout << "yes" << nl;
	} else {
		cout << "no" << nl;
	}

	return 0;
}
