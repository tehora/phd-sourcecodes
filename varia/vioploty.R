m <- read.table("details2.txt", sep=";", header=F, as.is=T)

graphs <- c("following ", "star      ", "forking   ", "issues    ", "pull      ", "comments  ")

library("vioplot")
par(mfrow=c(6,4))
par(mar=c(1,1,1,1))

#names <- c("sphere", "elli", "torus",  "minimal", "zebra", "kq", "quoth",  "hex", "euc", "eucl", "stdhr", "stdhr2")
names <- c("sphere", "elli", "torus",  "minimal", "zebra", "kq", "quoth", "euc", "stdhr")

pdf("diagnostyka.pdf", width=32, height=18)
par(mfrow=c(6,4))
par(mar=c(1,1,1,1), oma = c(0,0,0,0)))

#text("Link based on distance", cex=0.25)
#text("Link based on grouping (neurons)", cex=0.25)
#text("AIC neurons")
#text("BIC neurons")

for (graph in graphs) {
    sphere <- subset(m, V1=="sphere " & V2==graph)
    hex <- subset(m, V1=="hex    " & V2==graph)
    torus <- subset(m, V1=="torus  " & V2==graph)
    bottle <- subset(m, V1=="bottle " & V2==graph)
    stdhr <- subset(m, V1=="stdhr  " & V2==graph)
    kq <- subset(m, V1=="kq     " & V2==graph)
    mcb <- subset(m, V1=="mcb    " & V2==graph)
    elli <- subset(m, V1=="elli   " & V2==graph)
    zebra <- subset(m, V1=="zebra  " & V2==graph)
    quoth <- subset(m, V1=="quoth  " & V2==graph)
    minimal <- subset(m, V1=="minimal" & V2==graph)
    euc <- subset(m, V1=="euc    " & V2==graph)
    eucl <- subset(m, V1=="eucl   " & V2==graph)
    stdhr2 <- subset(m, V1=="stdhr2 " & V2==graph)
    
                                        # ile informacji w samej pozycji
    #vioplot(names = names, sphere$V10, elli$V10, torus$V10, bottle$V10, minimal$V10, zebra$V10, kq$V10, mcb$V10, quoth$V10, hex$V10, stdhr$V10)
    #title(main = "How much information in a position", ylab = graph, cex=0.25)
                                        # przewiduje polaczenie na podstawie odleglosci
    vioplot(names = names, sphere$V8, elli$V8, torus$V8, minimal$V8, zebra$V8, kq$V8, quoth$V8, hex$V8, euc$V8, eucl$V8, stdhr$V8, stdhr2$V8, col="forestgreen")
    if (graph=="following ") {
        title(main = "Link based on distance", ylab=graph, cex=1.5)
    } else{
        title(ylab=graph, cex=0.25)
    }    
# przewiduje na podstawie neuronow
    vioplot(names = names, sphere$V9, elli$V9, torus$V9, minimal$V9, zebra$V9, kq$V9, quoth$V9, hex$V9, euc$V9, eucl$V9, stdhr$V9, stdhr2$V9, col="forestgreen")
    if (graph=="following ") {
        title(main = "Link based on grouping (neurons)",ylab=graph, cex=1.5)
    } 
    #entropia
    #vioplot(names = names, sphere$V11, elli$V11, torus$V11, bottle$V11, minimal$V11, zebra$V11, kq$V11, mcb$V11, quoth$V11, hex$V11, stdhr$V11)
    #title(main = "Entropy")
# aic neurony
    vioplot(names = names, sphere$V12, elli$V12, torus$V12, minimal$V12, zebra$V12, kq$V12, quoth$V12, hex$V12, euc$V12, eucl$V12, stdhr$V12, stdhr2$V12, col="forestgreen")
    if (graph=="following ") {
        title(main = "AIC (neurons)",ylab=graph, cex=1.5)
    } 
# bic neurony
    vioplot(names = names, sphere$V13, elli$V13, torus$V13, minimal$V13, zebra$V13, kq$V13, quoth$V13, hex$V13, euc$V13, eucl$V13, stdhr$V13, stdhr2$V13, col="forestgreen")
    if (graph=="following ") {
        title(main = "BIC (neurons)", ,ylab=graph, cex=1.5)
    } 
}    

dev.off()

pdf("diagnostyka.pdf", width=32, height=18)
par(mfrow=c(6,4))
par(mar=c(1,1,1,1), oma = c(0,0,2,0)))

#text("Link based on distance", cex=0.25)
#text("Link based on grouping (neurons)", cex=0.25)
#text("AIC neurons")
#text("BIC neurons")

for (graph in graphs) {
    sphere <- subset(m, V1=="sphere " & V2==graph)
    hex <- subset(m, V1=="hex    " & V2==graph)
    torus <- subset(m, V1=="torus  " & V2==graph)
    bottle <- subset(m, V1=="bottle " & V2==graph)
    stdhr <- subset(m, V1=="stdhr  " & V2==graph)
    kq <- subset(m, V1=="kq     " & V2==graph)
    mcb <- subset(m, V1=="mcb    " & V2==graph)
    elli <- subset(m, V1=="elli   " & V2==graph)
    zebra <- subset(m, V1=="zebra  " & V2==graph)
    quoth <- subset(m, V1=="quoth  " & V2==graph)
    minimal <- subset(m, V1=="minimal" & V2==graph)
    euc <- subset(m, V1=="euc    " & V2==graph)
    eucl <- subset(m, V1=="eucl   " & V2==graph)
    stdhr2 <- subset(m, V1=="stdhr2 " & V2==graph)
    
                                        # ile informacji w samej pozycji
    #vioplot(names = names, sphere$V10, elli$V10, torus$V10, bottle$V10, minimal$V10, zebra$V10, kq$V10, mcb$V10, quoth$V10, hex$V10, stdhr$V10)
    #title(main = "How much information in a position", ylab = graph, cex=0.25)
                                        # przewiduje polaczenie na podstawie odleglosci
    vioplot(names = names, sphere$V8, elli$V8, torus$V8, minimal$V8, zebra$V8, kq$V8, quoth$V8, euc$V8, stdhr2$V8, col="forestgreen")
    if (graph=="following ") {
        title(main = "Link based on distance", ylab=graph, cex=2)
    } else{
        title(ylab=graph, cex=0.25)
    }    
# przewiduje na podstawie neuronow
    vioplot(names = names, sphere$V9, elli$V9, torus$V9, minimal$V9, zebra$V9, kq$V9, quoth$V9, euc$V9, stdhr2$V9, col="forestgreen")
    if (graph=="following ") {
        title(main = "Link based on grouping (neurons)",ylab=graph, cex=2)
    } 
    #entropia
    #vioplot(names = names, sphere$V11, elli$V11, torus$V11, bottle$V11, minimal$V11, zebra$V11, kq$V11, mcb$V11, quoth$V11, hex$V11, stdhr$V11)
    #title(main = "Entropy")
# aic neurony
    vioplot(names = names, sphere$V12, elli$V12, torus$V12, minimal$V12, zebra$V12, kq$V12, quoth$V12, euc$V12, stdhr2$V12, col="forestgreen")
    if (graph=="following ") {
        title(main = "AIC (neurons)",ylab=graph, cex=2)
    } 
# bic neurony
    vioplot(names = names, sphere$V13, elli$V13, torus$V13, minimal$V13, zebra$V13, kq$V13, quoth$V13, euc$V13, stdhr2$V13, col="forestgreen")
    if (graph=="following ") {
        title(main = "BIC (neurons)", ,ylab=graph, cex=2)
    } 
}    

dev.off()
