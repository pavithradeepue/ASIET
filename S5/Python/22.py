'''n = int(input("enter the number: "))
def factorial(n):
	r = 1
	for i in range(1,n+1):
		r*=i
	return r
print(factorial(n))'''

'''def factorial(n):
	if n == 0:
		return 1
	return n*factorial(n-1)
print(factorial(n))'''

def fibonacci(n):
	if n<= 1:
		return n
	return fibonacci(n-1) + fibonacci(n-2)
for i in range(10):
	print(fibonacci(i), end=" ")	 
