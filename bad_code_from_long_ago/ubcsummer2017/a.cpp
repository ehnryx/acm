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

int getmax(int n) {
	for (int i = 0; i < 64; i++) {
		if (n <= (1LL<<(i+1))) {
			return i;
		}
	}
}

int findday(int n, bool type) {
	if (n < 2) return 0;
	if (type) {
		int t = getmax(n);
		return t+1;
	}
	else {
		return n-1;
	}
}

void solve(int left, int right, bool type) {
	if (left == right) return;
	int len = right-left+1;
	if (type) {
		vector<int> first, second;
		int bit = 1<<getmax(len);
		while (bit) {
			first.clear();
			second.clear();
			for (int i = left-1; i < right; i++) {
				if (i & bit) first.push_back(i+1);
				else second.push_back(i+1);
			}
			cout << first.size() << " ";
			for (int i = 0; i < first.size(); i++)
				cout << first[i] << " ";
			cout << nl;
			cout << second.size() << " ";
			for (int i = 0; i < second.size(); i++) 
				cout << second[i] << " ";
			cout << nl;
			bit = bit>>1;
		}
	}
	else {
		cout << 1 << " " << left << nl;
		cout << len-1 << " "; 
		for (int i = left+1; i <= right; i++) 
			cout << i << " ";
		cout << nl;
		solve(left+1, right, type);
	}
}

int main() {
	ios::sync_with_stdio(0); 
	cin.tie(0); cout.tie(0);

	int n;
	bool type;
	int T;
	cin >> T;
	for (int cc = 1; cc <= T; cc++) {
		cin >> n >> type;
		int days = findday(n, type);
		cout << days << nl;
		solve(1, n, type);
	}

	return 0;
}
