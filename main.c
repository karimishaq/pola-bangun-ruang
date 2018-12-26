#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

#define GL3_PROTOTYPES 1

char *programName = "Headerphile SDL2 - OpenGL thing";

// Our SDL_Window ( just like with SDL2 wihout OpenGL)
SDL_Window *mainWindow;

// Our opengl context handle
SDL_GLContext mainContext;

int FPS=1;
float angle = 0.0;
unsigned int tex;
unsigned int nderajat=0;
unsigned int derajat[25]={120, 120, 120, 120, 120, 90, 72, 60, 45, 40, 30, 24, 20, 15, 12, 10, 9, 8, 6, 5, 4, 3, 2, 1, 1};

unsigned int loadTexture(const char* filename){
        SDL_Surface* img = SDL_LoadBMP(filename);
        unsigned int id;
        int Mode = GL_RGB;
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);

        if(img->format->BytesPerPixel == 4) {
            Mode = GL_RGBA;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, Mode, img->w, img->h, 0, Mode, GL_UNSIGNED_BYTE, img->pixels);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        //
        SDL_FreeSurface(img);
        return id;
}

int SetOpenGLAttributes(){
	// Set our OpenGL version.
	// SDL_GL_CONTEXT_CORE gives us only the newer version, deprecated functions are disabled
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// 3.2 is part of the modern versions of OpenGL, but most video cards whould be able to run it
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	// Turn on double buffering with a 24bit Z buffer.
	// You may need to change this to 16 or 32 for your system
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); //mungkin tidak perlu

	return 1;
}

int init(){
        glClearColor(0.0,0.0,0.0,1.0);  //background color and alpha
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45,640.0/480.0,1.0,500.0);
        glMatrixMode(GL_MODELVIEW);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_TEXTURE_2D);
        tex = loadTexture("brick.bmp");
        if(tex)return 1;
        else return 0;
        return 1;
}

