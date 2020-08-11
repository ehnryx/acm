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

vector<int> valid = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

int isleap(int n) {
	if (n % 400 == 0) return 1;
	else if (n % 100 == 0) return 0;
	else if (n % 4 == 0) return 1;
	else return 0;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n, m, k;
	cin >> m >> n >> k;

	string s;
	cin >> s;
	int day, month, year;
	day = stoi(s.substr(0, 2));
	month = stoi(s.substr(3, 5));
	year = stoi(s.substr(6, 10));

	year += 60;

	for (int i = 0; i < k; i++) {
		bool shit = false;
		if (month == 2 && day > valid[month] + isleap(year))
			shit = true;
		else if (month != 2 && day > valid[month]) 
			shit = true;

		if (2012 + i*n / 12 < year || (2012 + i*n / 12 <= year && 1 + i*n % 12 <= month + shit)) {
			month += m;
			if (month > 12) {
				month %= 12;
				year++;
			}
		}
	}

	if (month == 2 && day > valid[month] + isleap(year)) {
		month++;
		day = 1;
	} 
	else if (month != 2 && day > valid[month]) {
		month++;
		day = 1;
	}

	cout << setw(2) << setfill('0') << day << ".";
	cout << setw(2) << setfill('0') << month << ".";
	cout << year << nl;

	return 0;
}
