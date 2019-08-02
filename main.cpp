// ========================================================================================
// ================================== Projeto CG 2019 =====================================
// ========================================================================================


// Carlos Diogo - 2015248994
// Renato Santos - 2015237457

// ========================================================================================

#ifdef __APPLE__
    #include <OpenGL/OpenGL.h>
    #include <GLUT/glut.h>
    #include <OpenGL/gl.h>
#else
    #include <GL/glut.h>
#endif

#include <stdio.h>

#include "RgbImage.h"
#include "materiais.h"
#include "math.h"

// g++ RgbImage.cpp main.cpp -framework OpenGL -framework GLUT -o main
// g++ -Wno-deprecated RgbImage.cpp main.cpp -framework OpenGL -framework GLUT -o main

//==================== Definir cores
#define BLUE         0.0, 0.0, 1.0, 1.0
#define RED         1.0, 0.0, 0.0, 1.0
#define YELLOW         1.0, 1.0, 0.0, 1.0
#define GREEN         0.0, 1.0, 0.0, 1.0
#define WHITE         1.0, 1.0, 1.0, 1.0
#define BLACK         0.0, 0.0, 0.0, 1.0
#define CYAN        0.0, 1.0, 1.0, 1.0
#define YELLOWISH   1.0, 0.7, 0.0, 1.0
#define BROWN       0.423, 0.30, 0.234, 1.0

#define PI         3.14159

GLfloat black[] = {BLACK};
GLfloat yellow[] = {YELLOW};
GLfloat cyan[] = {CYAN};
GLfloat blue[] = {BLUE};
GLfloat white[] = {WHITE};
GLfloat red[] = {RED};
GLfloat green[] = {GREEN};
GLfloat yellowish[] = {YELLOWISH};
GLfloat brown[] = {BROWN};

//============================ Variaveis e constantes
//----------------------------- Sistema Coordenadas
GLfloat xC=15.0, zC=15.0;
GLint wScreen = 800, hScreen = 600;
GLint msec = 100;                    //.. definicao do timer (actualizacao)

GLfloat incH =0.0, incV=0.0;
GLfloat incMaxH =0.5, incMaxV=0.35;

// texturas
RgbImage img;
GLuint textures[10];
//chama
GLuint chama[34];
GLint chamaAtual = 0; //frame

//------------------------
GLboolean pLight = GL_TRUE;
GLboolean lamp = GL_TRUE;

//------------------- Observador
GLfloat  rVisao=3.0, aVisao=0.5*PI, incVisao=1.0; //INC VISAO -- VELOCIDADE SETA
GLfloat  angPersp=109.0;

GLfloat  obsPini[] = {17.0, 7.0, static_cast<GLfloat>(0.5*xC)};
GLfloat obsPfin[] = {obsPini[0]-rVisao*cos(aVisao), obsPini[1], obsPini[2]-rVisao*sin(aVisao)};

