graph = {
	'A':['B','C'],
	'B':['D','E'],
	'C':['E'],
	'D':[],
	'E':['F'],
	'F':[]
}

visited = set()

def dfs(node):
	if node not in visited:
		visited.add(node)
		print(node,end=" ")
	for neighbor in graph[node]:
		dfs(neighbor)
dfs('A')


