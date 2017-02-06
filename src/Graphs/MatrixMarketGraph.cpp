//
// Created by william on 30/01/17.
//

#include <sys/time.h>
#include <zconf.h>
#include "../../inc/Graphs/MatrixMarketGraph.h"
#include "../../inc/Graphs/mmio.h"
#include "../../src/Graphs/mmio.c"

MatrixMarketGraph::MatrixMarketGraph(char *filePath) : Graph(filePath) {
  read(filePath);
}

// Taken from the example @ http://math.nist.gov/MatrixMarket/mmio-c.html
void MatrixMarketGraph::read(char *filePath) {
  int ret_code;
  MM_typecode matcode;
  FILE *f;
  int rows, cols, edgs;
  int i, *I, *J;

  if ((f = fopen(filePath, "r")) == NULL){
    fprintf(stderr, "File not Opened");
    return;
  }



  if (mm_read_banner(f, &matcode) != 0) {
    printf("\nCould not process Matrix Market banner.\n");
    exit(1);
  }

  /*  This is how one can screen matrix types if their application */
  /*  only supports a subset of the Matrix Market data types.      */
//  if (!mm_is_coordinate(matcode) || mm_is_integer(matcode)) {
  if (!mm_is_coordinate(matcode)) {
    printf("Sorry, this application only supports graphs that are:");
    printf("Matrix Market type: [%s]\n", MM_COORDINATE_STR);
    printf("and not: [%s]\n", MM_INT_STR);
    exit(1);
  }

  /* find out size of sparse matrix .... */
  ret_code = mm_read_mtx_crd_size(f, &rows, &cols, &edgs);

  if (ret_code != 0)
    exit(1);

  /* reseve memory for matrices */
  I = (int *) malloc(edgs * sizeof(int));
  J = (int *) malloc(edgs * sizeof(int));

  for (i = 0; i < edgs; i++) {
    fscanf(f, "%d %d\n", &I[i], &J[i]);
    I[i]--;  /* adjust from 1-based to 0-based */
    J[i]--;
  }

  fclose(f);

  fprintf(stdout,"\n%s\n",filePath);
  mm_write_banner(stdout, matcode);
  mm_write_mtx_crd_size(stdout, rows, cols, edgs);
//  for (i = 0; i < edgs; i++)
//    fprintf(stderr, "%d %d\n", I[i] + 1, J[i] + 1);

  numVertices = (unsigned long) rows;

  //Initialise Edges Matrix
  adjacencyMatrix = new int *[numVertices];
  for (int i = 0; i < numVertices; ++i) {
    adjacencyMatrix[i] = new int[numVertices];
    for (int j = 0; j < numVertices; ++j) {
      adjacencyMatrix[i][j] = 0;
    }
  }

  //Initialise all the visitedVertices and give them a random colour and position
  struct timeval time;
  gettimeofday(&time, NULL);
  srand(hash3((unsigned int) time.tv_sec, (unsigned int) time.tv_usec, (unsigned int) getpid()));
  for (int j = 0; j < numVertices; ++j) {
    vertices.push_back(new Vertex(((double) rand() / RAND_MAX) * numVertices - numVertices / 2,
                                  ((double) rand() / RAND_MAX) * numVertices - numVertices / 2,
                                  0));
    vertices[j]->setColour(((double) rand() / (RAND_MAX)),
                           ((double) rand() / (RAND_MAX)),
                           ((double) rand() / (RAND_MAX)));
  }

  //Check for same positions
  for (int i = 0; i < numVertices; ++i) {
    for (int j = 0; j < numVertices; ++j) {
      if (vertices[i]->posX == vertices[j]->posX && i != j
          && vertices[i]->posY == vertices[j]->posY)
        fprintf(stderr, "Warning: duplicate positions generated @ %d\n", i);
    }
  }

  //Attach points to each other
  for (int k = 0; k < edgs; ++k) {
    vertices[I[k]]->attachPoint(vertices[J[k]]);
    adjacencyMatrix[I[k]][J[k]] = 1;
    adjacencyMatrix[J[k]][I[k]] = 1;
  }

  int *temp = new int[2];
  edgeList.clear();
  for (int i = 0; i < numVertices; ++i) {
    for (int j = 0; j < i; ++j) {
      if (adjacencyMatrix[i][j] == 1){
        temp[0] = j;
        temp[1] = i;
        edgeList.push_back(temp);
        temp = new int[2];
      }
    }
  }
  numEdges = edgeList.size();

  for (int i = 0; i < edgeList.size(); ++i) {
    fprintf(stderr,"%d,%d\n",edgeList[i][0],edgeList[i][1]);
  }
}

void MatrixMarketGraph::draw() {
  for (int i = 0; i < numVertices; ++i) {
    vertices[i]->drawPoints();
  }
  for (int i = 0; i < numVertices; ++i) {
    vertices[i]->drawText();
  }
}

void MatrixMarketGraph::update() {
  for (int i = 0; i < numVertices; ++i) {
    vertices[i]->update();
  }
}
MatrixMarketGraph::~MatrixMarketGraph() {
  fprintf(stderr,"Deleting MatrixGraph\n");
}
