#include<windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <MMsystem.h>
#include <iostream>
#include <string>

// game title
char GAME_TITLE[] = "Car Racing Game";

// created by
char TEAM_TITLE[] = "G-1, CSE, PUST";

// Track game stage
// 0: Initial, 1: racing, 2: Score board
int LAST_STAGE = 0;
int CURR_STAGE = 0;

//Track Sound
int SOUND_BOOL = 0;
// sound file path
char RACING_F[] = "G:\\My Drive\\academic\\cse42\\CG_4203\\lab\\2D-Car-Racing-Game-OpenGL\\racing-small.wav";
char BEGIN_F[] = "G:\\My Drive\\academic\\cse42\\CG_4203\\lab\\2D-Car-Racing-Game-OpenGL\\relaxing-small.wav";
// Starting Game Speed
int INITIAL_FPS = 45;

// Track Game Speed
int FPS = INITIAL_FPS;

// delta v is the increment rate of velocity
int LEVEL_DELTA_V = 3;

// Key delta v is the increment or decrement rate of velocity
// by pressing key-UP or key-DOWN
int KEY_DELTA_V = 1;

// Increse level after getting a target score
int LEVEL_UP_SCORE = 10;

//Game Track
int start=0;
int gv=0;

// Track level
int level = 0;

//Track Score
int score = 0;

