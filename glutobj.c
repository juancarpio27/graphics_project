/*
 * Proyecto Final, Museo de antropologia / artistic museum
 * Juan Andres Carpio A01021224
 * César Millán A01371813
 */

# ifdef _WIN32
    #include <windows.h>
# endif
#ifdef __APPLE__
    #include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
    #include <GL/gl.h>
    #include <GL/glut.h>
#endif

#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "glm.h"
#include "SOIL.h"

/*****
 ** 
 **  Constants
 ** 
 *****/
#define bool int
#define true 1
#define false 0

#define inside 1
#define outside 0

/*****
 ** 
 **  Camera data
 ** 
 *****/
float camX=0.0, camY=2.0, camZ=50.0;
float rotationAngle = 0.0;


/*****
 ** 
 **  View modes
 ** 
 *****/
int SOLID = true;
int show_info = true;
int VIEW_MODE =  outside;

/*****
 ** 
 **  Data
 ** 
 *****/
GLuint mode = GLM_SMOOTH;
GLUquadric* qobj;
int ww, wh;
void *Help_Font = GLUT_BITMAP_8_BY_13;
int linestart = 10;     /* start point on y axis for text lines */
int linespace = 20;     /* spac betwwen text lines */  
static GLuint texName[31];   

/*****
 ** 
 **  Museum colors
 ** 
 *****/
GLfloat wallColor [] = { 0.827, 0.827, 0.827, 0.65}; //gray wall
GLfloat floorColor [] = { 0.663, 0.663, 0.663, 0.6}; //gray floor
GLfloat paraguasColor []  = {0.07, 0.24, 0.22, 0.6}; //dark aquamarine
GLfloat doorColor []  = {0.74, 0.33, 0.18, 0.65}; //brown
GLfloat benchColor []  = {0.74, 0.33, 0.18, 0.6}; //brown
GLfloat noMat[] = {0.0,0.0,0.0, 0.0}; //black
GLfloat matSpecular[] = {1.0, 1.0, 1.0, 1.0}; //white
GLfloat blue[] = {0.118, 0.565, 1.000,0.4}; //blue
GLfloat light_blue[] = {0.529, 0.808, 0.980,0.4}; //light_blue
GLfloat green[] = {0.133, 0.545, 0.133, 0.6}; //green

/*****
 ** 
 **  Objects
 ** 
 *****/
GLMmodel *plant = NULL;
GLMmodel *bench = NULL;
GLMmodel *high_lamp = NULL;
GLMmodel *wall_lamp = NULL;
GLMmodel *bookcase = NULL;
GLMmodel *car1 = NULL;
GLMmodel *car2 = NULL;
GLMmodel *car3 = NULL;
GLMmodel *tree = NULL;


/*****************************************************************************/
/*Functions*******************************************************************/
/*****************************************************************************/

/*****
 ** 
 **  Menu functions
 ** 
 *****/
void menu(int value);
void HelpDisplay(GLint ww, GLint wh);
void HelpRenderBitmapString(float x, float y, void *font, char *string);

/*****
 ** 
 **  Callback functions
 ** 
 *****/
void Reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);

/*****
 ** 
 **  Draw parts
 ** 
 *****/
void drawDoor(int solid, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z,
              float s_x, float s_y, float s_z, float degrees);
void drawBench(int solid, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z,
              float s_x, float s_y, float s_z, float degrees);
void drawCube(int solid, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z,
              float s_x, float s_y, float s_z, float degrees);
void drawRoom(float t_x, float t_y, float t_z, float s_x, float s_y, float s_z, float r_x, 
              float r_y, float r_z, float degrees);
void drawFloor(float t_x, float t_y, float t_z, float s_x, float s_y, float s_z, float r_x, 
               float r_y, float r_z, float degrees);
void drawObject(GLMmodel *pmodel, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z,
              float s_x, float s_y, float s_z, float degrees);
void drawPaint(float t_x, float t_y, float t_z, float s_x, 
               float s_y, float s_z, float r_x, float r_y, 
               float r_z, float degrees, int index);

/*****
 ** 
 **  Draw museum parts
 ** 
 *****/
void elParaguas(); 
void patioCentral();
void accessoPrincipal();
void paintStatue(float t_x, float t_y, float t_z);
void bibliotecaAuditorio();
void salaCulturasDelGolfo();
void salaOaxaca();
void salaCulturasDelNorte();
void salaTeotihuacanaTolteca();
void salaMexica();
void drawParking();
void drawMuseum();



/*****
 ** 
 **  Objects and textures functions
 ** 
 *****/
void drawPaint(float t_x, float t_y, float t_z, float s_x, 
               float s_y, float s_z, float r_x, float r_y, 
               float r_z, float degrees, int index);
void drawRenascement();
void drawImpresionism();
void drawFrida();
void drawCubism();
void drawContemporary();
void drawPictures();
void display(void);
void loadObjects();
void loadObjects();
void loadtexture(int index, char file[]);
void loadPictures();
void loadRenascement();
void loadImpresionism();
void loadFrida();
void loadCubism();
void loadContemporary();


/*****
 ** 
 **  Initial configuration
 ** 
 *****/
void init(void);

/*****
 ** 
 **  Materials
 ** 
 *****/
void print_materials(GLfloat * ambient, GLfloat * diffuse, GLfloat * specular, float s);


/*****************************************************************************/
/*Main Functions**************************************************************/
/*****************************************************************************/
int main(int argc, char **argv)
{
    int i;

    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1024, 768);	/*  Window Size If We Start In Windowed Mode */
    glutCreateWindow("Museo");
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(Reshape);

    glutCreateMenu(menu);
    glutAddMenuEntry("View from the inside", 0);
    glutAddMenuEntry("View from the outside", 1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutSpecialFunc(keyboard);
    glutIdleFunc(NULL);
    glutMainLoop();

    return 0;
}