//================================= MATERIAIS
GLvoid initMaterials(GLint material) {
    switch (material){
        case 0: //……………………………………………………………………………………………esmerald
            glMaterialfv(GL_FRONT,GL_AMBIENT,  esmeraldAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  esmeraldDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, esmeraldSpec);
            glMaterialf (GL_FRONT,GL_SHININESS,esmeraldCoef);
            break;
        case 1: //……………………………………………………………………………………………jade
            glMaterialfv(GL_FRONT,GL_AMBIENT,  jadeAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  jadeDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, jadeSpec);
            glMaterialf (GL_FRONT,GL_SHININESS,jadeCoef);
            break;
        case 2: //……………………………………………………………………………………………obsidian
            glMaterialfv(GL_FRONT,GL_AMBIENT,  obsidianAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  obsidianDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, obsidianSpec);
            glMaterialf (GL_FRONT,GL_SHININESS,obsidianCoef);
            break;
        case 3: //……………………………………………………………………………………………pearl
            glMaterialfv(GL_FRONT,GL_AMBIENT,  pearlAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  pearlDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, pearlSpec);
            glMaterialf (GL_FRONT,GL_SHININESS,pearlCoef);
            break;
        case 4: //……………………………………………………………………………………………ruby
            glMaterialfv(GL_FRONT,GL_AMBIENT,  rubyAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  rubyDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, rubySpec);
            glMaterialf (GL_FRONT,GL_SHININESS,rubyCoef);
            break;
        case 5: //……………………………………………………………………………………………turquoise
            glMaterialfv(GL_FRONT,GL_AMBIENT,  turquoiseAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  turquoiseDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, turquoiseSpec);
            glMaterialf (GL_FRONT,GL_SHININESS,turquoiseCoef);
            break;
        case 6: //……………………………………………………………………………………………brass
            glMaterialfv(GL_FRONT,GL_AMBIENT,  brassAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  brassDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, brassSpec);
            glMaterialf (GL_FRONT,GL_SHININESS,brassCoef);
            break;
        case 7: //……………………………………………………………………………………………bronze
            glMaterialfv(GL_FRONT,GL_AMBIENT,  bronzeAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  bronzeDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, bronzeSpec);
            glMaterialf (GL_FRONT,GL_SHININESS,bronzeCoef);
            break;
        case 8: //……………………………………………………………………………………………chrome
            glMaterialfv(GL_FRONT,GL_AMBIENT,  chromeAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  chromeDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, chromeSpec);
            glMaterialf (GL_FRONT,GL_SHININESS,chromeCoef);
            break;
        case 9: //……………………………………………………………………………………………copper
            glMaterialfv(GL_FRONT,GL_AMBIENT,  copperAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  copperDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, copperSpec);
            glMaterialf (GL_FRONT,GL_SHININESS,copperCoef);
            break;
        case 10: //……………………………………………………………………………………………gold
            glMaterialfv(GL_FRONT,GL_AMBIENT,  goldAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  goldDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, goldSpec);
            glMaterialf (GL_FRONT,GL_SHININESS,goldCoef);
            break;
        case 11: //……………………………………………………………………………………………silver
            glMaterialfv(GL_FRONT,GL_AMBIENT,  silverAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  silverDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, silverSpec);
            glMaterialf (GL_FRONT,GL_SHININESS,silverCoef);
            break;
        case 12: //……………………………………………………………………………………………blackPlastic
            glMaterialfv(GL_FRONT,GL_AMBIENT,  blackPlasticAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  blackPlasticDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, blackPlasticSpec);
            glMaterialf (GL_FRONT,GL_SHININESS,blackPlasticCoef);
            break;
        case 13: //……………………………………………………………………………………………cyankPlastic
            glMaterialfv(GL_FRONT,GL_AMBIENT,  cyanPlasticAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  cyanPlasticDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, cyanPlasticSpec);
            glMaterialf (GL_FRONT,GL_SHININESS,cyanPlasticCoef);
            break;
        case 14: //……………………………………………………………………………………………greenPlastic
            glMaterialfv(GL_FRONT,GL_AMBIENT,  greenPlasticAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  greenPlasticDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, greenPlasticSpec);
            glMaterialf (GL_FRONT,GL_SHININESS,greenPlasticCoef);
            break;
        case 15: //……………………………………………………………………………………………redPlastic
            glMaterialfv(GL_FRONT,GL_AMBIENT,  redPlasticAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  redPlasticDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, redPlasticSpec);
            glMaterialf (GL_FRONT,GL_SHININESS,redPlasticCoef);
            break;
        case 16: //……………………………………………………………………………………………yellowPlastic
            glMaterialfv(GL_FRONT,GL_AMBIENT,  whitePlasticAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  whitePlasticDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, whitePlasticSpec);
            glMaterialf (GL_FRONT,GL_SHININESS,whitePlasticCoef);
            break;
        case 17: //……………………………………………………………………………………………blackRubber
            glMaterialfv(GL_FRONT,GL_AMBIENT,  blackRubberAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  blackRubberDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, blackRubberSpec);
            glMaterialf (GL_FRONT,GL_SHININESS,blackRubberCoef);
            break;
        case 18: //……………………………………………………………………………………………cyanRubber
            glMaterialfv(GL_FRONT,GL_AMBIENT,  cyanRubberAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  cyanRubberDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, cyanRubberSpec);
            glMaterialf (GL_FRONT,GL_SHININESS,cyanRubberCoef);
            break;
        case 19: //……………………………………………………………………………………………greenRubber
            glMaterialfv(GL_FRONT,GL_AMBIENT,  greenRubberAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  greenRubberDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, greenRubberSpec);
            glMaterialf (GL_FRONT,GL_SHININESS,greenRubberCoef);
            break;
        case 20: //……………………………………………………………………………………………redRubber
            glMaterialfv(GL_FRONT,GL_AMBIENT,  redRubberAmb  );
            glMaterialfv(GL_FRONT,GL_DIFFUSE,  redRubberDif );
            glMaterialfv(GL_FRONT,GL_SPECULAR, redRubberSpec);
            glMaterialf (GL_FRONT,GL_SHININESS,redRubberCoef);
            break;
    }
}

GLvoid initTextures(GLvoid) {
    glGenTextures(20, textures);
    
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    img.LoadBmpFile("woodfloor.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 (GLint)img.GetNumCols(),
                 (GLint)img.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 img.ImageData());
    
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    img.LoadBmpFile("wall.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 (GLint)img.GetNumCols(),
                 (GLint)img.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 img.ImageData());
    
    glBindTexture(GL_TEXTURE_2D, textures[2]);
    img.LoadBmpFile("marmore.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 (GLint)img.GetNumCols(),
                 (GLint)img.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 img.ImageData());
    
    // pedra fogo
    glBindTexture(GL_TEXTURE_2D, textures[3]);
    img.LoadBmpFile( "pedra-fogo.bmp" );
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 (GLint)img.GetNumCols(),
                 (GLint)img.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 img.ImageData());
    
    
    glBindTexture(GL_TEXTURE_2D, textures[4]);
    img.LoadBmpFile("luzT.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 (GLint)img.GetNumCols(),
                 (GLint)img.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 img.ImageData());
    
    
    glBindTexture(GL_TEXTURE_2D, textures[5]);
    img.LoadBmpFile("floor.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 (GLint)img.GetNumCols(),
                 (GLint)img.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 img.ImageData());
    
    glBindTexture(GL_TEXTURE_2D, textures[6]);
    img.LoadBmpFile("madeira.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_INTERPOLATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 (GLint)img.GetNumCols(),
                 (GLint)img.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 img.ImageData());
    
    glBindTexture(GL_TEXTURE_2D, textures[7]);
    img.LoadBmpFile("ceu.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 (GLint)img.GetNumCols(),
                 (GLint)img.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 img.ImageData());
    
    glBindTexture(GL_TEXTURE_2D, textures[8]);
    img.LoadBmpFile("wood-stair.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_INTERPOLATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 (GLint)img.GetNumCols(),
                 (GLint)img.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 img.ImageData());
    
    glBindTexture(GL_TEXTURE_2D, textures[9]);
    img.LoadBmpFile("lamp.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 (GLint)img.GetNumCols(),
                 (GLint)img.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 img.ImageData());
}

