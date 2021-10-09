n = gets().to_i
for i in 1..n
  a = gets().to_i
  for j in 1..10
    break if 26**j >= a
    a -= 26**j
  end
  s = (a-1).to_s(26).rjust(j,'0').tr('0123456789abcdefghijklmnop', 'ABCDEFGHIJKLMNOPQRSTUVWXYZ')
  puts s
end
