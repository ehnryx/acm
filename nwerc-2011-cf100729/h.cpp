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
  int cost() const {
    return contained.size();
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

int of_sz[14];

int check(int amt[13]) {
  for (int i=0; i<14; ++i) {
    of_sz[i] = 0;
  }
  for (int i=0; i<13; ++i) {
    if (amt[i] < 0) return 100;
    ++of_sz[amt[i]];
  }

  int ans = 0;
  int x = min(of_sz[2], of_sz[3]);
  ans += x;
  of_sz[2] -= x;
  of_sz[3] -= x;
  int y = min(of_sz[3]/2, of_sz[4]);
  ans += y*2;
  of_sz[3] -= y*2;
  of_sz[4] -= y;

  ans += of_sz[1] + of_sz[2] + of_sz[3] + of_sz[4];

  return ans;
}

void build(int amt[13], solution& sol) {
  vector<int> have[14];
  for (int i=0; i<13; ++i) {
    assert(amt[i] >= 0);
    have[amt[i]].push_back(i);
  }

  int x = min(have[2].size(), have[3].size());
  for (int i=0; i<x; ++i) {
    vector<int> p;
    for (int j=0; j<3; ++j) {
      p.push_back(have[3].back());
    }
    for (int j=0; j<2; ++j) {
      p.push_back(have[2].back());
    }
    have[2].pop_back();
    have[3].pop_back();
    sol.contained.push_back(p);
  }

  int y = min(have[3].size()/2, have[4].size());
  for (int i=0; i<y; ++i) {
    vector<int> p;
    for (int j=0; j<3; ++j) {
      p.push_back(have[3].back());
    }
    for (int j=0; j<2; ++j) {
      p.push_back(have[4].back());
    }
    have[3].pop_back();
    sol.contained.push_back(p);

    p.clear();
    for (int j=0; j<3; ++j) {
      p.push_back(have[3].back());
    }
    for (int j=0; j<2; ++j) {
      p.push_back(have[4].back());
    }
    have[3].pop_back();
    have[4].pop_back();
    sol.contained.push_back(p);
  }

  for (int i=1; i<=4; ++i) {
    while (!have[i].empty()) {
      vector<int> p;
      for (int j=0; j<i; ++j) {
        p.push_back(have[i].back());
      }
      have[i].pop_back();
      sol.contained.push_back(p);
    }
  }
}

struct option {
  int amt[13];
  int cost;
  option() {}
  option(int a[13], int c) {
    cost = c;
    for (int i=0; i<13; ++i) {
      amt[i] = a[i];
    }
  }
};

void solve() {
  int amt[13];
  memset(amt, 0, sizeof amt);
  vector<string> of[13];
  for (int i=0; i<13; ++i) {
    string pr;
    cin >> pr;
    amt[ord(pr[0])]++;
    of[ord(pr[0])].push_back(pr);
    ////cerr << " :: " << pr << endl;
  }

  solution best;
  build(amt, best);

  for (int a=0; a<13; ++a) {
    for (int b=a+5; b<=13; ++b) {
      for (int z=a; z<b; ++z) {
        --amt[z];
      }

      {
        int ch = check(amt);
        if (a == 0 && b == 13) {
          //cerr << "CH =  " << ch << endl;
          //for (int q=0;q<13;++q) {
            //cerr << "   AMT" << q << " " << amt[q] << endl;
          //}
        }
        if (ch+1 < best.cost()) {
          solution nsol;
          vector<int> p;
          for (int z=a; z<b; ++z) {
            p.push_back(z);
          }
          nsol.contained.push_back(p);
          build(amt, nsol);
          best = nsol;
        }
      }

      for (int c=a; c<13; ++c) {
        for (int d=c+5; d<=13; ++d) {
          for (int z=c; z<d; ++z) {
            --amt[z];
          }

          int ch = check(amt);
          if (ch+2 < best.cost()) {
            solution nsol;
            vector<int> p;
            for (int z=a; z<b; ++z) {
              p.push_back(z);
            }
            nsol.contained.push_back(p);
            p.clear();
            for (int z=c; z<d; ++z) {
              p.push_back(z);
            }
            nsol.contained.push_back(p);

            build(amt, nsol);

            best = nsol;
          }

          for (int z=c; z<d; ++z) {
            ++amt[z];
          }
        }
      }

      for (int z=a; z<b; ++z) {
        ++amt[z];
      }

    }
  }

  print_sol(best, of);

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