// ======= lights =======
GLvoid initLights(GLvoid){
    
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, black); //ambiente
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    
    // lampada teto
    glLightfv(GL_LIGHT0, GL_AMBIENT, white);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.2);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.2);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0);
    glEnable(GL_LIGHT0);
    
    // luz pequena
    glLightfv(GL_LIGHT1, GL_AMBIENT, yellowish);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, yellowish);
    glLightfv(GL_LIGHT1, GL_SPECULAR, yellowish);
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 5); //1.8
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.9); //0
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.03); //0
    glEnable(GL_LIGHT1);
    
    //luz pequena 2
    glLightfv(GL_LIGHT2, GL_AMBIENT, yellowish);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, yellowish);
    glLightfv(GL_LIGHT2, GL_SPECULAR, yellowish);
    glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 5); //1.8
    glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.9); //0
    glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.03); //0
    glEnable(GL_LIGHT2);
    
    
    glLightfv(GL_LIGHT3, GL_AMBIENT, yellowish);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, yellowish);
    glLightfv(GL_LIGHT3, GL_SPECULAR, yellowish);
    glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 5); //1.8
    glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 0.9); //0
    glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 0.03); //0
    glEnable(GL_LIGHT3);
    
    glLightfv(GL_LIGHT4, GL_AMBIENT, yellowish);
    glLightfv(GL_LIGHT4, GL_DIFFUSE, yellowish);
    glLightfv(GL_LIGHT4, GL_SPECULAR, yellowish);
    glLightf(GL_LIGHT4, GL_CONSTANT_ATTENUATION, 5); //1.8
    glLightf(GL_LIGHT4, GL_LINEAR_ATTENUATION, 0.9); //0
    glLightf(GL_LIGHT4, GL_QUADRATIC_ATTENUATION, 0.03); //0
    glEnable(GL_LIGHT4);
    
    // luz da chama
    glLightfv(GL_LIGHT5, GL_AMBIENT, yellowish);
    glLightfv(GL_LIGHT5, GL_DIFFUSE, yellowish);
    glLightfv(GL_LIGHT5, GL_SPECULAR, yellowish);
    glLightf(GL_LIGHT5, GL_CONSTANT_ATTENUATION, 1.5);
    glLightf(GL_LIGHT5, GL_LINEAR_ATTENUATION, 0.07);
    glLightf(GL_LIGHT5, GL_QUADRATIC_ATTENUATION, 0.01);
    glEnable(GL_LIGHT5);

    glEnable(GL_LIGHTING);
}

GLvoid initChama(GLvoid) {
    glGenTextures(34, chama);
    char aux[34];
    for (GLint i=0; i<34; i++){
        glBindTexture(GL_TEXTURE_2D, chama[i]);
        sprintf(aux, "chama/%02d_flame.bmp", i);
        img.LoadBmpFile(aux);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexImage2D(GL_TEXTURE_2D, 0, 3,
                     (GLint)img.GetNumCols(),
                     (GLint)img.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                     img.ImageData());
    }
}

// =================================
GLvoid updateLights(GLvoid){
    GLfloat light0Pos[4] = {0, 21, -7.5, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);
    
    GLfloat light1Pos[4] = {-10, 15, -20, 1}; //{-6, 10.5, -20, 1}
    glLightfv(GL_LIGHT1, GL_POSITION, light1Pos);
    
    GLfloat light2Pos[4] = {10, 15, -20, 1}; //{-6, 10.5, -20, 1}
    glLightfv(GL_LIGHT2, GL_POSITION, light2Pos);
    
    //10, 15, 20
    GLfloat light3Pos[4] = {10, 15, 20, 1};
    glLightfv(GL_LIGHT3, GL_POSITION, light3Pos);
    
    GLfloat light4Pos[4] = {-10, 15, 20, 1};
    glLightfv(GL_LIGHT4, GL_POSITION, light4Pos);
    
    // chama
    GLfloat light5Pos[4] = {-24, 5.5, -5, 1}; // -24, 5.5, -5
    glLightfv(GL_LIGHT5, GL_POSITION, light5Pos);
}

