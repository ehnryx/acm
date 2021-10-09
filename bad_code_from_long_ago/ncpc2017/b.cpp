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

struct Runner {
  string name;
  double first;
  double second;
};

bool cmpf(const Runner& a, const Runner& b) {
  return a.first < b.first;
}
bool cmps(const Runner& a, const Runner& b) {
  return a.second < b.second;
}

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  int n;
  cin >> n;
  vector<Runner> first(n), second(n);
  for (int i = 0; i < n; i++) {
    cin >> first[i].name >> first[i].first >> first[i].second;
    second[i] = first[i];
  }
  sort(first.begin(), first.end(), cmpf);
  sort(second.begin(), second.end(), cmps);

  int ans, seen;
  double best, cur;
  best = INFLL;
  for (int i = 0; i < 4; i++) {
    //cerr << "TSE" << nl;
    cur = first[i].first;
    //cerr << first[i].first << nl;
    seen = 0;
    for (int j = 0; j < 3; j++) {
      if (first[i].name == second[j].name) 
        seen = 1;
      cur += second[j + seen].second;
      //cerr << second[j+seen].second << nl;
    }
    if (cur < best) {
      best = cur;
      ans = i;
    }
  }
  
  cout << best << nl;
  cout << first[ans].name << nl;
  seen = 0;
  for (int j = 0; j < 3; j++) {
    if (first[ans].name == second[j].name)
      seen = 1;
    cout << second[j+seen].name << nl;
  }

  return 0;
}
