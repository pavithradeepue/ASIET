name = input("Enter file name: ")
with open(name, 'r') as f:
	text=f.read()
words=text.split()
d={}
for word in words:
	if word in d:
		d[word]=d[word]+1
	else:
		d[word]=1
max_word=max(d,key=d.get)
print("Most frequent word is: ",max_word)
print("Frequency: ",d[max_word])
