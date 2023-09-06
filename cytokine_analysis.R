library(Seurat)
library(readxl)
load("~/QC.RData")
sink("cytokine_graph_stat.txt")
cytokines <- unique(lig_seurat@meta.data$sample_display)
cytokines <- cytokines[!cytokines=="PBS"]
cell_types <- unique(lig_seurat@meta.data$celltype_display)
map <- read_excel("cytokine_map.xlsx")
for (cell in cell_types) {
  Idents(lig_seurat) <- "celltype_display"
  s_cell <- subset(lig_seurat,idents=cell)
  for (c1 in cytokines) {
    Idents(s_cell) <- "sample_display"
    if (c1 %in% Idents(s_cell)) {
      df <- FindMarkers(s_cell,ident.1=c1,min.pct=0.51,only.pos=TRUE,slot="scale.data",min.cells.feature=0,min.cells.group=0,verbose=FALSE)
      for (gene in rownames(df)) {
        if (df[gene,"p_val_adj"]>=0.05) {
          next
        }
        if (table(s_cell@meta.data$sample_display)[c1]==1) {
          s_cyto <- subset(s_cell,idents=c1)
          if (s_cyto[["RNA"]]@counts[gene,]<2) {
            next
          }
        }
        cat(paste(c1,cell,map$Cytokine[map$"Mouse gene symbol"==gene][[1]],sep=","))
        cat("\n")
      }
    }
  }
}