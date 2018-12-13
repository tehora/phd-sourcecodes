# cleaning
library("textclean")
m <- readLines()
m$text <- replace_emoji(iconv(m$text, "Latin1", "UTF-8"), emoji_dt = lexicon::hash_emojis)
m$text <- replace_emoticon(iconv(m$text, "Latin1", "UTF-8"), emoticon_dt = lexicon::hash_emoticons)
m$text <- replace_internet_slang(iconv(m$text, "Latin1", "UTF-8"))

# First, load the texts

#library(readtext)
#readtext(paste0("/mnt/src/hetero-lda/", "issues_comments_0-1.txt"))

cname <- file.path("/mnt/src/hetero-lda/", "tm")

# load the R package for text mining and load the texts into R (creating corpus)

# install.packages("tm")
library(tm)
docs <- VCorpus(DirSource(cname))

#for (j in seq(docs))
#{
#    docs[[j]] <- gsub("^f|Fix(es)?\\s#\\d", "fixnumber", docs[[j]])
#    docs[[j]] <- gsub("^c|Close(s|d)?\\s#\\d", "closenumber", docs[[j]])
#}

docs <- tm_map(docs,removePunctuation)

gc()

docs <- tm_map(docs, PlainTextDocument)
docs <- tm_map(docs, removeNumbers)

gc()

# and the analysis is also easier, e.g. counting words, when they are all e.g. lowercase
docs <- tm_map(docs, tolower)
#docs <- tm_map(docs, tolower)
docs <- tm_map(docs, PlainTextDocument)

gc()

for (j in seq(docs))
{
  docs[[j]] <- gsub("pull\\srequests?", "pullrequest", docs[[j]])
  docs[[j]] <- gsub("doesnt", "does\\snot", docs[[j]])
  docs[[j]] <- gsub("how\\sto", "howto", docs[[j]])
  docs[[j]] <- gsub("href", "", docs[[j]])
  docs[[j]] <- gsub("cant", "can\\snot", docs[[j]])
  docs[[j]] <- gsub("cannot", "can\\snot", docs[[j]])
  docs[[j]] <- gsub("not\\s(\\w)", "not\\1", docs[[j]])
  docs[[j]] <- gsub("can\\syou", "canyou", docs[[j]])
  docs[[j]] <- gsub("will\\s(\\w)", "will\\1", docs[[j]])
  docs[[j]] <- gsub("merged?", "merge", docs[[j]])
  docs[[j]] <- gsub("merging", "merge", docs[[j]])
  docs[[j]] <- gsub("github link", "githublink", docs[[j]])
  docs[[j]] <- gsub("errors", "error", docs[[j]])
}

gc()

# usually we want to get rid of commmon words that make little sense in analyses (e.g. auxiliary verbs, prepositions, ...)

docs <- tm_map(docs, removeWords, c(stopwords("english"),"seems","thats","youre", "willbe", "one", "without", "either", "theres", "did", "do", "com", "does", "another", "nothave", "nota", "yes", "also", "ive", "just", "can"))   
docs <- tm_map(docs, PlainTextDocument)

gc()

#docs <- tm_map(docs, stemDocument)   
#docs <- tm_map(docs, PlainTextDocument)

gc()

docs <- tm_map(docs, stripWhitespace)
docs <- tm_map(docs, PlainTextDocument)

gc()

for (j in seq(docs)) {
    docs[[j]] <- gsub("\\b[[:alpha:]]{17,}\\b", "", docs[[j]], perl=T)
}

gc()

dtm<-list()

for (i in 1:11) {    
    dtm[[i]] <- DocumentTermMatrix(Corpus(VectorSource(docs[[i]])))
}    

#for (i in 1:10) {
#    findAssocs(as.matrix(dtm[[i]]), c("help", "issue", "problem"), c(0.75, 0.75, 0.75)) 
#}  

rm(docs)
gc()

for (i in 1:11) {    
    dtm[[i]] <- as.matrix(removeSparseTerms(dtm[[i]], 0.99))
    gc()
} 

freqs <- list()

for (i in 1:11) {
    freqs[[i]] <- sort(colSums(as.matrix(dtm[[i]])), decreasing=T)
}

library(wordcloud)
#set.seed(12112018)

#wordcloud(names(freq), freq, min.freq=10)
#wordcloud(names(freq), freq, max.words=500) 

cols <- brewer.pal(4, "Greens")

