#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
#define nl '\n'

vector<int> query(const vector<int>& v) {
  if (v.size() == 0) return v;
  cout << "ASK " << v.size();
  for (auto& x : v) {
    cout << " " << x;
  }
  cout << endl;
  vector<int> w;
  for (int i=0; i<v.size(); ++i) {
    int x;
    cin >> x;
    w.push_back(x);
  }
  return w;
}

const int N = 1010;
int controller[N], b[N];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int n;
  cin >> n;

  for (int i=0; i<10; ++i) {
    vector<int> quer;
    for (int j=1; j<=n; ++j) {
      if (j&(1<<i)) {
        quer.push_back(j);
      }
    }
    vector<int> lights = query(quer);
    for (auto& x : lights) {
      //cerr << " CONTROLLER " << x << " : " << (1<<i) << endl;
      controller[x] |= (1<<i);
    }
  }
  cout << "ANSWER ";
  for (int i=1; i<=n; ++i) {
    cout << controller[i] << " ";
  }
  cout << endl;

  return 0;
}
