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

  string alphabet[26];
  alphabet['a'-'a'] = "@";
  alphabet['b'-'a'] = "8";
  alphabet['c'-'a'] = "(";
  alphabet['d'-'a'] = "|)";
  alphabet['e'-'a'] = "3";
  alphabet['f'-'a'] = "#";
  alphabet['g'-'a'] = "6";
  alphabet['h'-'a'] = "[-]";
  alphabet['i'-'a'] = "|";
  alphabet['j'-'a'] = "_|";
  alphabet['k'-'a'] = "|<";
  alphabet['l'-'a'] = "1";
  alphabet['m'-'a'] = "[]\\/[]";
  alphabet['n'-'a'] = "[]\\[]";
  alphabet['o'-'a'] = "0";
  alphabet['p'-'a'] = "|D";
  alphabet['q'-'a'] = "(,)";
  alphabet['r'-'a'] = "|Z";
  alphabet['s'-'a'] = "$";
  alphabet['t'-'a'] = "']['";
  alphabet['u'-'a'] = "|_|";
  alphabet['v'-'a'] = "\\/";
  alphabet['w'-'a'] = "\\/\\/";
  alphabet['x'-'a'] = "}{";
  alphabet['y'-'a'] = "`/";
  alphabet['z'-'a'] = "2";
  
  char c;
  while ((c = getchar()) != '\n') {
    if (isalpha(c))
      cout << alphabet[tolower(c)-'a'];
    else
      cout << c;
  }
  cout << endl;

  return 0;
}
