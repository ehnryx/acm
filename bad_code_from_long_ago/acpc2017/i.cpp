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

	int n, ans;
	string s;
	int T;
	cin >> T;
	while (T--) {
		ans = 0;
		cin >> s;
		n = s.size();
		for (int i = 0; i < n; i++) {
			if (letter[s[i]-'A']) {
				int j;
				for (j = 1; i-j >= 0 && j+i < n; j++) {
					if (s[i-j] == s[i+j] && letter[s[i+j]-'A'])
						continue;
					else 
						break;
				}
				ans = max(ans, 2*j-1);
			}
			if (i > 0 && s[i-1] == s[i] && letter[s[i]-'A']) {
				int j;
				for (j = 1; i-1-j >= 0 && j+i < n; j++) {
					if (s[i-1-j] == s[i+j] && letter[s[i+j]-'A'])
						continue;
					else
						break;
				}
				ans = max(ans, 2*j);
			}
			//cerr << "ans after " << i << ": " << ans << endl;
		}
		cout << ans << endl;
	}

	return 0;
}