GLvoid cubeForm(GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ, GLfloat dim, GLfloat repeatS, GLfloat repeatT, GLuint texture){
    GLint x = scaleX * dim;
    GLint y = scaleY * dim;
    
    if(x < 1)
        x = 1;
    if(y < 1)
        y = 1;
    
    glPushMatrix();
        glScalef(scaleX, scaleY, scaleZ);
    
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
    
        glNormal3f(0, 0, 1);
        glPushMatrix();
        glTranslatef(0, 0, 0.5);
    
        // ----PAREDE frontal
            glPushMatrix();
                glTranslatef(-0.5,-0.5,0);  // meio do poligono
                glBegin(GL_QUADS);
                for (GLint i=0;i<y;i++) {
                    for (GLint j=0;j<x;j++) {
                        glTexCoord2f(j*repeatS/x, i*repeatT/y);
                        glVertex3d((GLfloat)j/x,(GLfloat)i/y,0);
                        
                        glTexCoord2f( (j+1) * repeatS/x, i*repeatT/y);
                        glVertex3d( (GLfloat) (j+1)/x, (GLfloat)i/y, 0);
                        
                        glTexCoord2f((j+1)*repeatS/x, (i+1)*repeatT/y);
                        glVertex3d((GLfloat)(j+1)/x,(GLfloat)(i+1)/y,0);
                        
                        glTexCoord2f(j*repeatS/x,(i+1)*repeatT/y);
                        glVertex3d((GLfloat)j/x,(GLfloat)(i+1)/y,0);
                    }
                }
                glEnd();
            glPopMatrix();
        // -------------
    
        glTranslatef(0, 0, -1);
        glRotatef(180, 0, 1, 0);
    
        // ------ PAREDE atras
            glPushMatrix();
            glTranslatef(-0.5,-0.5,0);  // meio do poligono
            glBegin(GL_QUADS);
            for (GLint i=0;i<y;i++) {
                for (GLint j=0;j<x;j++) {
                    glTexCoord2f(j*repeatS/x, i*repeatT/y);
                    glVertex3d((GLfloat)j/x,(GLfloat)i/y,0);
                    
                    glTexCoord2f( (j+1) * repeatS/x, i*repeatT/y);
                    glVertex3d( (GLfloat) (j+1)/x, (GLfloat)i/y, 0);
                    
                    glTexCoord2f((j+1)*repeatS/x, (i+1)*repeatT/y);
                    glVertex3d((GLfloat)(j+1)/x,(GLfloat)(i+1)/y,0);
                    
                    glTexCoord2f(j*repeatS/x,(i+1)*repeatT/y);
                    glVertex3d((GLfloat)j/x,(GLfloat)(i+1)/y,0);
                }
            }
            glEnd();
            glPopMatrix();
        // END -----------
        glPopMatrix();
    
        glPushMatrix();
        glTranslatef(0.5, 0, 0);
        glRotatef(90, 0, 1, 0);
    
        // PAREDE DIREITA
            glPushMatrix();
            glTranslatef(-0.5,-0.5,0);  // meio do poligono
            glBegin(GL_QUADS);
            for (GLint i=0;i<y;i++) {
                for (GLint j=0;j<x;j++) {
                    glTexCoord2f(j*repeatS/x, i*repeatT/y);
                    glVertex3d((GLfloat)j/x,(GLfloat)i/y,0);
                    
                    glTexCoord2f( (j+1) * repeatS/x, i*repeatT/y);
                    glVertex3d( (GLfloat) (j+1)/x, (GLfloat)i/y, 0);
                    
                    glTexCoord2f((j+1)*repeatS/x, (i+1)*repeatT/y);
                    glVertex3d((GLfloat)(j+1)/x,(GLfloat)(i+1)/y,0);
                    
                    glTexCoord2f(j*repeatS/x,(i+1)*repeatT/y);
                    glVertex3d((GLfloat)j/x,(GLfloat)(i+1)/y,0);
                }
            }
            glEnd();
            glPopMatrix();
        // ---- END
        glPopMatrix();
    
        glPushMatrix();
        glTranslatef(-0.5, 0, 0);
        glRotatef(-90, 0, 1, 0);
        //--- PAREDE ESQUERDA
            glPushMatrix();
            glTranslatef(-0.5,-0.5,0);  // meio do poligono
            glBegin(GL_QUADS);
            for (GLint i=0;i<y;i++) {
                for (GLint j=0;j<x;j++) {
                    glTexCoord2f(j*repeatS/x, i*repeatT/y);
                    glVertex3d((GLfloat)j/x,(GLfloat)i/y,0);
                    
                    glTexCoord2f( (j+1) * repeatS/x, i*repeatT/y);
                    glVertex3d( (GLfloat) (j+1)/x, (GLfloat)i/y, 0);
                    
                    glTexCoord2f((j+1)*repeatS/x, (i+1)*repeatT/y);
                    glVertex3d((GLfloat)(j+1)/x,(GLfloat)(i+1)/y,0);
                    
                    glTexCoord2f(j*repeatS/x,(i+1)*repeatT/y);
                    glVertex3d((GLfloat)j/x,(GLfloat)(i+1)/y,0);
                }
            }
            glEnd();
            glPopMatrix();
        // --- END PAREDE ESQUERDA
        glPopMatrix();
    
        glPushMatrix();
        glTranslatef(0, -0.5, 0);
        glRotatef(90, 1, 0, 0);
        // -----CHAO
        glPushMatrix();
        glTranslatef(-0.5,-0.5,0);  // meio do poligono
        glBegin(GL_QUADS);
        for (GLint i=0;i<y;i++) {
            for (GLint j=0;j<x;j++) {
                glTexCoord2f(j*repeatS/x, i*repeatT/y);
                glVertex3d((GLfloat)j/x,(GLfloat)i/y,0);
                
                glTexCoord2f( (j+1) * repeatS/x, i*repeatT/y);
                glVertex3d( (GLfloat) (j+1)/x, (GLfloat)i/y, 0);
                
                glTexCoord2f((j+1)*repeatS/x, (i+1)*repeatT/y);
                glVertex3d((GLfloat)(j+1)/x,(GLfloat)(i+1)/y,0);
                
                glTexCoord2f(j*repeatS/x,(i+1)*repeatT/y);
                glVertex3d((GLfloat)j/x,(GLfloat)(i+1)/y,0);
            }
        }
        glEnd();
        glPopMatrix();
        // --- END CHAO
    
        glPopMatrix();
    
        glPushMatrix();
        glTranslatef(0, 0.5, 0);
        glRotatef(-90, 1, 0, 0);
        // --- TETO
            glPushMatrix();
            glTranslatef(-0.5,-0.5,0);  // meio do poligono
            glBegin(GL_QUADS);
            for (GLint i=0;i<y;i++) {
                for (GLint j=0;j<x;j++) {
                    glTexCoord2f(j*repeatS/x, i*repeatT/y);
                    glVertex3d((GLfloat)j/x,(GLfloat)i/y,0);
                    
                    glTexCoord2f( (j+1) * repeatS/x, i*repeatT/y);
                    glVertex3d( (GLfloat) (j+1)/x, (GLfloat)i/y, 0);
                    
                    glTexCoord2f((j+1)*repeatS/x, (i+1)*repeatT/y);
                    glVertex3d((GLfloat)(j+1)/x,(GLfloat)(i+1)/y,0);
                    
                    glTexCoord2f(j*repeatS/x,(i+1)*repeatT/y);
                    glVertex3d((GLfloat)j/x,(GLfloat)(i+1)/y,0);
                }
            }
            glEnd();
            glPopMatrix();
        // --- END TETO
    glPopMatrix();
    
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

GLvoid desenhaRectangulo(GLint tx, GLfloat tam, GLint tz)
{
    glPushMatrix();
    //glBindTexture(GL_TEXTURE_2D, textures[6]);
    glTranslatef(tx, tam, tz); // tam = Y
    glScalef(2, tam, 0.3);
    glutSolidCube(6);
    glPopMatrix();
}

GLvoid drawEscada(GLvoid){
    //texturas
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    
    GLfloat t = 0.00; //tamanho degrau
    for (int i=0; i<7;i++){
        glBindTexture(GL_TEXTURE_2D, textures[6]);
        desenhaRectangulo(0, t, i);
        t+=0.15;
    }
    //plano
    for (int i=0;i<2;i++){
        glBindTexture(GL_TEXTURE_2D, textures[8]);
        desenhaRectangulo(0, t, 7+i); // lance
    }
    //degraus
    for (int i=9; i<16;i++){
        glBindTexture(GL_TEXTURE_2D, textures[6]);
        desenhaRectangulo(0, t, i);
        t+=0.15;
    }
    //plano
    for (int i=0;i<2;i++){
        glBindTexture(GL_TEXTURE_2D, textures[8]);
        desenhaRectangulo(0, t, 16+i);
    }
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_2D);
}

