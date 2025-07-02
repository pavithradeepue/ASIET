with open("f1.txt") as f1, open("f2.txt") as f2:
	with open("merged.txt","w") as f3:
		f3.write(f1.read() + f2.read())