/*****************************************************************************/
/*Program Functions***********************************************************/
/*****************************************************************************/

/*
 * Function that executes when every option of the menu is clicked
 */
void menu(int value) {
    switch (value) {
        case 0:
            VIEW_MODE = inside;
            break;
        case 1:
            VIEW_MODE = outside;
            break;
    }
    glutPostRedisplay();
}

/*
 * Window size function and view configuration
 */
void Reshape(int w, int h) {
    //Data required for the help menu
    ww = w;
    wh = h;
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //Perspective view configuration. 0.01 near so the camera can see like an human eye
    gluPerspective(60.0, (double) w / (double) h, 0.01,1000.0);
    glMatrixMode(GL_MODELVIEW);
}


/*
 * Function that draws a door
 * solid: true for solid cube, false for wire cube
 * t_x,t_y,t_z: translation
 * r_x,r_y,r_z: rotation
 * s_x,s_y,s_z: scale
 * degrees: degrees of rotation
 */
void drawDoor(int solid, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z,
              float s_x, float s_y, float s_z, float degrees){
    print_materials(noMat, doorColor, matSpecular,100.0);
    drawCube(solid, t_x, t_y, t_z, r_x, r_y, r_z, s_x, s_y, s_z, degrees);
}

/*
 * Function that draws a bench
 * solid: true for solid cube, false for wire cube
 * t_x,t_y,t_z: translation
 * r_x,r_y,r_z: rotation
 * s_x,s_y,s_z: scale
 * degrees: degrees of rotation
 */
void drawBench(int solid, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z,
              float s_x, float s_y, float s_z, float degrees){
    print_materials(noMat, benchColor, matSpecular,100.0);
    drawCube(solid, t_x, t_y, t_z, r_x, r_y, r_z, s_x, s_y, s_z, degrees);
}

/*
 * Function that draws a cube
 * solid: true for solid cube, false for wire cube
 * t_x,t_y,t_z: translation
 * r_x,r_y,r_z: rotation
 * s_x,s_y,s_z: scale
 * degrees: degrees of rotation
 */
void drawCube(int solid, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z,
              float s_x, float s_y, float s_z, float degrees){
    glPushMatrix();
        glRotatef(degrees,r_x,r_y,r_z);
        glTranslatef(t_x,t_y,t_z);
        glScalef(s_x,s_y,s_z);
        //Paint solid of wire cube according to parameter
        if (solid)
            glutSolidCube(2.0);
        else
            glutWireCube(2.0);
    glPopMatrix();
}

/*
 * Function that draws a room
 * solid: true for solid cube, false for wire cube
 * t_x,t_y,t_z: translation
 * r_x,r_y,r_z: rotation
 * s_x,s_y,s_z: scale
 * degrees: degrees of rotation
 */
void drawRoom(float t_x, float t_y, float t_z, float s_x, float s_y, float s_z, float r_x, float r_y, float r_z, float degrees){

    glPushMatrix();
        glRotatef(degrees,r_x,r_y,r_z);
        glTranslatef(t_x,t_y,t_z);
        glScalef(s_x,s_y,s_z);
        //floor
        print_materials(noMat, floorColor, matSpecular,100.0);
        drawCube(true,0.0,0.0,0.0,0.0,0.0,0.0,10.0,0.2,10.0,0.0);
        drawCube(SOLID,0.0,10.0,0.0,0.0,0.0,0.0,10.0,0.2,10.0,0.0);

        //Outer walls
        print_materials(noMat, wallColor, matSpecular,100.0);
        drawCube(SOLID,10.0,5.0,0.0,0.0,0.0,0.0,0.2,5.0,10.0,0.0);
        drawCube(SOLID,-10.0,5.0,0.0,0.0,0.0,0.0,0.2,5.0,10.0,0.0);
        drawCube(SOLID,-10.0,5.0,0.0,0.0,1.0,0.0,0.2,5.0,10.0,90.0);
        drawCube(SOLID,10.0,5.0,0.0,0.0,1.0,0.0,0.2,5.0,10.0,90.0);
    glPopMatrix();

}

/*
 * Function that draws the floor
 * solid: true for solid cube, false for wire cube
 * t_x,t_y,t_z: translation
 * r_x,r_y,r_z: rotation
 * s_x,s_y,s_z: scale
 * degrees: degrees of rotation
 */
void drawFloor(float t_x, float t_y, float t_z, 
               float s_x, float s_y, float s_z, 
               float r_x, float r_y, float r_z, 
               float degrees){
    glPushMatrix();
        glRotatef(degrees,r_x,r_y,r_z);
        glTranslatef(t_x,t_y,t_z);
        glScalef(s_x,s_y,s_z);
        //floor
        print_materials(noMat, floorColor, matSpecular,100.0);
        drawCube(true,0.0,0.0,0.0,0.0,0.0,0.0,10.0,0.2,10.0,0.0);
    glPopMatrix();
}

/*
 * Function that draws an obj object
 * pmoder: pointer to the object
 * t_x,t_y,t_z: translation
 * r_x,r_y,r_z: rotation
 * s_x,s_y,s_z: scale
 * degrees: degrees of rotation
 */
void drawObject(GLMmodel *pmodel, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z,
              float s_x, float s_y, float s_z, float degrees){
    glPushMatrix();
        glTranslatef(t_x,t_y,t_z);
        glRotatef(degrees,r_x,r_y,r_z);
        glScalef(s_x,s_y,s_z);
        glmDraw(pmodel, mode);
    glPopMatrix();

}