GLvoid drawWalls(GLvoid) {
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, brown);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, brown);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128);
    cubeForm(50, 1, 48, 0.5, 5, 5, textures[0]); // chao
    
    // teto
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128);
    glPushMatrix();
    glTranslatef(0, 29, 0);
    cubeForm(50, 1, 48, 0.5, 3, 3, textures[1]); // teto
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, 14.5, 24.5);
    cubeForm(50, 30, 1, 0.5, 3, 3, textures[1]);    //wall 1
    glTranslatef(0, 0, -49);
    cubeForm(50, 30, 1, 0.5, 3, 3, textures[1]);    //wall 2
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(25.5, 14.5, 0);
    cubeForm(1, 30, 50, 0.5, 3, 3, textures[1]); //wall 3
    glTranslatef(-51, 0, 0);
    cubeForm(1, 30, 50, 0.5, 3, 3, textures[1]); //wall 4
    glPopMatrix();
}

GLvoid draw2ndFloor(GLvoid){
    glEnable(GL_TEXTURE_2D);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, brown);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128); // 128 e valor maximo
    
    glBindTexture(GL_TEXTURE_2D, textures[2]);
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    
    glScalef(0.25, 1, 1);
    glMatrixMode(GL_MODELVIEW);
    GLUquadric* quad = gluNewQuadric();
    gluQuadricTexture(quad, GLU_TRUE);
    
    //suporte 1
    glPushMatrix();
        glTranslatef(-14, 0, 17);
        glRotatef(-90, 1, 0, 0);
        gluCylinder(quad, 0.5, 0.5, 7.5 , 8, 8);
    glPopMatrix();
    
    //suporte 2
    glPushMatrix();
        glTranslatef(14, 0, 17);
        glRotatef(-90, 1, 0, 0);
        gluCylinder(quad, 0.5, 0.5, 7.5, 8, 8);
    glPopMatrix();
    
    //seguranda suporte
    glPushMatrix();
    glTranslatef(4.1, 8, 13);
    glRotatef(-90, 1, 0, 0);
    gluCylinder(quad, 0.1, 0.2, 2, 4, 4);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(10.1, 8, 13);
    glRotatef(-90, 1, 0, 0);
    gluCylinder(quad, 0.1, 0.2, 2, 4, 4);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(16.1, 8, 13);
    glRotatef(-90, 1, 0, 0);
    gluCylinder(quad, 0.1, 0.2, 2, 4, 4);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(22.1, 8, 13);
    glRotatef(-90, 1, 0, 0);
    gluCylinder(quad, 0.1, 0.2, 2, 4, 4);
    glPopMatrix();
    
    //seguranca suporte
    glPushMatrix();
    glTranslatef(-4.1, 8, 13);
    glRotatef(-90, 1, 0, 0);
    gluCylinder(quad, 0.1, 0.2, 2, 4, 4);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-10.1, 8, 13);
    glRotatef(-90, 1, 0, 0);
    gluCylinder(quad, 0.1, 0.2, 2, 4, 4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-16.1, 8, 13);
    glRotatef(-90, 1, 0, 0);
    gluCylinder(quad, 0.1, 0.2, 2, 4, 4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-22.1, 8, 13);
    glRotatef(-90, 1, 0, 0);
    gluCylinder(quad, 0.1, 0.2, 2, 4, 4);
    glPopMatrix();

    gluDeleteQuadric(quad);
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glRotatef(-90, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    
    // ----- piso ------
    glPushMatrix();
        glTranslatef(0, 8, 18);
        cubeForm(50, 1, 12, 1, 4, 1, textures[5]);
    glPopMatrix();
    // ------------------
    
    // apoio seguranca
    glPushMatrix();
        glTranslatef(14, 10, 13);
        cubeForm(20, 0.2, 0.5, 1, 1, 1, textures[2]);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(14, 9.5, 13);
    cubeForm(20, 0.2, 0.5, 1, 1, 1, textures[2]);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(14, 9.0, 13);
    cubeForm(20, 0.2, 0.5, 1, 1, 1, textures[2]);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-14, 10, 13);
    cubeForm(20, 0.2, 0.5, 1, 1, 1, textures[2]);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-14, 9.5, 13);
    cubeForm(20, 0.2, 0.5, 1, 1, 1, textures[2]);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-14, 9.0, 13);
    cubeForm(20, 0.2, 0.5, 1, 1, 1, textures[2]);
    glPopMatrix();
    
    glDisable(GL_TEXTURE_2D);
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
}

