n = gets.to_i
a = gets.split.map(&:to_i)
s = 0
for i in 1...n do
  s += x = [a[i], a[i-1]].max - a[i]
  a[i] += x
end
p s
