try:
	with open("nofile.txt") as f:
		print(f.read())
except FileNotFoundError:
	print("File not Found")
