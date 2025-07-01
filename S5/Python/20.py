a = int(input("Enter first number: "))
b = int(input("Enter second number: "))
c = int(input("Enter third number: "))
if a >= b and a >= c:
	print("Maximum is ",a)
elif b >= a and b >= c:
	print("Maximum is ",b)
else:
	print("Maximum is ",c)
