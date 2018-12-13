m <- read.table("survey_data.csv", header=T, sep=",", quote='"')

m <- read.table("survey_data.csv", header=T, sep=",", quote='"')
z <- subset(m, m$POPULATION=="github")
y <- subset(z, z$PARTICIPATION.TYPE.CONTRIBUTE==1)
x <- subset(y,(y$CONTRIBUTOR.TYPE.CONTRIBUTE.CODE!="" | y$CONTRIBUTOR.TYPE.CONTRIBUTE.DOCS!="" | y$CONTRIBUTOR.TYPE.PROJECT.MAINTENANCE!="" | y$CONTRIBUTOR.TYPE.FILE.BUGS!="" | y$CONTRIBUTOR.TYPE.FEATURE.REQUESTS!="" | y$CONTRIBUTOR.TYPE.COMMUNITY.ADMIN!=""))

counts_1 <- table(x$CONTRIBUTOR.TYPE.CONTRIBUTE.CODE)
counts_2 <- table(x$CONTRIBUTOR.TYPE.CONTRIBUTE.DOCS)
counts_3 <- table(x$CONTRIBUTOR.TYPE.PROJECT.MAINTENANCE)
counts_4 <- table(x$CONTRIBUTOR.TYPE.FILE.BUGS)
counts_5 <- table(x$CONTRIBUTOR.TYPE.FEATURE.REQUESTS)
counts_6 <- table(x$CONTRIBUTOR.TYPE.COMMUNITY.ADMIN)

library("RColorBrewer")
greens <- brewer.pal(5, "Greens")

barplot(counts_1, col=greens, names.arg=c("No answer", "Never", "Rarely", "Occasionally", "Frequently"), beside=F)

nazwy <- c("Contribute code", "Contribute docs", "Project maintenance", "File bugs","Feature requests", "Community admin")

par(mfrow=c(2,3))

z <- subset(m, m$EMPLOYMENT.STATUS=="Employed full time")
s <- data.frame(z$OSS.HIRING, z$OSS.AS.JOB)
s <- subset(s, s$z.OSS.HIRING!="")
s <- subset(s, s$z.OSS.AS.JOB!="")
s$z.OSS.HIRING <- factor(s$z.OSS.HIRING)
s$z.OSS.AS.JOB <- factor(s$z.OSS.AS.JOB)

s$z.OSS.AS.JOB <- relevel(s$z.OSS.AS.JOB, "Yes, directly-  some or all of my work duties include contributing to open source projects.")
s$z.OSS.AS.JOB <- relevel(s$z.OSS.AS.JOB, "Yes, indirectly- I contribute to open source in carrying out my work duties, but I am not required or expected to do so.")
s$z.OSS.AS.JOB <- relevel(s$z.OSS.AS.JOB, "No.")

counts_1 <- table(s$z.OSS.HIRING, s$z.OSS.AS.JOB)

library("RColorBrewer")
greens <- brewer.pal(5, "Greens")
#barplot(counts_1, main = "Importance of OSS contributions for hiring -- Full time employed", ylab = "Frequency", xlab="Working on OSS in current job", names.arg = c("No", "Yes-directly", "Yes-indirectly"), col = greens, beside=T )

pdf("fulltimers.pdf")
barplot(counts_1, main = "Importance of OSS contributions for hiring -- Full time employed", legend.text=c("Not applicable", "Not at all important", "Not too important", "Somewhat important", "Very important"), ylim=c(0,250), args.legend = list(x = "topleft", bty="n"), ylab = "Frequency", xlab="Working on OSS in current job", names.arg = c("No", "Yes-indirectly", "Yes-directly"), col = greens, beside=T )
dev.off()

y <- subset(m, m$EMPLOYMENT.STATUS=="Employed part time")
a <- data.frame(y$OSS.HIRING, y$OSS.AS.JOB)
a <- subset(a, a$y.OSS.HIRING!="")
a <- subset(a, a$y.OSS.AS.JOB!="")
a$y.OSS.HIRING <- factor(a$y.OSS.HIRING)
a$y.OSS.AS.JOB <- factor(a$y.OSS.AS.JOB)

a$y.OSS.AS.JOB <- relevel(a$y.OSS.AS.JOB, "Yes, directly-  some or all of my work duties include contributing to open source projects.")
a$y.OSS.AS.JOB <- relevel(a$y.OSS.AS.JOB, "Yes, indirectly- I contribute to open source in carrying out my work duties, but I am not required or expected to do so.")
a$y.OSS.AS.JOB <- relevel(a$y.OSS.AS.JOB, "No.")

