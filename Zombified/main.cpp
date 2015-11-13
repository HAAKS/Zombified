#include <GLUT/glut.h>
#include <iostream>
#include <random>
#include <stdlib.h>

void Gatherer();
void Defender(); //draws the defender
void Attacker();
void Grid();
void Keyboard(unsigned char key, int x, int y);
void HighlightTheTile();
void Timer(int value);
void IsPresent(); //keeps track of where defenders & RG's are
void Gettingcorrespondingaxes(int row, int column); //have the row and column and get the coordinates
void Hit(); //checks for the collision and fires the bullets
void Settingrowsdead(int coresponsingrow);//KILLS THE ROW
void Killtherow(int n);

float zoomin=200;
float rotangle;
bool defenders [6][10]; //to keep track which tile has defenders
bool resourcegatherers [6][10];
bool bullet[6][10];
int attacktime[6][10];
int row;
int column;
bool destroyedrows [10]; //checks which row is destroyed
GLboolean pause = false;
float moveattackerx =6;
int moveattackerz =0;
int cordinates[2]; //carrying the coordinates from rows and columns
int x;
int z;
int kills; //calculate kills
int hits; //calculate hit times
float movebullet;
int checkforeven;//for random numbers
int a ; //looper variable for getting axes of defenders
int b ; //looper variable for getting axes of defenders
float R =0;//color of car
float G =0;
float B =0;
int attackerwin=0; //a counter to keep track of how many times the attacker reached the house

//y is the row and x is the column
void Keyboard(unsigned char key, int x, int y){
    int valueofchar = key-48;

    if(key=='d'){
        if(resourcegatherers[row][column] == true){
           resourcegatherers[row][column] = false;
        }
        defenders[row][column] = true;
        bullet[row][column]=true;
        column =0;
        row = 0;
    }
    if(key=='p' && !pause){
        pause = true;
    }
    else if(key=='p' && pause){
        pause = false;
    }

    if(key=='r'){
        if(defenders[row][column] == true){
            defenders[row][column] = false;
            bullet[row][column]=false;
        }
        resourcegatherers[row][column] = true;
        column =0;
        row = 0;
    }
    if(key=='c'){
        defenders[row][column] = false;
        bullet[row][column]=false;
        resourcegatherers[row][column] = false;
        column =0;
        row = 0;
    }
    
    if(row==0 && valueofchar > 0 && valueofchar <6){
        row=key-48;

    }
    else if(valueofchar > 0 && valueofchar <10 && row !=0) {
        column=key-48;
    }
    glutPostRedisplay();
}

void IsPresent(){
  
    for(a =1;a<6;a++){
        for(b=1;b<10;b++){
            if(defenders[a][b] == true){
                 Gettingcorrespondingaxes(a, b);
                 glPushMatrix();
                 glTranslatef(cordinates[0]+0.5, 0, cordinates[1]-1.5);
                 Defender();
                 glPopMatrix();
                 Hit();
            }
            if(resourcegatherers[a][b] == true){
                Gettingcorrespondingaxes(a, b);
                glPushMatrix();
                glTranslatef(cordinates[0]+0.5, 0, cordinates[1]-1.5);
                Gatherer();
                glPopMatrix();
            }
        }
    }
}

