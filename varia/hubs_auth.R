m <- read.table("graph_degrees.csv", sep=";", as.is=T, header=T)

library(igraph)
options(scipen = 999)


# comments

nodes <- read.table("comments_nodes.csv", as.is=T)
links <- read.table("comments_un.csv", as.is=T, sep=";")
net <- graph_from_data_frame(d=links, vertices=nodes, directed=T)

net <- simplify(net)
com_hubs <- hub_score(net)$vector

x <- data.frame(id=names(com_hubs), value=com_hubs, row.names=NULL)

x$value <- 10000000*x$value

quantile(x$value, c(.9, .95, .99))

x$value <- trunc(x$value)


com_auth <- authority_score(net)$vector
y <- data.frame(id=names(com_auth), value=com_auth, row.names=NULL)

y$value <- 10000000*y$value

quantile(y$value, c(.9, .95, .99))

y$value <- trunc(y$value)

write.table(x,"scores/hub_com.csv", row.names=FALSE, sep=";", quote=FALSE)
write.table(y,"scores/auth_com.csv", row.names=FALSE, sep=";", quote=FALSE)

# forking

nodes <- read.table("../fork_nodes.csv", as.is=T)
links <- read.table("../fork_un.csv", as.is=T, sep=";")
net <- graph_from_data_frame(d=links, vertices=nodes, directed=T)

rm(links, nodes)
net <- simplify(net)

hubs <- hub_score(net)$vector

x <- data.frame(id=names(hubs), value=hubs, row.names=NULL)

x$value <- 100000*x$value

quantile(x$value, c(.9, .95, .99))

auth <- authority_score(net)$vector
y <- data.frame(id=names(auth), value=auth, row.names=NULL)

y$value <- 1000000000*y$value

quantile(y$value, c(.9, .95, .99))

write.table(x,"hub_fork.csv", row.names=FALSE, sep=";", quote=FALSE)
write.table(y,"auth_fork.csv", row.names=FALSE, sep=";", quote=FALSE)


# pulls

nodes <- read.table("pulls_nodes.csv", as.is=T)
links <- read.table("pulls_un.csv", as.is=T, sep=";")
net <- graph_from_data_frame(d=links, vertices=nodes, directed=T)

rm(links, nodes)
net <- simplify(net)

hubs <- hub_score(net)$vector

x <- data.frame(id=names(hubs), value=hubs, row.names=NULL)

x$value <- 1000000*x$value

quantile(x$value, c(.9, .95, .99))

auth <- authority_score(net)$vector
y <- data.frame(id=names(auth), value=auth, row.names=NULL)

y$value <- 1000000*y$value

quantile(y$value, c(.9, .95, .99))

write.table(x,"hub_pull.csv", row.names=FALSE, sep=";", quote=FALSE)
write.table(y,"auth_pull.csv", row.names=FALSE, sep=";", quote=FALSE)


# issues

nodes <- read.table("issues_nodes.csv", as.is=T)
links <- read.table("issues_un.csv", as.is=T, sep=";")
net <- graph_from_data_frame(d=links, vertices=nodes, directed=T)

rm(links, nodes)
net <- simplify(net)
hubs <- hub_score(net)$vector

x <- data.frame(id=names(hubs), value=hubs, row.names=NULL)

x$value <- 10000000*x$value

quantile(x$value, c(.9, .95, .99))

auth <- authority_score(net)$vector
y <- data.frame(id=names(auth), value=auth, row.names=NULL)

y$value <- 10000000*y$value

quantile(y$value, c(.9, .95, .99))

write.table(x,"hub_is.csv", row.names=FALSE, sep=";", quote=FALSE)
write.table(y,"auth_is.csv", row.names=FALSE, sep=";", quote=FALSE)

# starring

nodes <- read.table("star_nodes.csv", as.is=T)
links <- read.table("starring_un.csv", as.is=T, sep=";")
net <- graph_from_data_frame(d=links, vertices=nodes, directed=T)

rm(nodes, links)

net <- simplify(net)

hubs <- hub_score(net)$vector

x <- data.frame(id=names(hubs), value=hubs, row.names=NULL)

x$value <- 1000000*x$value

quantile(x$value, c(.9, .95, .99))

auth <- authority_score(net)$vector
y <- data.frame(id=names(auth), value=auth, row.names=NULL)

y$value <- 1000000*y$value

quantile(y$value, c(.9, .95, .99))

write.table(x,"hub_star.csv", row.names=FALSE, sep=";", quote=FALSE)
write.table(y,"auth_star.csv", row.names=FALSE, sep=";", quote=FALSE)


#following

nodes <- read.table("follow_nodes.csv", as.is=T)
links <- read.table("follow_un.csv", as.is=T, sep=";")
net <- graph_from_data_frame(d=links, vertices=nodes, directed=T)

rm(links, nodes)
net <- simplify(net)

hubs <- hub_score(net)$vector

x <- data.frame(id=names(hubs), value=hubs, row.names=NULL)

x$value <- 1000000*x$value

quantile(x$value, c(.9, .95, .99))

auth <- authority_score(net)$vector
y <- data.frame(id=names(auth), value=auth, row.names=NULL)

y$value <- 1000000*y$value

quantile(y$value, c(.9, .95, .99))

write.table(x,"hub_fol.csv", row.names=FALSE, sep=";", quote=FALSE)
write.table(y,"auth_fol.csv", row.names=FALSE, sep=";", quote=FALSE)

# wizualizacja?

nodes <- read.table("1_pull_auth_nodes.csv", as.is=T, sep=";")
links <- read.table("1_pull_auth_edges.csv", as.is=T, sep=";")
net <- graph_from_data_frame(d=links, vertices=nodes, directed=T)
