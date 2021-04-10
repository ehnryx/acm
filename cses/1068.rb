n = gets.to_i
(
  print n,?\s
  n = n%2 > 0 ? 3*n+1 : n/2
) while n > 1
p 1
