n = gets.to_i
a = n/2
s = [*(1+n/4..n-a+n/4)]
puts (n+1) % 4 > 1 ?  "NO" :
[
  "YES",
  a,
  ([*(1..n)] - s)*?\s,
  n - a,
  s*?\s
]
