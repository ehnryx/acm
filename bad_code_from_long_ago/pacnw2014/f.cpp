#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG

#define ll long long
#define pii pair<int,int>
#define pdd pair<ldouble,ldouble>
#define ldouble long double
#define pt complex<ldouble>
#define ld ldouble
#define nl '\n'
const ll MOD = 1e9+9;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ldouble EPS = 1e-9;

vector<vector<int>> mats[5];

ll twopow(ll& e) {
	ll ans = 1;
	ll cur = 2;
	while (e) {
		if (e % 2)
			ans *= cur, ans %= MOD;
		cur *= cur, cur %= MOD;
		e /= 2;
	}
	return ans;
}

inline vector<vector<int>> togrid(int sz, int mask) {
	vector<vector<int>> ans(sz, vector<int>(sz));
	for (int i = 0; i < sz; i++) {
		fo 

void pre() {
	mats[2] = vector<vector<int>>(1 << 4, vector<int>(1 << 4));
	for (int i = 0; i < (1 << 4); i++) {
		for (int j = 0; j < (1 << 4); j++) {


int main() {
	ios::sync_with_stdio(0); 
	cin.tie(0); cout.tie(0);

	pre();
	int T; cin >> T;
	while (T--) {
		int M; ll N; cin >> M >> N;
		switch (M) {
			case 1: cout << twopow(N) << endl; break;
			default: cout << matexp(M, N) << endl; break;
		}
	}
	return 0;
}
