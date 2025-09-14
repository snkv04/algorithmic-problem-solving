class Solution:
    def __init__(self):
        self.hashed_guesses = set()
        self.adj = []
        self.dp = []
        self.guess_counts = []

    def dfs(self, node: int, parent: int):
        # the reason why we're using a count is because we want to 
        # accumulate some count over all the subtrees
        count = 0
        for next in self.adj[node]:
            if next == parent:
                continue
            
            self.dfs(next, node)
            count += self.dp[next]
            guess = (node, next)
            if guess in self.hashed_guesses:
                count += 1
        self.dp[node] = count

    def dfs2(self, node: int, parent: int):
        self.guess_counts[node] = self.dp[node]

        for next in self.adj[node]:
            if next == parent:
                continue

            downward = (node, next)
            upward = (next, node)

            self.dp[node] -= self.dp[next]
            if downward in self.hashed_guesses:
                self.dp[node] -= 1
            self.dp[next] += self.dp[node]
            if upward in self.hashed_guesses:
                self.dp[next] += 1

            self.dfs2(next, node)

            if upward in self.hashed_guesses:
                self.dp[next] -= 1
            self.dp[next] -= self.dp[node]
            if downward in self.hashed_guesses:
                self.dp[node] += 1
            self.dp[node] += self.dp[next]

    def rootCount(self, edges: List[List[int]], guesses: List[List[int]], k: int) -> int:
        """
        - what are we trying to do?
          - we have some undirected tree, and we're given some set of
          "guesses", which are basically directed edges. we are told that
          at least some of the guesses are true. what this means is that if
          the tree is rooted at some node, then at least some of the guesses
          (directed edges) are pointing down. all we know is that >=k of the
          directed edges stated are pointing down. now, we want to find out
          how many of the nodes could possibly be the root
        - how can we go about this?
          - the brute-force way would be to go over all the subsets of guesses
          of size k (so, there would be C(n, k) ways, which is clearly too 
          many), and for each of them, find all of the root nodes which has 
          those guesses go downward and has the other ones go upward. then,
          take the union across all of those root nodes
          - the quicker way is to iterate over all root nodes, and for each,
          count how many of those guesses go downward. if it's >=k, then we're
          good.
        - why doesn't the actual set of guesses that is true for a given root
        node have to be consistent across all root nodes?
          - the question only says that we know that >=k of the guesses are
          true, not which of them are. if it was the latter, then we would have
          to fix the subset of downward edges and find the possible root nodes
          that satisfy that property. here, what we're basically saying is:
          we know that p is true, and there are several possibilities within p
          each called p_i. if we know that p is true, then that could mean that
          p_1 is true, meaning that node 1 could be the root node. if we know that
          p is true, that could instead mean that p_3 is true, meaning that node 7
          could be the root node. we're looking for each root node where some p_i
          is true, and one of the key ideas here is that the p_i for each root node
          doesn't have to be the same.
          - what would an alternative question be, to pose, that doesn't allow for
          this flexibility? this will help in comparing and contrasting. maybe
          this: "suppose we're given some guesses and we know that >=k of them
          are true. what is the maximum number of root nodes that can satisfy the
          same subset of true guesses?"
          - what are the differences between this and that? the one where the
          subset is fixed asks for maximum, while the one where the subset isn't
          fixed just asks for number of root nodes for which the number of guesses
          (assuming that node is the root node) that are true is >= k. and then
          some other differences
        - a more general property: if we only know that a loose condition is
        true, and that condition allows for many possibilities, then the long
        way of going about it is looking at all of those possibilities, and
        for each, finding out the consequences, then concluding that the possible
        consequences are the union of the consequences for each of the
        possibilities. a more concise way of saying it is that we want to
        look for the consequences where ANY of the possibilities is true
          - in the context of the problem, we are lookign for the nodes for
          which ANY subset of true guesses is greater than or equal to k in
          size. more rigorously, we simply find the set of true guesses,
          and then check to see if it's >=k in size. why does this work? because
          we don't have to check for a subset; there's already a specific fixed
          subset for any given root node. we just check it.
        - put simply: if we only know the loose condition (for which there are 
        multiple possibilities), where each possibility has some consequences,
        then the consequences that are possible for the loose condition are simply
        the union across all of the possibilities. it's a superset of if the 
        possibility (the subset) was fixed
        """

        n = len(edges) + 1
        self.adj = [[] for _ in range(n)]
        for edge in edges:
            a, b = edge
            self.adj[a].append(b)
            self.adj[b].append(a)

        for guess in guesses:
            as_tuple = tuple(guess)
            self.hashed_guesses.add(as_tuple)

        self.dp = [[0] for _ in range(n)]
        self.dfs(0, -1)

        self.guess_counts = [[0] for _ in range(n)]
        self.dfs2(0, -1)

        ans = 0
        for count in self.guess_counts:
            if count >= k:
                ans += 1
        return ans