#par(mfrow = c(2,5))
par(mar=c(1,1,1,1))

for (i in 1:11) {
    file <- paste("hetero-wordcloud1",i,".pdf",sep="")
    freqs_small <- freqs[[i]]
    pdf(file)
    wordcloud(names(freqs_small), freqs_small, max.words=200, rot.per=0.3, colors=cols)
    dev.off()
}

library(sentimentr)
dict <- read.table("/mnt/src/hetero-lda/emoji_dict.txt", header=T, as.is=T)
dict <- as_key(dict)

x <- as.character(readLines("/mnt/src/hetero-lda/tm/issues_comments_00.txt"))
m <- get_sentences(x)
a <- sentiment(m,  polarity_dt=dict,  adversative.weight = 0.5)
a <- subset(a, word_count  < 50)

s <- as.data.frame(a$sentiment)
names(s) <- c("sent")
s$sent_factor <-  NA
s$sent_factor[s$sent > 0] <- 1
s$sent_factor[s$sent == 0] <- 2
s$sent_factor[s$sent < 0] <- 3

#s$sent_factor <- factor(s$sent_factor, levels <- c(1,2,3), labels <- c("positive","neutral", "negative"))
s$dist[is.na(s$sent_factor)==F] <- 0

s <- as.matrix(s)
s <- s[,2:3]

#pdf("sent-density-0.pdf")
#plot(density(a$sentiment), main="Distance 0", col="forestgreen", lwd=2)
#abline(v=0, col="red")
#dev.off()

x <- as.character(readLines("/mnt/src/hetero-lda/tm/issues_comments_01.txt"))
m <- get_sentences(x)
a <- sentiment(m,  polarity_dt=dict,  adversative.weight = 0.5)
a <- subset(a, word_count  < 50)

b <- as.data.frame(a$sentiment)
names(b) <- c("sent")
b$sent_factor <-  NA
b$sent_factor[b$sent > 0] <- 1
b$sent_factor[b$sent == 0] <- 2
b$sent_factor[b$sent < 0] <- 3

b$dist[is.na(b$sent_factor)==F] <- 1

b <- b[,2:3]

s <- rbind(s,as.matrix(b))

gc()
write.table(s, "tm/matrix.txt", sep=";", row.names=F)

x <- as.character(readLines("/mnt/src/hetero-lda/tm/issues_comments_02.txt"))
m <- get_sentences(x)
a <- sentiment(m, polarity_dt= dict,  adversative.weight = 0.5)
a <- subset(a, word_count  < 50)

b <- as.data.frame(a$sentiment)
names(b) <- c("sent")
b$sent_factor <-  NA
b$sent_factor[b$sent > 0] <- 1
b$sent_factor[b$sent == 0] <- 2
b$sent_factor[b$sent < 0] <- 3

b$dist[is.na(b$sent_factor)==F] <- 2

s <- rbind(s,as.matrix(b[,2:3]))

write.table(s, "tm/matrix.txt", sep=";", row.names=F)
gc()

x <- as.character(readLines("/mnt/src/hetero-lda/tm/issues_comments_03.txt"))
m <- get_sentences(x)
a <- sentiment(m, polarity_dt=dict,  adversative.weight = 0.5)
a <- subset(a, word_count  < 50)
b <- as.data.frame(a$sentiment)
names(b) <- c("sent")
b$sent_factor <-  NA
b$sent_factor[b$sent > 0] <- 1
b$sent_factor[b$sent == 0] <- 2
b$sent_factor[b$sent < 0] <- 3

b$dist[is.na(b$sent_factor)==F] <- 3

s <- rbind(s,as.matrix(b[,2:3]))

write.table(s, "tm/matrix.txt", sep=";", row.names=F)
gc()

x <- as.character(readLines("/mnt/src/hetero-lda/tm/issues_comments_04.txt"))
m <- get_sentences(x)
a <- sentiment(m, polarity_dt=dict,  adversative.weight = 0.5)
a <- subset(a, word_count  < 50)

b <- as.data.frame(a$sentiment)
names(b) <- c("sent")
b$sent_factor <-  NA
b$sent_factor[b$sent > 0] <- 1
b$sent_factor[b$sent == 0] <- 2
b$sent_factor[b$sent < 0] <- 3

b$dist[is.na(b$sent_factor)==F] <- 4

s <- rbind(s,as.matrix(b[,2:3]))

write.table(s, "tm/matrix.txt", sep=";", row.names=F)
gc()

