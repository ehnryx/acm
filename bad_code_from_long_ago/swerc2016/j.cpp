#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG
//#define USE_MAGIC_IO

#define ll long long
#define pii pair<int,int>
#define pdd pair<ldouble,ldouble>
#define ldouble long double
#define nl '\n'
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

const ldouble EPS = exp(-exp(2));
const ldouble step = EPS/exp(2);

#ifdef DEBUG
const int cap = 1e0;
#else
const int cap = 1e9;
#endif

double power(double b, int e) {
	double res = 1;
	double p = b;
	while (e) {
		if (e&1) res *= p;
		p *= p;
		e = e >> 1;
	}
	return res;
}

set<int> sol[10][10]; // id, used
void generate_pref(const int id, const int n, const int m, const int cur, const int used) {
	if (id == m-1) {
		sol[id][used].insert(cur);
	}
	else {
		for (int i = id; i < m; i++) {
			sol[i][used].insert(cur);
		}
		generate_pref(id+1, n, m, cur, used);
		for (int add = 2; add < n-used; add++) {
			generate_pref(id+1, n, m, cur | (add<<(3*id)), used + add);
		}
	}
}

int fact[10];
ldouble calculate(const int id, const vector<ldouble>& p, const int n, const int m) {
	ldouble res = 0;
	ldouble left = 0;
	for (int i = id+1; i < m; i++) {
		left += p[i];
	}
	for (int count = 0; count < n; count++) {
		for (int v : sol[id][count]) {
			ldouble prob = 1;
			int times = fact[n-1]/fact[n-1-count];
			for (int i = 0; i < id; i++) {
				times /= fact[(v>>(3*i))&7];
				prob *= power(p[i], (v>>(3*i))&7);
			}
			res += times * prob * power(left, n-1-count);
		}
	}
	return res;
}

int main() {
	ios::sync_with_stdio(0); 
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(5);

	fact[0] = 1;
	for (int i = 1; i < 10; i++) {
		fact[i] = i * fact[i-1];
	}

	int n, m;
	cin >> n >> m;
	generate_pref(0, n, m, 0, 0);

	// start with probabilities equal
	vector<ldouble> p(m, 1.0/m);
	vector<ldouble> win(m);
	ldouble best, worst, avg;
	for (int t = 0; t < cap; t++) {
		best = 0;
		worst = 1;
		avg = 0;
		for (int i = 0; i < m; i++) {
			win[i] = calculate(i, p, n, m);
			best = max(best, win[i]);
			worst = min(worst, win[i]);
			avg += win[i]/m;
		}
		if (best - worst < EPS) {
			//cerr << "break properly after " << t << " iterations" << nl;
			break;
		}
		p[0] = 1;
		for (int i = 1; i < m; i++) {
			if (win[i] > avg) p[i] += step;
			else p[i] = max(0.0L, p[i] - step);
			p[0] -= p[i];
		}
	}
	//cerr << "found wins: " << nl; for (int i = 0; i < m; i++) {
		//cerr << "win " << i << ": " << win[i] << nl; }
	for (int i = 0; i < m; i++) {
		cout << p[i] << nl;
	}

	return 0;
}
