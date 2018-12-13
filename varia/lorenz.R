m <- read.table("graph_degrees.csv", sep=";", as.is=T, header=T)

library(vcd)
gf = goodfit(m$follow_in, type="poisson", method="ML")

#summary(m)

library(ineq)

z <- subset(m, m$comments_out >0 | m$comments_in > 0)
#ineq(z$comments_out, type="Gini")
#ineq(z$comments_in, type="Gini")
#quantile(z$comments_out, c(.90, .95, .99))
#quantile(z$comments_in, c(.90, .95, .99)) 

ind <- Lc(m$comments_in)
ino <- Lc(m$comments_out)

x <- m$comments_out + m$comments_in
#quantile(x, c(.90, .95, .99)) 

pdf("LC_comments.pdf")
plot(Lc(x), xlab="Percent of population", ylab = "Percent of activity in network", main="Lorenz Curve for comments", col = "forestgreen", lwd=2, lty=1)
lines(ind, lty=5, col="forestgreen", lwd=2)
lines(ino, lty=3, col="forestgreen", lwd=2)
legend("topleft",legend=c("degree", "in-degree", "out-degree"), lty=c(1,5,3))
dev.off()

z <- subset(m, m$issues_out >0 | m$issues_in > 0)
#ineq(z$issues_out, type="Gini") 
#ineq(z$issues_in, type="Gini")
#quantile(z$issues_out, c(.90, .95, .99))
#quantile(z$issues_in, c(.90, .95, .99)) 

ind <- Lc(m$issues_in)
ino <- Lc(m$issues_out)

x <- m$issues_out + m$issues_in
#quantile(x, c(.90, .95, .99)) 
pdf("LC_issues.pdf")
plot(Lc(x), xlab="Percent of population", ylab = "Percent of activity in network", main="Lorenz Curve for issues", col = "forestgreen", lwd=2)
lines(ind, lty=5, col="forestgreen", lwd=2)
lines(ino, lty=3, col="forestgreen", lwd=2)
legend("topleft",legend=c("degree", "in-degree", "out-degree"), lty=c(1,5,3))
dev.off()

z <- subset(m, m$forking_out >0 | m$forking_in > 0)
#ineq(z$forking_out, type="Gini") 
#ineq(z$forking_in, type="Gini")
#quantile(z$forking_out, c(.90, .95, .99))
#quantile(z$forking_in, c(.90, .95, .99)) 

ind <- Lc(m$forking_in)
ino <- Lc(m$forking_out)

x <- m$forking_out + m$forking_in
#quantile(x, c(.90, .95, .99)) 
pdf("LC_forking.pdf")
plot(Lc(x), xlab="Percent of population", ylab = "Percent of activity in network", main="Lorenz Curve for forks", col = "forestgreen", lwd=2)
lines(ind, lty=5, col="forestgreen", lwd=2)
lines(ino, lty=3, col="forestgreen", lwd=2)
legend("topleft",legend=c("degree", "in-degree", "out-degree"), lty=c(1,5,3))
dev.off()

z <- subset(m, m$pulls_out >0 | m$pulls_in > 0)
#ineq(z$pulls_out, type="Gini") 
#ineq(z$pulls_in, type="Gini")
#quantile(z$pulls_out, c(.90, .95, .99))
#quantile(z$pulls_in, c(.90, .95, .99)) 

ind <- Lc(m$pulls_in)
ino <- Lc(m$pulls_out)

x <- m$pulls_out + m$pulls_in
#quantile(x, c(.90, .95, .99)) 
pdf("LC_pulls.pdf")
plot(Lc(x), xlab="Percent of population", ylab = "Percent of activity in network", main="Lorenz Curve for pull requests", col = "forestgreen", lwd=2)
lines(ind, lty=5, col="forestgreen", lwd=2)
lines(ino, lty=3, col="forestgreen", lwd=2)
legend("topleft",legend=c("degree", "in-degree", "out-degree"), lty=c(1,5,3))
dev.off()

z <- subset(m, m$starring_out >0 | m$starring_in > 0)
#ineq(z$starring_out, type="Gini") 
#ineq(z$starring_in, type="Gini")
#quantile(z$starring_out, c(.90, .95, .99))
#quantile(z$starring_in, c(.90, .95, .99)) 