GLvoid drawLamp(GLvoid){
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128);
    
    initMaterials(12);
    
    glPushMatrix();
        glTranslatef(0, 25, 0);
        glScalef(0.1, 7, 0.1);
        glutSolidCube(0.7);    //fio 1
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(0, 25, -5);
        glScalef(0.1, 7, 0.1);
        glutSolidCube(0.7);    //fio 2
    glPopMatrix();
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textures[9]);
    
    GLUquadric* quad = gluNewQuadric();
    gluQuadricTexture(quad, GLU_TRUE);
    if (lamp)
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, white);
    glPushMatrix();
        glTranslatef(0, 23, -7.5);
        glScalef(3.5, 1, 2.5);
        gluCylinder(quad, 0.5, 0.5, 4, 8, 8);
    glPopMatrix();
    if (lamp)
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
    glDisable(GL_TEXTURE_2D);
    gluDeleteQuadric(quad);
}

GLvoid drawLights(GLvoid){
    initMaterials(16);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textures[4]);
    GLUquadric* quad = gluNewQuadric();
    gluQuadricTexture(quad, GLU_TRUE);
    
    if (pLight) // luzes de presenca amarela
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, yellowish);
    
    //luz 1
    glPushMatrix();
        glTranslatef(-10, 20, -24); //-10, 10, -20, 1 -> posicao luz
        glScalef(1, 1, 1);
        gluSphere(quad, 1, 3, 3);    //lampada
    glPopMatrix();
    
    //luz 2
    glPushMatrix();
    glTranslatef(10, 20, -24); //-10, 10, -20, 1 -> posicao luz
    glScalef(1, 1, 1);
    gluSphere(quad, 1, 3, 3);    //lampada
    glPopMatrix();
    
    //luz 3
    glPushMatrix();
    glTranslatef(10, 20, 24); //-10, 10, -20, 1 -> posicao luz
    glScalef(1, 1, 1);
    gluSphere(quad, 1, 3, 3);    //lampada
    glPopMatrix();

    
    //luz 4
    glPushMatrix();
    glTranslatef(-10, 20, 24); //-10, 10, -20, 1 -> posicao luz
    glScalef(1, 1, 1);
    gluSphere(quad, 1, 3, 3);    //lampada
    glPopMatrix();

    if (pLight)
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
    
    glDisable(GL_TEXTURE_2D);
    gluDeleteQuadric(quad);
}

