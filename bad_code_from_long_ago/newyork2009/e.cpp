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
	ios::sync_with_stdio(0); 
	cin.tie(0); cout.tie(0);

	string s;
	int T;
	cin >> T;
	for (int cc = 1; cc <= T; cc++) {
		cin >> cc >> s;
		if (s.size() == 1) cout << cc << " BIGGEST" << nl;
		else {
			int start = -1;
			for (int i = s.size()-2; i >= 0; i--) {
				if (s[i] < s[i+1]) {
					start = i;
					break;
				}
			}
			if (start == -1) cout << cc << " BIGGEST" << nl;
			else {
				vector<int> head;
				for (int i = 0; i < start; i++) {
					head.push_back(s[i]-'0');
				}
				vector<int> tail;
				for (int i = start; i < s.size(); i++) {
					tail.push_back(s[i]-'0');
				}
				for (int i = tail.size()-1; i > 0; i--) {
					if (tail[i] > tail[0]) {
						swap(tail[i], tail[0]);
						break;
					}
				} sort(tail.begin()+1, tail.end());
				cout << cc << " ";
				for (int it: head) cout << it;
				for (int it: tail) cout << it;
				cout << nl;
			}
		}
	}

	return 0;
}
