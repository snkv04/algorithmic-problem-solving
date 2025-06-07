#!/usr/bin/env python3
# Author: Sri Vangaru

import sys, resource

# resource.setrlimit(resource.RLIMIT_STACK, (-1, -1))
sys.setrecursionlimit(1000000)

# utility function for Kosaraju's algorithm
def dfs(node):
    visited[node] = True
    for next in graph[node]:
        if not visited[next]:
            dfs(next)
    reverse_topological.append(node)

# utility function for Kosaraju's algorithm
def dfs2(node, start):
    visited[node] = True
    scc[node] = start
    for next in transpose_graph[node]:
        if not visited[next]:
            dfs2(next, start)

# utility function for finding the reverse topological sorting of the
# condensed graph's nodes
def dfs3(condensed_node):
    visited[condensed_node] = True
    for next in condensed_graph[condensed_node]:
        if not visited[next]:
            dfs3(next)
    reverse_topological.append(condensed_node)

# sets up directed graph and transpose graph, and takes input
n, m = map(int, input().split())
graph = []
for i in range(n): graph.append([])
transpose_graph = []
for i in range(n): transpose_graph.append([])
for i in range(m):
    a, b = map(int, input().split())
    a -= 1
    b -= 1
    graph[a].append(b)
    transpose_graph[b].append(a)

# uses Kosaraju's algorithm to map each node to its strongly connected
# component (SCC), where each SCC is denoted by a representative node
visited = [False] * n
reverse_topological = []
for i in range(n):
    if not visited[i]: dfs(i)
visited = [False] * n
scc = [0] * n
for node in reversed(reverse_topological):
    if not visited[node]: dfs2(node, node)

# condenses the graph so that each SCC is treated as a singular node--keeping
# track of the original nodes within each SCC--resulting in a directed acylic
# graph (DAG)
condensed_graph = []
for i in range(n): condensed_graph.append([])
nodes_in_scc = []
for i in range(n): nodes_in_scc.append([])
for i in range(n):
    for adjacent in graph[i]:
        if scc[i] != scc[adjacent]:
            condensed_graph[scc[i]].append(scc[adjacent])
    nodes_in_scc[scc[i]].append(i)

# finds the reverse topological ordering (or normal DFS postorder ordering) of
# the nodes in the condensed graph
visited = [False] * n
reverse_topological.clear()
for i in range(n):
    if not visited[i] and i == scc[i]: dfs3(i)

# uses dynamic programming to find the longest path in the condensed graph,
# where the length of a path is defined by the number of bases (nodes from the
# original graph) covered in the path; this approach is allowed because the
# drone is allowed to visit the same base multiple times in its "path", so it
# can go around and around in circles within an SCC in order to land at the
# correct node in the SCC that has an outgoing edge to a different SCC, and
# similarly, any node within the start SCC is a valid start node, so we simply
# arbitrarily choose the SCC's representative node
memo = [0] * n
next = [-1] * n
for node in reverse_topological:
    max = 0
    for adjacent in condensed_graph[node]:
        if memo[adjacent] > max:
            max = memo[adjacent]
            next[node] = adjacent
    memo[node] = len(nodes_in_scc[node]) + max

# finds the node in the condensed graph that is the start of the longest path
max = -1
start = -1
for node in reverse_topological:
    if memo[node] > max:
        max = memo[node]
        start = node

# retrieves all of the nodes reachable within the longest path defined by the
# DP earlier
on_path = []
current_node = start
while True:
    for original_node in nodes_in_scc[current_node]:
        on_path.append(original_node)

    if next[current_node] == -1: break
    else: current_node = next[current_node]

# outputs the results
print(max)
for node in on_path: print(f"{node+1} ", end="")
print(f"\n{start+1}")