/*****
 ** 
 **  Museum room
 ** 
 *****/

/*
 * Function that draws the museum structure called "El paraguas"
 */
void elParaguas() {
    glPushMatrix();
        glRotatef(90.0,1.0,0.0,0.0);
        glTranslatef(0.0,-30.0,-25.0);
        print_materials(noMat, paraguasColor, matSpecular,100.0);
        gluCylinder(qobj, 4.0, 4.0, 25.0, 15,15);
    glPopMatrix();
    drawFloor(0.0,25.0,-40.0,2.0,1.0,3.0,0.0,0.0,0.0,0.0);
}

/*
 * Function that draws the "patio central" of the museum
 */
void patioCentral(){
    //Main hall
    drawFloor(0.0,0.0,-53.0,2.0,1.0,4.3,0.0,0.0,0.0,0.0);
    print_materials(blue, blue, blue,100.0);
    //Transparency to the water
    glEnable (GL_BLEND);
    glDepthMask (GL_FALSE);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE);
    drawCube(1.0,0.0,1.0,-70.0,0.0,0.0,0.0,10.0,1.0,9.0,0.0);
    glDepthMask (GL_TRUE);
    glDisable (GL_BLEND);
    //End transparency
    print_materials(noMat, floorColor, matSpecular,100.0);
    drawCube(1.0,0.0,1.0,-90.0,0.0,0.0,0.0,3.0,1.0,8.0,0.0);
    elParaguas();
}

/*
 * Function that draws the main entrance of the museum
 */
void accessoPrincipal() {
    //Entrance
    drawFloor(0.0,0.0,30.0,1.0,1.0,2.0,0.0,0.0,0.0,0.0);
    
    drawBench(1.0,-8.0,1.0,20.0,0.0,0.0,0.0,1.0,1.0,5.0,0.0);
    drawBench(1.0,-8.0,1.0,40.0,0.0,0.0,0.0,1.0,1.0,5.0,0.0);
    drawBench(1.0,8.0,1.0,20.0,0.0,0.0,0.0,1.0,1.0,5.0,0.0);
    drawBench(1.0,8.0,1.0,40.0,0.0,0.0,0.0,1.0,1.0,5.0,0.0);

    //Draw the plants on the museum entrance
    drawObject(plant,8.0,2.5,23.0,0.0,0.0,0.0,1.5,1.5,1.5,0.0);
    drawObject(plant,8.0,2.5,18.0,0.0,0.0,0.0,1.5,1.5,1.5,0.0);
    drawObject(plant,8.0,2.5,43.0,0.0,0.0,0.0,1.5,1.5,1.5,0.0);
    drawObject(plant,8.0,2.5,38.0,0.0,0.0,0.0,1.5,1.5,1.5,0.0);
    drawObject(plant,-8.0,2.5,23.0,0.0,0.0,0.0,1.5,1.5,1.5,0.0);
    drawObject(plant,-8.0,2.5,18.0,0.0,0.0,0.0,1.5,1.5,1.5,0.0);
    drawObject(plant,-8.0,2.5,43.0,0.0,0.0,0.0,1.5,1.5,1.5,0.0);
    drawObject(plant,-8.0,2.5,38.0,0.0,0.0,0.0,1.5,1.5,1.5,0.0);

}

/*
 * Function that draws the library and the auditorium of the museum
 */
void bibliotecaAuditorio() {
    //door to main hall
    drawDoor(1.0,0.0,2.5,-10.0,0.0,0.0,0.0,7.0,3.0,0.5,0.0);
    //door to museum
    drawDoor(1.0,0.0,2.5,10.0,0.0,0.0,0.0,4.0,3.0,0.5,0.0);
    drawRoom(0.0,0.0,0.0,4.0,1.0,1.0,0.0,0.0,0.0,0.0);  

    //Draw the pedestals
    paintStatue(-5.0,1.0,0.5);
    paintStatue(-5.0,1.0,-1.5);
    paintStatue(5.0,1.0,-1.5);
    paintStatue(5.0,1.0,0.5);
    
    //Draw the library
    drawObject(bookcase,-38.0,5.0,0.0,0.0,1.0,0.0,25.0,12.0,12.0,90.0);
    drawObject(bookcase,-29.0,5.0,-8.0,0.0,1.0,0.0,25.0,12.0,12.0,0.0);
    drawObject(bookcase,-24.0,5.0,8.0,0.0,1.0,0.0,40.0,12.0,12.0,0.0);
}





/*
 * Function that draws the "Culturas del Golfo" exhibition
 */
void salaCulturasDelGolfo() {
    drawRoom(-30.0,0.0,-75.0,1.0,1.0,4.0,0.0,0.0,0.0,0.0);

    //Draw benchs on the room
    drawObject(bench,-32.0,1.5,-75.0,0.0,1.0,0.0,2.0,2.0,2.0,90.0);
    drawObject(bench,-28.0,1.5,-75.0,0.0,1.0,0.0,2.0,2.0,2.0,-90.0);
    drawObject(bench,-32.0,1.5,-65.0,0.0,1.0,0.0,2.0,2.0,3.0,90.0);
    drawObject(bench,-28.0,1.5,-65.0,0.0,1.0,0.0,2.0,2.0,3.0,-90.0);
    drawObject(bench,-32.0,1.5,-55.0,0.0,1.0,0.0,2.0,2.0,2.0,90.0);
    drawObject(bench,-28.0,1.5,-55.0,0.0,1.0,0.0,2.0,2.0,2.0,-90.0);
    drawObject(bench,-32.0,1.5,-45.0,0.0,1.0,0.0,2.0,2.0,2.0,90.0);
    drawObject(bench,-28.0,1.5,-45.0,0.0,1.0,0.0,2.0,2.0,2.0,-90.0);

    //Draw lamps
    drawObject(high_lamp,-30.0,6,-75.0,0.0,1.0,0.0,6.0,6.0,6.0,-90.0);
    drawObject(high_lamp,-30.0,6,-50.0,0.0,1.0,0.0,6.0,6.0,6.0,-90.0);

    drawObject(wall_lamp,-22.0,6,-103.5,0.0,1.0,0.0,1.5,1.5,1.5,-90.0);
    drawObject(wall_lamp,-22.0,6,-83.5,0.0,1.0,0.0,1.5,1.5,1.5,-90.0);
    
    drawDoor(1.0,-20.0,2.5,-45.0,0.0,0.0,0.0,0.8,3.0,2.0,0.0);
    drawDoor(1.0,-20.0,2.5,-85.0,0.0,0.0,0.0,0.8,3.0,2.0,0.0);
    drawDoor(1.0,-20.0,2.5,-105.0,0.0,0.0,0.0,0.8,3.0,2.0,0.0);
}

