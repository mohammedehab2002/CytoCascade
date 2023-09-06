library(Seurat)
load("~/QC.RData")
cytokines <- unique(lig_seurat@meta.data$sample_display)
cytokines <- cytokines[!cytokines=="PBS"]
Idents(lig_seurat) <- "sample_display"
GetSignature <- function(c) {
  df <- FindMarkers(lig_seurat,ident.1=c,min.pct=0.25,verbose=FALSE,min.cells.feature=0,min.cells.group=0)
  return(rownames(df))
}
GetIntersection <- function(r) {
  c1 <- r[["c1"]]
  c2 <- r[["c2"]]
  return(length(intersect(sig[[c1]],sig[[c2]]))/length(sig[[c2]]))
}
sig <- list()
for (c in cytokines) {
  sig[[c]] <- GetSignature(c)
}
df <- read.csv("reduced_graph.txt")
df$intersection <- apply(df,1,GetIntersection)
write.csv(df,file="edges.csv")