x <- as.character(readLines("/mnt/src/hetero-lda/tm/issues_comments_05.txt"))
m <- get_sentences(x)
a <- sentiment(m, polarity_dt=dict,  adversative.weight = 0.5)
a <- subset(a, word_count  < 50)

b <- as.data.frame(a$sentiment)
names(b) <- c("sent")
b$sent_factor <-  NA
b$sent_factor[b$sent > 0] <- 1
b$sent_factor[b$sent == 0] <- 2
b$sent_factor[b$sent < 0] <- 3

b$dist[is.na(b$sent_factor)==F] <- 5

s <- rbind(s,as.matrix(b[,2:3]))

write.table(s, "tm/matrix.txt", sep=";", row.names=F)
gc()

# 200 000 lines
x <- as.character(readLines("/mnt/src/hetero-lda/tm/is_com_06a.txt"))
m <- get_sentences(x)
a <- sentiment(m, polarity_dt=dict,  adversative.weight = 0.5)
a <- subset(a, word_count  < 50)

b <- as.data.frame(a$sentiment)
names(b) <- c("sent")
b$sent_factor <-  NA
b$sent_factor[b$sent > 0] <- 1
b$sent_factor[b$sent == 0] <- 2
b$sent_factor[b$sent < 0] <- 3

b$dist[is.na(b$sent_factor)==F] <- 6

s <- rbind(s,as.matrix(b[,2:3]))

write.table(s, "tm/matrix.txt", sep=";", row.names=F)
gc()

# 150 000 lines
x <- as.character(readLines("/mnt/src/hetero-lda/tm/is_com_06b.txt"))
m <- get_sentences(x)
a <- sentiment(m, polarity_dt=dict,  adversative.weight = 0.5)
a <- subset(a, word_count  < 50)
b <- as.data.frame(a$sentiment)
names(b) <- c("sent")
b$sent_factor <-  NA
b$sent_factor[b$sent > 0] <- 1
b$sent_factor[b$sent == 0] <- 2
b$sent_factor[b$sent < 0] <- 3

b$dist[is.na(b$sent_factor)==F] <- 6

s <- rbind(s,as.matrix(b[,2:3]))

write.table(s, "tm/matrix.txt", sep=";", row.names=F)
gc()

# the remaining
x <- as.character(readLines("/mnt/src/hetero-lda/tm/is_com_06c.txt"))
m <- get_sentences(x)
a <- sentiment(m, polarity_dt=dict,  adversative.weight = 0.5)
a <- subset(a, word_count  < 50)
b <- as.data.frame(a$sentiment)
names(b) <- c("sent")
b$sent_factor <-  NA
b$sent_factor[b$sent > 0] <- 1
b$sent_factor[b$sent == 0] <- 2
b$sent_factor[b$sent < 0] <- 3

b$dist[is.na(b$sent_factor)==F] <- 6

s <- rbind(s,as.matrix(b[,2:3]))

write.table(s, "tm/matrix.txt", sep=";", row.names=F)
gc()

#200 000 lines
x <- as.character(readLines("/mnt/src/hetero-lda/tm/is_com_07a.txt"))
m <- get_sentences(x)
a <- sentiment(m, polarity_dt=dict,  adversative.weight = 0.5)
a <- subset(a, word_count  < 50)
b <- as.data.frame(a$sentiment)
names(b) <- c("sent")
b$sent_factor <-  NA
b$sent_factor[b$sent > 0] <- 1
b$sent_factor[b$sent == 0] <- 2
b$sent_factor[b$sent < 0] <- 3

b$dist[is.na(b$sent_factor)==F] <- 7

s <- rbind(s,as.matrix(b[,2:3]))

write.table(s, "tm/matrix.txt", sep=";", row.names=F)
gc()

# 100 000 lines
x <- as.character(readLines("/mnt/src/hetero-lda/tm/is_com_07b.txt"))
m <- get_sentences(x)
a <- sentiment(m, polarity_dt=dict,  adversative.weight = 0.5)
a <- subset(a, word_count  < 50)
b <- as.data.frame(a$sentiment)
names(b) <- c("sent")
b$sent_factor <-  NA
b$sent_factor[b$sent > 0] <- 1
b$sent_factor[b$sent == 0] <- 2
b$sent_factor[b$sent < 0] <- 3

b$dist[is.na(b$sent_factor)==F] <- 7

s <- rbind(s,as.matrix(b[,2:3]))

