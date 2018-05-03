arithmetic exercise 算法实验：

- 生成100个点，500条边的有向无环图，任选一点为源点，计算s到其它点的距离。（用邻接链表存储）
- 将上述有向图变成dag图，从中去掉一些边，不允许使用递归
- 计算上述dag图中最长路径（记录路径）
- 求得图中所有的强连通分支

需要考虑： 1.有没有孤立点

2.有向图有没有两点之间多条边

3.随机怎么生成

4.注意生成DAG图中的细节
