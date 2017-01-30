//
// Created by william on 30/01/17.
//

#include "../../inc/Graphs/MatrixMarketGraph.h"
#include "../../inc/Graphs/mmio.h"
#include "../../src/Graphs/mmio.c"


MatrixMarketGraph::MatrixMarketGraph(char *filePath) : Graph(filePath) {

}
// Taken from the example @ http://math.nist.gov/MatrixMarket/mmio-c.html
void MatrixMarketGraph::read(char *filePath) {
  int ret_code;
  MM_typecode matcode;
  FILE *f;
  int rows, cols, edges;
  int i, *I, *J;
  double *val;

  if ((f = fopen("/home/william/netvizGL/Graphs/MatrixMarket/fxm3_6.mtx", "r")) == NULL)
    fprintf(stderr,"File not Opened");

  if (mm_read_banner(f, &matcode) != 0) {
    printf("Could not process Matrix Market banner.\n");
    exit(1);
  }

  /*  This is how one can screen matrix types if their application */
  /*  only supports a subset of the Matrix Market data types.      */
  if (!mm_is_coordinate(matcode)) {
    printf("Sorry, this application only supports");
    printf("Market Market type: [%s]\n", mm_typecode_to_str(matcode));
    exit(1);
  }

  /* find out size of sparse matrix .... */

  if ((ret_code = mm_read_mtx_crd_size(f, &rows, &cols, &edges)) != 0)
    exit(1);


  /* reseve memory for matrices */

  I = (int *) malloc(edges * sizeof(int));
  J = (int *) malloc(edges * sizeof(int));
  val = (double *) malloc(edges * sizeof(double));


  /* NOTE: when reading in doubles, ANSI C requires the use of the "l"  */
  /*   specifier as in "%lg", "%lf", "%le", otherwise errors will occur */
  /*  (ANSI C X3.159-1989, Sec. 4.9.6.2, p. 136 lines 13-15)            */

  for (i = 0; i < edges; i++) {
    fscanf(f, "%d %d %lg\n", &I[i], &J[i], &val[i]);
    I[i]--;  /* adjust from 1-based to 0-based */
    J[i]--;
  }

  if (f != stdin) fclose(f);

  /************************/
  /* now write out matrix */
  /************************/

  mm_write_banner(stderr, matcode);
  mm_write_mtx_crd_size(stderr, rows, cols, edges);
  for (i = 0; i < edges; i++)
    fprintf(stderr, "%d %d %20.19g\n", I[i] + 1, J[i] + 1, val[i]);
}

void MatrixMarketGraph::draw() {

}

void MatrixMarketGraph::update() {

}
