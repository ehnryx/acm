cap = 2e12.to_i

_T = readline().to_i(10)
while _T > 0
	_T -= 1

	n = readline().to_i(10)
	arr = readline().split(' ').map{|x| x.to_i(10)}

	ans = 0
	for i in 0..n-1
		sum = 0
		lcm = 1
		for j in i..n-1
			break if lcm > cap
			lcm = lcm.lcm(arr[j])
			sum += arr[j]
			ans += 1 if sum % lcm == 0
		end
	end

	puts(ans)

end