/*
 * Function that draws the "Culturas de Oaxaca" exhibition
 */
void salaOaxaca() {

    //Draw objects in the room
    drawObject(bench,-30.0,1.0,-25.0,0.0,0.0,0.0,2.0,2.0,2.0,0.0);
    drawObject(bench,-30.0,1.0,-22.0,0.0,1.0,0.0,2.0,2.0,2.0,180.0);

    drawObject(wall_lamp,-22.0,6,-25.5,0.0,1.0,0.0,1.5,1.5,1.5,-90.0);
    drawObject(wall_lamp,-30.0,6.5,-32.0,0.0,0.0,0.0,1.5,1.5,1.5,0.0);

    //Room structure
    drawRoom(-30.0,0.0,-25.0,1.0,1.0,1.0,0.0,0.0,0.0,0.0);
    drawDoor(1.0,-30.0,2.5,-35.0,0.0,0.0,0.0,2.0,3.0,1.2,0.0);
    drawDoor(1.0,-20.0,2.5,-25.0,0.0,0.0,0.0,0.8,3.0,2.0,0.0);
}

/*
 * Function that draws the "Culturas del Norte" exhibition
 */
void salaCulturasDelNorte() {    
    drawRoom(30.0,0.0,-30.0,1.0,1.0,1.5,0.0,0.0,0.0,0.0);
    drawDoor(1.0,30.0,2.5,-45.0,0.0,0.0,0.0,3.0,3.0,0.8,0.0);
    drawDoor(1.0,20.0,2.5,-25.0,0.0,0.0,0.0,0.8,3.0,2.0,0.0);

    //Draw room objects
    drawObject(bench,30.0,1.0,-25.0,0.0,0.0,0.0,2.0,2.0,2.0,0.0);
    drawObject(bench,30.0,1.0,-22.0,0.0,1.0,0.0,2.0,2.0,2.0,180.0);
    drawObject(bench,30.0,1.0,-33.0,0.0,0.0,0.0,2.0,2.0,2.0,0.0);
    drawObject(bench,30.0,1.0,-30.0,0.0,1.0,0.0,2.0,2.0,2.0,180.0);

    drawObject(wall_lamp,30.0,6.5,-40.0,0.0,0.0,0.0,1.5,1.5,1.5,0.0);
}

/*
 * Function that draws the "Culturas teotihuacana y tolteca" exhibition
 */
void salaTeotihuacanaTolteca () {
    drawRoom(30.0,0.0,-70.0,1.0,1.0,2.5,0.0,0.0,0.0,0.0);
    drawDoor(1.0,20.0,2.5,-55.0,0.0,0.0,0.0,0.8,3.0,2.0,0.0);
    drawDoor(1.0,20.0,2.5,-85.0,0.0,0.0,0.0,0.8,3.0,2.0,0.0); 

    //Draw room objects
    drawObject(bench,32.0,1.5,-75.0,0.0,1.0,0.0,2.0,2.0,2.0,90.0);
    drawObject(bench,28.0,1.5,-75.0,0.0,1.0,0.0,2.0,2.0,2.0,-90.0);
    drawObject(bench,32.0,1.5,-65.0,0.0,1.0,0.0,2.0,2.0,3.0,90.0);
    drawObject(bench,28.0,1.5,-65.0,0.0,1.0,0.0,2.0,2.0,3.0,-90.0);
    drawObject(bench,32.0,1.5,-55.0,0.0,1.0,0.0,2.0,2.0,2.0,90.0);
    drawObject(bench,28.0,1.5,-55.0,0.0,1.0,0.0,2.0,2.0,2.0,-90.0);

    drawObject(wall_lamp,22.0,6.5,-85.5,0.0,1.0,0.0,1.5,1.5,1.5,90.0);

}
/*
 * Function that draws the "Culturas del Mexica" exhibition
 */
void salaMexica () {
    drawRoom(0.0,0.0,-105.0,2.0,1.0,1.0,0.0,0.0,0.0,0.0);
    drawDoor(1.0,0.0,4.5,-95.0,0.0,0.0,0.0,2.0,3.0,0.5,0.0);

    //Draw room objects
    drawObject(bench,-10.0,1.0,-105.0,0.0,0.0,0.0,2.0,2.0,2.0,0.0);
    drawObject(bench,-10.0,1.0,-100.0,0.0,1.0,0.0,2.0,2.0,2.0,180.0);
    drawObject(bench,0.0,1.0,-105.0,0.0,0.0,0.0,2.0,2.0,2.0,0.0);
    drawObject(bench,0.0,1.0,-100.0,0.0,1.0,0.0,2.0,2.0,2.0,180.0);
    drawObject(bench,10.0,1.0,-105.0,0.0,0.0,0.0,2.0,2.0,2.0,0.0);
    drawObject(bench,10.0,1.0,-100.0,0.0,1.0,0.0,2.0,2.0,2.0,180.0);

    drawObject(high_lamp,0.0,6,-102.5,0.0,1.0,0.0,6.0,6.0,6.0,-90.0);    
}

