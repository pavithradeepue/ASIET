s = input("Enter the sentence: ")
words = s.split()
occurence={}
for word in words:
	if word in occurence:
		occurence[word]+=1
	else:
		occurence[word]=1
print("Word Occurence\n")
for word,count in occurence.items():
	print(word,":",count)
