a = gets.split().map(&:to_i).sort()
ans = 0
for i in 0..4
  for j in 0..i-1
    for k in 0..j-1
      if a[j] + a[k] > a[i]
        ans += 1
      end
    end
  end
end
puts ans
