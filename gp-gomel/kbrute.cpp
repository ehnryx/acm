#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using pii = pair<int,int>;
using ll = long long;
using ld = long double;
using pt = complex<ld>;
const char nl = '\n';

const int N = 100;
int divs[N];

vector<pii> factorize(int n) {
  if (n == 1) {
    return vector<pii>();
  }

  vector<pii> ans;
  for (int i=2; i*i <=n; ++i) {
    if (n%i == 0) {
      ans.push_back(pii(i, 0));
      while (n%i == 0) {
        ans.back().second++;
        n/=i;
      }
    }
  }
  return ans;
}

vector<vector<int>> solve(int n) {
  vector<int> divs;
  for (int i=1; i*i<=n; ++i) {
    if (n%i == 0) {
      divs.push_back(i);
      if (i*i != n) {
        divs.push_back(n/i);
      }
    }
  }

  vector<vector<int>> ans;
  for (int i=1; i<(1<<(divs.size())); ++i) {
    vector<int> v;
    int g = 0;
    for (int j=0; j<divs.size(); ++j) {
      if ((i&(1<<j)) == 0) continue;
      v.push_back(divs[j]);
      g = __gcd(g, divs[j]);
    }
    int lcm = 1;
    for (int i=0; i<v.size(); ++i) {
      lcm = lcm*v[i]/__gcd(lcm, v[i]);
    }

    if (lcm == n && g == 1) {
      ans.push_back(v);
    }
  }

  return ans;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  for (int i=1; i<=100; ++i) {
    vector<pii> f = factorize(i);
    cout << i << ": {";
    for (auto& p : f) {
      cout << p.first << "^" << p.second << ", ";
    }
    cout << "} : ";
    vector<vector<int>> s = solve(i);
    cout << " (SIZE " << s.size() << ") ";
    for (auto& v : s) {
      cout << "{";
      for (auto& x : v) {
        cout << x << ",";
      }
      cout << "}; ";
    }
    cout << endl;
  }

  return 0;
}
