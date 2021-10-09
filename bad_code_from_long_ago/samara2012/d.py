
vector<int> primes;
def getprimes(n):
  primes = []
  bitset<10000000> notprime;
  int lim = sqrt(n);
  notprime[0] = notprime[1] = true;
  for (int i = 2; i <= lim; i++)
    if (notprime[i])
      for (int j = i*i; j <= n; j++)
        notprime[j] = true;
  for (int i = 0; i <= n; i++)
    if (!notprime[i])
      primes.push_back(i);
}

vector<int> primefactor(int n) {
  vector<int> res;
  int count;
  int lim = sqrt(n);
  for (int i = 0; primes[i] <= lim; i++) {
    if (n % primes[i] == 0) {
      count = 0;
      while (n % primes[i] == 0) {
        n /= primes[i];
        count++;
      }
      res.push_back(count);
      lim = sqrt(n);
    }
  }
  if (n > 1) {
    res.push_back(1);
  }
  return res;
}

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  vector<int> pf;
  int n;
  cin >> n;
  pf = primefactor(n);
  int sum = 0;
  for (int it: pf) 
    sum += it;
  ll ans = 1;
  for (int i = 1; i <= sum; i++) {
    ans *= i;
  }

  return 0;
}
