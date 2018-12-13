library("igraph")

nodes <- read.table("/mnt/agregaty/laczenie_grafow/issues_opened_nodes.csv", header=T, sep=";", stringsAsFactors=FALSE)
links <- read.table("/mnt/agregaty/laczenie_grafow/issues_opened_edges.csv", header=T, sep=";", stringsAsFactors=FALSE)

net <- graph_from_data_frame(d=links, vertices=nodes, directed=T)

ev2 <- eigen_centrality(net, directed=F, weights=NA, scale=F)
m <- ev2$vector
x <- data.frame(id=names(m), value=m, row.names=NULL)

x$value <- 1000000*x$value
write.table(x,"evc_issues.csv", row.names=FALSE, sep=";", quote=FALSE)

#following
nodes <- read.table("/mnt/agregaty/laczenie_grafow/fol_nodes.csv", header=T, sep=";", stringsAsFactors=FALSE)
links <- read.table("/mnt/agregaty/laczenie_grafow/fol_edges.csv", header=T, sep=";", stringsAsFactors=FALSE)

net <- graph_from_data_frame(d=links, vertices=nodes, directed=T)

ev2 <- eigen_centrality(net, directed=F, weights=NA, scale=F)
m <- ev2$vector
x <- data.frame(id=names(m), value=m, row.names=NULL)

x$value <- 1000000*x$value
write.table(x,"evc_following.csv", row.names=FALSE, sep=";", quote=FALSE)

                                        #betweenness
estimate_betweenness(net, v=V(net), directed=TRUE, weights = NA, nobigint = T, -1)