write.table(s, "tm/matrix.txt", sep=";", row.names=F)
gc()

# 100 000 lines
x <- as.character(readLines("/mnt/src/hetero-lda/tm/is_com_07c.txt"))
m <- get_sentences(x)
a <- sentiment(m, polarity_dt=dict,  adversative.weight = 0.5)
a <- subset(a, word_count  < 50)
b <- as.data.frame(a$sentiment)
names(b) <- c("sent")
b$sent_factor <-  NA
b$sent_factor[b$sent > 0] <- 1
b$sent_factor[b$sent == 0] <- 2
b$sent_factor[b$sent < 0] <- 3

b$dist[is.na(b$sent_factor)==F] <- 7

s <- rbind(s,as.matrix(b[,2:3]))

write.table(s, "tm/matrix.txt", sep=";", row.names=F)
gc()

# 50 000 lines
x <- as.character(readLines("/mnt/src/hetero-lda/tm/is_com_07d.txt"))
m <- get_sentences(x)
a <- sentiment(m, polarity_dt=dict,  adversative.weight = 0.5)
a <- subset(a, word_count  < 50)
b <- as.data.frame(a$sentiment)
names(b) <- c("sent")
b$sent_factor <-  NA
b$sent_factor[b$sent > 0] <- 1
b$sent_factor[b$sent == 0] <- 2
b$sent_factor[b$sent < 0] <- 3

b$dist[is.na(b$sent_factor)==F] <- 7

s <- rbind(s,as.matrix(b[,2:3]))

write.table(s, "tm/matrix.txt", sep=";", row.names=F)
gc()

# 100 000 lines
x <- as.character(readLines("/mnt/src/hetero-lda/tm/is_com_07e.txt"))
m <- get_sentences(x)
a <- sentiment(m, polarity_dt=dict,  adversative.weight = 0.5)
a <- subset(a, word_count  < 50)
b <- as.data.frame(a$sentiment)
names(b) <- c("sent")
b$sent_factor <-  NA
b$sent_factor[b$sent > 0] <- 1
b$sent_factor[b$sent == 0] <- 2
b$sent_factor[b$sent < 0] <- 3

b$dist[is.na(b$sent_factor)==F] <- 7

s <- rbind(s,as.matrix(b[,2:3]))

write.table(s, "tm/matrix.txt", sep=";", row.names=F)
gc()

#50 000 lines
x <- as.character(readLines("/mnt/src/hetero-lda/tm/is_com_07f.txt"))
m <- get_sentences(x)
a <- sentiment(m, polarity_dt=dict,  adversative.weight = 0.5)
a <- subset(a, word_count  < 50)
b <- as.data.frame(a$sentiment)
names(b) <- c("sent")
b$sent_factor <-  NA
b$sent_factor[b$sent > 0] <- 1
b$sent_factor[b$sent == 0] <- 2
b$sent_factor[b$sent < 0] <- 3

b$dist[is.na(b$sent_factor)==F] <- 7

s <- rbind(s,as.matrix(b[,2:3]))

write.table(s, "tm/matrix.txt", sep=";", row.names=F)
gc()

# 32 704 lines
x <- as.character(readLines("/mnt/src/hetero-lda/tm/is_com_07g.txt"))
m <- get_sentences(x)
a <- sentiment(m, polarity_dt=dict,  adversative.weight = 0.5)
a <- subset(a, word_count  < 50)
b <- as.data.frame(a$sentiment)
names(b) <- c("sent")
b$sent_factor <-  NA
b$sent_factor[b$sent > 0] <- 1
b$sent_factor[b$sent == 0] <- 2
b$sent_factor[b$sent < 0] <- 3

b$dist[is.na(b$sent_factor)==F] <- 7

s <- rbind(s,as.matrix(b[,2:3]))

write.table(s, "tm/matrix.txt", sep=";", row.names=F)
gc()

# 330 000 lines
x <- as.character(readLines("/mnt/src/hetero-lda/tm/is_com_08a.txt"))
m <- get_sentences(x)
a <- sentiment(m, polarity_dt=dict,  adversative.weight = 0.5)
a <- subset(a, word_count  < 50)
b <- as.data.frame(a$sentiment)
names(b) <- c("sent")
b$sent_factor <-  NA
b$sent_factor[b$sent > 0] <- 1
b$sent_factor[b$sent == 0] <- 2
b$sent_factor[b$sent < 0] <- 3