void gambarRumah2(){
    glBindTexture(GL_TEXTURE_2D, tex);
    glBegin(GL_QUADS);
        glColor3f(0.0, 0.7, 0.1);
        glTexCoord2f(0, 0);
        glVertex3f(-0.9, 0.0, 0.9);
        glTexCoord2f(0.1, 0);
        glVertex3f(-0.7, 0.0, 0.9);
        glTexCoord2f(0.1, 1);
        glVertex3f(-0.7, -0.9, 0.9);
        glTexCoord2f(0, 1);
        glVertex3f(-0.9, -0.9, 0.9);

        glColor3f(0.0, 0.7, 0.1);
        glTexCoord2f(0.3, 0);
        glVertex3f(-0.3, 0.0, 0.9);
        glTexCoord2f(1, 0);
        glVertex3f(0.9, 0.0, 0.9);
        glTexCoord2f(1, 1);
        glVertex3f(0.9, -0.9, 0.9);
        glTexCoord2f(0.3, 1);
        glVertex3f(-0.3, -0.9, 0.9);

        //atas pintu
        glColor3f(0.0, 0.7, 0.1);
        glTexCoord2f(0.3, 0);
        glVertex3f(-0.3, 0.0, 0.9);
        glTexCoord2f(0.1, 0);
        glVertex3f(-0.7, 0.0, 0.9);
        glTexCoord2f(0.1, 0.45);
        glVertex3f(-0.7, -0.4, 0.9);
        glTexCoord2f(0.3, 0.45);
        glVertex3f(-0.3, -0.4, 0.9);

        //pintu
        glColor3f(0.5, 0.0, 0.5);
        glTexCoord2d(0.0, 0.0);
        glVertex3f(-0.3, -0.4, 0.9);
        glTexCoord2d(1.0, 0.0);
        glVertex3f(-0.7, -0.4, 0.9);
        glTexCoord2d(1.0, 1.0);
        glVertex3f(-0.7, -0.9, 0.9);
        glTexCoord2d(0.0, 1.0);
        glVertex3f(-0.3, -0.9, 0.9);

        glColor3f(0.9, 0.9, 0.0);
        glVertex3f(-0.9, 0.0, -0.9);
        glVertex3f(0.9, 0.0, -0.9);
        glVertex3f(0.9, -0.9, -0.9);
        glVertex3f(-0.9, -0.9, -0.9);

        glColor3f(0.2, 0.2, 0.9);
        glVertex3f(-0.9, 0.0, 0.9);
        glVertex3f(0.9, 0.0, 0.9);
        glVertex3f(0.9, 0.0, -0.9);
        glVertex3f(-0.9, 0.0, -0.9);

        glColor3f(0.7, 0.0, 0.1);
        glVertex3f(-0.9, -0.9, 0.9);
        glVertex3f(0.9, -0.9, 0.9);
        glVertex3f(0.9, -0.9, -0.9);
        glVertex3f(-0.9, -0.9, -0.9);

        glColor3f(0.9, 0.9, 0.9);
        glVertex3f(-0.9, -0.9, 0.9);
        glVertex3f(-0.9, 0.0, 0.9);
        glVertex3f(-0.9, 0.0, -0.9);
        glVertex3f(-0.9, -0.9, -0.9);


        glColor3f(0.9, -0.9, 0.9);
        glVertex3f(0.9, -0.9, 0.9);
        glVertex3f(0.9, 0.0, 0.9);
        glVertex3f(0.9, 0.0, -0.9);
        glVertex3f(0.9, -0.9, -0.9);
    glEnd();

    glTranslatef(0.0, 1.0, 0.0);
    glBegin(GL_TRIANGLES);
      //
      glColor3f(0.7, 0.7, 1.0);
      glVertex3f(-1.0, -1.0, 1.0);
      glVertex3f(1.0, -1.0, 1.0);
      glVertex3f(0.0, 0.0, 0.0);

      //
      glColor3f(0.7, 0.5, 1.0);
      glVertex3f(-1.0, -1.0, -1.0);
      glVertex3f(1.0, -1.0, -1.0);
      glVertex3f(0.0, 0.0, 0.0);

            //
      glColor3f(0.0, 0.0, 1.0);
      glVertex3f(-1.0, -1.0, 1.0);
      glVertex3f(-1.0, -1.0, -1.0);
      glVertex3f(0.0, 0.0, 0.0);

      //
      glColor3f(0.5, 0.0, 1.0);
      glVertex3f(1.0, -1.0, 1.0);
      glVertex3f(1.0, -1.0, -1.0);
      glVertex3f(0.0, 0.0, 0.0);
    glEnd();

    glBegin(GL_QUADS);
      glColor3f(1.0, 0.7, 1.0);  /* green */
      glVertex3f(-1.0, -1.0, 1.0);
      glVertex3f(1.0, -1.0, 1.0);
      glVertex3f(1.0, -1.0, -1.0);
      glVertex3f(-1.0, -1.0, -1.0);
    glEnd();
}

