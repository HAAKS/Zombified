#include <GLUT/glut.h>
#include <iostream>
#include <random>
//eshm3na when I stopped the if for attacker it disappeared opposite to the attacker!
void Gatherer();
void Defender(); //draws the defender
void Attacker();
void Grid();
void Keyboard(unsigned char key, int x, int y);
void HighlightTheTile();
void Timer(int value);
void IsPresent(); //keeps track of where defenders are
void IsResourceGatherer(); //keeps track of where RGs are
void Gettingcorrespondingaxes(int row, int column); //have the row and column and get the coordinates

float zoomin=200;
float rotangle;
bool defenders [6][10]; //to keep track which tile has defenders
bool resourcegatherers [6][10];
int row;
int column;
GLboolean pause = false;
float moveattackerx =6;
float moveattackerz =0;
int cordinates[2]; //carrying the coordinates from rows and columns
int x;
int z;

//y is the row and x is the column
void Keyboard(unsigned char key, int x, int y){
    int valueofchar = key-48;

    if(key=='d'){
        defenders[row][column] = true;
        column =0;
        row = 0;
    }
    if(key=='r'){
        resourcegatherers[row][column] = true;
        //        std::cout << " THE ROW IN DEFENDER IS : " <<row;
        column =0;
        row = 0;
    }
    
    if(row==0 && valueofchar > 0 && valueofchar <6){
        row=key-48;
        std::cout << " THE ROW IS : " <<row; ;

    }
    else if(valueofchar > 0 && valueofchar <10 && row !=0) {
        column=key-48;
        
    }
  
    
    glutPostRedisplay();
}
/*
void IsResourceGatherer(){
    int a;
    int b;
}
*/
void IsPresent(){
    int a ;
    int b ;
    for(a =1;a<6;a++){
        for(b=1;b<10;b++){
            if(defenders[a][b] == true){
                 Gettingcorrespondingaxes(a, b);
                 glPushMatrix();
                 glTranslatef(cordinates[0]+0.5, 0, cordinates[1]-1.5);
                 Defender();
                 glPopMatrix();
                //std::cout << " A IS: "<<a; ;
            }
        }
    }
    for(a =1;a<6;a++){
        for(b=1;b<10;b++){
            if(resourcegatherers[a][b] == true){
                Gettingcorrespondingaxes(a, b);
                glPushMatrix();
                glTranslatef(cordinates[0]+0.5, 0, cordinates[1]-1.5);
                Gatherer();
                glPopMatrix();
                //std::cout << " A IS: "<<a; ;
            }
        }
    }

}

void Grid(){
    float first;
    float second;
    glPushMatrix();
    glTranslatef(-10, 0, 0);
    for(first =0;first<=18;first+=2){
        glBegin(GL_LINE_LOOP);
        glColor3f(0, 0, 0);
        glVertex3f(first, 0, 0);
        glVertex3f(first, 0,10);
        glEnd();
    }
    for(second =0;second<=10;second+=2){
        glBegin(GL_LINE_LOOP);
        glVertex3f(0, 0, second);
        glVertex3f(18, 0, second);
        glEnd();
    }
        glPopMatrix();
   
}

void Gatherer(){
        int i;
        glPushMatrix();
        glRotatef(rotangle, 0, 1, 0);
        glPushMatrix();
        glScaled(0.5, 0.5, 0.5);
        glTranslatef(-0.20,4, 0);
        glutSolidSphere(0.7, 6, 5);
        glPopMatrix();
        for(i =0; i<360*5;i++){
            glPushMatrix();
            glScaled(0.1, 0.1, 0.1);
            glTranslatef(0, 0.01*i, 0);
            glRotatef(i, 0, 1, 0);
            glTranslatef(2, 0, 0);
            glColor3f(0.5f, 0.5f, 0.5f);
            glutSolidSphere(0.40, 25, 25);
            glPopMatrix();
    }
        glPopMatrix();
}

void Defender(){
    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glScaled(0.22, 0.22, 0.22);
    glPushMatrix();
    glScaled(0.5, 0.5, 0.5);
    glTranslatef(5, -10, 0);
    glRotatef(0.01, 0, 0, 0);
    int j;
    for(j =0; j<15;j++){
        glPushMatrix();
        glTranslatef(0, j, 0);
        glutSolidSphere(1.5, 30, 30);
        glPopMatrix();
    }
    glTranslatef(0, 15, 0);
    glutSolidSphere(2.5, 30, 30);
    glPopMatrix();
    GLUquadric* qobj;
    qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj, GLU_LINE);
    glPushMatrix();
    glScaled(0.5, 0.5, 0.5);
    glTranslatef(5, 5, 0);
    gluCylinder(qobj, 1.6, 1.6, 5, 100, 100); //the long extended tip
    glPopMatrix();
    glPopMatrix();
}

