// Adjacency List Graph

#define MVNum	100			// maximum number of vexs
#define MAXInt	INFINITY	// define maximum in as INFINITY
	
typedef char VerTexType;	// define the data type of vexs as char
typedef int ArcType;		// define the weight type of edges as int
typedef int OtherInfo;

// connected nodes define
typedef struct ArcNode
{
	int adjvex;					// the index of vex
	struct ArcNode * nextarc;	// the next node of current node
	OtherInfo info;				// other info wants to store in the node
}ArcNode;

// vex node define
typedef struct
{
	VerTexType	data;		// the data of the node
	ArcNode*	firstarc;	// the nodes connected by current node
}VNode, AdjList[MVNum];

typedef struct
{
	AdjList vertices; 
	int vexnum, arcnum;
}ALGraph;
