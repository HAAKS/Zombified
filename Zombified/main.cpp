#include <GLUT/glut.h>
#include <iostream>
#include <random>
#include <stdlib.h>
#include <stdio.h>

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
int Settingrowsdead(int coresponsingrow);//KILLS THE ROW
void Killtherow(int n); //overlaps the whole row with a rectangle to kill it
void Display();
void Anim();
void Counter(int x, int y);
void DScreen(std::string string, int x, int y);
void RGScreen(std::string string, int x, int y);
void EndGame(std::string string);

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
int kills; //calculate how many attackers died
int hits; //calculate hit times of the bullet lel attacker
float movebullet;
int checkforeven;//for random numbers
int a ; //looper variable for getting axes of defenders
int b ; //looper variable for getting axes of defenders
float R =0;//color of car
float G =0;
float B =0;
int attackerwin=0; //a counter to keep track of how many times the attacker reached the house
int resourceholder =100; //to get the final value Resources(R) available
int addresourceforgatherers=0;
int timeforresource; //In time function, so that every 20 seconds, its increments R from RG

void Keyboard(unsigned char key, int x, int y){
    int valueofchar = key-48;
    int temp;//to hold the row value -1 to compare with moveattackerz
    Gettingcorrespondingaxes(row,0);
    temp = cordinates[1]-1;

    if(key=='d'&& row!=0 && column!=0 &&!pause){
        if( resourcegatherers[row][column] == true){
            addresourceforgatherers--;
            resourcegatherers[row][column] = false;
        }
        if(destroyedrows[temp] == false && resourceholder>=25){
        resourceholder =resourceholder-25;
        defenders[row][column] = true;
        bullet[row][column]=true;
        }
        column =0;
        row = 0;
        
    }
    if(key=='p' && !pause){
        pause = true;
    }
    else if(key=='p' && pause ){
        pause = false;
    }
    if(key=='r' && row!=0 && column!=0 &&!pause){
            defenders[row][column] = false;
            bullet[row][column]=false;
        if(destroyedrows[temp] == false && resourceholder>=50){
            resourceholder =resourceholder-50;
            resourcegatherers[row][column] = true;
         //   bullet[row][column]=true;
            addresourceforgatherers++;
        }
        column =0;
        row = 0;
    }
    if(key=='c'&& row!=0 && column!=0 &&!pause){
        defenders[row][column] = false;
        bullet[row][column]=false;
        if( resourcegatherers[row][column] == true){
            addresourceforgatherers--;
            resourcegatherers[row][column] = false;
        }
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
//checkes when defender/RG and attacker collides.
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
                if((cordinates[1]-1 ==moveattackerz) && ((cordinates[0]+0.5) >= moveattackerx)) {
                    defenders[a][b]=false;
                }
                        }
            if(resourcegatherers[a][b] == true){
                Gettingcorrespondingaxes(a, b);
                glPushMatrix();
                glTranslatef(cordinates[0]+0.5, 0, cordinates[1]-1.5);
                Gatherer();
                glPopMatrix();
                if((cordinates[1]-1 ==moveattackerz) && ((cordinates[0]+0.5) >= moveattackerx)) {
                    resourcegatherers[a][b]=false;
                        addresourceforgatherers--;
                }
                
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
            moveattackerz = 0;
            kills++;
            resourceholder =resourceholder+20;
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

void Display(void) {
    int counter;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Grid();
    IsPresent();
    if(row !=0 && column !=0)
    {
        HighlightTheTile();
    }
    if(moveattackerz!=0){ //after attackerwin++ it doesn't enter again until a new attacker is present
    if(moveattackerx >=-11.4){ //moves as long as the object didnt reach the end
    glPushMatrix();
    glTranslatef(moveattackerx, 1, moveattackerz);
    Attacker();
    glPopMatrix();

    }
        
    else if(moveattackerx<-11.5){ //check here the BUG !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ANA HENA
        destroyedrows[moveattackerz] =true;
        attackerwin++;
        moveattackerz =0;
    }
    }
    for(counter =1;counter<12;counter+=2){
        if(destroyedrows[counter]==true){
            Killtherow(counter);
        }
    }
    if(attackerwin ==3){
       EndGame("Game is Over ya Amoor ! :D");
        pause = true;
    }
    Counter(-10, 10);
    DScreen("25", -6, 10); //display value of Defender
    RGScreen("50", 0, 10);//display value of RG
    //EndGame("YOU ARE OUT");
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
}

//int Settingrowsdead(int h){
//    switch(h){
//        case 1: n=1;
//            break;
//        case 3: n=2;
//            break;
//        case 5: n=3;
//            break;
//        case 7: n=4;
//            break;
//        case 9: n=5;
//            break;
//    }
//    return n;
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
        std::cout<<" HERE IAM HENAA5: " << moveattackerx;
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
    }
    }
    while(destroyedrows[moveattackerz]==true);
    moveattackerx=6; // re-initialize the x coordinate when the function is called so the attacker appear
    if(timeforresource==1){
        resourceholder= resourceholder+ addresourceforgatherers*10;
        timeforresource=0;
    }
    else{
        timeforresource ++; //checks for time to see when to increment resourceholders for RG
    }
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

void Counter(int x, int y) {
    std::string string = std::to_string(resourceholder);
    glRasterPos2d(x, y);
    std::string text = "Resource: ";
    int tol =text.length();
    int len = string.length();
    int i;
    for(i=0;i<tol;i++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
    }
    for(i =0;i<len;i++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
    }
    glutPostRedisplay();
}

void DScreen(std::string string, int x, int y) {
    glRasterPos2d(x, y);
    std::string text = "Defender cost: ";
    int tol =text.length();
    int len = string.length();
    int i;
    for(i=0;i<tol;i++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
    }
    for(i =0;i<len;i++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
    }
    glutPostRedisplay();
}

void RGScreen(std::string string, int x, int y) {
    glRasterPos2d(x, y);
    std::string text = "Resource Gatherer cost: ";
    int tol =text.length();
    int len = string.length();
    int i;
    for(i=0;i<tol;i++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
    }
    for(i =0;i<len;i++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
    }
    glutPostRedisplay();
}

void EndGame(std::string string){
        glRasterPos2i(-4,2);
        int len = string.length();
        int i;
        for(i =0;i<len;i++){
            glColor3b(1.0f, 0.9f,0.0f);
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
        }
}