counts_2 <- table(a$y.OSS.HIRING, a$y.OSS.AS.JOB)

library("RColorBrewer")
greens <- brewer.pal(5, "Greens")

#barplot(counts_2, main = "Importance of OSS contributions for hiring -- Part time employed", legend.text=c("Not applicable", "Not at all important", "Not too important", "Somewhat important", "Very important"), args.legend = list(x = "topleft", bty="n"), ylab = "Frequency", xlab="Working on OSS in current job", names.arg = c("No", "Yes-indirectly", "Yes-directly"), col = greens, beside=T )

pdf("parttimers.pdf")
barplot(counts_2, main = "Importance of OSS contributions for hiring -- Part time employed", legend.text=c("Not applicable", "Not at all important", "Not too important", "Somewhat important", "Very important"), args.legend = list(x = "topright", bty="n"), ylab = "Frequency",ylim=c(0,20), xlab="Working on OSS in current job", names.arg = c("No", "Yes-indirectly", "Yes-directly"), col = greens, beside=T )
dev.off()


s <- data.frame(m$EXTERNAL.EFFICACY, m$FUTURE.CONTRIBUTION.INTEREST, m$FUTURE.CONTRIBUTION.LIKELIHOOD)
s <- subset(s, s$m.EXTERNAL.EFFICACY!="")
s <- subset(s, s$m.FUTURE.CONTRIBUTION.INTEREST!="")
s <- subset(s, s$m.FUTURE.CONTRIBUTION.LIKELIHOOD!="")
s$m.EXTERNAL.EFFICACY <- factor(s$m.EXTERNAL.EFFICACY)
s$m.FUTURE.CONTRIBUTION.INTEREST <- factor(s$m.FUTURE.CONTRIBUTION.INTEREST)
s$m.FUTURE.CONTRIBUTION.LIKELIHOOD <- factor(s$m.FUTURE.CONTRIBUTION.LIKELIHOOD)

s$m.EXTERNAL.EFFICACY <- relevel(s$m.EXTERNAL.EFFICACY, "Strongly agree")
s$m.EXTERNAL.EFFICACY <- relevel(s$m.EXTERNAL.EFFICACY, "Somewhat agree")
s$m.EXTERNAL.EFFICACY <- relevel(s$m.EXTERNAL.EFFICACY, "Neither agree nor disagree")
s$m.EXTERNAL.EFFICACY <- relevel(s$m.EXTERNAL.EFFICACY, "Somewhat disagree")
s$m.EXTERNAL.EFFICACY <- relevel(s$m.EXTERNAL.EFFICACY, "Strongly disagree")

s$m.FUTURE.CONTRIBUTION.LIKELIHOOD <- relevel(s$m.FUTURE.CONTRIBUTION.LIKELIHOOD, "Very likely")
s$m.FUTURE.CONTRIBUTION.LIKELIHOOD <- relevel(s$m.FUTURE.CONTRIBUTION.LIKELIHOOD, "Somewhat likely")
s$m.FUTURE.CONTRIBUTION.LIKELIHOOD <- relevel(s$m.FUTURE.CONTRIBUTION.LIKELIHOOD, "Somewhat unlikely")
s$m.FUTURE.CONTRIBUTION.LIKELIHOOD <- relevel(s$m.FUTURE.CONTRIBUTION.LIKELIHOOD, "Very unlikely")

pdf("reputation_future_interest.pdf")
spineplot(s$m.EXTERNAL.EFFICACY,s$m.FUTURE.CONTRIBUTION.INTEREST , col = greens, main = "Perceived reputation and interest in future contributions", ylab = "Level of Interest", xlab = "The community values contributions from people like me")
dev.off()

pdf("reputation_future_likelihood.pdf")
spineplot(s$m.EXTERNAL.EFFICACY,s$m.FUTURE.CONTRIBUTION.LIKELIHOOD , col = greens, main = "Perceived reputation and likelihood of future contributions", ylab = "Declared likelihood", xlab = "The community values contributions from people like me")
dev.off()


