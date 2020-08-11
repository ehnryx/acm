#include <bits/stdc++.h>
using namespace std;

#define debug

#define ll long long
#define pii pair<int,int>
#define pdd pair<double,double>
#define ldouble long double
const ll MOD = 1e9+7;
const int INF = 0x7f7f7f7f;
const ll INFLL = 0x7f7f7f7f7f7f7f7f;

vector<bool> letter(26);
bool ismirror(const string &s) {
	for (int i = 0; i < s.size(); i++) {
		if (s[i] != s[s.size()-1-i])
			return false;
		if (!letter[s[i]-'A'])
			return false;
	}
	return true;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	letter['A'-'A'] = true;
	letter['H'-'A'] = true;
	letter['I'-'A'] = true;
	letter['M'-'A'] = true;
	letter['O'-'A'] = true;
	letter['T'-'A'] = true;
	letter['U'-'A'] = true;
	letter['V'-'A'] = true;
	letter['W'-'A'] = true;
	letter['X'-'A'] = true;
	letter['Y'-'A'] = true;

	string s;
	int T;
	cin >> T;
	while (T--) {
		cin >> s;
		if (ismirror(s)) cout << "yes" << endl;
		else cout << "no" << endl;
	}

	return 0;
}
