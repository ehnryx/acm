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

  string n, m;
  cin >> n >> m;
  int trail = 0;
  for (int i = n.size()-1; i >= 0; i--) {
    if (n[i] == '0') trail++;
    else break;
  }
  int length = m.size()-1;
  int nonzero = n.size()-trail;

  int overlap = min(length, trail);
  length -= overlap;
  trail -= overlap;

  if (length == 0) {
    for (int i = 0; i < trail + nonzero; i++)
      cout << n[i];
    cout << nl;
  } else {
    if (length >= nonzero) {
      //cerr << "length: " << length << nl;
      //cerr << "nonzero: " << nonzero << nl;
      cout << "0.";
      for (int i = 0; i < length-nonzero; i++)
        cout << "0";
      for (int i = 0; i < nonzero; i++)
        cout << n[i];
      cout << nl;
    } else {
      for (int i = 0; i < nonzero-length; i++)
        cout << n[i];
      cout << ".";
      for (int i = nonzero-length; i < nonzero; i++)
        cout << n[i];
      cout << nl;
    }
  }

  return 0;
}