z <- subset(m, m$EMPLOYMENT.STATUS=="Employed full time")
a <- data.frame(z$OSS.AS.JOB, z$PROFESSIONAL.SOFTWARE)
a <- subset(a, a$z.OSS.AS.JOB!="")
a <- subset(a, a$z.PROFESSIONAL.SOFTWARE!="")
a$z.OSS.AS.JOB <- factor(a$z.OSS.AS.JOB)
a$z.PROFESSIONAL.SOFTWARE <- factor(a$z.PROFESSIONAL.SOFTWARE)

a$z.PROFESSIONAL.SOFTWARE <- relevel(a$z.PROFESSIONAL.SOFTWARE, "Never")
a$z.PROFESSIONAL.SOFTWARE <- relevel(a$z.PROFESSIONAL.SOFTWARE, "Rarely")
a$z.PROFESSIONAL.SOFTWARE <- relevel(a$z.PROFESSIONAL.SOFTWARE, "Occasionally")
a$z.PROFESSIONAL.SOFTWARE <- relevel(a$z.PROFESSIONAL.SOFTWARE, "Frequently")

a$z.OSS.AS.JOB <- relevel(a$z.OSS.AS.JOB, "Yes, directly-  some or all of my work duties include contributing to open source projects.")
a$z.OSS.AS.JOB <- relevel(a$z.OSS.AS.JOB, "Yes, indirectly- I contribute to open source in carrying out my work duties, but I am not required or expected to do so.")
a$z.OSS.AS.JOB <- relevel(a$z.OSS.AS.JOB, "No.")


counts <- table(a$z.OSS.AS.JOB, a$z.PROFESSIONAL.SOFTWARE)

greens <- brewer.pal(3, "Greens")

pdf("fulltimers-freqxoss.pdf")
spineplot(a$z.PROFESSIONAL.SOFTWARE, a$z.OSS.AS.JOB, col = greens, main = "Contributing to OSS in software production -- Full time", ylab = "OSS contributions in job", yaxlabels=c("No", "Yes-indirectly", "Yes-directly"), xlab = "Frequency of contributions to software production")
dev.off()

z <- subset(m, m$EMPLOYMENT.STATUS=="Employed part time")
a <- data.frame(z$OSS.AS.JOB, z$PROFESSIONAL.SOFTWARE)
a <- subset(a, a$z.OSS.AS.JOB!="")
a <- subset(a, a$z.PROFESSIONAL.SOFTWARE!="")
a$z.OSS.AS.JOB <- factor(a$z.OSS.AS.JOB)
a$z.PROFESSIONAL.SOFTWARE <- factor(a$z.PROFESSIONAL.SOFTWARE)
counts <- table(a$z.OSS.AS.JOB, a$z.PROFESSIONAL.SOFTWARE)

a$z.PROFESSIONAL.SOFTWARE <- relevel(a$z.PROFESSIONAL.SOFTWARE, "Never")
a$z.PROFESSIONAL.SOFTWARE <- relevel(a$z.PROFESSIONAL.SOFTWARE, "Rarely")
a$z.PROFESSIONAL.SOFTWARE <- relevel(a$z.PROFESSIONAL.SOFTWARE, "Occasionally")
a$z.PROFESSIONAL.SOFTWARE <- relevel(a$z.PROFESSIONAL.SOFTWARE, "Frequently")

a$z.OSS.AS.JOB <- relevel(a$z.OSS.AS.JOB, "Yes, directly-  some or all of my work duties include contributing to open source projects.")
a$z.OSS.AS.JOB <- relevel(a$z.OSS.AS.JOB, "Yes, indirectly- I contribute to open source in carrying out my work duties, but I am not required or expected to do so.")
a$z.OSS.AS.JOB <- relevel(a$z.OSS.AS.JOB, "No.")

pdf("parttimers-freqxoss.pdf")
spineplot(a$z.PROFESSIONAL.SOFTWARE, a$z.OSS.AS.JOB, col = greens, main = "Contributing to OSS in software production -- Part time", ylab = "OSS contributions in job", yaxlabels=c("No", "Yes-indirectly", "Yes-directly"), xlab = "Frequency of contributions to software production")
dev.off()


a <- data.frame(m$EMPLOYMENT.STATUS, m$RECEIVED.HELP)
a <- subset(a, a$m.RECEIVED.HELP!="")
a <- subset(a, a$m.EMPLOYMENT.STATUS!="")
a$m.RECEIVED.HELP <- factor(a$m.RECEIVED.HELP)
a$m.EMPLOYMENT.STATUS <- factor(a$m.EMPLOYMENT.STATUS)

