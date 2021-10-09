#include <bits/stdc++.h>
using namespace std;

const char nl = '\n';

////////////////////////////////////////////////////////////////////////
// Z Value String Matching -- O(n+m) (UNTESTED)
// n = length of string; m = length of pattern
// USAGE:
//  0. given string s and pattern t
//  1. vector<int> z = zValue(t+s);
//  2. for i from m to m+n-1: match at i-m if z[i] >= m;
//*!
vector<int> zValue(const string& s) {
    int n = s.size();
    vector<int> z(n, n);
    for (int i=1,l=0,r=0; i<n; i++) {
        int e = max(i, min(i+z[i-l], r));
        while (e<n && s[e]==s[e-i]) e++;
        if ((z[i]=e-i)>r-i) l=i,r=e;
    }
    return z;
}
//*/

////////////////////////////////////////////////////////////////////////
// KMP String Matching (prefix function) -- O(n+m) (UNTESTED)
// n = length of string; m = length of pattern
// USAGE:
//  0. given string s and pattern t
//  1. vector<int> matches = kmp(s, t);
//*!
vector<int> prefixFunc(const string& s) {
    int n = s.size();
    vector<int> p(n, 0);
    for (int i=1,j=0; i<n; i++) {
        while (j>0 && s[i]!=s[j]) j = p[j-1];
        p[i] = (s[i]==s[j] ? ++j : j);
    }
    return p;
}
vector<int> kmp(const string& s, const string& t) {
    vector<int> p = prefixFunc(t);
    vector<int> res;
    int n = s.size();
    int m = t.size();
    for (int i=0,j=0; i<n; i++) {
        while (j>0 && s[i]!=t[j]) j = p[j-1];
        if ((s[i]==t[j] ? ++j : j) == m) {
            res.push_back(i-m+1); // store match
            j = p[j-1];
        }
    }
    return res;
}
//*/

int main() {
  ios::sync_with_stdio(0);

  for (string s,t; getline(cin,s),getline(cin,t); ) {
    /* z value string matching
    vector<int> z = zvalue(s+t);
    for (int i=s.size(); i<z.size(); i++) {
      if (z[i] >= s.size()) cout << i-s.size() << " ";
    }
    cout << nl;
    */
    ///* KMP string matching
    for (int i : kmp(t,s)) {
      cout << i << " ";
    }
    cout << nl;
    //*/
  }

  return 0;
}
