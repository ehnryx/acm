#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const char nl = '\n';

struct solution {
  vector<vector<int>> contained;
  solution() {}
  void insert(int x[13]) {
    vector<int> opt;
    for (int i=0; i<13; ++i) {
      for (int j=0; j<x[i]; ++j) {
        opt.push_back(i);
      }
    }
    contained.push_back(opt);
  }
  bool operator < (const solution& o) const {
    return contained.size() < o.contained.size();
  }
};

int ord(char c) {
  switch(c) {
    case '2': return 0;
    case '3': return 1;
    case '4': return 2;
    case '5': return 3;
    case '6': return 4;
    case '7': return 5;
    case '8': return 6;
    case '9': return 7;
    case 'T': return 8;
    case 'J': return 9;
    case 'Q': return 10;
    case 'K': return 11;
    case 'A': return 12;
  }
  return -1;
}

void fill_rem(solution& sol, int amt[13]) {
  for (int i=0; i<13; ++i) {
    if (amt[i]) {
      vector<int> p;
      for (int j=0; j<amt[i]; ++j) {
        p.push_back(i);
      }
      sol.contained.push_back(p);
    }
  }
}

int count_extra(int amt[13]) {
  bool good = true;
  int extra = 0;
  for (int z=0; z<13; ++z) {
    if (amt[z] < 0) good = false;
    if (amt[z]) ++ extra;
  }
  return (good ? extra : 100);
}

solution two_straights(int amt[13]) {
  solution sol;
  int ee[13];
  memset(ee, 0, sizeof ee);
  for (int i=0; i<13; ++i) {
    ee[i]++;
    sol.insert(ee);
    ee[i]--;
  }

  for (int i=0; i<=8; ++i) {
    for (int z=i; z<i+5; ++z) {
      amt[z]--;
    }
    for (int j=i; j<=8; ++j) {
      for (int z=j; z<j+5; ++z) {
        amt[z]--;
      }

      int extra = count_extra(amt);

      if (extra < sol.contained.size()) {
        solution nsol;
        vector<int> p;
        for (int z=i; z<i+5; ++z) {
          p.push_back(z);
        }
        nsol.contained.push_back(p);
        p.clear();
        for (int z=j; z<j+5; ++z) {
          p.push_back(z);
        }
        nsol.contained.push_back(p);
        p.clear();

        fill_rem(nsol, amt);

        sol = nsol;
      }

      for (int z=j; z<j+5; ++z) {
        amt[z]++;
      }
    }
    for (int z=i; z<i+5; ++z) {
      amt[z]++;
    }
  }

  return sol;
}

void print_sol(solution sol, vector<string> of[13]) {
  cout << sol.contained.size() << "\n";
  for (auto& v : sol.contained) {
    for (auto& x : v) {
      cout << of[x].back() << " ";
      of[x].pop_back();
    }
    cout << "\n";
  }
}

void solve() {
  int amt[13];
  memset(amt, 0, sizeof amt);
  vector<string> of[13];
  for (int i=0; i<13; ++i) {
    string pr;
    cin >> pr;
    amt[ord(pr[0])]++;
    of[ord(pr[0])].push_back(pr);
    cerr << " :: " << pr << endl;
  }

  solution sol;
  int ee[13];
  memset(ee, 0, sizeof ee);
  for (int i=0; i<13; ++i) {
    for (int j=0; j<amt[i]; ++j) {
      sol.contained.push_back({i});
    }
  }

  // two straights
  solution two_s = two_straights(amt);
  if (two_s < sol) {
    sol = two_s;
  }

  print_sol(sol, of);
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);

  int TT;
  cin >> TT;
  while (TT--) {
    solve();
  }


  return 0;
}