ind <- Lc(m$starring_in)
ino <- Lc(m$starring_out)

x <- m$starring_out + m$starring_in
#quantile(x, c(.90, .95, .99)) 
pdf("LC_starring.pdf")
plot(Lc(x), xlab="Percent of population", ylab = "Percent of activity in network", main="Lorenz Curve for stars", col = "forestgreen", lwd=2)
lines(ind, lty=5, col="forestgreen", lwd=2)
lines(ino, lty=3, col="forestgreen", lwd=2)
legend("topleft",legend=c("degree", "in-degree", "out-degree"), lty=c(1,5,3))
dev.off()

z <- subset(m, m$follow_out >0 | m$follow_in > 0)
#ineq(z$follow_out, type="Gini") 
#ineq(z$follow_in, type="Gini")

#quantile(z$follow_out, c(.90, .95, .99))
#quantile(z$follow_in, c(.90, .95, .99)) 

ind <- Lc(m$follow_in)
ino <- Lc(m$follow_out)

x <- m$follow_out + m$follow_in
#quantile(x, c(.90, .95, .99)) 
pdf("LC_follow.pdf")
plot(Lc(x), xlab="Percent of population", ylab = "Percent of activity in network", main="Lorenz Curve for following", col = "forestgreen", lwd=2)
lines(ind, lty=5, col="forestgreen", lwd=2)
lines(ino, lty=3, col="forestgreen", lwd=2)
legend("topleft",legend=c("degree", "in-degree", "out-degree"), lty=c(1,5,3))
dev.off()


sum((m$comments_out > 0 | m$comments_in > 0) & m$issues_out == 0 &  m$issues_in == 0  & m$forking_out ==0 & m$forking_in ==0 & m$pulls_out == 0 & m$pulls_in == 0 &  m$starring_out==0 &  m$starring_in==0 & m$follow_out == 0 &  m$follow_in ==0)

sum((m$issues_out > 0 |m$issues_in > 0) & m$comments_out == 0 & m$comments_in == 0  & m$forking_out ==0 & m$forking_in ==0 & m$pulls_out == 0 & m$pulls_in == 0 &  m$starring_out==0 &  m$starring_in==0 & m$follow_out == 0 &  m$follow_in ==0)

sum((m$forking_out> 0 | m$forking_in > 0) & m$comments_out == 0 & m$comments_in == 0  & m$issues_out ==0 & m$issues_in ==0 & m$pulls_out == 0 & m$pulls_in == 0 &  m$starring_out==0 &  m$starring_in==0 & m$follow_out == 0 &  m$follow_in ==0)

sum((m$forking_out> 0 | m$forking_in > 0) & m$comments_out == 0 & m$comments_in == 0  & m$issues_out ==0 & m$issues_in ==0 & m$pulls_out == 0 & m$pulls_in == 0 &  m$starring_out==0 &  m$starring_in==0 & m$follow_out == 0 &  m$follow_in ==0)

sum((m$pulls_out> 0 | m$pulls_in > 0) & m$comments_out == 0 & m$comments_in == 0  & m$issues_out ==0 & m$issues_in ==0 &  m$forking_out == 0 & m$forking_in == 0 &  m$starring_out==0 &  m$starring_in==0 & m$follow_out == 0 &  m$follow_in ==0)

sum((m$starring_out> 0 | m$starring_in > 0) & m$comments_out == 0 & m$comments_in == 0  & m$issues_out ==0 & m$issues_in ==0 &  m$forking_out == 0 & m$forking_in == 0 &  m$pulls_out==0 &  m$pulls_in==0 & m$follow_out == 0 &  m$follow_in ==0)

sum((m$follow_out> 0 | m$follow_in > 0) & m$comments_out == 0 & m$comments_in == 0  & m$issues_out ==0 & m$issues_in ==0 &  m$forking_out == 0 & m$forking_in == 0 &  m$pulls_out==0 &  m$pulls_in==0 & m$starring_out == 0 &  m$starring_in ==0)


library(igraph)

