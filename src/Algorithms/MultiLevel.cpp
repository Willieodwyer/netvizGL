//
// Created by william on 30/01/17.
//

#include "../../inc/Algorithms/MultiLevel.h"
MultiLevel::MultiLevel(Graph *g) : Algorithm(g) {

}

void MultiLevel::apply() {
  popu = 0;
  int //lin = (int) (Math.random()*variables.links);
      lin = 0; // First link or random link
  double vv = graph->numVertices;

//  double max_x0 = -1000; //Borders
//  double min_x0 = 1000;
//  double max_y0 = -1000;
//  double min_y0 = 1000;

  double dir = (double) M_PI / vv;
  int lev = 0;

  level = 1;
  double disp = 10.0 / vv;
  tol = sqrt(graph->numVertices);
  tol = 0.1;

  bool check = false;

  //*************************************

  int a1 = 0, a2 = 0;
  int *ini = new int[2];

  a1 = lists[0][lin];
  a2 = lists[1][lin];

  ini[0] = a1;
  ini[1] = a2;

  seen_links.push_back(ini);

  graph->vertices[a1]->posX = cos((double) 0) * 0.025;
  graph->vertices[a1]->posY = sin((double) 0) * 0.025;

  popu++;
  vertices[a1] = 1;
  degree_met[a1]--;

  graph->vertices[a2]->posX = cos((double) 1.0) * 0.025;
  graph->vertices[a2]->posY = sin((double) 1.0) * 0.025;
  popu++;
  vertices[a2] = 1;
  degree_met[a2]--;

  //k=0.5/popu;
  k=di/popu;

//  for (int i = 0; i < 2; i++) {
//    if (graph->vertices[ini[i]]->posX > max_x0)
//      max_x0 = graph->vertices[ini[i]]->posX;
//    if (graph->vertices[ini[i]]->posX < min_x0)
//      min_x0 = graph->vertices[ini[i]]->posX;
//
//    if (graph->vertices[ini[i]]->posY > max_y0)
//      max_y0 = graph->vertices[ini[i]]->posY;
//    if (graph->vertices[ini[i]]->posY < min_y0)
//      min_y0 = graph->vertices[ini[i]]->posY;
//  }

  hypotenuse = (abs(max_x0 - min_x0) + abs(max_y0 - min_y0));

//  System.out.println("Starts algorithm parallel: ... ");
  int t = 0;

//  System.out.println(variables.v + " Vertices and  " + variables.links + " links  exist!");
  double di = 0.5;
  double ti = 0.1;
  double ti_lev = ti;
  double ti_rate = 0.9;
  double k_rate = 0.99;
  double rnd = round(sqrt(vv));
  double last = 0;
  while (!check) {

    k = di / ((popu));
    ti = ti * ti_rate;

    force_x = new double[graph->numVertices];
    force_y = new double[graph->numVertices];
    t++;

    energy1 = 0;
    ////forc(t, (int) variables.links, 0); /////////////////


    bool maxmin = true;
    for (int i = 0; i < graph->numVertices; i++) {
      if (graph->vertices[i] != 0) {
        graph->vertices[i]->posX = graph->vertices[i]->posX + (force_x[i] * ti);
        graph->vertices[i]->posY = graph->vertices[i]->posY + (force_y[i] * ti);

        if (maxmin) {
          max_x0 = graph->vertices[i]->posX;
          min_x0 = graph->vertices[i]->posX;
          max_y0 = graph->vertices[i]->posY;
          min_y0 = graph->vertices[i]->posY;
          maxmin = false;
        }

        if (graph->vertices[i]->posX > max_x0)
          max_x0 = graph->vertices[i]->posX;
        if (graph->vertices[i]->posX < min_x0)
          min_x0 = graph->vertices[i]->posX;
        if (graph->vertices[i]->posY > max_y0)
          max_y0 = graph->vertices[i]->posY;
        if (graph->vertices[i]->posY < min_y0)
          min_y0 = graph->vertices[i]->posY;
      }
    }
    //hypotenuse = Math.sqrt(Math.pow(max_x0-min_x0, 2)+Math.pow(max_y0-min_y0, 2));
    hypotenuse = (abs(max_x0 - min_x0) + abs(max_y0 - min_y0));

    if ((abs(energy1 - energy0) < tol * disp && popu == vv) /*last>=rnd*/ ) {
      int_pr = 0;
      if(!check){
        check = true;
      }
    }

    if (abs(energy1 - energy0) < tol * disp  /*(t % rnd)==0*/) {
      di = di * k_rate; // mesh

      for (int i = 0; i < graph->numVertices; i++) {
        if (vertices[i] == level) { //level of the nodes
          double s = 0;
          //double chunk = (Math.PI*2.0)/(double)variables.node_degree[i];
          double chunk = (M_PI * 2.0) / (double) degree_met[i];
          for (int j = 0; j < variables.links; j++) {
            a1 = lists[0][j];
            a2 = lists[1][j];

            /*a1 = lists.get(j)[0];
            a2 = lists.get(j)[1];*/

            /*a1=matx[0][j];
            a2=matx[1][j];*/


            //chunk = Math.random()*Math.PI*2;
            //disp=Math.random()*(40.0/(double)variables.v);
            if ((a1 == i && vertices[a2] == 0)) { // If equal to zero means unvisited

              vertices[a2] = level + 1;

              variables.pos[0][a2] = variables.pos[0][i] + (Math.cos(chunk * s) * disp);
              variables.pos[1][a2] = variables.pos[1][i] + (Math.sin(chunk * s) * disp);
              s += 1;
              popu++;
              degree_met[a2]--;
            } else if (a2 == i && vertices[a1] == 0) {

              vertices[a1] = level + 1;

              variables.pos[0][a1] = variables.pos[0][i] + (Math.cos(chunk * s) * disp);
              variables.pos[1][a1] = variables.pos[1][i] + (Math.sin(chunk * s) * disp);
              s += 1;
              popu++;
              degree_met[a1]--;
            }
          }
        } // if vertice -> level
      }  // for loop
      level++;
      //k=di/Math.sqrt(popu);
      //System.out.println(popu+" "+k+" "+ti+" "+hypotenuse);
      ti = ti_lev;
      //ti_lev = ti_lev - (20.0/vv);
      lev++;
      //tol=tol*1.02;
      int_pr = 0;
    }
    int_pr++;
    energy0 = energy1;
    //tol = tol*0.9;
    if (popu == vv)
      last++;
    if (check)
      break;
  }
}