/*
 * Function that draws the parking of the museum
 */
void drawParking(){
    //Path from entrance to the parking
    glPushMatrix();
        print_materials(noMat,floorColor,matSpecular,100.0);
        glTranslatef(40.0,0.0,30.0);
        glScalef(60.0,1.0,10.0);
        glutSolidCube(1.0);
    glPopMatrix();
    //Draw the cars
    drawObject(car1,75.0,4.0,20.0,0.0,1.0,0.0,6.0,6.0,6.0,90.0);
    drawObject(car2,99.0,4.0,34.0,0.0,1.0,0.0,6.0,6.0,6.0,90.0);
    drawObject(car3,75.0,4.0,0.0,0.0,1.0,0.0,6.0,6.0,6.0,90.0);

    //Iterate to draw the 
    float count = 0.0;
    for (int i = 0; i < 5; i++){
        drawObject(tree,15.0 + count,6.0,18.0,0.0,0.0,0.0,6.0,6.0,6.0,0.0);
        drawObject(tree,15.0 + count,6.0,40.0,0.0,0.0,0.0,6.0,6.0,6.0,0.0);

        drawObject(tree,-1*(15.0 + count),6.0,18.0,0.0,0.0,0.0,6.0,6.0,6.0,0.0);
        drawObject(tree,-1*(15.0 + count),6.0,40.0,0.0,0.0,0.0,6.0,6.0,6.0,0.0);
        count += 10.0;
    }
}

/*
 * Function that draws the main structure of the museum
 */
void drawMuseum() {
    
    //Draw museum rooms
    accessoPrincipal();
    patioCentral();
    bibliotecaAuditorio();
    
    salaCulturasDelGolfo();
    salaOaxaca();
    salaCulturasDelNorte();
    salaTeotihuacanaTolteca();
    salaMexica(); 

    drawParking();

    //Draw museum landscape    
    glPushMatrix();
        print_materials(noMat,green,matSpecular,100.0);
        glTranslatef(0.0,-1.0,0.0);
        glScalef(600.0,1.0,400.0);
        glutSolidCube(1.0);
    glPopMatrix();

    
}

/*
 * Function that draws a pedestal and a glass protection for a statue
 */
void paintStatue(float t_x, float t_y, float t_z){
     glPushMatrix();
        //First draw the base
        glTranslatef(t_x,t_y,t_z);
        glScalef(1.0,1.3,1.0);
        glutSolidCube(1.0);
        glPushMatrix();
            print_materials(blue,blue,blue,100.0);
            glScalef(1.0,0.5,1.0);
            glTranslatef(0.0,1.5,0.0);
            //Transparency for the glass
            glEnable (GL_BLEND);
            glDepthMask (GL_FALSE);
            glBlendFunc (GL_SRC_ALPHA, GL_ONE);
            glutSolidCube(1.0);
            glDepthMask (GL_TRUE);
            glDisable (GL_BLEND);
        glPopMatrix();
    glPopMatrix();
}


/*
 * Function that draws a paint in the museum
 * pmoder: pointer to the object
 * t_x,t_y,t_z: translation
 * r_x,r_y,r_z: rotation
 * s_x,s_y,s_z: scale
 * degrees: degrees of rotation
 * index: index of the paint in the textures array
 */
void drawPaint(float t_x, float t_y, float t_z, float s_x, 
               float s_y, float s_z, float r_x, float r_y, 
               float r_z, float degrees, int index){
    //Enable textures
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
        //Get the texture from the array
        glBindTexture(GL_TEXTURE_2D, texName[index]);
        glTranslatef(t_x,t_y,t_z);
        glRotatef(degrees,r_x,r_y,r_z);
        glScalef(s_x,s_y,s_z);
        //Disable lighting and paint the texture in a square
        glDisable(GL_LIGHTING);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0, 1.0); glVertex3f(-2.0, -1.0, 0.0);
            glTexCoord2f(0.0, 0.0); glVertex3f(-2.0, 1.0, 0.0);
            glTexCoord2f(1.0, 0.0); glVertex3f(0.0, 1.0, 0.0);
            glTexCoord2f(1.0, 1.0); glVertex3f(0.0, -1.0, 0.0);
        glEnd();
        glEnable(GL_LIGHTING);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

/* 
 * Function that draws paint from the renascement room 
 */
void drawRenascement(){
    drawPaint(-23.0,5.0,-34.1,1.2,2.0,5.0,0.0,0.0,0.0,0.0,0);
    drawPaint(-33.0,5.0,-34.1,1.2,2.0,5.0,0.0,0.0,0.0,0.0,1);
    drawPaint(-39.5,5.0,-27.1,5.2,3.0,5.0,0.0,1.0,0.0,90.0,2);
    drawPaint(-23.0,5.0,-15.5,6.0,2.0,5.0,0.0,0.0,0.0,0.0,3);
}

/* 
 * Function that draws paint from the impresionism room 
 */
