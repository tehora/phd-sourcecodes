dane <- read.table("~/github2fala.csv", header=TRUE, sep=",", stringsAsFactors=FALSE, quote="\"", comment.char="")

# zadeklarowanie, ze jedna z kolumn ma byc widziana jako data

dane$joined1 <-as.Date(dane$joined, "%b %d %Y")

# usun konta organizacji:
dane <- subset(dane, is.na(dane$joined1)==FALSE)

# zmienna dyskretna, czy czlowiek ma podanego maila, czy nie
dane$mail1[dane$mail!=""]<-1  
dane$mail1[dane$mail==""]<-0

# wycinanie subsetow
nowe <- subset(dane, is.na(dane$starred1)==TRUE)
nowe <- subset(dane, select=c(url, starred))

# poprawianie starred i liczb w postaci "1.2k"
dane$starred1 <- as.integer(sub("\\.?([0-9])k", "\\100", dane$starred))

write.table(nowe, "starred.csv", row.names=FALSE)

# wczytanie loginow z api
api <- read.table("~/loginy_male.csv", header=TRUE, sep=",", stringsAsFactors=FALSE)

api1<-api[,c(1,6)]
dane1 <- dane[,c(2,4)]

zbiorcze <- merge(api1, dane1, by.x="zbiorcze", by.y="url", all.x=TRUE)

# sortowanie po zmiennej

dane[order(zmienna),]

# dzielenie stringow

strsplit(x, split, fixed = FALSE, perl = FALSE, useBytes = FALSE)

rexp <- "^(\\w+)\\s?(.*)$"
y <- data.frame(MANUF=sub(rexp,"\\1",x), MAKE=sub(rexp,"\\2",x))

# troche prostsze
library(reshape2)
y <- colsplit(x," ",c("MANUF","MAKE"))

# szukanie trefnych members
laczenie <- merge(nowe, zebrani, by.x="zbiorcze", by.y="owner", all.x=TRUE)
laczenie$typ1<- as.factor(laczenie$typ1)
loginy<- subset(laczenie, laczenie$typ1!="Organization" & is.na(jest)==TRUE)







