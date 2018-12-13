m <- read.table("follow_richclub.csv", sep=";", header=T, as.is=T)

pdf("richclub_fol.pdf")
plot(log(m$k[m$richclub>0]), m$richclub[m$richclub>0], ylab = "richclub coefficient", ylim= c(0.2,1.2), xlab = "log(k)", main = "Following", col="forestgreen", pch = 20)
abline(h=1, col="red")

dev.off()

x <- read.table("fol_in_richclub.csv", sep=";", header=T, as.is=T)
y <- read.table("fol_out_richclub.csv", sep=";", header=T, as.is=T)

pdf("richclub_fol_inouts.pdf")
plot(log(x$k[x$richclub>0]), x$richclub[x$richclub>0], ylab = "richclub coefficient", ylim= c(0.2,1.6), xlab = "log(k)", xlim=c(0,12), main = "Following", col="darkgreen", pch = 20)
points(log(y$k[y$richclub>0]), y$richclub[y$richclub>0], col="limegreen", pch = 20)
abline(h=1, col="red")
legend("topright",legend=c("in-degree", "out-degree"), fill=c("darkgreen", "limegreen"))
dev.off()

m <- read.table("star_richclub.csv", sep=";", header=T, as.is=T)

pdf("richclub_star.pdf")
plot(log(m$k[m$richclub>0]), m$richclub[m$richclub>0], ylab = "richclub coefficient", ylim= c(0.7,1.1), xlab = "log(k)", xlim= c(0,12), main = "Starring", col="forestgreen", pch = 20)
abline(h=1, col="red")
dev.off()

x <- read.table("star_in_richclubs.csv", sep=";", header=T, as.is=T)
y <- read.table("star_out_richclubs.csv", sep=";", header=T, as.is=T)

pdf("richclub_star_inouts.pdf")
plot(log(x$k[x$richclub>0]), x$richclub[x$richclub>0], ylab = "richclub coefficient", ylim= c(0.2,1.5), xlab = "log(k)", xlim= c(0,12), main = "Starring", col="darkgreen", pch = 20)
points(log(y$k[y$richclub>0]), y$richclub[y$richclub>0], col="limegreen", pch = 20)
abline(h=1, col="red")
legend("topright",legend=c("in-degree", "out-degree"), fill=c("darkgreen", "limegreen"))
dev.off()

m <- read.table("comments_richclub.csv", sep=";", header=T, as.is=T)

pdf("richclub_com.pdf")
plot(log(m$k[m$richclub>0]), m$richclub[m$richclub>0], ylab = "richclub coefficient", ylim= c(0.7,1.1), xlab = "log(k)", xlim = c(0,10), main = "Comments", col="forestgreen", pch = 20)
abline(h=1, col="red")
dev.off()

x <- read.table("com_in_richclubs.csv", sep=";", header=T, as.is=T)
y <- read.table("com_out_richclubs.csv", sep=";", header=T, as.is=T)

pdf("richclub_com_inouts.pdf")
plot(log(y$k[y$richclub>0]), y$richclub[y$richclub>0], ylab = "richclub coefficient", ylim= c(0.2,2.5), xlab = "log(k)", xlim= c(0,10), main = "Comments", col="limegreen", pch = 20)
points(log(x$k[x$richclub>0]), x$richclub[x$richclub>0], col="darkgreen", pch = 20)
abline(h=1, col="red")
legend("topright",legend=c("in-degree", "out-degree"), fill=c("darkgreen", "limegreen"))
dev.off()

m <- read.table("pull_richclub.csv", sep=";", header=T, as.is=T)

pdf("richclub_pull.pdf")
plot(log(m$k[m$richclub>0]), m$richclub[m$richclub>0], ylab = "richclub coefficient", ylim = c(0.6,1.2), xlab = "log(k)", xlim= c(0,10), main = "Pull requests", col="forestgreen", pch = 20)
abline(h=1, col="red")
dev.off()

x <- read.table("pull_in_richclubs.csv", sep=";", header=T, as.is=T)
y <- read.table("pull_out_richclubs.csv", sep=";", header=T, as.is=T)

pdf("richclub_pull_inouts.pdf")
plot(log(y$k[y$richclub>0]), y$richclub[y$richclub>0], ylab = "richclub coefficient", ylim= c(0.2,2.5), xlab = "log(k)", xlim= c(0,10), main = "Pull requests", col="limegreen", pch = 20)
points(log(x$k[x$richclub>0]), x$richclub[x$richclub>0], col="darkgreen", pch = 20)
abline(h=1, col="red")
legend("topright",legend=c("in-degree", "out-degree"), fill=c("darkgreen", "limegreen"))
dev.off()