void drawImpresionism(){
    drawPaint(-23.0,5.0,-36.0,1.2,2.0,5.0,0.0,0.0,0.0,0.0,4);
    drawPaint(-33.0,5.0,-36.0,1.2,2.0,5.0,0.0,0.0,0.0,0.0,5);
    drawPaint(-39.5,5.0,-47.1,5.2,3.0,5.0,0.0,1.0,0.0,90.0,6);
    drawPaint(-39.5,5.0,-62.1,5.2,3.0,5.0,0.0,1.0,0.0,90.0,7);
    drawPaint(-39.5,5.0,-77.1,5.2,3.0,5.0,0.0,1.0,0.0,90.0,8);
    drawPaint(-39.5,5.0,-92.1,5.2,3.0,5.0,0.0,1.0,0.0,90.0,9);
    drawPaint(-39.5,5.0,-107.1,5.2,3.0,5.0,0.0,1.0,0.0,90.0,10);
    drawPaint(-23.0,5.0,-110.0,6.0,3.0,5.0,0.0,0.0,0.0,0.0,11);
    drawPaint(-20.5,5.0,-100.1,5.2,3.0,5.0,0.0,1.0,0.0,90.0,12);
    drawPaint(-20.5,5.0,-75.1,7.2,3.0,5.0,0.0,1.0,0.0,90.0,13);
    drawPaint(-20.5,5.0,-58.1,4.2,3.0,5.0,0.0,1.0,0.0,90.0,14);
}

/* 
 * Function that draws paint from the frida room 
 */
void drawFrida(){
    drawPaint(-10.0,5.0,-113.0,4.0,2.0,5.0,0.0,0.0,0.0,0.0,16);
    drawPaint(-1.0,5.0,-113.0,4.0,2.0,5.0,0.0,0.0,0.0,0.0,17);
    drawPaint(8.0,5.0,-113.0,4.0,2.0,5.0,0.0,0.0,0.0,0.0,18);
    drawPaint(17.0,5.0,-113.0,4.0,2.0,5.0,0.0,0.0,0.0,0.0,19);
    drawPaint(19.0,5.0,-113.0,4.0,2.0,5.0,0.0,1.0,0.0,90.0,15);
}

/* 
 * Function that draws paint from the cubism room 
 */
void drawCubism(){
    drawPaint(20.5,5.0,-69.0,5.2,3.0,5.0,0.0,1.0,0.0,90.0,20);
    drawPaint(20.5,5.0,-80.0,5.2,3.0,5.0,0.0,1.0,0.0,90.0,21);
    drawPaint(39.5,5.0,-95.0,5.2,3.0,5.0,0.0,1.0,0.0,90.0,22);
    drawPaint(39.5,5.0,-80.0,5.2,3.0,5.0,0.0,1.0,0.0,90.0,23);
    drawPaint(39.5,5.0,-65.0,5.2,3.0,5.0,0.0,1.0,0.0,90.0,25);
    drawPaint(35.5,5.0,-93.0,6.0,4.0,4.0,0.0,0.0,0.0,0.0,24);
}

/* 
 * Function that draws paint from the contemporary room 
 */
void drawContemporary(){
   drawPaint(39.5,5.0,-45.0,5.2,3.0,5.0,0.0,1.0,0.0,90.0,27);
    drawPaint(39.5,5.0,-30.0,5.2,3.0,5.0,0.0,1.0,0.0,90.0,26);
    drawPaint(20.5,5.0,-40.0,5.2,3.0,5.0,0.0,1.0,0.0,90.0,28);
    drawPaint(37.5,5.0,-42.0,2.0,3.0,5.0,0.0,0.0,0.0,0.0,29); 
}

/* 
 * Function that draws the pictures of the museum
 */ 
void drawPictures(){
    
    drawRenascement();
    drawImpresionism();
    drawFrida();
    drawCubism();
    drawContemporary();    
    //Parking
    drawPaint(120.0,2.0,20.0,30.2,40.0,2.0,1.0,0.0,0.0,90.0,30);

}

/*
 * Functions that display everything in the scene
 */
void display(void) {

    //Enable light again
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);

    //Mode for the obj files look good
    mode = mode | GLM_MATERIAL;
    mode = mode | GLM_2_SIDED;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity (); 
    glPushMatrix();
        //Focus the camera acording to the view movde
        if (VIEW_MODE == inside){
            gluLookAt (camX,camY,camZ,camX,0.0,-120.0, 0.0,1.0, 0.0); 
            //glRotatef(rotationAngle,0.0,1.0,0.0);
        } else if (VIEW_MODE == outside){
            gluLookAt (0.0,25.0,85.0,0.0,25.0,0.0,0.0,1.0, 0.0); 
            glRotatef(rotationAngle,0.0,1.0,0.0);
        }
        //Function to draw the museum structure
        drawMuseum();
        drawPictures();

    glPopMatrix();
    //Show the help
    HelpDisplay(ww, wh);
    glutSwapBuffers();  
}

/*
 * Function that loads obj files 
 */
void loadObjects(){
    //Read objects
    plant = glmReadOBJ("./home/maceta.obj");
    glmUnitize(plant);
    glmVertexNormals(plant, 90.0, GL_TRUE); 

    bench = glmReadOBJ("./home/bench.obj");
    glmUnitize(bench);
    glmVertexNormals(bench, 90.0, GL_TRUE);

    high_lamp = glmReadOBJ("./home/hangingLight.obj");
    glmUnitize(high_lamp);
    glmVertexNormals(high_lamp, 90.0, GL_TRUE);

    wall_lamp = glmReadOBJ("./home/wall-spotlight.obj");
    glmUnitize(wall_lamp);
    glmVertexNormals(wall_lamp, 90.0, GL_TRUE);

    bookcase = glmReadOBJ("./home/bookcase.obj");
    glmUnitize(bookcase);
    glmVertexNormals(bookcase, 90.0, GL_TRUE);

    car1 = glmReadOBJ("./home/concept-sedan-01v1.obj");
    glmUnitize(car1 );
    glmVertexNormals(car1 , 90.0, GL_TRUE);

    car2 = glmReadOBJ("./home/fordFocus.obj");
    glmUnitize(car2 );
    glmVertexNormals(car2 , 90.0, GL_TRUE);

    car3 = glmReadOBJ("./home/peugeot-308.obj");
    glmUnitize(car3 );
    glmVertexNormals(car3 , 90.0, GL_TRUE);

    tree = glmReadOBJ("./home/quakingAspen.obj");
    glmUnitize(tree );
    glmVertexNormals(tree , 90.0, GL_TRUE);
}

