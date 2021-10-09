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

  string s;
  cin >> s;
  if (s.size() > 26) {
    cout << "IMPOSSIBLE" << nl;
  }
  else {
    bitset<26> fixed, seen;
    char arr[27]; arr[s.size()] = '\0';
    for (int i = 0; i < s.size(); i++) {
      if (!seen[s[i]-'a']) {
        seen[s[i]-'a'] = true;
        fixed[s[i]-'a'] = true;
      }
    }
    int curr = 0;
    seen.reset();
    for (int i = 0; i < s.size(); i++) {
      if (!seen[s[i]-'a']) {
        seen[s[i]-'a'] = true;
        arr[i] = s[i];
      }
      else {
        while (fixed[curr])
          curr++;
        arr[i] = curr+'a';
        curr++;
      }
    }
    cout << arr << nl;
  }

  return 0;
}