b$dist[is.na(b$sent_factor)==F] <- 8

s <- rbind(s,as.matrix(b[,2:3]))

write.table(s, "tm/matrix.txt", sep=";", row.names=F)
gc()

# 359 399 lines
x <- as.character(readLines("/mnt/src/hetero-lda/tm/is_com_08b.txt"))
m <- get_sentences(x)
a <- sentiment(m, polarity_dt=dict,  adversative.weight = 0.5)
a <- subset(a, word_count  < 50)
b <- as.data.frame(a$sentiment)
names(b) <- c("sent")
b$sent_factor <-  NA
b$sent_factor[b$sent > 0] <- 1
b$sent_factor[b$sent == 0] <- 2
b$sent_factor[b$sent < 0] <- 3

b$dist[is.na(b$sent_factor)==F] <- 8

s <- rbind(s,as.matrix(b[,2:3]))

write.table(s, "tm/matrix.txt", sep=";", row.names=F)
gc()


# 300 000 lines
x <- as.character(readLines("/mnt/src/hetero-lda/tm/is_com_09a.txt"))
m <- get_sentences(x)
a <- sentiment(m, polarity_dt=dict,  adversative.weight = 0.5)
a <- subset(a, word_count  < 50)
b <- as.data.frame(a$sentiment)
names(b) <- c("sent")
b$sent_factor <-  NA
b$sent_factor[b$sent > 0] <- 1
b$sent_factor[b$sent == 0] <- 2
b$sent_factor[b$sent < 0] <- 3

b$dist[is.na(b$sent_factor)==F] <- 9

s <- rbind(s,as.matrix(b[,2:3]))

write.table(s, "tm/matrix.txt", sep=";", row.names=F)
gc()

# 300 000 lines
x <- as.character(readLines("/mnt/src/hetero-lda/tm/is_com_09b.txt"))
m <- get_sentences(x)
a <- sentiment(m, polarity_dt=dict,  adversative.weight = 0.5)
a <- subset(a, word_count  < 50)
b <- as.data.frame(a$sentiment)
names(b) <- c("sent")
b$sent_factor <-  NA
b$sent_factor[b$sent > 0] <- 1
b$sent_factor[b$sent == 0] <- 2
b$sent_factor[b$sent < 0] <- 3

b$dist[is.na(b$sent_factor)==F] <- 9

s <- rbind(s,as.matrix(b[,2:3]))

write.table(s, "tm/matrix.txt", sep=";", row.names=F)
gc()

# 300 000 lines
x <- as.character(readLines("/mnt/src/hetero-lda/tm/is_com_09c.txt"))
m <- get_sentences(x)
a <- sentiment(m, polarity_dt=dict,  adversative.weight = 0.5)
a <- subset(a, word_count  < 50)
b <- as.data.frame(a$sentiment)
names(b) <- c("sent")
b$sent_factor <-  NA
b$sent_factor[b$sent > 0] <- 1
b$sent_factor[b$sent == 0] <- 2
b$sent_factor[b$sent < 0] <- 3

b$dist[is.na(b$sent_factor)==F] <- 9

s <- rbind(s,as.matrix(b[,2:3]))

write.table(s, "tm/matrix.txt", sep=";", row.names=F)
gc()

x <- as.character(readLines("/mnt/src/hetero-lda/tm/issues_comments_10.txt"))
m <- get_sentences(x)
a <- sentiment(m, polarity_dt=dict,  adversative.weight = 0.5)
a <- subset(a, word_count  < 50)
b <- as.data.frame(a$sentiment)
names(b) <- c("sent")
b$sent_factor <-  NA
b$sent_factor[b$sent > 0] <- 1
b$sent_factor[b$sent == 0] <- 2
b$sent_factor[b$sent < 0] <- 3

b$dist[is.na(b$sent_factor)==F] <- 10

b <- as.matrix(b)
b <- b[,2:3]

s <- rbind(s,as.matrix(b))

write.table(s, "matrix.txt", sep=";", row.names=F)

rm(x,m,a,b)
gc()

s <- as.data.frame(s)
s$sent_factor <- factor(s$sent_factor, levels <- c(1,2,3), labels <- c("positive","neutral", "negative"))
pdf("~/sentiments-distribution.pdf",11,7)
spineplot(ordered(s$dist), s$sent_factor, col = c("forestgreen", "lightgrey", "red3"), ylab = "Sentiment", xlab = "Distance")
dev.off()

