// from https://practice.geeksforgeeks.org/problems/bfs-traversal-of-graph/1/
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution
{
	public:
		vector<int> bfsOfGraph(int V, vector<int> adj[]) 
		{
			// use a bool vector to store if the node is visited
			vector<bool> visited(V, false);
			// store the order in which each node appears
			vector<int> result;
			// store the nodes come from the same parent node
			queue<int> q;
			
			// as we defaultlt regard adj[0] is the entrence of the graph
			// the first node is visited and pushed into the queue
			visited[0] = true;
			q.push(0);

			// while the queue is not empty, which means there are nodes not visited
			while(!q.empty())
			{
				// get the first node in the queue
				int currentNode = q.front();
				q.pop();
				result.push_back(currentNode);

				// visit the child nodes of this node 
				for(int node : adj[currentNode])
				{
					// if the node is not visited, visit it and set as visited
					if(!visited[node])
					{
						visited[node] = true;
						q.push(node);
					}
				}
			}

			return result;
		}
};

int main() 
{
	int tc;			// test time count
	cin >> tc;
	while(tc--) 
	{
		int V, E;				// V for number of vertex, E for number of edge
		cin >> V >> E;
		// create a vector array
		// each vector element represents a node
		// storing the nodes connect current node
		vector<int> adj[V];
		//for each node of the graph
		for (size_t i = 0; i < E; i++) {
			int u,v;			//u for index of node, v for index of destinition of the node
			cin >> u >> v;
			adj[u].push_back(v);
		}
		Solution obj;
		vector<int> ans = obj.bfsOfGraph(V, adj);
		for (size_t i = 0; i < ans.size(); i++) {
			cout << ans[i] << " ";
		}
		cout << endl;
	}
	return 0;
}