//Form move track
int roadDivTopMost = 0;
int roadDivTop = 0;
int roadDivMdl = 0;
int roadDivBtm = 0;
//For Card Left / RIGHT
int lrIndex = 0 ;
//Car Coming
int car1 = 0;
int lrIndex1=0;
int car2 = +33;
int lrIndex2=0;
int car3 = +66;
int lrIndex3=0;
//For Display TEXT
const int font1=(int)GLUT_BITMAP_TIMES_ROMAN_24;
const int font2=(int)GLUT_BITMAP_HELVETICA_18;
const int font3=(int)GLUT_BITMAP_8_BY_13;
char s[30];
void renderBitmapString(float x, float y, void *font,const char *string){
    const char *c;
    glRasterPos2f(x, y);
    for (c=string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void create_object(int x, int y){
    int h = 6;
    //Bottom
    glColor3f(0.871, 0.722, 0.529);
    glBegin(GL_TRIANGLES);
        glVertex2f(x+5,y+h+3);
        glVertex2f(x+6,y);
        glVertex2f(x+4,y);
    glEnd();
    // Top
    glColor3f(0.133, 0.545, 0.133);
    glBegin(GL_POLYGON);
        glVertex2f(x+6,y+h+6);
        glVertex2f(x+8,y+h+4);
        glVertex2f(x+7,y+h+4);
        glVertex2f(x+10,y+h);

        glVertex2f(x,y+h);
        glVertex2f(x+1,y+h+4);
        glVertex2f(x+2,y+h+4);
        glVertex2f(x+4,y+h+7);
    glEnd();
}

void create_cloud(int x, int y){
    int h = 5;
    glColor3f(0.901, 0.912, 0.999);
    glBegin(GL_POLYGON);
        glVertex2f(x+6,y+h+6);
        glVertex2f(x+8,y+h+4);
        glVertex2f(x+7,y+h+4);
        glVertex2f(x+10,y+h);

        glVertex2f(x+7,y+h-2);
        glVertex2f(x+8,y+h-3);
        glVertex2f(x+5,y+h-4);

        glVertex2f(x+4,y+h-5);
        glVertex2f(x+3,y+h-4);
        glVertex2f(x+2,y+h-3);
        glVertex2f(x+1,y+h-2);

        glVertex2f(x,y+h);
        glVertex2f(x+1,y+h+4);
        glVertex2f(x+2,y+h+4);
        glVertex2f(x+4,y+h+7);
    glEnd();
}

void startGame(){
    if(LAST_STAGE!=CURR_STAGE){
        if(SOUND_BOOL==1){
            PlaySound(NULL, NULL, SND_PURGE);
            SOUND_BOOL = 0;
        }
        LAST_STAGE = CURR_STAGE;
    }

    if(SOUND_BOOL==0){
        printf("Game Start!\n"); // BEGIN_F, RACING_F
        SOUND_BOOL = PlaySound(TEXT(RACING_F), NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
        if (SOUND_BOOL){
            SOUND_BOOL = 1;
        }
        //printf("gv=%d, SOUND_BOOL=%d\n", gv, SOUND_BOOL);
    }

    //Road
    glColor3f(0.412, 0.412, 0.412);
    glBegin(GL_POLYGON);
        glVertex2f(15,0);
        glVertex2f(15,100);
        glVertex2f(70,100);
        glVertex2f(70,0);
    glEnd();

    //Road Left Border
    glColor3f(1.000, 1.000, 1.000);
    glBegin(GL_POLYGON);
        glVertex2f(15,0);
        glVertex2f(15,100);
        glVertex2f(18,100);
        glVertex2f(18,0);
    glEnd();

    //Road Right Border
    glColor3f(1.000, 1.000, 1.000);
    glBegin(GL_POLYGON);
        glVertex2f(67,0);
        glVertex2f(67,100);
        glVertex2f(70,100);
        glVertex2f(70,0);
    glEnd();
    //Road Middel Border
        //TOP
    glColor3f(1.000, 1.000, 1.000);
    glBegin(GL_POLYGON);
        glVertex2f(33,roadDivTop+80);
        glVertex2f(33,roadDivTop+100);
        glVertex2f(35,roadDivTop+100);
        glVertex2f(35,roadDivTop+80);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(50,roadDivTop+80);
        glVertex2f(50,roadDivTop+100);
        glVertex2f(52,roadDivTop+100);
        glVertex2f(52,roadDivTop+80);
    glEnd();
    roadDivTop--;
    if(roadDivTop<-100){
        roadDivTop =20;
        score++;
    }
        //Midle
    //glColor3f(0.000, 1.000, 0.000);
    glBegin(GL_POLYGON);
        glVertex2f(33,roadDivMdl+40);
        glVertex2f(33,roadDivMdl+60);
        glVertex2f(35,roadDivMdl+60);
        glVertex2f(35,roadDivMdl+40);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f(50,roadDivMdl+40);
        glVertex2f(50,roadDivMdl+60);
        glVertex2f(52,roadDivMdl+60);
        glVertex2f(52,roadDivMdl+40);
    glEnd();
    roadDivMdl--;
    if(roadDivMdl<-60){
        roadDivMdl =60;
        score++;
    }
        //Bottom
    //glColor3f(1.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
        glVertex2f(33,roadDivBtm+0);
        glVertex2f(33,roadDivBtm+20);
        glVertex2f(35,roadDivBtm+20);
        glVertex2f(35,roadDivBtm+0);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f(50,roadDivBtm+0);
        glVertex2f(50,roadDivBtm+20);
        glVertex2f(52,roadDivBtm+20);
        glVertex2f(52,roadDivBtm+0);
    glEnd();
    roadDivBtm--;
    if(roadDivBtm<-20){
        roadDivBtm=100;
        score++;
    }

    //Score Board
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
        glVertex2f(80,97);
        glVertex2f(100,97);
        glVertex2f(100,98-8);
        glVertex2f(80,98-8);
    glEnd();
    //Print Score
    char buffer [50];
    sprintf (buffer, "SCORE: %d", score);
    glColor3f(0.000, 1.000, 0.000);
    renderBitmapString(80.5,95,(void *)font3,buffer);
    //Speed Print
    char buffer1 [50];
    sprintf (buffer1, "SPEED:%dKm/h", FPS);
    glColor3f(0.000, 1.000, 0.000);
    renderBitmapString(80.5,95-2,(void *)font3,buffer1);
    //level Print
    if(score % LEVEL_UP_SCORE == 0){
        int last = score /LEVEL_UP_SCORE;
        if(last!=level){
            level = score /LEVEL_UP_SCORE;
            FPS=FPS+LEVEL_DELTA_V;
        }
    }
    char level_buffer [50];
    sprintf (level_buffer, "LEVEL: %d", level);
    glColor3f(0.000, 1.000, 0.000);
    renderBitmapString(80.5,95-4,(void *)font3,level_buffer);
    //Increse Speed With level
    //MAIN car
    //Front Tire
   /* glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
        glVertex2f(lrIndex+26-2,5);
        glVertex2f(lrIndex+26-2,7);
        glVertex2f(lrIndex+30+2,7);
        glVertex2f(lrIndex+30+2,5);
    glEnd();
        //Back Tire
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
        glVertex2f(lrIndex+26-2,1);
        glVertex2f(lrIndex+26-2,3);
        glVertex2f(lrIndex+30+2,3);
        glVertex2f(lrIndex+30+2,1);
    glEnd();
        //Car Body
    glColor3f(0.678, 1.000, 0.184);
    glBegin(GL_POLYGON);
        glVertex2f(lrIndex+26,1);
        glVertex2f(lrIndex+26,8);
        glColor3f(0.000, 0.545, 0.545);
        glVertex2f(lrIndex+28,10);
        glVertex2f(lrIndex+30,8);
        glVertex2f(lrIndex+30,1);
    glEnd();
    */
    glColor3f(0.678, 1.000, 0.184);
    glBegin(GL_POLYGON);
        glVertex2f(lrIndex+23,0);
        glVertex2f(lrIndex+22,1);
        glVertex2f(lrIndex+22,10);
        glVertex2f(lrIndex+24,12);
        glVertex2f(lrIndex+27,12);
        glVertex2f(lrIndex+29,10);
        glColor3f(0.000, 0.545, 0.545);
        glVertex2f(lrIndex+29,1);
        glVertex2f(lrIndex+28,0);
    glEnd();

    //Opposite car 1
    /*glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
        glVertex2f(lrIndex1+26-2,car1+100-4);
        glVertex2f(lrIndex1+26-2,car1+100-6);
        glVertex2f(lrIndex1+30+2,car1+100-6);
        glVertex2f(lrIndex1+30+2,car1+100-4);
    glEnd();
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
        glVertex2f(lrIndex1+26-2,car1+100);
        glVertex2f(lrIndex1+26-2,car1+100-2);
        glVertex2f(lrIndex1+30+2,car1+100-2);
        glVertex2f(lrIndex1+30+2,car1+100);
    glEnd();
    glColor3f(1.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
        glVertex2f(lrIndex1+26,car1+100);
        glVertex2f(lrIndex1+26,car1+100-7);
        glVertex2f(lrIndex1+28,car1+100-9);
        glVertex2f(lrIndex1+30,car1+100-7);
        glVertex2f(lrIndex1+30,car1+100);
    glEnd();
    */
    glColor3f(.500, 0.000, 0.300);
    glBegin(GL_POLYGON);
        glVertex2f(lrIndex1+23,car1+100-0);
        glVertex2f(lrIndex1+22,car1+100-1);
        glVertex2f(lrIndex1+22,car1+100-10);
        glVertex2f(lrIndex1+24,car1+100-12);
        glVertex2f(lrIndex1+27,car1+100-12);
        glVertex2f(lrIndex1+29,car1+100-10);
        glColor3f(0.800, 0.545, 0.545);
        glVertex2f(lrIndex1+29,car1+100-1);
        glVertex2f(lrIndex1+28,car1+100-0);

    glEnd();
    car1--;
    if(car1<-100){
        car1=0;
        lrIndex1=lrIndex;
    }
    //KIll check car1
    if((abs(lrIndex-lrIndex1)<8) && (car1+100<24 )){
            start = 0;
            gv=1;
    }
    //Opposite car 2
    glColor3f(.200, 0.3000, 0.300);
    glBegin(GL_POLYGON);
        glVertex2f(lrIndex2+23,car2+100-0);
        glVertex2f(lrIndex2+22,car2+100-1);
        glVertex2f(lrIndex2+22,car2+100-10);
        glVertex2f(lrIndex2+24,car2+100-12);
        glVertex2f(lrIndex2+27,car2+100-12);
        glVertex2f(lrIndex2+29,car2+100-10);
        glColor3f(0.300, 0.545, 0.545);
        glVertex2f(lrIndex2+29,car2+100-1);
        glVertex2f(lrIndex2+28,car2+100-0);

         glEnd();
    car2--;
    if(car2<-100){
        car2=0;
        lrIndex2=lrIndex;
    }
    //KIll check car2
    if((abs(lrIndex-lrIndex2)<8) && (car2+100<24)){
            start = 0;
            gv=1;
    }
    //Opposite car 3
    glColor3f(0.600, 0.545, 0.3);
    glBegin(GL_POLYGON);
        glVertex2f(lrIndex3+23,car3+100-0);
        glVertex2f(lrIndex3+22,car3+100-1);
        glVertex2f(lrIndex3+22,car3+100-10);
        glVertex2f(lrIndex3+24,car3+100-12);
        glVertex2f(lrIndex3+27,car3+100-12);
        glVertex2f(lrIndex3+29,car3+100-10);
        glColor3f(0.20, 0.545, 0.6);
        glVertex2f(lrIndex3+29,car3+100-1);
        glVertex2f(lrIndex3+28,car3+100-0);

        glEnd();

    car3--;
    if(car3<-100){
        car3=0;
        lrIndex3=lrIndex;
    }
    //KIll check car3
    if((abs(lrIndex-lrIndex3)<8) && (car3+100<24)){
            start = 0;
            gv=1;
    }
}
void fristDesign(){
    if(LAST_STAGE!=CURR_STAGE){
        if(SOUND_BOOL==1){
            PlaySound(NULL, 0, 0);
            SOUND_BOOL = 0;
        }
        LAST_STAGE = CURR_STAGE;
        SOUND_BOOL = PlaySound(TEXT(BEGIN_F), NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
        SOUND_BOOL = 1;
    }

    //Road Backgound
    glColor3f(0.000, 0.392, 0.000);
    glBegin(GL_POLYGON);
        glVertex2f(0,55);
        glVertex2f(100,55);
        glColor3f(0.604, 0.804, 0.196);
        glVertex2f(100,50-50);
        glVertex2f(0,50-50);
    glEnd();
    //Road Design In Front Page
    //glColor3f(0, 0, 0);
    glColor3f(0.412, 0.412, 0.412);
    glBegin(GL_TRIANGLES);
        glVertex2f(32-2+21,55);
        glVertex2f(32+58,50-50);
        glVertex2f(32-22,50-50);
    glEnd();
    //Road Midle
    glColor3f(1, 1, 1);
    glBegin(GL_TRIANGLES);
        glVertex2f(32-2+21,55);
        glVertex2f(50+2,50-50);
        glVertex2f(50-2,50-50);
    glEnd();
     //Road Sky
    glColor3f(0.000, 0.749, 1.000);
    glBegin(GL_POLYGON);
        glVertex2f(100,100);
        glVertex2f(0,100);
        glColor3f(0.686, 0.933, 0.933);
        glVertex2f(0,55);
        glVertex2f(100,55);
    glEnd();
    //Hill 1
    glColor3f(0.235, 0.702, 0.443);
    glBegin(GL_TRIANGLES);
        glVertex2f(20,55+10);
        glVertex2f(20+7,55);
        glVertex2f(0,55);
    glEnd();
    //Hill 2
    glColor3f(0.000, 0.502, 0.000);
        glBegin(GL_TRIANGLES);
        glVertex2f(20+15,55+20);
        glVertex2f(20+20+10,55);
        glVertex2f(0+10,55);
    glEnd();
    //Hill 4
    glColor3f(0.235, 0.702, 0.443);
    glBegin(GL_TRIANGLES);
        glVertex2f(87,55+12);
        glVertex2f(100,55);
        glVertex2f(60,55);
    glEnd();
     //Hill 3
    glColor3f(0.000, 0.502, 0.000);
    glBegin(GL_TRIANGLES);
        glVertex2f(70,70);
        glVertex2f(90,55);
        glVertex2f(50,55);
    glEnd();

    // Trees
    create_object(2,55);
    create_object(78,53);
    create_object(5,45);
    create_object(75,38);
    create_object(70,50);
    create_object(3,30);

    // Clouds
    create_cloud(7, 67);
    create_cloud(13, 65);
    create_cloud(12, 69);

    create_cloud(40, 65);
    create_cloud(38, 67);
    create_cloud(43, 64);

    create_cloud(75, 68);
    create_cloud(68, 70);

    //Text Information in Frist Page
    int title_posy = 80;

    //glColor3f(0.50, 0.60, 1.00);
    glBegin(GL_POLYGON);
        glColor3f(1.0f, 0.99f, 1.0f); // make this vertex purple
        glVertex2f(40-4,title_posy+5+2);
        glColor3f(1.0f, 0.99f, 0.0f); // make this vertex red
        glVertex2f(40+30,title_posy+5+2);
        glColor3f(0.0f, 0.99f, 0.0f); // make this vertex green
        //glColor3f(1.0f, 0.99f, 0.0f); // make this vertex red
        glVertex2f(40+30,title_posy-7+2);
        //glColor3f(1.0f, 1.1f, 0.0f); // make this vertex yellow
        glColor3f(1.0f, 0.50f, 1.0f); // make this vertex purple
        glVertex2f(40-4,title_posy-7+2);
    glEnd();

    glColor3f(0.000, 0.000, 0.000);
    renderBitmapString(40, title_posy,(void *)font1, GAME_TITLE);

    // relative position of "Help" box
    int help_rel_posy = title_posy-30;

    // if game is over
    if(gv==1){
        int score_board_h = 10;
        int score_board_rel_posy = title_posy - 20;

        //Score Board Place Holder
        //glColor3f(0.098, 0.098, 0.439);
        glColor3f(0.20, 0.50, 0.60);
        glBegin(GL_POLYGON);
            glColor3f(1.0f, 0.99f, 1.0f);
            glVertex2f(40-4,score_board_rel_posy+5+10);
            glColor3f(1.0f, 0.99f, 0.0f);
            glVertex2f(40+26+4,score_board_rel_posy+5+10);
            glColor3f(0.0f, 0.99f, 0.0f);
            glVertex2f(32+46,score_board_rel_posy-15+10);
            glColor3f(1.0f, 0.50f, 1.0f);
            glVertex2f(32-4,score_board_rel_posy-15+10);
        glEnd();

        glColor3f(0.000, 0.000, 0.000);
        renderBitmapString(43,score_board_rel_posy+score_board_h,(void *)font1,"GAME OVER");
        glColor3f(0.000, 0.000, 0.000);
        char buffer2 [50];
        sprintf (buffer2, "Your Score is : %d", score);
        renderBitmapString(41,score_board_rel_posy+score_board_h-4,(void *)font1,buffer2);
        glColor3f(0.000, 0.000, 0.000);
        char buffer3 [50];
        sprintf (buffer3, "Max Level is : %d", level);
        renderBitmapString(41,score_board_rel_posy+score_board_h-8,(void *)font1,buffer3);

        // update relative help box
        help_rel_posy = help_rel_posy - score_board_h;
    }

    //Help Menu Place Holder
    glColor3f(1.000, 1.000, 1.000);
    glBegin(GL_LINES);
        glVertex2f(32-4, help_rel_posy+5+10);
        glVertex2f(32+46, help_rel_posy+5+10);
    glEnd();
    glColor3f(0.098, 0.098, 0.439);
    glBegin(GL_POLYGON);
        glVertex2f(32-4,help_rel_posy+5+10);
        glVertex2f(32+46,help_rel_posy+5+10);
        glVertex2f(32+46,help_rel_posy-15+10);
        glVertex2f(32-4,help_rel_posy-15+10);
    glEnd();

    glColor3f(0.000, 1.000, 0.000);
    renderBitmapString(30+15,help_rel_posy+1.5+10,(void *)font2,"Control Info");
    glColor3f(1.000, 1.000, 1.000);
    glPushAttrib(GL_ENABLE_BIT);
    // glPushAttrib is done to return everything to normal after drawing
    glLineStipple(1, 0xAAAA);  // [1]
    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINES);
        glVertex2f(32-4, help_rel_posy+1.30+10);
        glVertex2f(32+46, help_rel_posy+1.30+10);
    glEnd();
    glPopAttrib();
    // renderBitmapString(30+10,help_rel_posy+1.49+10,(void *)font2,"____");
    glColor3f(0.200, 1.000, 0.900);
    renderBitmapString(30,help_rel_posy-2+10,(void *)font2,"Press SPACE to START New Game");
    renderBitmapString(30,help_rel_posy-2-3+10,(void *)font2,"Press ESC to Exit");
    glColor3f(1.000, 1.000, 1.000);
    renderBitmapString(30,help_rel_posy-1-6+10,(void *)font3,"Press UP Arrow Button to increase Speed");
    renderBitmapString(30,help_rel_posy-1-8+10,(void *)font3,"Press DWON Arrow Button to decrease Speed");
    renderBitmapString(30,help_rel_posy-1-10+10,(void *)font3,"Press RIGHT Arrow Button to turn Right");
    renderBitmapString(30,help_rel_posy-1-12+10,(void *)font3,"Press LEFT Arrow Button to turn Left");
    glColor3f(0.000, 1.000, 0.000);
    renderBitmapString(60-5,50-40,(void *)font2,"Created By :");
    glColor3f(1.000, 1.000, 0.000);
    renderBitmapString(60-5,50-43,(void *)font2,TEAM_TITLE);
}
void display(){
    if(CURR_STAGE==1 && start==0){
        printf("(Score Board)LAST_STAGE=%d, SOUND_BOOL=%d\n", LAST_STAGE, SOUND_BOOL);
        LAST_STAGE = CURR_STAGE;
        CURR_STAGE = 2;
    }
    else if(CURR_STAGE==2 && start==1){
        printf("(Racing)LAST_STAGE=%d, SOUND_BOOL=%d\n", LAST_STAGE, SOUND_BOOL);
        LAST_STAGE = CURR_STAGE;
        CURR_STAGE = 1;
    }
    else if(CURR_STAGE==0 && start==1){
        printf("(Begin)LAST_STAGE=%d, SOUND_BOOL=%d\n", LAST_STAGE, SOUND_BOOL);
        LAST_STAGE = CURR_STAGE;
        CURR_STAGE = 1;
    }
    else if(CURR_STAGE==0 && start==0){
        //printf("(Initial)LAST_STAGE=%d\n", LAST_STAGE);
        if(SOUND_BOOL==0){
            PlaySound(TEXT(BEGIN_F), NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
            SOUND_BOOL = 1;
            //printf("SOUND_BOOL=%d ", SOUND_BOOL);
        }
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(start==1){
        //glClearColor(0.627, 0.322, 0.176,1);
        glClearColor(0.000, 0.392, 0.000,1);
        startGame();
    }
    else{
        SOUND_BOOL = 0;
        fristDesign();
        //glClearColor(0.184, 0.310, 0.310,1);
    }
    glFlush();
    glutSwapBuffers();
}
void spe_key(int key, int x, int y){
    switch (key) {
        case GLUT_KEY_DOWN:
            if(FPS>(LEVEL_UP_SCORE+(level*LEVEL_DELTA_V)))
                FPS=FPS-KEY_DELTA_V;
            break;
        case GLUT_KEY_UP:
            FPS=FPS + KEY_DELTA_V;
            break;
        case GLUT_KEY_LEFT:
            if(lrIndex>=0){
                lrIndex = lrIndex - 17;
                if(lrIndex<0){
                    lrIndex=0;
                }
            }
            break;
        case GLUT_KEY_RIGHT:
            if(lrIndex<=34){
                lrIndex = lrIndex + 17;
                if(lrIndex>34){
                    lrIndex = 34;
                }
            }
            break;
        default:
            break;
    }
}
void processKeys(unsigned char key, int x, int y) {
      switch (key){
        case ' ':
            if(start==0){
                start = 1;
                gv = 0;
                FPS = INITIAL_FPS;
                roadDivTopMost = 0;
                roadDivTop = 0;
                roadDivMdl = 0;
                roadDivBtm = 0;
                lrIndex = 0 ;
                car1 = 0;
                lrIndex1=0;
                car2 = +35;
                lrIndex2=0;
                car3 = +70;
                lrIndex3=0;
                score=0;
                level=0;
            }
            break;
        case 27:
            printf("27 key presed!");
            PlaySound(NULL, 0,0);
            exit(0);
            break;
        default:
            break;
    }
}
void timer(int){
    glutPostRedisplay();
    glutTimerFunc(1000/FPS,timer,0);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(800,600);
    glutInitWindowPosition(200,20);
    glutCreateWindow(GAME_TITLE);
    glutDisplayFunc(display);
    glutSpecialFunc(spe_key);
    glutKeyboardFunc(processKeys );
    glOrtho(0,100,0,100,-1,1);
    glClearColor(0.184, 0.310, 0.310,1);
    glutTimerFunc(1000,timer,0);
    glutMainLoop();
    return 0;
}