GLvoid drawEsferaSky(GLvoid){
    glDisable(GL_LIGHTING);
    
    GLUquadricObj*  sky = gluNewQuadric ();
    GLfloat sizeSky = 30;
    
    glEnable(GL_TEXTURE_2D);
    // ativar textura
    glBindTexture(GL_TEXTURE_2D,textures[7]);
    
    glPushMatrix();
        // Desenhar esfera + Textura
        glRotatef (90, -1, 0, 0);
        gluQuadricDrawStyle(sky, GLU_FILL);
        gluQuadricNormals(sky, GLU_SMOOTH);
        gluQuadricTexture(sky, GL_TRUE);
        gluSphere (sky, sizeSky*2, 1000, 1000);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    gluDeleteQuadric(sky);
}

GLvoid drawEspelho(GLvoid){
    glPushMatrix();
        glTranslatef(0, 7.5, -24); //-24
        glBegin(GL_QUADS);
            glVertex3f (-10, -3, 0.5);
            glVertex3f (10, -3, 0.5);
            glVertex3f (10, 7, 0.5);
            glVertex3f (-10, 7, 0.5);
        glEnd();
    glPopMatrix();
}

GLvoid drawBorderEspelho(GLvoid){
    glPushMatrix();
    glTranslatef(0, 7.5, -24.2); //-24
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textures[5]);
    glBegin(GL_QUADS);
        glVertex3f (-11, -4, 0.5);
        glVertex3f (11, -4, 0.5);
        glVertex3f (11, 8, 0.5);
        glVertex3f (-11, 8, 0.5);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glPopMatrix();
}

// --- CHAMA ----
GLvoid drawChama(GLvoid) {
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);
    
    glBindTexture(GL_TEXTURE_2D, chama[chamaAtual]);
    chamaAtual = (chamaAtual + 1) % 34;
    glPushMatrix();
    
    //posicao
    glTranslatef(-24, 5.5, -5);
    glScalef(0.2, 7.0, 10.0);
    
    glRotatef(90 - aVisao, 0, 1, 0);
    // CHAMAA
    glBegin(GL_QUADS);
        glTexCoord2d(0,0); glVertex3f(-1, -1, 0);
        glTexCoord2d(1,0); glVertex3f( 1, -1, 0);
        glTexCoord2d(1,1); glVertex3f( 1,  1, 0);
        glTexCoord2d(0,1); glVertex3f(-1,  1, 0);
    glEnd();
    glPopMatrix();
    
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
}

GLvoid drawSuportChama(GLvoid){
    glPushMatrix();
    glTranslatef(-21.5, 0.3, -5);
    cubeForm(1, 2.5, 8, 1, 0.3, 1, textures[3]);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-23, 0.3, -9);
    cubeForm(4, 5.5, 0.8, 1, 0.3, 1, textures[3]);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-23, 0.3, -1);
    cubeForm(4, 5.5, 0.8, 1, 0.3, 1, textures[3]);
    glPopMatrix();
}

// ===============================================================================
// ============================ INICIALIZAR ======================================
// ===============================================================================

GLvoid initEspelho(GLvoid){
    glFrontFace(GL_CCW);
    glPolygonMode(GL_FRONT, GL_FILL);
    glEnable(GL_COLOR_MATERIAL);
}

GLvoid init(GLvoid) {
    glClearColor(WHITE);  //…………………………………………………Apagar
    glEnable(GL_DEPTH_TEST); //………………………………………………………Profundidade
    glShadeModel(GL_SMOOTH); //………………………………………………Interpolacao de cores
    glEnable(GL_NORMALIZE);
 
    initEspelho();
    initTextures();
    initLights();
    initChama();
}

GLvoid drawScene(GLvoid){
    glPushMatrix();
        drawWalls();
        draw2ndFloor();
        drawLamp();
        drawLights();
        drawChama();
        drawSuportChama();
        drawBorderEspelho();
        glPushMatrix();
            glTranslatef(0, 0, -6);
            drawEscada();
        glPopMatrix();
        drawEsferaSky();
    glPopMatrix();
}

