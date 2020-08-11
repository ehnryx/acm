#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;



int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	string s;
	cin >> s;

	list<char> ans;
	auto it = ans.begin();
	for (char c : s) {
		if (c == 'L') {
			if (it != ans.begin()) --it;
		} else if (c == 'R') {
			if (it != ans.end()) ++it;
		} else {
			it = next(ans.insert(it, c));
		}
	}

	for (char c : ans) {
		cout << c;
	}
	cout << nl;

	return 0;
}