/*
 * Function that loads a texture from image file and asign it to a position
 * in the texture array
 * index: position in the texture array
 * file: name of the file of the image
 */
void loadtexture(int index, char file[]){

    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, texName[index]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    int width_1, height_1;
    unsigned char* image_1 = SOIL_load_image(file, &width_1, &height_1, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_1,height_1, 0, GL_RGB, GL_UNSIGNED_BYTE, image_1);

    glDisable(GL_TEXTURE_2D);

}

/* 
 * Function that loads paint from the renascement room 
 */
void loadRenascement(){
    loadtexture(0,"images/gioconda.jpg");
    loadtexture(1,"images/venus.jpg");
    loadtexture(2,"images/ultima_cena.jpg");
    loadtexture(3,"images/dios.jpg");
}

/* 
 * Function that loads paint from the impresionism room 
 */
void loadImpresionism(){
    loadtexture(4,"images/amanecer.jpg");
    loadtexture(5,"images/ninos.jpg");
    loadtexture(6,"images/noche.jpg");
    loadtexture(7,"images/parlamento.jpg");
    loadtexture(8,"images/party.jpg");
    loadtexture(9,"images/van_gogh.png");
    loadtexture(10,"images/risco.jpg");
    loadtexture(11,"images/water_lilies.jpg");
    loadtexture(12,"images/bote.jpg");
    loadtexture(13,"images/puente.jpg");
    loadtexture(14,"images/paisaje.png");
}

/* 
 * Function that loads paint from the frida room 
 */
void loadFrida(){
    loadtexture(15,"images/frutas2.jpg");
    loadtexture(16,"images/frida.jpeg");
    loadtexture(17,"images/frutas.jpg");
    loadtexture(18,"images/mariposas.jpg");
    loadtexture(19,"images/patillas.jpg");
}

/* 
 * Function that loads paint from the cubism room 
 */
void loadCubism(){
    loadtexture(20,"images/abrazo.jpg");
    loadtexture(21,"images/gris.jpg");
    loadtexture(22,"images/mujer.jpg");
    loadtexture(23,"images/palmas.jpeg");
    loadtexture(24,"images/picasso.jpeg");
    loadtexture(25,"images/vino.jpg");
}

/* 
 * Function that loads paint from the contemporary room 
 */
void loadContemporary(){

    loadtexture(26,"images/loco.jpg");
    loadtexture(27,"images/dali.jpg");
    loadtexture(29,"images/hojas.jpg");
    loadtexture(28,"images/rara.jpg");
}

/*
 * Function that loads the textures from images 
 */
 void loadPictures(){
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    //Number of textures to read
    glGenTextures(30, texName);

    loadRenascement();
    loadImpresionism();
    loadFrida();
    loadCubism();
    loadContemporary();

    loadtexture(30,"images/parking.jpg");
}

/*
 * Initialization values for objects, cylinder and lights
 */ 
void init(void) {

    loadPictures();

    qobj = gluNewQuadric();
    gluQuadricNormals(qobj, GLU_SMOOTH);
    gluQuadricDrawStyle(qobj, GLU_FILL);

    //Lights data 
    GLfloat ambient[] = { 1.0,1.0,1.0, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat position[] = { 0.0, 2.0, 3.0, 0.0 };
    GLfloat diffuse[] = {1.0,1.0,1.0};
    GLfloat position_room_1[] = { -30.0, 10.0, -20.0, 0.0 };

    GLfloat lmodel_ambient[] = { 1.0,1.0,1.0, 1.0 };
    GLfloat local_view[] = { 0.0 };

    GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat mat_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat high_shininess[] = { 100.0 };

    //Enable depth
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    //Set data to lights
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT1, GL_POSITION, position_room_1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    //Turn on lights
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    
    loadObjects();
  
    //Background colors
    glClearColor(0.529, 0.808, 0.922,0.0);
}

/*
 * Keyboard function 
 */
void keyboard(unsigned char key, int x, int y){
    switch (key) {
        //Rotate the camera
        case 'r':
            rotationAngle = rotationAngle + 6.0;
            glutPostRedisplay();
            break;
        case 'R':
            rotationAngle = rotationAngle - 6.0;
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT:
            camX += 1.5;
            glutPostRedisplay();
            break;
        case GLUT_KEY_LEFT:
            camX -= 1.5;
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN:
            if (camZ + 1.5 < 85){
                camZ += 1.5;
                glutPostRedisplay();
            } 
            break;
        case GLUT_KEY_UP:
            if (camZ - 1.5 > -115){
                camZ -= 1.5;
                glutPostRedisplay();
            }
            break;  
        case 's':
            SOLID = true;
            glutPostRedisplay();
            break;
        case 'S':
            SOLID = false;
            glutPostRedisplay();
            break;
        case 'h':
            show_info = true;
            glutPostRedisplay();
            break;
        case 'H':
            show_info = false;
            glutPostRedisplay();
            break;
    }
}


/*
 * Function that sets the color of the materials 
 * Ambient: array colors for ambient lights
 * Diffuse: array colors for diffuse lights
 * Specular: array colors for specular lights
 * s: shininess of the material
 */

void print_materials( GLfloat * ambientColor, GLfloat * diffuseColor, GLfloat * specularColor, float s){    
    //Set the arrays
    GLfloat ambient[] = {ambientColor[0], ambientColor[1], ambientColor[2]};
    GLfloat diffuse[] = {diffuseColor[0], diffuseColor[1], diffuseColor[2]};
    GLfloat specular[] = {specularColor[0], specularColor[1], specularColor[2]};
    GLfloat shininess[] = { s };
    //Assign materials
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);

}


