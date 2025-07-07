a = float(input("Enter first number: "))
op = input("Enter operator(+,-,*,/): ")
b = float(input("Enter second number: "))

if op == '+':
         print("SUM is: ",a+b)
elif op == '-':
         print("Diff is: ",a-b)
elif op == '*':
         print("Product is: ",a*b)
elif op == '/':
         if b != 0:
                  print("Result: ",a/b)
         else:
                  print("Cannot divide by zero")
else:
         print("Invalid operator")
