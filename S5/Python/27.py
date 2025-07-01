def sum_digits(n):
	return 0 if n == 0 else n%10 + sum_digits(n // 10)
print(sum_digits(1234))