m <- read.table("issues_richclub.csv", sep=";", header=T, as.is=T)

pdf("richclub_is.pdf")
plot(log(m$k[m$richclub>0]), m$richclub[m$richclub>0], ylab = "richclub coefficient", ylim = c(0.4,1.1), xlab = "log(k)", main = "Issues", col="forestgreen", pch = 20)
abline(h=1, col="red")
dev.off()

x <- read.table("iss_in_richclubs.csv", sep=";", header=T, as.is=T)
y <- read.table("iss_out_richclubs.csv", sep=";", header=T, as.is=T)

pdf("richclub_iss_inouts.pdf")
plot(log(y$k[y$richclub>0]), y$richclub[y$richclub>0], ylab = "richclub coefficient", ylim= c(0.2,2.5), xlab = "log(k)", xlim= c(0,10), main = "Issues", col="limegreen", pch = 20)
points(log(x$k[x$richclub>0]), x$richclub[x$richclub>0], col="darkgreen", pch = 20)
abline(h=1, col="red")
legend("topright",legend=c("in-degree", "out-degree"), fill=c("darkgreen", "limegreen"))
dev.off()

m <- read.table("fork_richclub.csv", sep=";", header=T, as.is=T)

pdf("richclub_fork.pdf")
plot(log(m$k[m$richclub>0]), m$richclub[m$richclub>0], ylab = "richclub coefficient", ylim = c(0.5,1.1), xlim= c(0,12), xlab = "log(k)", main = "Forks", col="forestgreen", pch = 20)
abline(h=1, col="red")
dev.off()

x <- read.table("fork_in_richclubs.csv", sep=";", header=T, as.is=T)
y <- read.table("fork_out_richclubs.csv", sep=";", header=T, as.is=T)

pdf("richclub_fork_inouts.pdf")
plot(log(y$k[y$richclub>0]), y$richclub[y$richclub>0], ylab = "richclub coefficient", ylim= c(0.4,2.2), xlab = "log(k)", xlim= c(0,12), main = "Forks", col="limegreen", pch = 20)
points(log(x$k[x$richclub>0]), x$richclub[x$richclub>0], col="darkgreen", pch = 20)
abline(h=1, col="red")
legend("topright",legend=c("in-degree", "out-degree"), fill=c("darkgreen", "limegreen"))
dev.off()


plot(f$k[f$richclub>0], f$richclub[f$richclub>0], ylab = "rich-club coefficient", ylim = c(0.1,1.2), xlim= c(0,5000), xlab = "log(k)", main = "Rich-clubs for 5000 first degrees", col="forestgreen", pch = 20)
points(m$k[m$richclub>0], m$richclub[m$richclub>0], ylim = c(0.1,1.2), xlim= c(0,5000), col="orange", pch = 20)
points(s$k[s$richclub>0], s$richclub[s$richclub>0], ylim = c(0.1,1.2), xlim= c(0,5000), col="blue", pch = 20)
points(p$k[p$richclub>0], p$richclub[p$richclub>0], ylim = c(0.1,1.2), xlim= c(0,5000), col="magenta", pch = 20)
points(i$k[i$richclub>0], i$richclub[i$richclub>0], ylim = c(0.1,1.2), xlim= c(0,5000), col="yellow", pch = 20)
points(c$k[c$richclub>0], c$richclub[c$richclub>0], ylim = c(0.1,1.2), xlim= c(0,5000), col="black", pch = 20)
abline(h=1, col="red")

plot(f$k[f$richclub>0], f$richclub[f$richclub>0], ylab = "rich-club coefficient", ylim = c(0.1,1.2), xlim= c(0,200), xlab = "log(k)", main = "Rich-clubs for 1000 first degrees", col="forestgreen", pch = 20)
points(m$k[m$richclub>0], m$richclub[m$richclub>0], ylim = c(0.1,1.2), xlim= c(0,200), col="orange", pch = 20)
points(s$k[s$richclub>0], s$richclub[s$richclub>0], ylim = c(0.1,1.2), xlim= c(0,200), col="blue", pch = 20)
points(p$k[p$richclub>0], p$richclub[p$richclub>0], ylim = c(0.1,1.2), xlim= c(0,200), col="magenta", pch = 20)
points(i$k[i$richclub>0], i$richclub[i$richclub>0], ylim = c(0.1,1.2), xlim= c(0,200), col="yellow", pch = 20)
points(c$k[c$richclub>0], c$richclub[c$richclub>0], ylim = c(0.1,1.2), xlim= c(0,200), col="black", pch = 20)
abline(h=1, col="red")
