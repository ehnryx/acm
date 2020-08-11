#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

const ll INF = 0x3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;

int n, X; ld v;
int L[101];
int sumL;
ld vx, vy, vi[101];

ld vertical() {
	ld res = vy * (X - sumL)/vx;
	for (int i = 0; i < n; i++) {
		res += (vy + vi[i]) * L[i]/vx;
	}
	return res;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(3);

	int li, ri;
	cin >> n >> X >> v;
	for (int i = 0; i < n; i++) {
		cin >> li >> ri >> vi[i];
		L[i] = ri-li;
		sumL += L[i];
	}
	ld left = -v;
	ld right = v;
	for (int i = 0; i < 10000 && right-left > EPS; i++) {
		vy = (left+right)/2;
		vx = sqrt(v*v - vy*vy);
		ld vert = vertical();
		if (vert > 0) 
			right = vy;
		else 
			left = vy;
	}
	ld orig_time = X/v;
	ld new_time = X/vx;
	if (new_time > 2*orig_time)
		cout << "Too hard" << nl;
	else
		cout << new_time << nl;

	return 0;
}
