#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG
//#define USE_MAGIC_IO

#define ll long long
#define pii pair<int,int>
#define pdd pair<double,double>
#define ldouble long double
#define nl '\n'
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

int main() {
	//ios::sync_with_stdio(0); 
	cin.tie(0); cout.tie(0);

	string s;
	char m;
	int c;
	int T;
	vector<int> val, pref;
	cin >> T;
	while (T--) {
		int cur = 0;
		val.clear();
		cin >> m; getchar();
		if (m == 'e') {
			val.push_back(0);
			while ((c = getchar()) != '\n') {
				if (c == ' ')
					val.push_back((val[cur] + 0)%27);
				else 
					val.push_back((val[cur] + c-'a'+1)%27);
				cur++;
			}
			for (int i = 1; i < val.size(); i++) {
				if (val[i] == 0)
					cout << ' ';
				else
					cout << (char)(val[i] + 'a'-1);
			}
			cout << nl;
		}
		else {
			pref.clear();
			val.push_back(0);
			while ((c = getchar()) != '\n') {
				if (c == ' ')
					val.push_back(0);
				else
					val.push_back(c-'a'+1);
			}
			for (int i = 1; i < val.size(); i++) {
				int tmp = ((val[i] + 27 - val[i-1])%27);
				if (tmp == 0) cout << ' ';
				else cout << (char)(tmp + 'a'-1);
			}
			cout << nl;
		}
	}

	return 0;
}