void forc(int t, int e, int s)
{

  ch1=Math.sqrt((double) variables.v); //Makes sure it's not too long in either axis
  ch2=ch1*5;

  /*ch1=2;
  ch2=ch1*5;*/

  /*if(hypotenuse>1.0)
  {
      ch1=ch1*((hypotenuse)*(1/hypotenuse));
      ch2=ch2*((hypotenuse)*(1/hypotenuse));
  }*/
  if(hypotenuse<0.1)
  {
    ch1=ch1*(0.1);
    ch2=ch2*(0.1);
  }


  for(int j=s;j<e;j++)
  {

    int v1 = lists[0][j]; // List of the edges that you have
    int v2 = lists[1][j]; // EDge list

    /*int v1 = lists.get(j)[0];
    int v2 = lists.get(j)[1];*/

    int v1=matx[0][j];
    int v2=matx[1][j];


    if(vertices[v1]!=0 && vertices[v2]!=0   )
    {
      double rep=0;
      double att=0;
      force=0;
      com++;
      double dis=Math.abs(variables.pos[0][v1]-variables.pos[0][v2])+Math.abs(variables.pos[1][v1]-variables.pos[1][v2]);
      if(dis<0.00000000002)
        dis=0.00000000002;
      double cos=((variables.pos[0][v2]-variables.pos[0][v1])/dis);
      double sin=((variables.pos[1][v2]-variables.pos[1][v1])/dis);


      rep = ((k*k)/-dis);  //Takes care of the distances making sure they're not small
      att = dis*dis/k;

      /*if(popu==variables.v)
          System.out.println(dis+"  "+rep+" "+att);*/



      force= rep+att;

      if(force>0 && force>hypotenuse/ch1)
        force=hypotenuse/ch1;
      if(force<0 && Math.abs(force)>hypotenuse/ch2)
        force=-hypotenuse/ch2;

      energy1 +=force*2;

      double x_t=cos*force;
      double y_t=sin*force;

      force_x[v1]+=x_t;
      force_y[v1]+=y_t;


      force_x[v2]-=x_t;
      force_y[v2]-=y_t;

      /*force_x[v1]+=cos*force;
      force_y[v1]+=sin*force;


      force_x[v2]-=cos*force;
      force_y[v2]-=sin*force;*/


      //*********replusion for nighbures
    }
  }

  /*	for(int i=0;i<variables.v;i++)
      {
          //for(int j=i+1;j<variables.v;j++)
          for(int b=0;b<progress;b++)
          {
              int j= (int) Math.random()*variables.v;
              if(vertices[i]!=0 && vertices[j]!=0 && !mat[i][j] && i!=j)
              {

                  double dis=Math.abs(variables.pos[0][i]-variables.pos[0][j])+Math.abs(variables.pos[1][i]-variables.pos[1][j]);
                  double cos=((variables.pos[0][j]-variables.pos[0][i])/dis);
                  double sin=((variables.pos[1][j]-variables.pos[1][i])/dis);

                  double force = (k*k)/(-dis);

                  if(Math.abs(force)>hypotenuse/1)
                      force=-(double) hypotenuse/1;

                  force_x[i]+=cos*force;
                  force_y[i]+=sin*force;

                  force_x[j]-=cos*force;
                  force_y[j]-=sin*force;


                  energy1 += force*2;
              }
          }
      }*/


}