void gambarRumah1(){
float difamb[] = {1.0,0.5,0.3,1.0};
    glTranslatef(-1.0,0.0,-6.0);
    glRotatef(angle,1.0,1.0,1.0);
    glBegin(GL_QUADS);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, difamb);

        //glNormal3f(0.0,0.0,0.9);
        glColor3f(0.0, 0.7, 0.1);
        glVertex3f(-0.9, 0.0, 0.9);
        glVertex3f(-0.7, 0.0, 0.9);
        glVertex3f(-0.7, -0.9, 0.9);
        glVertex3f(-0.9, -0.9, 0.9);

        //glNormal3f(0.0,0.0,0.9);
        glColor3f(0.0, 0.7, 0.1);
        glVertex3f(-0.3, 0.0, 0.9);
        glVertex3f(0.9, 0.0, 0.9);
        glVertex3f(0.9, -0.9, 0.9);
        glVertex3f(-0.3, -0.9, 0.9);

        //glNormal3f(0.0,0.0,0.9);
        glColor3f(0.0, 0.7, 0.1);
        glVertex3f(-0.3, 0.0, 0.9);
        glVertex3f(-0.7, 0.0, 0.9);
        glVertex3f(-0.7, -0.4, 0.9);
        glVertex3f(-0.3, -0.4, 0.9);

        //glNormal3f(0.0,0.0,0.9);
        glColor3f(0.5, 0.0, 0.5);
        glVertex3f(-0.3, -0.4, 0.9);
        glVertex3f(-0.7, -0.4, 0.9);
        glVertex3f(-0.7, -0.9, 0.9);
        glVertex3f(-0.3, -0.9, 0.9);

        /* back face */
        //glNormal3f(0.0,0.0,-0.9);
        glColor3f(0.9, 0.9, 0.0);  /* yellow */
        glVertex3f(-0.9, 0.0, -0.9);
        glVertex3f(0.9, 0.0, -0.9);
        glVertex3f(0.9, -0.9, -0.9);
        glVertex3f(-0.9, -0.9, -0.9);

        /* top side face */
        //glNormal3f(0.0,0.9,0.0);
        glColor3f(0.2, 0.2, 0.9);  /* blue */
        glVertex3f(-0.9, 0.0, 0.9);
        glVertex3f(0.9, 0.0, 0.9);
        glVertex3f(0.9, 0.0, -0.9);
        glVertex3f(-0.9, 0.0, -0.9);

        /* bottom side face */
        //glNormal3f(0.0,-0.9,0.0);
        glColor3f(0.7, 0.0, 0.1);  /* red */
        glVertex3f(-0.9, -0.9, 0.9);
        glVertex3f(0.9, -0.9, 0.9);
        glVertex3f(0.9, -0.9, -0.9);
        glVertex3f(-0.9, -0.9, -0.9);

        //left
        //glNormal3f(-0.9,0.0,0.0);
        glColor3f(0.9, 0.9, 0.9);
        glVertex3f(-0.9, -0.9, 0.9);
        glVertex3f(-0.9, 0.0, 0.9);
        glVertex3f(-0.9, 0.0, -0.9);
        glVertex3f(-0.9, -0.9, -0.9);

        //right
        //glNormal3f(0.9,0.0,0.0);
        glColor3f(0.9, -0.9, 0.9);
        glVertex3f(0.9, -0.9, 0.9);
        glVertex3f(0.9, 0.0, 0.9);
        glVertex3f(0.9, 0.0, -0.9);
        glVertex3f(0.9, -0.9, -0.9);
    glEnd();

    glTranslatef(0.0, 1.0, 0.0);

    glBegin(GL_QUADS);
      glColor3f(1.0, 0.7, 1.0);  /* green */
      glVertex3f(-1.0, 0.0, 0.0);
      glVertex3f(1.0, 0.0, 0.0);
      glVertex3f(1.0, -1.0, -1.0);
      glVertex3f(-1.0, -1.0, -1.0);

      glColor3f(1.0, 0.7, 0.0);  /* green */
      glVertex3f(-1.0, -1.0, 1.0);
      glVertex3f(1.0, -1.0, 1.0);
      glVertex3f(1.0, 0.0, 0.0);
      glVertex3f(-1.0, 0.0, 0.0);

      glColor3f(1.0, 0.7, 1.0);  /* green */
      glVertex3f(-1.0, -1.0, 1.0);
      glVertex3f(1.0, -1.0, 1.0);
      glVertex3f(1.0, -1.0, -1.0);
      glVertex3f(-1.0, -1.0, -1.0);
    glEnd();

    glBegin(GL_TRIANGLES);
      glColor3f(1.0, 0.5, 1.0);  /* green */
      glVertex3f(1.0, -1.0, 1.0);
      glVertex3f(1.0, 0.0, 0.0);
      glVertex3f(1.0, -1.0, -1.0);

      glColor3f(1.0, 0.5, 1.0);  /* green */
      glVertex3f(-1.0, -1.0, 1.0);
      glVertex3f(-1.0, 0.0, 0.0);
      glVertex3f(-1.0, -1.0, -1.0);
    glEnd();

    glTranslatef(2.5, -1.0, 0.0);
}

