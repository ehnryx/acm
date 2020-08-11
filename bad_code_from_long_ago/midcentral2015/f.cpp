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

	int N; cin >> N;
	vector<string> v(N);
	for (int i = 0; i < N; i++)
		cin >> v[i];
	vector<string> v2(v);
	sort(v2.begin(), v2.end());
	if (v2 == v) {
		cout << "INCREASING" << endl;
		return 0;
	}
	sort(v2.rbegin(), v2.rend());
	if (v2 == v) {
		cout << "DECREASING" << endl;
		return 0;
	}
	cout << "NEITHER" << endl;

	return 0;
}
