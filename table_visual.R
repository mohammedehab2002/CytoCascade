library(gplots)
replace_unicode_patterns <- function(input_string) {
  pattern <- "<U\\+([[:xdigit:]]{4})>"
  matches <- gregexpr(pattern, input_string)
  if (any(unlist(matches)>0)) {
    hex_code_points <- regmatches(input_string, matches)
    for (i in 1:length(hex_code_points)) {
      hex_code <- substr(hex_code_points[[i]],4,7)
      unicode_char <- intToUtf8(as.integer(paste0("0x",hex_code)))
      input_string <- gsub(paste0("<U\\+",hex_code,">"),unicode_char,input_string)
      print(input_string)
      print(hex_code)
      print(unicode_char)
    }
  }
  return(input_string)
}
df <- read.csv("edges.csv")
mat <- xtabs(intersection ~ c1+c2,data=df)
heatmap.2(
  mat,
  Rowv=FALSE,
  Colv=FALSE,
  dendrogram="none",
  scale="none",
  key=TRUE,
  density.info="none",
  trace="none",
  margins=c(5,5),
  col=colorRampPalette(c("white","darkblue"))(100),
  labRow=replace_unicode_patterns(rownames(mat)),
  labCol=replace_unicode_patterns(colnames(mat)),
  notecex=0.7,
  main="Signature Intersection"
)