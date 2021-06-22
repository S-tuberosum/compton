library(tidyverse)
library(stringr)

setwd(dirname(rstudioapi::getActiveDocumentContext()$path))

data <- read.csv("magnet_KEKB.csv")

# renaming and adding columns 
data <- cbind("comp" = NA, data)
colnames(data)[2] <- "name"
colnames(data)[3] <- "center_z"
colnames(data)[4] <- "center_x"
colnames(data)[5] <- "center_y"
colnames(data)[7] <- "length"
colnames(data)[9] <- "angle"
data$"rin(z-in)" <- 0.1
data$"rin(z-out)" <- 0.1
data$"dout" <- 0.6
data$"B" <- 0
data$"gradient" <- 12

# rearranging columns
data <- data[c("comp", "name", "center_x", "center_y", "center_z", "rin(z-in)", 
               "rin(z-out)", "dout", "length", "angle", "B", "gradient")]

data$center_z <- strsplit(data$center_z, "\\s+")

for(x in 1:length(data$name))
{
  if(lengths(data$center_z[x]) == 2)
  {
    data$name[x] <- paste(data$name[x], data$center_z[[x]][1], sep = "")
    data$center_z[x] <- data$center_z[[x]][2]
  }
}

data$center_z <- as.numeric(data$center_z)

# filtering unneeded components, mutating some columns 
data <- data %>% 
  filter(!is.na(center_x), !str_detect(name, "M\\w+"), 
         !str_detect(name, "Z\\w+"), !str_detect(name, "S\\w+")) %>%
  mutate(angle = angle*pi/180, center_x = center_x + sin(angle)*(length/2), center_z = center_z + cos(angle)*(length/2)) 

data$comp <- ifelse(str_starts(data$name, "Q"), "QF", NA)
data$comp <- ifelse(str_starts(data$name, "B"), "DB", data$comp)
data$angle <- data$angle*-1

for(x in 1:length(data$name))
{
  if(data$length[x] == 0)
    {
      data$length[x] <- 0.01
    }
}

write.table(data, "./full_magnet.dat", append = FALSE, sep = "  ", dec = ".",
            row.names = FALSE, col.names = TRUE, quote = FALSE)


  