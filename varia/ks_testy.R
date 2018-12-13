torus <- subset(m, V1=="torus  " & V2=="pull      ")
bottle <- subset(m, V1=="bottle " & V2=="pull      ")
ks.test(torus$V8, bottle$V8) #H0
ks.test(torus$V9, bottle$V9) #H0
ks.test(torus$V10, bottle$V10) #H0 (1%)
ks.test(torus$V11, bottle$V11) #H0
ks.test(torus$V12, bottle$V12) #H0
ks.test(torus$V13, bottle$V13) #H0

torus <- subset(m, V1=="torus  " & V2=="issues    ")
bottle <- subset(m, V1=="bottle " & V2=="issues    ")
ks.test(torus$V8, bottle$V8)
ks.test(torus$V9, bottle$V9)
ks.test(torus$V10, bottle$V10)
ks.test(torus$V11, bottle$V11)
ks.test(torus$V12, bottle$V12)
ks.test(torus$V13, bottle$V13)

# V10 1%

torus <- subset(m, V1=="torus  " & V2=="following ")
bottle <- subset(m, V1=="bottle " & V2=="following ")
ks.test(torus$V8, bottle$V8) #!
ks.test(torus$V9, bottle$V9)
ks.test(torus$V10, bottle$V10) #!
ks.test(torus$V11, bottle$V11)
ks.test(torus$V12, bottle$V12)
ks.test(torus$V13, bottle$V13)

torus <- subset(m, V1=="torus  " & V2=="forking   ")
bottle <- subset(m, V1=="bottle " & V2=="forking   ")
ks.test(torus$V8, bottle$V8) #!
ks.test(torus$V9, bottle$V9)
ks.test(torus$V10, bottle$V10) #!
ks.test(torus$V11, bottle$V11)
ks.test(torus$V12, bottle$V12)
ks.test(torus$V13, bottle$V13)

torus <- subset(m, V1=="torus  " & V2=="comments  ")
bottle <- subset(m, V1=="bottle " & V2=="comments  ")
ks.test(torus$V8, bottle$V8)
ks.test(torus$V9, bottle$V9)
ks.test(torus$V10, bottle$V10) #!
ks.test(torus$V11, bottle$V11)
ks.test(torus$V12, bottle$V12)
ks.test(torus$V13, bottle$V13)

torus <- subset(m, V1=="torus  " & V2=="star      ")
bottle <- subset(m, V1=="bottle " & V2=="star      ")
ks.test(torus$V8, bottle$V8) #!
ks.test(torus$V9, bottle$V9)
ks.test(torus$V10, bottle$V10) #!
ks.test(torus$V11, bottle$V11)
ks.test(torus$V12, bottle$V12)
ks.test(torus$V13, bottle$V13)



