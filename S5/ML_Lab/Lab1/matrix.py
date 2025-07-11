r1=int(input("Enter the number of rows in 1st Matrix: "))
c1=int(input("Enter the number of columns in 1st Matrix: "))
r2=int(input("Enter the number of rows in 2nd Matrix: "))
c2=int(input("Enter the number of columns in 2nd Matrix: "))
if c1!=r2:
	print("Invalid, cannot multiply.")
else:
	print("Matrix A")
	A=[]
	for i in range(r1):
		row=list(map(int,input().split()))
		A.append(row)
	print("Matrix B")
	B=[]
	for i in range(r2):
		row=list(map(int,input().split()))
		B.append(row)
	result=[]
	for i in range(r1):
		row=[]
		for j in range(c2):
			s=0
			for k in range(c1):
				s=s+A[i][k]*B[k][j]
			row.append(s)
		result.append(row)
	print("RESULT: ")
	for row in result:
		print(*row)
