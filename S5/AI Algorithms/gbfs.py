import heapq
graph = {
	'A':['B','C'],
	'B':['D','E'],
	'C':['F'],
	'D':[],
	'E':['F'],
	'F':[]
}

hueristic ={'A':6,'B':4,'C':2,'D':7,'E':1,'F':0}

def gbfs(start,goal):
	pq = ([(hueristic[start],start,[start])])
	visited = set()
	while pq:
		h,node,path = heapq.heappop(pq)
		if node == goal:
			print("Path",path)
			return
		if node not in visited:
			visited.add(node)
			for neighbor in graph[node]:
				heapq.heappush(pq,(hueristic[neighbor],neighbor,path+[neighbor]))
gbfs('A','F')
	