/* 
 * Function with information to show on the help section
 */
void HelpDisplay(GLint ww, GLint wh) {
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glColor3f(1.0f, 1.0f, 1.0f);


    /*  switch to projection mode */
    glMatrixMode(GL_PROJECTION);
    /*  save previous matrix which contains the  */
    /* settings for the perspective projection */
    glPushMatrix();
    /*  reset matrix */
    glLoadIdentity();
    /*  set a 2D orthographic projection */
    gluOrtho2D(0, ww, 0, wh);
    /*  invert the y axis, down is positive */
    glScalef(1, -1, 1);
    /*  mover the origin from the bottom left corner */
    /*  to the upper left corner */
    glTranslatef(0, -wh, 0);
    glMatrixMode(GL_MODELVIEW);


    glPushMatrix();
    glLoadIdentity();
    linestart = 10;

    
    HelpRenderBitmapString(30, linestart +=
               linespace, Help_Font, "s/S solid or wire view");
    HelpRenderBitmapString(30, linestart +=
               linespace, Help_Font, "h/H to show or hide more information");
    HelpRenderBitmapString(30, linestart +=
               linespace, Help_Font, "Use arrow keys to move");
    HelpRenderBitmapString(30, linestart +=
               linespace, Help_Font, "Current location = ");


    if (VIEW_MODE == outside){
        HelpRenderBitmapString(30, linestart +=
               linespace, Help_Font, "Outside view");
        if (show_info){
            HelpRenderBitmapString(30, linestart +=
            linespace, Help_Font, "Info about the museum");
        } 
    } else{
        if (camX >= -10 && camX <= 10 && camZ <= 85 && camZ >= 10) {
            HelpRenderBitmapString(30, linestart +=
            linespace, Help_Font, "Entrance road");
            if (show_info){
                HelpRenderBitmapString(30, linestart +=
                linespace, Help_Font, "Info about Entrance road");
            }   
        }

        else if (camX >= -40 && camX <= 40 && camZ <= 10 && camZ >= -10) {
            HelpRenderBitmapString(30, linestart +=
            linespace, Help_Font, "Entrance hall");
            if (show_info){
                HelpRenderBitmapString(30, linestart +=
                linespace, Help_Font, "Info about Entrance hall");
            }   
        }
        else if (camX >= -40 && camX <= -20 && camZ <= -10 && camZ >= -35){
            HelpRenderBitmapString(30, linestart +=
            linespace, Help_Font, "Renascement room");
            if (show_info){
                HelpRenderBitmapString(30, linestart +=
                linespace, Help_Font, "Info about Renascement room");
            } 
        }
        else if (camX >= 20 && camX <= 40 && camZ <= -10 && camZ >= -45){
            HelpRenderBitmapString(30, linestart +=
            linespace, Help_Font, "Cuarto 5");
            if (show_info){
                HelpRenderBitmapString(30, linestart +=
                linespace, Help_Font, "Info about Cuarto 5");
            } 
        }
        else if (camX >= 20 && camX <= 40 && camZ <= -45 && camZ >= -93){
            HelpRenderBitmapString(30, linestart +=
            linespace, Help_Font, "Cuarto 6");
            if (show_info){
                HelpRenderBitmapString(30, linestart +=
                linespace, Help_Font, "Info about Cuarto 6");
            } 
        }

        else if (camX >= -20 && camX <= 20 && camZ <= -90 && camZ >= -115){
            HelpRenderBitmapString(30, linestart +=
            linespace, Help_Font, "Cuarto del fondo");
            if (show_info){
                HelpRenderBitmapString(30, linestart +=
                linespace, Help_Font, "Info about Cuarto del fondo");
            } 
        }

        else if (camX >= -20 && camX <= 20 && camZ <= 10 && camZ >= -90){
            HelpRenderBitmapString(30, linestart +=
            linespace, Help_Font, "Centro cool ");
            if (show_info){
                HelpRenderBitmapString(30, linestart +=
                linespace, Help_Font, "Info about Cuarto del fondo");
            } 
        }

        else if (camX >= -40 && camX <= -20 && camZ <= -35 && camZ >= -115){
            HelpRenderBitmapString(30, linestart +=
            linespace, Help_Font, "Impresionism room");
            if (show_info){
                HelpRenderBitmapString(30, linestart +=
                linespace, Help_Font, "Info about Impresionism room");
            } 
        }  

        else {
            HelpRenderBitmapString(30, linestart +=
               linespace, Help_Font, "Out of bounds, please go back to the museum"); 
            if (show_info){
                HelpRenderBitmapString(30, linestart +=
                    linespace, Help_Font, "Info about going out of bounds!!!");
        } 
        }
    }
    
    glPopMatrix();

    /*  set the current matrix to GL_PROJECTION */
    glMatrixMode(GL_PROJECTION);
    /*  restore previous settings */
    glPopMatrix();
    /*  get back to GL_MODELVIEW matrix */
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_TEXTURE_2D);
}

//Helper of the menu option
void HelpRenderBitmapString(float x, float y, void *font, char *string) {
    char *c;
    /*  set position to start drawing fonts */
    glRasterPos2f(x, y);
    /*  loop all the characters in the string */
    for (c = string; *c != '\0'; c++) {
    glutBitmapCharacter(font, *c);
    }
}

