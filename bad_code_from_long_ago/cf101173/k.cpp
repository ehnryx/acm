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

void flip(char s[], int i) {
  if (s[i] == '0') s[i] = '1';
  else s[i] = '0';
  if (s[i-1] == '0') s[i-1] = '1';
  else s[i-1] = '0';
}

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  char s[1000000];
  scanf("%s", s);
  int n = strlen(s);
  vector<int> ans;
  for (int i = 0; i < n-3; i++) {
    if (s[i] == s[i+1]) {
      if (s[i+1] == s[i+2]) {
        if (s[i+2] == s[i+3]) {
          ans.push_back(i+2);
          flip(s, i+2);
        }
        else {
          ans.push_back(i+3);
          flip(s, i+3);
        }
      } else {
        if (s[i+2] == s[i+3]) { 
          ans.push_back(i+2);
          flip(s, i+2);
        }
      }
      i += 2;
    }
  }
  if (s[n-2] == s[n-3]) {
    ans.push_back(n-1);
  }

  cout << ans.size() << nl;
  for (int it : ans) 
    cout << it << " ";
  cout << nl;

  return 0;
}
