# CytoCascade
This project is about mapping how certain proteins (cytokines) cause the release of eachother in mouse cells. The initial data was the raw RNA counts from treating a mouse with ~80 different cytokines for 100K cells of ~20 different types. The data was quality-controlled, a graph of all cytokines relationships was produced, and then an algorithm was used to remove the indirect edges from the graph.
![](https://github.com/mohammedehab2002/CytoCascade/blob/main/reduced_graph.svg)
Furthermore, for every edge, we looked into how many genes that are produced by the second cytokine is also produced by the first cytokine to measure the strength of the edge, and the following heatmap was generated.
![](https://github.com/mohammedehab2002/CytoCascade/blob/main/intersection_table.png)