levels(a$m.EMPLOYMENT.STATUS) <- c("Employed full time", "Employed part time", "Full time student", "Other", "Other", "Temporarily not working")

count <- table(a$m.EMPLOYMENT.STATUS, a$m.RECEIVED.HELP)
greens <- brewer.pal(2, "Greens")

pdf("receiving_help.pdf")
spineplot(a$m.EMPLOYMENT.STATUS, a$m.RECEIVED.HELP, col = greens, main = "Receiving help", ylab = "Received help", xaxlabels=c("Full-time", "Part-time", "Student", "Other", "Temp. not working"), xlab = "Employment status")
dev.off()

b <- data.frame(m$EMPLOYMENT.STATUS, m$PROVIDED.HELP)
b <- subset(b, b$m.PROVIDED.HELP!="")
b <- subset(b, b$m.EMPLOYMENT.STATUS!="")
b$m.PROVIDED.HELP <- factor(b$m.PROVIDED.HELP)
b$m.EMPLOYMENT.STATUS <- factor(b$m.EMPLOYMENT.STATUS)

levels(b$m.EMPLOYMENT.STATUS) <- c("Employed full time", "Employed part time", "Full time student", "Other", "Other", "Temporarily not working")

count <- table(b$m.EMPLOYMENT.STATUS, b$m.PROVIDED.HELP)

pdf("providing_help.pdf")
spineplot(b$m.EMPLOYMENT.STATUS, b$m.PROVIDED.HELP, col = greens, main = "Providing help", ylab = "Provided help", xaxlabels=c("Full-time", "Part-time", "Student", "Other", "Temp. not working"), xlab = "Employment status")
dev.off()


                                        #correspondence analysis
library("factoextra")

#place of help x relationship with helper

b <- data.frame(m$FIND.HELPER, m$HELPER.PRIOR.RELATIONSHIP)
b <- subset(b, b$m.FIND.HELPER!="")
b <- subset(b, b$m.HELPER.PRIOR.RELATIONSHIP!="")
b$m.FIND.HELPER <- factor(b$m.FIND.HELPER)
b$m.HELPER.PRIOR.RELATIONSHIP <- factor(b$m.HELPER.PRIOR.RELATIONSHIP)

levels(b$m.FIND.HELPER) <- c("I asked specific person", "I wrote in public forum or GitHub Issue", "Other", "I received unsolicited help")

levels(b$m.HELPER.PRIOR.RELATIONSHIP) <- c("I knew only their contributions", "Total strangers", "We knew each other a little", "We knew each other well")

mytable <- table(b$m.FIND.HELPER,b$m.HELPER.PRIOR.RELATIONSHIP)

prop.table(mytable, 1)
prop.table(mytable, 2)

library(ca)
fit <- ca(mytable)

pdf("ca_receive_place_relation.pdf")
fviz_ca_biplot(fit, repel = TRUE, arrow=c(FALSE,TRUE), title="Receiving help (relationship with helper)")
dev.off()

chisq.test(mytable)

# place of offered help X relationship with helped

b <- data.frame(m$FIND.HELPEE, m$HELPEE.PRIOR.RELATIONSHIP)
b <- subset(b, b$m.FIND.HELPEE!="")
b <- subset(b, b$m.HELPEE.PRIOR.RELATIONSHIP!="")
b$m.FIND.HELPEE <- factor(b$m.FIND.HELPEE)
b$m.HELPEE.PRIOR.RELATIONSHIP <- factor(b$m.HELPEE.PRIOR.RELATIONSHIP)

levels(b$m.FIND.HELPEE) <- c("I offered unsolicited help", "Other", "They wrote in public forum or GitHub Issue", "They asked me directly")

levels(b$m.HELPEE.PRIOR.RELATIONSHIP) <- c("I knew only their contributions", "Total strangers", "We knew each other a little", "We knew each other well")

mytable <- table(b$m.FIND.HELPEE,b$m.HELPEE.PRIOR.RELATIONSHIP)

fit <- ca(mytable)

pdf("ca_provide_plate_relation.pdf")
fviz_ca_biplot(fit, repel = TRUE, arrow=c(FALSE,TRUE), title="Providing help (relationship with helper)")
dev.off()

chisq.test(mytable)

                                        # employment x received help place

