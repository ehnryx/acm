#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

///* advent of code
typedef istringstream iss;
#define pb push_back
#define ins insert
#define multiset mset
#define getl(A) getline(cin, A)
//*/

const ll INF = 0x3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;



int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	map<char,int> bs;
	bs['i'] = bs['I'] = 0;
	bs['v'] = bs['V'] = 0;
	bs['x'] = bs['X'] = 0;
	bs['l'] = bs['L'] = 0;
	bs['c'] = bs['C'] = 0;
	bs['d'] = bs['D'] = 0;
	bs['m'] = bs['M'] = 0;

	string s;
	cin >> s;
	for (char c : s) {
		if (bs.count(c)) {
			bs[tolower(c)]++;
		}
	}

	string ans;
	for (int i = 0; i < min(3, bs['m']); i++)
		ans.push_back('M');
	bs['m'] -= min(3, bs['m']);
	if (bs['m'] > 0 && bs['c'] > 0 && bs['c'] + (bs['d']>0) <= 2) {
		ans.push_back('C');
		ans.push_back('M');
		bs['c']--;
		bs['m']--;
	} else {
		for (int i = 0; i < min(1, bs['d']); i++)
			ans.push_back('D');
		for (int i = 0; i < min(3, bs['c']); i++)
			ans.push_back('C');
		bs['d'] -= min(1, bs['d']);
		bs['c'] -= min(3, bs['c']);
	}
	if (bs['c'] > 0 && bs['x'] > 0 && bs['x'] + (bs['l']>0) <= 2) {
		ans.push_back('X');
		ans.push_back('C');
		bs['x']--;
		bs['c']--;
	} else {
		for (int i = 0; i < min(1, bs['l']); i++)
			ans.push_back('L');
		for (int i = 0; i < min(3, bs['x']); i++)
			ans.push_back('X');
		bs['l'] -= min(1, bs['l']);
		bs['x'] -= min(3, bs['x']);
	}
	if (bs['x'] > 0 && bs['i'] > 0 && bs['i'] + (bs['v']>0) <= 2) {
		ans.push_back('I');
		ans.push_back('X');
	} else {
		for (int i = 0; i < min(1, bs['v']); i++)
			ans.push_back('V');
		for (int i = 0; i < min(3, bs['i']); i++)
			ans.push_back('I');
	}
	cout << ans << nl;

	return 0;
}
