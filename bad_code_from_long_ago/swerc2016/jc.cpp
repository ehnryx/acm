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
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ldouble EPS = 1e-9;

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
  cerr << "------------------------------" << nl;
  cerr << "calculating probability for " << id << nl;
  cerr << nl;
  for (int count = 0; count < n; count++) {
    cerr << "prev count: " << count << nl;
    for (int v : sol[id][count]) {
      cerr << "do sol " << bitset<7*3>(v) << nl;
      cerr << "left: " << left << nl;
      cerr; ldouble add = 0;
      ldouble prob = 1;
      int times = fact[n-1]/fact[n-1-count];
      for (int i = 0; i < id; i++) {
        times /= fact[(v>>(3*i))&7];
        prob *= power(p[i], (v>>(3*i))&7);
      }
      cerr << "times: " << times << nl;
      cerr << "prob: " << prob << nl;
      cerr << "left pow: " << n-1-count << nl;
      res += times * prob * power(left, n-1-count);
      cerr; add += times * prob * power(left, n-1-count);
      cerr << "add: " << add << nl;
      cerr << nl;
    }
  }
  return res;
}

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  const int id = 6;

  fact[0] = 1;
  for (int i = 1; i < 10; i++)
    fact[i] = i * fact[i-1];

  vector<ldouble> p;
  ldouble t;
  while (cin >> t) {
    p.push_back(t);
  }
  int m = p.size();
  int n = m-1;
  generate_pref(0, n, m, 0, 0);
  cout << calculate(id, p, n, m) << nl;

  return 0;
}
