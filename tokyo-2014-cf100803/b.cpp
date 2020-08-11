#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int INF = 0x3f3f3f3f;
const char nl = '\n';

vector<int> toks; vector<char> ops;
string s;

ll eval1() {
	stack<ll> exps; stack<char> op;
	for (char c : s) {
		if (c >= '0' && c <= '9') exps.push(c-'0');
		else {
			while (!op.empty() && op.top() == '*') {
				int a = exps.top(); exps.pop();
				int b = exps.top(); exps.pop();
				exps.push(a * b);
				op.pop();
			}
			op.push(c);
		}
	}
	while (!op.empty()) {
		int a = exps.top(); exps.pop();
		int b = exps.top(); exps.pop();
		char c = op.top(); op.pop();
		if (c == '+') {
			exps.push(a + b);
		} else exps.push(a * b);
	}
	return exps.top();
}

ll eval2() {
	ll ans = s[0] - '0'; char op;
	for (int i = 1; i < s.size(); i++) {
		if (s[i] >= '0' && s[i] <= '9') {
			if (op == '+') ans += s[i] - '0';
			else ans *= s[i] - '0';
		} else {
			op = s[i];
		}
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> s;
	int a; cin >> a;
	int k = eval1(), l = eval2();
	//cerr << k << " " << l << " " << a << endl;
	if (k == a && l == a) {
		puts("U");
	} else if (k == a) {
		puts("M");
	} else if (l == a) {
		puts("L");
	} else puts("I");
	return 0;
}
