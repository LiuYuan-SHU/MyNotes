# 数据结构

> https://www.geeksforgeeks.org/

## 图

### 广度优先搜索

> 图的广度优先遍历（或搜索）类似于树的广度优先遍历。这里唯一需要注意的是，与树不同，图可能包含循环，因此我们可能再次来到同一个节点。为了避免多次处理节点，我们使用布尔数组。为简单起见，假设所有顶点都可以从起始顶点到达。