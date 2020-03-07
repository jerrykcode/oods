# SSSP 
## Single Source Shortest Path 单源最短路径

![](https://wx4.sinaimg.cn/mw690/006XXwaCgy1gclhp9f2ntj30m50tj79n.jpg)

Sssp<EdgeWeight, DistWeight>, EdgeWeight为图的边权类型, DistWeight为最短路径的权重类型, 将这两个类型分开是因为路径的权重可能比边的权重大很多, 比如边权使用unsigned char, 而路径的权重可能超过了255, 需要使用unsigned short
