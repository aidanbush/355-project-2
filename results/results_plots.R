stuff <- read.table("/home/aidan/Documents/school/current/355/projects/355-project-2/results/data.csv", header = TRUE, sep = ",")

ymax <- max(round((stuff$explore * 1.25)))
xmax <- length(stuff$explore)
turns = seq(1,xmax)

plot(1, type='n', xlim=c(1, xmax), ylim=c(0, ymax), xlab='Our turn', ylab='States explored (Millions)')
lines(stuff$explore, type='o', col="blue", lwd=1, pch=1)

arrows(turns, stuff$explore, turns, stuff$explore + stuff$explore.stdev, length=0.05, angle=90)
arrows(turns, stuff$explore, turns, stuff$explore - stuff$explore.stdev, length=0.05, angle=90)

# create

ymax <- max(round(stuff$create * 1.25))
xmax <- length(stuff$create)
turns = seq(1,xmax)

plot(1, type='n', xlim=c(1, xmax), ylim=c(0, ymax), xlab='Our turn', ylab='States created (Millions)')
lines(stuff$create, type='o', col="blue", lwd=1, pch=1)

arrows(turns, stuff$create, turns, stuff$create + stuff$create.stdev, length=0.05, angle=90)
arrows(turns, stuff$create, turns, stuff$create - stuff$create.stdev, length=0.05, angle=90)

# depth

ymax <- max(round(stuff$depth * 1.25))
xmax <- length(stuff$depth)
turns = seq(1,xmax)

plot(1, type='n', xlim=c(1, xmax), ylim=c(0, ymax), xlab='Our turn', ylab='Max depth')
lines(stuff$depth, type='o', col="blue", lwd=1, pch=1)

arrows(turns, stuff$depth, turns, stuff$depth + stuff$depth.stdev, length=0.05, angle=90)
arrows(turns, stuff$depth, turns, stuff$depth - stuff$depth.stdev, length=0.05, angle=90)
