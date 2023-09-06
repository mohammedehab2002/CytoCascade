library(Seurat)
library(readxl)
load("~/cytokines_dictionary_sub.RData")
cytokines <- unique(lig_seurat@meta.data$sample_display)
cell_types <- unique(lig_seurat@meta.data$celltype_display)
map <- read_excel("cytokine_map.xlsx")
cyt_genes <- c()
for (c in cytokines) {
  cyt_genes <- append(cyt_genes,map$"Mouse gene symbol"[map$Cytokine==c][[1]])
}
lig_seurat <- subset(lig_seurat,subset=(nFeature_RNA>200 & nFeature_RNA<2500 & percent_mito<5))
lig_seurat <- NormalizeData(lig_seurat)
lig_seurat <- ScaleData(lig_seurat,features=cyt_genes)
save(lig_seurat,file="QC.RData")