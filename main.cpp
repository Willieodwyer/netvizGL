#include <GL/glut.h>

void sendHELP()
{
  glClear(GL_COLOR_BUFFER_BIT); // clear the window

  // set line width, in pixels
  glLineWidth(4.0);

  // Draw H
  glBegin(GL_LINES);
    glColor3f(1.0, 1.0, 1.0); // set color to white
    glVertex3f(-0.8, -0.6 ,0.0);
    glVertex3f(-0.8, 0.6, 0.0);
    glVertex3f(-0.4, 0.6, 0.0);
    glVertex3f(-0.4, -0.6, 0.0);
    glVertex3f(-0.8, 0.0, 0.0);
    glVertex3f(-0.4, 0.0, 0.0);
  glEnd();

  // Draw E
  glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0); // set color to red
    glVertex3f(-0.3, -0.6 ,0.0);
    glVertex3f(-0.3, 0.6, 0.0);
    glVertex3f(-0.3, 0.6 , 0.0);
    glVertex3f(0.0, 0.6 , 0.0);
    glVertex3f(-0.3, 0.0 , 0.0);
    glVertex3f(0.0, 0.0 , 0.0);
    glVertex3f(-0.3, -0.6 , 0.0);
    glVertex3f(0.0, -0.6 , 0.0);
  glEnd();

  //Draw L
  glBegin(GL_LINES);
    glColor3f(0.0, 1.0, 0.0); // set color to red
    glVertex3f(0.1, -0.6 ,0.0);
    glVertex3f(0.1, 0.6, 0.0);
    glVertex3f(0.1, -0.6 , 0.0);
    glVertex3f(0.4, -0.6 , 0.0);
  glEnd();

  //Draw P

  glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 1.0); // set color to red
    glVertex3f(0.5, 0.6 ,0.0);
    glColor3f(1.0,1.0,0.0);
    glVertex3f(0.9, 0.6, 0.0);
    glColor3f(1.0,0.0,0.0);
    glVertex3f(0.5, 0.0 , 0.0);
    glVertex3f(0.9, 0.0 , 0.0);
    glVertex3f(0.5, 0.6 , 0.0);
    glColor3f(1.0,1.0,0.0);
    glVertex3f(0.5, -0.6 , 0.0);
    glVertex3f(0.9, 0.6 , 0.0);
    glVertex3f(0.9, -0.0 , 0.0);
  glEnd();


  glFlush();
}

// input keyboard function to quit with q or Q.
void quit(unsigned char key, int x, int y)
{
  if (key == 'q' || key == 'Q')
    exit(0);
}

int main (int argc, char** argv)
{
  glutInit(&argc, argv);        // initialize glut
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE); // RGB, single buffer mode
  glutInitWindowSize(1280,720);  // set window width, height in pixels
  glutInitWindowPosition(0,0);  // x, y from top left corner of screen
  glutCreateWindow(argv[0]);    // create window, with program name in titlebar
  glutDisplayFunc(sendHELP);     // set display callback function
  glutKeyboardFunc(quit);       // set keyboard callback function
  glutMainLoop();               // hand over control to glut
  return 0;
}