GLvoid espelho(GLvoid){
    glPushMatrix();
    glColorMask(0,0,0,0); // nao escreve no colorBUF
    glDisable(GL_DEPTH_TEST); //nao considerar profundidade
    
    // ativa o uso do stencil buffer
    glEnable( GL_STENCIL_TEST );
    
    glStencilFunc(GL_ALWAYS, 1, 1 ); //passa sempre teste
    glStencilOp( GL_REPLACE, GL_REPLACE, GL_REPLACE ); //substitui por ref = 1
    
    // escrever no colorBuffer
    glColorMask(1,1,1,1);
    glEnable(GL_DEPTH_TEST); //ativar Zbuffer
    glClear(GL_STENCIL_BUFFER_BIT);
    // desenha so na zona do Stencil Buff
    glStencilFunc(GL_EQUAL,1,1);
    
    drawEspelho();
    // stencil buffer apenas le
    glStencilOp( GL_KEEP, GL_KEEP, GL_KEEP ); //stencil fica igual
    
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    GLdouble cenario[4] = {0.0, 0.0, -15.0, 0.0 };
    // desenhar imagem do espelho
    glPushMatrix();
        // inverte imagem pelo plano xy
        glTranslatef(0, 0, -24);
        glScalef( 1.0, 1.0, -1.0);
    
        if(cos(aVisao * PI / 180.0 ) < 0.0){
            cenario[2] = -1.0;
        }
        else{
            cenario[2] = 1.0;
        }
        // dividir cenario
        glClipPlane(GL_CLIP_PLANE0, cenario);
        glEnable(GL_CLIP_PLANE0);
        // desenha o cenario
        glTranslatef(0, 0, 23);
        drawScene();
        glDisable(GL_CLIP_PLANE0);
    glPopMatrix();
    
    // desativa stencil buffer - desenhar em todo o lado
    glDisable(GL_STENCIL_TEST);
    
    //desativar escrita para o color color buffer
    GLint buffers = GL_NONE;
    // busca cor atual do buffer para escrever
    glGetIntegerv( GL_DRAW_BUFFER, &buffers );
    // desativar escrita para o color color buffer
    glDrawBuffer(GL_NONE);
    drawEspelho();
    // escrever para o color buffer
    glDrawBuffer( (GLenum) buffers);
    // desenha cenario normal
    drawScene();

    glPopMatrix( );
    
    glFlush();
}

GLvoid display(GLvoid) {
    // ------ apaga ecra / profundidade / reflexo
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glLoadIdentity();
   
    // visualizacao
    glViewport (0, 0, wScreen, hScreen);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(angPersp, (GLfloat)wScreen/hScreen, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(obsPini[0], obsPini[1], obsPini[2], obsPfin[0], obsPfin[1], obsPfin[2], 0, 1, 0);
    
    updateLights();
    espelho();
    
    // ~~~~~~~~ atualizacao
    glutSwapBuffers();
}


GLvoid reshape(GLint larg, GLint alt) {
    wScreen = larg;
    hScreen = alt;
    
    if (wScreen == 0 || hScreen == 0)
        return;
    
    glViewport(0,0,wScreen,hScreen);
    
    glutPostRedisplay();
}

GLvoid Timer(GLint value)
{
    glutPostRedisplay();
    glutTimerFunc(msec,Timer, 1);
}


GLvoid updateVisao(GLvoid){
    obsPfin[0] =obsPini[0]+rVisao*cos(aVisao);
    obsPfin[2] =obsPini[2]-rVisao*sin(aVisao);
    glutPostRedisplay();
}

GLvoid teclasNotAscii(GLint key, GLint x, GLint y)
{
    if(key == GLUT_KEY_UP) {
        obsPini[0]=obsPini[0]+incVisao*cos(aVisao);
        obsPini[2]=obsPini[2]-incVisao*sin(aVisao);
    }
    if(key == GLUT_KEY_DOWN) {
        obsPini[0]=obsPini[0]-incVisao*cos(aVisao);
        obsPini[2]=obsPini[2]+incVisao*sin(aVisao);
    }
    if(key == GLUT_KEY_LEFT)
        aVisao = (aVisao + 0.1) ;
    
    if(key == GLUT_KEY_RIGHT)
        aVisao = (aVisao - 0.1) ;
    
    updateVisao();
}

//================= EVENTOS
GLvoid keyboard(unsigned char key, GLint x, GLint y){
    switch (key) {
        // lampada branca
        case 'l': case 'L':
            lamp=!lamp;
            if(lamp){
                glEnable(GL_LIGHT0);
            }
            else{
                glDisable(GL_LIGHT0);
            }
            glutPostRedisplay();
            break;
        // luzes pequenas amarelas
        case 'p': case 'P':
            pLight = !pLight;
            if(pLight){
                glEnable(GL_LIGHT1);
                glEnable(GL_LIGHT2);
                glEnable(GL_LIGHT3);
                glEnable(GL_LIGHT4);
            }
            else{
                glDisable(GL_LIGHT1);
                glDisable(GL_LIGHT2);
                glDisable(GL_LIGHT3);
                glDisable(GL_LIGHT4);
            }
            glutPostRedisplay();
            break;

            //--------------------------- Altura observador
        case 'q': case 'Q':
            obsPini[1]=obsPini[1]+1;
            glutPostRedisplay();
            break;
        case 'a': case 'A':
            obsPini[1]=obsPini[1]-1;
            glutPostRedisplay();
            break;
        
        //--------------------------- Escape
        case 27:
            exit(0);
            break;
    }
}

GLint main(GLint argc, GLchar **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL); // | GLUT_STENCIL
    glutInitWindowSize(wScreen,hScreen);
    glutInitWindowPosition (400, 200);

    glutCreateWindow ("Obs:'SETAS' | Luzes: P | lamp: L | Alt. Obs. Q-A || Carlos Diogo | Renato Santos || DEI-UC ");

    init();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(teclasNotAscii);
    glutKeyboardFunc(keyboard);

    glutTimerFunc(msec, Timer, 1);

    glutMainLoop();
}

