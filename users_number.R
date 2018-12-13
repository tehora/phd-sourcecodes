library("plotly")

plotly_github = function(wektor, zbior_danych, nr_zmiennej, nr_koloru, log) {
    nazwa <- colnames(zbior_danych)[nr_zmiennej]
    wektor <- plot_ly(type = "scatter",
                      mode = "lines", # wykres liniowy
                      x = zbior_danych$data,
                      y = zbior_danych[[nr_zmiennej]], # wybór zbioru wartości
                      line = list(color=colors[nr_koloru]), # kolor punktów
                      name = nazwa # nazwa zmiennej
                      ) %>%
        add_trace(x = launch, y= c(min(zbior_danych[[nr_zmiennej]]),max(zbior_danych[[nr_zmiennej]])),  mode = "lines", line=list(color="red"), name="Launch date") %>%
        #add_trace(x = watching, y= c(min(zbior_danych[[nr_zmiennej]]),max(zbior_danych[[nr_zmiennej]])),  mode = "lines", line=list(color="magenta"), name="Stars day") %>%
        layout(xaxis = msc, # zapisany format
               yaxis = list(title = nazwa, # nazwa osi rzędnych,
                            nticks = 10, # liczba osi
                            type = ifelse(log == 1, "log", ""),
                            ticks = "outside") # na zewnątrz      
              )             
}

plotly_github_more = function(wektor, zbior_danych, nr_zmiennej, nr_koloru, log, zmienne_dodatkowe, nazwa_wykresu) {
    nazwa <- colnames(zbior_danych)[nr_zmiennej]
    wektor <- plot_ly(type = "scatter",
                      mode = "lines", # wykres liniowy
                      x = zbior_danych$data,
                      y = zbior_danych[[nr_zmiennej]], # wybór zbioru wartości
                      line = list(color=colors[nr_koloru]), # kolor punktów
                      name = nazwa # nazwa zmiennej
                      )
    for (i in zmienne_dodatkowe) {
            line_name <- colnames(zbior_danych)[i]
            wektor <- wektor %>% add_trace(y = zbior_danych[[i]], line = list(color = colors[(i/2)]), name=line_name)
        }     
    wektor <- wektor %>% add_trace(x = launch, y= c(min(zbior_danych[[nr_zmiennej]]),max(zbior_danych[[nr_zmiennej]])),  mode = "lines", line=list(color="red"), name="Launch date")%>%
        layout(xaxis = msc, # zapisany format
               yaxis = list(title = nazwa_wykresu, # nazwa osi rzędnych,
                            nticks = 10, # liczba osi
                            type = ifelse(log == 1, "log", ""),
                            ticks = "outside"), # na zewnątrz
               legend = c(list(x=.1, y=.95))
              )             
}

# definicja stylow dla wykresow

msc <- list(title = "date", # nazwa osi odciętych
            tickformat = "%y/%m/%d", # format daty rrr/mm/dd
            tick0 = "2007-10-19", # początek
            dtick = "M6", #odstęp
            ticks = "outside" # na zewnątrz
            )

                                        # definicja kolorow

colors <- c("forestgreen", "palegreen", "royalblue", "dodgerblue", "gold", "orange", "yellow", "lightgoldenrod", "bisque")

# Specjalna data
launch <- as.Date.character("2008-04-10")
    
# Rejestracje
m <- read.table("date_number_daily.csv",  sep=";", header=T, as.is=T)

m$data <- as.Date.character(m$data)
nazwy <- c("Raw", "Cumulative")

colnames(m) <- c("data", nazwy[1], nazwy[2]) #zmiana nazwy kolumn

w <- list(NULL) #lista na wykresy

# przygotowanie pod logarytmy
for (i in 2:3) {
    m[[i]][m[[i]]==0] <- 1
}    

# przyciecie do 31.12.2014 max
m <- m[1:2633,]

w <- plotly_github(w, m, 2, 1, 0)
x <- plotly_github(x, m, 3, 1, 0)
y <- plotly_github(y, m, 2, 1, 1)
z <- plotly_github(z, m, 3, 1, 1)

subplot(w, x, y, z, # łączenie rysunków
        nrows = 2, shareX= TRUE, # liczba
        heights = c(0.45, 0.45), widths = c(0.48, 0.48), 
        titleY = TRUE, # zachowanie nazw osi rzędnych
        titleX = FALSE # zachowanie nazw osi odciętych
        ) %>%      
  layout(separators = ".", # separator dziesiętny 
         hovermode = "x", # sposób wyświetlania
         showlegend = FALSE, # brak legendy
         title = "Daily registrations on GitHub" # tytuł
         )

# Starring

o <- read.table("date_stars_daily.csv",  sep=";", header=T, as.is=T)

watching <- as.Date.character("2012-08-06")
o$data <- as.Date.character(o$data)
nazwy <- c("Raw", "Cumulative")

colnames(m) <- c("data", nazwy[1], nazwy[2]) #zmiana nazwy kolumn

w <- list(NULL) #lista na wykresy

# przygotowanie pod logarytmy
for (i in 2:3) {
    o[[i]][o[[i]]==0] <- 1
}    

# przyciecie do 31.12.2014 max
o <- o[1:2633,]

