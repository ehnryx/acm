//////////
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

	int n, m, id;
	int arr[1000];

	int T;
	cin >> T;
	while (T--) {
		cin >> n >> m;
		for (int i = 0; i < n; i++) {
			cin >> arr[i];
			if (arr[i] != -1)
				id = i;
		}
		for (int i = id-1; i >= 0; i--)
			arr[i] = (arr[i+1] + m-1) % m;
		for (int i = id+1; i < n; i++)
			arr[i] = (arr[i-1] + 1) % m;
		for (int i = 0; i < n; i++)
			cout << arr[i] << " ";
		cout << nl;
	}

	return 0;
}