b <- data.frame(m$FIND.HELPER, m$EMPLOYMENT.STATUS)
b <- subset(b, b$m.FIND.HELPER!="")
b <- subset(b, b$m.EMPLOYMENT.STATUS!="")
b$m.FIND.HELPER <- factor(b$m.FIND.HELPER)
b$m.EMPLOYMENT.STATUS <- factor(b$m.EMPLOYMENT.STATUS)

levels(b$m.EMPLOYMENT.STATUS) <- c("Employed full time", "Employed part time", "Full time student", "Other", "Other", "Temporarily not working")
levels(b$m.FIND.HELPER) <- c("I asked specific person", "I wrote in public forum or GitHub Issue", "Other", "I received unsolicited help")

mytable <- table(b$m.FIND.HELPER,b$m.EMPLOYMENT.STATUS)
chisq.test(mytable)

# offered help place and employment

b <- data.frame(m$FIND.HELPEE, m$EMPLOYMENT.STATUS)
b <- subset(b, b$m.FIND.HELPEE!="")
b <- subset(b, b$m.EMPLOYMENT.STATUS!="")
b$m.FIND.HELPEE <- factor(b$m.FIND.HELPEE)
b$m.EMPLOYMENT.STATUS <- factor(b$m.EMPLOYMENT.STATUS)

levels(b$m.EMPLOYMENT.STATUS) <- c("Employed full time", "Employed part time", "Full time student", "Other", "Other", "Temporarily not working")
levels(b$m.FIND.HELPEE) <- c("I offered unsolicited help", "Other", "They wrote in public forum or GitHub Issue", "They asked me directly")

mytable <- table(b$m.FIND.HELPEE,b$m.EMPLOYMENT.STATUS)

fit <- ca(mytable)

pdf("ca_provide_place_employ.pdf")
fviz_ca_biplot(fit, repel = TRUE, arrow=c(FALSE,TRUE), title=" Providing help (professional status)")
dev.off()

chisq.test(mytable)

                                        # received type of help
b <- data.frame(m$RECEIVED.HELP.TYPE, m$EMPLOYMENT.STATUS)
b <- subset(b, b$m.RECEIVED.HELP.TYPE!="")
b <- subset(b, b$m.EMPLOYMENT.STATUS!="")
b$m.RECEIVED.HELP.TYPE <- factor(b$m.RECEIVED.HELP.TYPE)
b$m.EMPLOYMENT.STATUS <- factor(b$m.EMPLOYMENT.STATUS)

levels(b$m.EMPLOYMENT.STATUS) <- c("Employed full time", "Employed part time", "Full time student", "Other", "Other", "Temporarily not working")
levels(b$m.RECEIVED.HELP.TYPE) <- c("Installing/using of app", "Introductions to other people", "Other", "Understanding community norms", "Writing code")

mytable <- table(b$m.RECEIVED.HELP.TYPE,b$m.EMPLOYMENT.STATUS)

fit <- ca(mytable)

pdf("ca_receive_type_employ.pdf")
fviz_ca_biplot(fit, repel = TRUE, arrow=c(FALSE,TRUE), title="Receiving help (professional status)")
dev.off()

chisq.test(mytable)

                                        # offered type of help
b <- data.frame(m$PROVIDED.HELP.TYPE, m$EMPLOYMENT.STATUS)
b <- subset(b, b$m.PROVIDED.HELP.TYPE!="")
b <- subset(b, b$m.EMPLOYMENT.STATUS!="")
b$m.PROVIDED.HELP.TYPE <- factor(b$m.PROVIDED.HELP.TYPE)
b$m.EMPLOYMENT.STATUS <- factor(b$m.EMPLOYMENT.STATUS)

levels(b$m.EMPLOYMENT.STATUS) <- c("Employed full time", "Employed part time", "Full time student", "Other", "Other", "Temporarily not working")
levels(b$m.PROVIDED.HELP.TYPE) <- c("Installing/using of app", "Introductions to other people", "Other", "Understanding community norms", "Writing code")

mytable <- table(b$m.PROVIDED.HELP.TYPE,b$m.EMPLOYMENT.STATUS)

fit <- ca(mytable)

pdf("ca_provide_type_employ.pdf")
fviz_ca_biplot(fit, repel = TRUE, arrow=c(FALSE,TRUE), title="Providing help (professional status)")
dev.off()

chisq.test(mytable)