void Attacker(){
    GLUquadric* qobj;
    qobj = gluNewQuadric();
    glPushMatrix(); //Matrix of the Big Cube, Body of the Car
    glScaled(0.7, 0.5, 0.5);
    glTranslatef(2.5, 0, 0);
    glColor3f(1.0, 0.0, 0.0);
    glutSolidCube(1.5);
    glPopMatrix();
    glPushMatrix(); //The next four matrices are for the wheels
    glScaled(0.15, 0.15, 0.15);
    glTranslatef(8, -2.5, -2.9);
    gluQuadricDrawStyle(qobj, GLU_LINE);
    gluDisk(qobj, 0, 1, 200, 200);
    gluCylinder(qobj, 1, 1, 1, 100, 100);
    glPopMatrix();
    glPushMatrix();
    glScaled(0.15, 0.15, 0.15);
    glTranslatef(8, -2.5, 2.4);//side
    gluDisk(qobj, 0, 1, 200, 200);
    gluCylinder(qobj, 1, 1, 1, 100, 100);
    glPopMatrix();
    glPushMatrix();
    glScaled(0.15, 0.15, 0.15);
    glTranslatef(15.5, -2.5, 2.3);//side
    gluDisk(qobj, 0, 1, 200, 200);
    gluCylinder(qobj, 1, 1, 1, 100, 100);
    glPopMatrix();
    glPushMatrix();
    glScaled(0.15, 0.15, 0.15);
    glTranslatef(15.5, -2.5, -2.9);
    gluDisk(qobj, 0, 1, 200, 200);
    gluCylinder(qobj, 1, 1, 1, 100, 100);
    glPopMatrix();
    glPushMatrix();
    glScaled(0.15, 0.15, 0.15);
    glColor3f(0.0, 1, 1);
    glTranslatef(8.5, 0, -1.5);
    glRotatef(270, 0, 1, 0);
    gluCylinder(qobj, 0.8, 0, 2, 70, 70);
    glPopMatrix();
    glPushMatrix();
    glScaled(0.15, 0.15, 0.15);
    glColor3f(0.0, 0, 1);
    glTranslatef(8.5, 0, 0);
    glRotatef(270, 0, 1, 0);
    gluCylinder(qobj, 0.8, 0, 2, 70, 70);
    glPopMatrix();
    glPushMatrix();
    glScaled(0.15, 0.15, 0.15);
    glColor3f(0.0, 1, 0);
    glTranslatef(8.5, 0, 1.5);
    glRotatef(270, 0, 1, 0);
    gluCylinder(qobj, 0.8, 0, 2, 70, 70);
    glPopMatrix();
    glPushMatrix();
    glScaled(0.15, 0.15, 0.15);
    glTranslatef(12, 4, 0);
    glutSolidDodecahedron();
    glPopMatrix();
    
}

void Display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Grid();
    IsPresent();
    if(row !=0 && column !=0)
    {
        HighlightTheTile();
    }
    
    Gatherer();
    if(moveattackerx >=-11.5){ //moves as long as the object didnt reach the end
    glPushMatrix();
    glTranslatef(moveattackerx, 1, moveattackerz);
    Attacker();
    glPopMatrix();
    }
    else if(moveattackerx<-11.5){
        moveattackerz =0;
    }
   
    glFlush();
}


void HighlightTheTile(){
        Gettingcorrespondingaxes(row, column);
        glBegin(GL_QUADS);
        glVertex3f(x,0, z-2);
        glVertex3f(x, 0, z);
        glVertex3f(x+2, 0, z);
        glVertex3f(x+2, 0, z-2);
        glEnd();
}

void Gettingcorrespondingaxes(int row, int column){
     z=0;
     x =-12;
    int i=0;
    for(i=0;i<column;i++){ //to get column
        x+=2;
        //   std::cout<<" THIS IS HERE X" << x;
    }
    for(i =0;i<row;i++){
        z+=2;
        //       std::cout<<" THIS IS HERE Y"<<z;
    }
     cordinates[0] =x;
     cordinates[1] = z;
}

void Anim() {
    rotangle+=2;
    if(moveattackerz !=0){
        moveattackerx-=0.1;
    }
    glutPostRedisplay();
}
void Timer(int value) {
    int checkforeven = rand() % 10; //gets the random number to check later if even or odd
    //Get a different z value to stand a different column
    moveattackerz = checkforeven ; //get a random z number
    if(moveattackerz ==0) //random number is 0, then make the z =1
        moveattackerz =1;
    else if(checkforeven%2==0){
        moveattackerz-=1;
    }
    moveattackerx=6; // re-initialize the x coordinate when the function is called so the attacker appear
    glutPostRedisplay();
    glutTimerFunc(10 * 1000, Timer, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(900, 1000);
    glutInitWindowPosition(150, 150);
    glutCreateWindow("OpenGL - 3D Template");
    glutDisplayFunc(Display);
    glutKeyboardFunc(Keyboard);
    glutTimerFunc(0, Timer, 0);
    glutIdleFunc(Anim);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 300 / 300, 0.1f, 300.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0f, 20.0f, 25.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    glutMainLoop();
}
