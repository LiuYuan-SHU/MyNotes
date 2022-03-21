// from https://practice.geeksforgeeks.org/problems/bfs-traversal-of-graph/1/
#include <iostream>
#include <vcruntime.h>
#include <vector>
#include <stack>

using namespace std;

class Solution
{
	public:
		vector<int> dfsOfGraph(int V, vector<int> adj[]) 
		{
			vector<bool> visited(V, false);
			vector<int> result;
			stack<int> s;

			int currentNode = 0;				// record the index of current node
			visited[currentNode] = true;		// set the entrence as visited
			s.push(currentNode);				// push entrence into the stack

			while(!s.empty())
			{
				int currentNode = s.top();
				s.pop();
				visited[currentNode] = true;

				while(adj[currentNode].size() > 0 && visited[currentNode] == false)
				{
					for(int childNode = adj[currentNode].size() - 1; childNode >= 0 && !visited[currentNode]; childNode--)
					{
						s.push(childNode);
					}

					currentNode = s.top();
					if(visited[currentNode])
					{
						s.pop();
					}
					else
					{
						visited[currentNode] = true;
						result.push_back(currentNode);
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
		vector<int> ans = obj.dfsOfGraph(V, adj);
		for (size_t i = 0; i < ans.size(); i++) {
			cout << ans[i] << " ";
		}
		cout << endl;
	}
	return 0;
}
