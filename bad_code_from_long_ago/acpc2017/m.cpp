#include <bits/stdc++.h>
using namespace std;

#define debug

#define ll long long
#define pii pair<int,int>
#define pdd pair<double,double>
#define ldouble long double
const ll MOD = 1e9+7;
const int INF = 0x7f7f7f7f;
const ll INFLL = 0x7f7f7f7f7f7f7f7f;

int main() {
  //ios::sync_with_stdio(0);
  cin.tie(0);

  map<string,double> convert;
  string s;
  double rate, ans;
  int types, n;
  int T;
  scanf("%d", &T);
  //cerr << T << endl;
  while (T--) {
    convert.clear();
    convert.insert(pair<string,double>("JD", 1));
    scanf("%d %d", &types, &n);
    //cerr << types << " " << n << endl;
    for (int i = 0; i < types; i++) {
      cin >> s; scanf("%lf", &rate);
      //cerr << s << " " << rate << endl;
      convert.insert(pair<string,double>(s, rate));
    }
    ans = 0;
    for (int i = 0; i < n; i++) {
      scanf("%lf", &rate); cin >> s;
      //cerr << rate << " " << s << endl;
      ans += (convert[s]*rate);
    }
    cout << fixed << setprecision(6) << ans << endl;
  }

  return 0;
}