nodes <- read.table("comments_nodes.csv", as.is=T)
links <- read.table("comments_un.csv", as.is=T, sep=";")
net <- graph_from_data_frame(d=links, vertices=nodes, directed=T)

diameter(net)

transitivity(net, type="undirected")
assortativity_degree(net, directed=T)


nodes <- read.table("fork_nodes.csv", as.is=T)
links <- read.table("forking_un.csv", as.is=T, sep=";")
net <- graph_from_data_frame(d=links, vertices=nodes, directed=T)

transitivity(net, type="undirected")
assortativity_degree(net, directed=T)

nodes <- read.table("pulls_nodes.csv", as.is=T)
links <- read.table("pulls_un.csv", as.is=T, sep=";")
net <- graph_from_data_frame(d=links, vertices=nodes, directed=T)

mean_distance(net, directed = T)

#transitivity(net, type="undirected")
#assortativity_degree(net, directed=T)

nodes <- read.table("issues_nodes.csv", as.is=T)
links <- read.table("issues_un.csv", as.is=T, sep=";")
net <- graph_from_data_frame(d=links, vertices=nodes, directed=T)

mean_distance(net, directed = T)

#transitivity(net, type="undirected")
#assortativity_degree(net, directed=T)

nodes <- read.table("star_nodes.csv", as.is=T)
links <- read.table("starring_un.csv", as.is=T, sep=";")
net <- graph_from_data_frame(d=links, vertices=nodes, directed=T)

rm(nodes, links)

net <- simplify(net)

d <- degree(net)
fit <- fit_power_law(d)


transitivity(net, type="undirected")
assortativity_degree(net, directed=T)

nodes <- read.table("follow_nodes.csv", as.is=T)
links <- read.table("follow_un.csv", as.is=T, sep=";")
net <- graph_from_data_frame(d=links, vertices=nodes, directed=T)

transitivity(net, type="undirected")
assortativity_degree(net, directed=T)

plot(men, xlab="Percent of occupations", ylab="Percent of accidents", main="Lorenz Curve -- overal accidents", lty=1)
lines(ov, lty=5)
lines(fem, lty=3)
legend("topleft",legend=c("men", "women", "overal"), lty=c(1,3,5))
                                        # spearmany vs pearsony
links <- read.table("comments_un.csv", as.is=T, sep=";")
edges <- merge(links, m, by.x="V1", by.y="id", all.x=T)
edges <- edges[,1:4]
edges1 <- merge(edges, m, by.x = "V2", by.y="id", all.x=T)
edges <- edges1[,1:6]

edges$source_deg <- edges$comments_out.x+edges$comments_in.x
edges$target_deg <- edges$comments_out.y+edges$comments_in.y

edges <- subset(edges, edges$V1 != edges$V2)

cor(log(edges$source_deg), log(edges$target_deg))
cor(log(edges$source_deg), log(edges$target_deg), method="spearman")

cor(log(edges$comments_in.x+1), log(edges$comments_in.y),)
cor(log(edges$comments_in.x+1), log(edges$comments_in.y), method="spearman")

cor(log(edges$comments_out.x), log(edges$comments_out.y+1))
cor(log(edges$comments_out.x), log(edges$comments_out.y+1), method="spearman")

links <- read.table("follow_un.csv", as.is=T, sep=";")
edges <- merge(links, m, by.x="V1", by.y="id", all.x=T)
edges <- edges[,c(1,2,13,14)]
edges1 <- merge(edges, m, by.x = "V2", by.y="id", all.x=T)
edges <- edges1[,c(1,2,3,4,15,16)]

edges <- subset(edges, edges$V1 != edges$V2)

edges$source_deg <- edges$follow_out.x+edges$follow_in.x
edges$target_deg <- edges$follow_out.y+edges$follow_in.y

cor(log(edges$source_deg), log(edges$target_deg))
cor(log(edges$source_deg), log(edges$target_deg), method="spearman")

cor(log(edges$follow_in.x+1), log(edges$follow_in.y),)
cor(log(edges$follow_in.x+1), log(edges$follow_in.y), method="spearman")

cor(log(edges$follow_out.x), log(edges$follow_out.y+1))
cor(log(edges$follow_out.x), log(edges$follow_out.y+1), method="spearman")