void gambarBola(){
const float DEG2RAD = 22.0/7/180;
int i, j, n=3;
float cx=0, cy=0, cz=0, cradius=1, pradius=1, tx, tz, px, py, pz;

    glTranslatef(0.0, 0.0,-6.0);
    glRotatef(angle, 0.0, 1.0, 0.0);
    glTranslatef(-2.0, 0.0, 0.0);

    //tumpukan lingkaran
    for (i=93; i < 270; i+=5){
        cz=sin(i*DEG2RAD);
        cradius=cos(i*DEG2RAD);
        glBegin(GL_LINE_LOOP);
        glColor3f(1.0, 1.0, 0.0);
        for (j=0; j < 360; j++){
            float degInRad = j*DEG2RAD;
            cx=cos(degInRad)*cradius;
            cy=sin(degInRad)*cradius;
            glVertex3f(cx, cy, cz);
        }
        glEnd();
    }

    //tumpukan segiempat
    glTranslatef(2.0, 0.0,0.0);
    for (i=93; i < 270; i+=9){
        cz=sin(i*DEG2RAD);
        cradius=cos(i*DEG2RAD);
        glBegin(GL_LINE_LOOP);
        glColor3f(1.0, 1.0, 0.0);
        for (j=0; j < 360; j+=90){
            float degInRad = j*DEG2RAD;
            cx=cos(degInRad)*cradius;
            cy=sin(degInRad)*cradius;
            glVertex3f(cx, cy, cz);
        }
        glEnd();
    }

    //bola
    glTranslatef(2.5, 0.0, 0.0);

    cy=sin((90+n)*DEG2RAD);
    cradius=cos((90+n)*DEG2RAD);
    for(i=96; i < 270; i+=n){
        py=cy;
        cy=sin(i*DEG2RAD);

        pradius=cradius;
        cradius=cos(i*DEG2RAD);

        glBegin(GL_QUADS);
        glColor3f(cradius, cy, 1.0);
        cx=cos(0)*cradius;
        cz=sin(0)*cradius;
        for (j=n; j <= 360; j+=n){
            float degInRad = j*DEG2RAD;
            px=cx;
            pz=cz;
            cx=cos(degInRad)*cradius;
            cz=sin(degInRad)*cradius;
            tx=cos(degInRad)*pradius;
            tz=sin(degInRad)*pradius;
            glVertex3f(cx, cy, cz);
            glVertex3f(px, cy, pz);
            glVertex3f(tx, py, tz);
            tx=cos(degInRad+n)*pradius;
            tz=sin(degInRad+n)*pradius;
            glVertex3f(tx, py, tz);
        }
        glEnd();
    }

    cy=sin((90+n)*DEG2RAD);
    cradius=cos((90+n)*DEG2RAD);
    glBegin(GL_TRIANGLES);
    for (i=0; i <= 360; i+=n){
        float degInRad = i*DEG2RAD;
        px=cx;
        pz=cz;
        cx=cos(degInRad)*cradius;
        cz=sin(degInRad)*cradius;
        glColor3f(cradius, cy, 1.0);
        glVertex3f(cx, cy, cz);
        glVertex3f(px, cy, pz);
        glVertex3f(0.0, 1.0, 0.0);
    }
    glEnd();

    cy=sin((270-n)*DEG2RAD);
    cradius=cos((270-n)*DEG2RAD);
    glBegin(GL_TRIANGLES);
    for (i=0; i <= 360; i+=n){
        float degInRad = i*DEG2RAD;
        px=cx;
        pz=cz;
        cx=cos(degInRad)*cradius;
        cz=sin(degInRad)*cradius;

        glColor3f(cradius, cy, 1.0);
        glVertex3f(cx, cy, cz);
        glVertex3f(px, cy, pz);
        glVertex3f(0.0, -1.0, 0.0);
    }
    glEnd();
}