w <- plotly_github(w, o, 2, 1, 0)
x <- plotly_github(x, o, 3, 1, 0)
y <- plotly_github(y, o, 2, 1, 1)
z <- plotly_github(z, o, 3, 1, 1)

subplot(w, x, y, z, # łączenie rysunków
        nrows = 2, shareX= TRUE, # liczba
        heights = c(0.45, 0.45), widths = c(0.48, 0.48), 
        titleY = TRUE, # zachowanie nazw osi rzędnych
        titleX = FALSE # zachowanie nazw osi odciętych
        ) %>%      
  layout(separators = ".", # separator dziesiętny 
         hovermode = "x", # sposób wyświetlania
         showlegend = FALSE, # brak legendy
         title = "Stars given on GitHub" # tytuł
         )

# Following

o <- read.table("date_follow_daily.csv",  sep=";", header=T, as.is=T)

watching <- as.Date.character("2014-01-01")
o$data <- as.Date.character(o$data)
nazwy <- c("Raw", "Cumulative")

colnames(m) <- c("data", nazwy[1], nazwy[2]) #zmiana nazwy kolumn

w <- list(NULL) #lista na wykresy

# przygotowanie pod logarytmy
for (i in 2:3) {
    o[[i]][o[[i]]==0] <- 1
}    

# przyciecie do 31.12.2014 max
o <- o[1:2633,]

w <- plotly_github(w, o, 2, 1, 0)
x <- plotly_github(x, o, 3, 1, 0)
y <- plotly_github(y, o, 2, 1, 1)
z <- plotly_github(z, o, 3, 1, 1)

subplot(w, x, y, z, # łączenie rysunków
        nrows = 2, shareX= TRUE, # liczba
        heights = c(0.45, 0.45), widths = c(0.48, 0.48), 
        titleY = TRUE, # zachowanie nazw osi rzędnych
        titleX = FALSE # zachowanie nazw osi odciętych
        ) %>%      
  layout(separators = ".", # separator dziesiętny 
         hovermode = "x", # sposób wyświetlania
         showlegend = FALSE, # brak legendy
         title = "Following on GitHub" # tytuł
         )

# Wspolpraca
c <- read.table("date_collab_daily.csv",  sep=";", header=T, as.is=T)

c$data <- as.Date.character(c$data)
nazwy <- c("Raw_Issues_Opened", "Cumulative_Issues_Opened","Raw_Issues_Closed", "Cumulative_Issues_Closed", "Raw_PR_Opened", "Cumulative_PR_Opened", "Raw_PR_Closed", "Cumulative_PR_Closed", "Raw_Comments", "Cumulative_Comments")

colnames(c) <- c("data", nazwy[1], nazwy[2], nazwy[3], nazwy[4], nazwy[5], nazwy[6], nazwy[7], nazwy[8], nazwy[9], nazwy[10]) #zmiana nazwy kolumn

# przygotowanie pod logarytmy
for (i in 2:11) {
    c[[i]][c[[i]]==0] <- 1
}    

# przyciecie do 31.12.2014 max
c <- c[1:2633,]

# Komentarze

w <- plotly_github(w, c, 10, 1, 0)
x <- plotly_github(x, c, 11, 1, 0)
y <- plotly_github(y, c, 10, 1, 1)
z <- plotly_github(z, c, 11, 1, 1)

subplot(w, x, y, z, # łączenie rysunków
        nrows = 2, shareX= TRUE, # liczba
        heights = c(0.45, 0.45), widths = c(0.48, 0.48), 
        titleY = TRUE, # zachowanie nazw osi rzędnych
        titleX = FALSE # zachowanie nazw osi odciętych
        ) %>%      
  layout(separators = ".", # separator dziesiętny 
         hovermode = "x", # sposób wyświetlania
         showlegend = FALSE, # brak legendy
         title = "Comments written on GitHub, daily" # tytuł
         )

# Pullrequests + issues

zmienne1 <- c(4,6,8)
zmienne2 <- c(5,7,9)

w <- plotly_github_more(w, c, 2, 1, 0, zmienne1, "Number of Events")
w
z <- plotly_github_more(z, c, 3, 1, 0, zmienne2, "Number of Events")
z
w <- plotly_github_more(w, c, 2, 1, 1, zmienne1, "Number of Events")
w
z <- plotly_github_more(z, c, 3, 1, 1, zmienne2, "Number of Events")
z

# Repozytoria

n <- read.table("date_repos_daily.csv",  sep=";", header=T, as.is=T)
n$data <- as.Date.character(n$data)
nazwy <- c("Raw_Repositories", "Cumulative_Repositories", "Raw_Forks", "Cumulative_Forks")

colnames(n) <- c("data", nazwy[1], nazwy[2], nazwy[3], nazwy[4]) #zmiana nazwy kolumn

# przygotowanie pod logarytmy
for (i in 2:5) {
    n[[i]][n[[i]]==0] <- 1
}    

# przyciecie do 31.12.2014 max
n <- n[1:2633,]

forks <- c(4)
forks_c <- c(5)

w <- plotly_github_more(w, n, 2, 1, 0, forks, "Repositories")
w
z <- plotly_github_more(z, n, 3, 1, 0, forks_c, "Repositories")
z
w <- plotly_github_more(w, n, 2, 1, 1, forks, "Repositories")
w
z <- plotly_github_more(z, n, 3, 1, 1, forks_c, "Repositories")
z

