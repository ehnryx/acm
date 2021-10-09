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

  int cnt[10];
  int ans = 0;
  string s;
  cin >> s;
  if (s.size() == 3) {
    for (int i = 0; i < 10; i++) {
      memset(cnt, 0, sizeof(cnt));
      cnt[i]++;
      int temp = 1;
      temp *= (1<<(cnt[2]));
      temp *= (1<<(cnt[5]));
      temp *= (1<<(cnt[6]));
      temp *= (1<<(cnt[9]));
      ans += temp;
    }
  } else if (s.size() == 5) {
    for (int j = 0; j < 10; j++)
    for (int i = 0; i < 10; i++) {
      memset(cnt, 0, sizeof(cnt));
      cnt[i]++;
      cnt[j]++;
      int temp = 1;
      temp *= (1<<(cnt[2]));
      temp *= (1<<(cnt[5]));
      temp *= (1<<(cnt[6]));
      temp *= (1<<(cnt[9]));
      ans += temp;
    }
  } else if (s.size() == 7) {
    for (int k = 0; k < 10; k++)
    for (int j = 0; j < 10; j++)
    for (int i = 0; i < 10; i++) {
      memset(cnt, 0, sizeof(cnt));
      cnt[i]++;
      cnt[j]++;
      cnt[k]++;
      int temp = 1;
      temp *= (1<<(cnt[2]));
      temp *= (1<<(cnt[5]));
      temp *= (1<<(cnt[6]));
      temp *= (1<<(cnt[9]));
      ans += temp;
    }
  }
  cout << ans << nl;

  return 0;
}