void display(){
const float DEG2RAD = 22.0/7/180;
int i, n=derajat[nderajat];
float cx=0, cy=0, px, py;
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if(nderajat<24){
        glTranslatef(-3.0,0.0,-8.0);
        glColor3f(1.0, 1.0, 0.0);
        glBegin(GL_LINE_LOOP);
        for (i=0; i <= 360; i+=n){
            float degInRad = i*DEG2RAD;
            cx=cos(degInRad);
            cy=sin(degInRad);
            glVertex3f(cx, cy, 0.0);
        }
        glEnd();

        glTranslatef(2.1, 0.0, 0.0);
        cx=cos(0);
        cy=sin(0);
        glBegin(GL_TRIANGLES);
        for (i=n; i <= 360; i+=n){
            float degInRad = i*DEG2RAD;
            px=cx;
            py=cy;
            cx=cos(degInRad);
            cy=sin(degInRad);
            glVertex3f(cx, cy, 0.0);
            glVertex3f(px, py, 0.0);
            glVertex3f(0.0,0.0, 0.0);
        }
        glEnd();

        glTranslatef(2.0, 0.0, 0.0);
        glRotatef(-30, 1.0, 0.0, 0.0);
        cx=cos(0);
        cy=sin(0);
        glBegin(GL_TRIANGLES);
        for (i=n; i <= 360; i+=n){
            float degInRad = i*DEG2RAD;
            px=cx;
            py=cy;
            cx=cos(degInRad);
            cy=sin(degInRad);
            glVertex3f(cx, -1.0, cy);
            glVertex3f(px, -1.0, py);
            glVertex3f(0.0, -1.0, 0.0);
        }
        glEnd();

        cx=cos(0);
        cy=sin(0);
        glBegin(GL_TRIANGLES);
        for (i=n; i <= 360; i+=n){
            float degInRad = i*DEG2RAD;
            px=cx;
            py=cy;
            cx=cos(degInRad);
            cy=sin(degInRad);
            glColor3f(cx, 0.5, cy);
            glVertex3f(cx, -1.0, cy);
            glVertex3f(px, -1.0, py);
            glVertex3f(0.0, 1.0, 0.0);
        }
        glEnd();

        glTranslatef(2.1, 0.0, 0.0);
        cx=cos(0);
        cy=sin(0);
        glBegin(GL_TRIANGLES);
        glColor3f(1.0, 1.0, 0.0);
        for (i=n; i <= 360; i+=n){
            float degInRad = i*DEG2RAD;
            px=cx;
            py=cy;
            cx=cos(degInRad);
            cy=sin(degInRad);
            glVertex3f(cx, -1.0, cy);
            glVertex3f(px, -1.0, py);
            glVertex3f(0.0, -1.0, 0.0);
        }
        glEnd();

        cx=cos(0);
        cy=sin(0);
        glBegin(GL_QUADS);
        for (i=n; i <= 360; i+=n){
            float degInRad = i*DEG2RAD;
            px=cx;
            py=cy;
            cx=cos(degInRad);
            cy=sin(degInRad);
            glColor3f(1.0, cx, cy);
            glVertex3f(cx, 1.0, cy);
            glVertex3f(px, 1.0, py);
            glVertex3f(px, -1.0, py);
            glVertex3f(cx, -1.0, cy);
        }
        glEnd();

        cx=cos(0);
        cy=sin(0);
        glBegin(GL_TRIANGLES);
        for (i=n; i <= 360; i+=n){
            float degInRad = i*DEG2RAD;
            px=cx;
            py=cy;
            cx=cos(degInRad);
            cy=sin(degInRad);
            glVertex3f(cx, 1.0, cy);
            glVertex3f(px, 1.0, py);
            glVertex3f(0.0, 1.0, 0.0);
        }
        glEnd();
        nderajat++;
    }else if(nderajat<300){
        FPS=20;
        gambarBola();
        nderajat++;
    }else{
        glEnable(GL_LIGHTING);
        glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 128);
        glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 90);
        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1);
        glEnable(GL_LIGHT0);
        gambarRumah1();
        gambarRumah2();
    }
}

int main(int argc, char** argv){
        if (SDL_Init(SDL_INIT_VIDEO) < 0){
            return 0;
        }

        mainWindow = SDL_CreateWindow(programName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);

        mainContext = SDL_GL_CreateContext(mainWindow);

        SetOpenGLAttributes();
        SDL_GL_SetSwapInterval(1);

        int running = 1;
        FPS = 30;
        Uint32 start;
        SDL_Event event;
        if(init()==0)return 0;
        while(running) {
            start = SDL_GetTicks();
            while(SDL_PollEvent(&event)) {
                switch(event.type) {
                    case SDL_QUIT:
                        running = 0;
                        break;
                    case SDL_KEYDOWN:
                        switch(event.key.keysym.sym){
                            case SDLK_ESCAPE:
                                running = 0;
                                break;
                        }
                        break;
                }
            }

            display();
            SDL_GL_SwapWindow(mainWindow);
            angle += 0.5;
            if(angle > 360)
                angle -= 360;
            if(1000/FPS > SDL_GetTicks()-start)
                SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
        }
        SDL_Quit();
        return 0;
}

