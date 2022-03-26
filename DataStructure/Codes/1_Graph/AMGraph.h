// the definition of Adjacency Matrix Graph

#define MVNum	100			// maximum number of vexs
#define MAXInt	INFINITY	// define maximum in as INFINITY
	
typedef char VerTexType;	// define the data type of vexs as char
typedef int ArcType;		// define the weight type of edges as int

typedef struct
{
	VerTexType	vexs[MVNum];		// vexs
	ArcType		arcs[MVNum][MVNum];	// AMGraph
	int vexnum, arcnum;		// current number of vexs and edges of graph
}AMGraph;					// Adjacency Matrix Graph
