#include <bits/stdc++.h>
using namespace std;

const char nl = '\n';
typedef long long ll;
typedef long double ld;

void answer(string s) {
	cout << "! " << s << endl;
	exit(0);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int good = 0;
	int bad = 0;

	function<void(int)> check_good = [&](int s) {
		while(good > -s) {
			good -= 1;
			bad -= 2;
			cout << '-' << endl;
			int yes;
			cin >> yes;
			if(yes) {
				cout << '-' << endl;
				cin >> yes;
				cout << '+' << endl;
				cin >> yes;
				if(yes) answer("ugly");
				else answer("good");
			}
		}
	};

	function<void(int)> check_bad = [&](int s) {
		while(bad < s) {
			good += 2;
			bad += 1;
			cout << '+' << endl;
			int yes;
			cin >> yes;
			if(yes) {
				cout << '-' << endl;
				cin >> yes;
				cout << '+' << endl;
				cin >> yes;
				if(yes) answer("ugly");
				else answer("bad");
			}
		}
	};

	for(int i=1, t=0; ; i=i*7, t++) {
		if(t%2) check_good(i);
		else check_bad(i);
	}

	return 0;
}