links <- read.table("forking_un.csv", as.is=T, sep=";")
edges <- merge(links, m, by.x="V1", by.y="id", all.x=T)
edges <- edges[,c(1,2,7,8)]
edges1 <- merge(edges, m, by.x = "V2", by.y="id", all.x=T)
edges <- edges1[,c(1,2,3,4,9,10)]

edges <- subset(edges, edges$V1 != edges$V2)

edges$source_deg <- edges$forking_out.x+edges$forking_in.x
edges$target_deg <- edges$forking_out.y+edges$forking_in.y

cor(log(edges$source_deg), log(edges$target_deg))
cor(log(edges$source_deg), log(edges$target_deg), method="spearman")

cor(log(edges$forking_in.x+1), log(edges$forking_in.y),)
cor(log(edges$forking_in.x+1), log(edges$forking_in.y), method="spearman")

cor(log(edges$forking_out.x), log(edges$forking_out.y+1))
cor(log(edges$forking_out.x), log(edges$forking_out.y+1), method="spearman")

links <- read.table("pulls_un.csv", as.is=T, sep=";")
edges <- merge(links, m, by.x="V1", by.y="id", all.x=T)
edges <- edges[,c(1,2,9,10)]
edges1 <- merge(edges, m, by.x = "V2", by.y="id", all.x=T)
edges <- edges1[,c(1,2,3,4,11,12)]

edges <- subset(edges, edges$V1 != edges$V2)

edges$source_deg <- edges$pulls_out.x+edges$pulls_in.x
edges$target_deg <- edges$pulls_out.y+edges$pulls_in.y

cor(log(edges$source_deg), log(edges$target_deg))
cor(log(edges$source_deg), log(edges$target_deg), method="spearman")

cor(log(edges$pulls_in.x+1), log(edges$pulls_in.y),)
cor(log(edges$pulls_in.x+1), log(edges$pulls_in.y), method="spearman")

cor(log(edges$pulls_out.x), log(edges$pulls_out.y+1))
cor(log(edges$pulls_out.x), log(edges$pulls_out.y+1), method="spearman")

links <- read.table("issues_un.csv", as.is=T, sep=";")
edges <- merge(links, m, by.x="V1", by.y="id", all.x=T)
edges <- edges[,c(1,2,5,6)]
edges1 <- merge(edges, m, by.x = "V2", by.y="id", all.x=T)
edges <- edges1[,c(1,2,3,4,7,8)]

edges <- subset(edges, edges$V1 != edges$V2)

edges$source_deg <- edges$issues_out.x+edges$issues_in.x
edges$target_deg <- edges$issues_out.y+edges$issues_in.y

cor(log(edges$source_deg), log(edges$target_deg))
cor(log(edges$source_deg), log(edges$target_deg), method="spearman")

cor(log(edges$issues_in.x+1), log(edges$issues_in.y),)
cor(log(edges$issues_in.x+1), log(edges$issues_in.y), method="spearman")

cor(log(edges$issues_out.x), log(edges$issues_out.y+1))
cor(log(edges$issues_out.x), log(edges$issues_out.y+1), method="spearman")

links <- read.table("starring_un.csv", as.is=T, sep=";")
edges <- merge(links, m, by.x="V1", by.y="id", all.x=T)
edges <- edges[,c(1,2,5,6)]
edges1 <- merge(edges, m, by.x = "V2", by.y="id", all.x=T)
edges <- edges1[,c(1,2,3,4,7,8)]

edges <- subset(edges, edges$V1 != edges$V2)

edges$source_deg <- edges$starring_out.x+edges$starring_in.x
edges$target_deg <- edges$starring_out.y+edges$starring_in.y

cor(log(edges$source_deg), log(edges$target_deg))
cor(log(edges$source_deg), log(edges$target_deg), method="spearman")

cor(log(edges$starring_in.x+1), log(edges$starring_in.y),)
cor(log(edges$starring_in.x+1), log(edges$starring_in.y), method="spearman")

cor(log(edges$starring_out.x), log(edges$starring_out.y+1))
cor(log(edges$starring_out.x), log(edges$starring_out.y+1), method="spearman")