void Hit(){
    float holderofbullet = cordinates[0]+0.7+movebullet;
    if(movebullet==0){
        bullet[a][b]=true;
    }
    if(bullet[a][b]==false)
        return;
    glPushMatrix();
    glTranslatef(holderofbullet, 1, cordinates[1]-1.5);
    glutSolidSphere(0.25, 7, 7);
    glPopMatrix();
    if((moveattackerz+1) == cordinates[1]){
    if(((holderofbullet<=0)) && ((moveattackerx)<=0) && (moveattackerx>-10)){
        if((moveattackerx)+(abs(holderofbullet))<0){
            hits++;
            R+=0.2;
            G+=0.2;
            B+=0.2;
            bullet[a][b]=false;

        }
    }
    else if ((holderofbullet>0) && (moveattackerx>0)){
        if((holderofbullet-moveattackerx)<0.000001){
            hits++;
            R+=0.2;
            G+=0.2;
            B+=0.2;
            bullet[a][b]=false;
        }

}
        if(hits==4){
            moveattackerx = -12;
            kills++;
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
        glutSolidSphere(0.7, 5, 5);
        glPopMatrix();
        for(i =0; i<360*5;i++){
            glPushMatrix();
            glScaled(0.1, 0.1, 0.1);
            glTranslatef(0, 0.01*i, 0);
            glRotatef(i, 0, 1, 0);
            glTranslatef(2, 0, 0);
            glColor3f(0.5f, 0.5f, 0.5f);
            glutSolidSphere(0.90, 2, 2);
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
    glColor3f(R, G, B);
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
    glColor3f(R, G, B);
    glTranslatef(8.5, 0, -1.5);
    glRotatef(270, 0, 1, 0);
    gluCylinder(qobj, 0.8, 0, 2, 70, 70);
    glPopMatrix();
    glPushMatrix();
    glScaled(0.15, 0.15, 0.15);
    glColor3f(R, G, B);
    glTranslatef(8.5, 0, 0);
    glRotatef(270, 0, 1, 0);
    gluCylinder(qobj, 0.8, 0, 2, 70, 70);
    glPopMatrix();
    glPushMatrix();
    glScaled(0.15, 0.15, 0.15);
    glColor3f(R, G, B);
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
    int counter ;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Grid();
    IsPresent();
    if(row !=0 && column !=0)
    {
        HighlightTheTile();
    }
    if(moveattackerx >=-11.5){ //moves as long as the object didnt reach the end
    glPushMatrix();
    glTranslatef(moveattackerx, 1, moveattackerz);
    Attacker();
    glPopMatrix();
    }
    else if(moveattackerx<-11.5){
        moveattackerz =0;
    }

    if(moveattackerx <-11.4){
        destroyedrows[moveattackerz] =true;
        attackerwin++;
        }
    
    for(counter =1;counter<12;counter+=2){
        if(destroyedrows[counter]==true){
            Killtherow(counter);
        }
    }
    glFlush();
}

void Killtherow(int counter){
    glPushMatrix();
    glBegin(GL_POLYGON);
    glVertex3f(8, 0, counter-1);
    glVertex3f(8, 0, counter+1);
    glVertex3f(-10, 0, counter+1);
    glVertex3f(-10, 0, counter-1);
    glEnd();
    glPopMatrix();
    std::cout<<" THE COUNTER IS KILLED "<<counter;

}
//void Settingrowsdead(int h){
//    switch(h){
//        case 1: destroyedrows[1]=true;
//            break;
//        case 3: destroyedrows[2]=true;
//            break;
//        case 5: destroyedrows[3]=true;
//            break;
//        case 7: destroyedrows[4]=true;
//            break;
//        case 9: destroyedrows[5]=true;
//            break;
//    }
//    
//}

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
    if(column!=0){
    for(i=0;i<column;i++){ //to get column
        x+=2;
    }
    }
    for(i =0;i<row;i++){
        z+=2;
    }
     cordinates[0] =x;
     cordinates[1] = z;
}

void Anim() {
    if(!pause){
    rotangle+=2;
    if(moveattackerz !=0){
        moveattackerx-=0.1;
    }
        if(movebullet >= 17){
            movebullet=0;
        }
        else movebullet+=0.5;

    }
    glutPostRedisplay();
}

void Timer(int value) {
    hits=0;
    R=0;
    G=0;
    B=0;
    do{
     checkforeven = rand() % 10; //gets the random number to check later if even or odd
     moveattackerz = checkforeven ; //get a random z number
    if(moveattackerz ==0) {//random number is 0, then make the z =1
        moveattackerz =1;
        checkforeven =1;
    }
    else if(checkforeven%2==0){
        moveattackerz-=1;
    }}
    while(destroyedrows[moveattackerz]==true);
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
