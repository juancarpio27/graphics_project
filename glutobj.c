/*
 * Proyecto Final, Museo de Antropologia 
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

//Constants for boolean management
#define bool int
#define true 1
#define false 0

#define inside 1
#define outside 0

//Initial camera data
float camX=-40.0, camY=2.0, camZ=-35.0;
float rotationAngle = 0.0;
//Mode to render the objects
GLuint mode = GLM_SMOOTH;

/*****
 ** 
 **  View modes
 ** 
 *****/
int SOLID = false;
int show_info = true;
int VIEW_MODE =  outside;
int ww, wh;     

/*****
 ** 
 **  Museum colors
 ** 
 *****/
//Museum walls
GLfloat wallColor [] = { 0.74,0.74,0.72 };
//Museum floors
GLfloat floorColor [] = { 0.19, 0.19, 0.22};
//Museum Paraguas
GLfloat paraguasColor []  = {0.07, 0.24, 0.22};
//Museum Doors
GLfloat doorColor []  = {0.74, 0.33, 0.18};
//Museum bench
GLfloat benchColor []  = {0.74, 0.33, 0.18};
//Other materials
GLfloat noMat[] = {0.0, 0.0, 0.0};
GLfloat matSpecular[] = {1.0, 1.0, 1.0};
//Blue materials
GLfloat blue[] = {0.118, 0.565, 1.000,0.4};
GLfloat light_blue[] = {0.529, 0.808, 0.980,0.4};
//Green
GLfloat green[] = {0.000, 0.502, 0.000};

//Cylinder
GLUquadric* qobj;


/*****
 ** 
 **  Objects
 ** 
 *****/
GLMmodel *plant = NULL;

void *Help_Font = GLUT_BITMAP_8_BY_13;
int linestart = 10;     /* start point on y axis for text lines */
int linespace = 20;     /* spac betwwen text lines */


/*****************************************************************************/
/*Functions*******************************************************************/
/*****************************************************************************/

//Windows size function and view configuration
void Reshape(int w, int h);
//Objects to display in the scene
void display(void);
//Initial configuration
void init(void);
void keyboard(unsigned char key, int x, int y);

/*
 * Function that sets the color of the materials 
 * ambient: array colors for ambient lights
 * diffuse: array colors for diffuse lights
 * specular: array colors for specular lights
 * s: shininess of the material
 */
void print_materials(GLfloat * ambient, GLfloat * diffuse, GLfloat * specular, float s);

/*
 * Function that draws a cube
 * solid: true for solid cube, false for wire cube
 * t_x,t_y,t_z: translation
 * r_x,r_y,r_z: rotation
 * s_x,s_y,s_z: scale
 * degrees: degrees of rotation
 */
void drawCube(int solid, float t_x, float t_y, float t_z, float r_x, float r_y, float r_z,
              float s_x, float s_y, float s_z, float degrees);

void menu(int value);
void loadObjects();
void LoadGLTextures();
void drawPaint(float t_x, float t_y, float t_z, float s_x, 
               float s_y, float s_z, float r_x, float r_y, 
               float r_z, float degrees, int index);
void loadtexture(int index, char file[]);
void HelpDisplay(GLint ww, GLint wh);
void HelpRenderBitmapString(float x, float y, void *font, char *string);

static GLuint texName[10];




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
    LoadGLTextures();
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(Reshape);

    glutCreateMenu(menu);
    glutAddMenuEntry("View from the inside", 0);
    glutAddMenuEntry("View from the outside", 1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutKeyboardFunc(keyboard);
    glutIdleFunc(NULL);
    glutMainLoop();

    return 0;
}

void LoadGLTextures() { 
 

};

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

//Windows size function and view configuration
void Reshape(int w, int h)
{

    ww = w;
    wh = h;
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
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
    print_materials(doorColor, doorColor, doorColor,100.0);
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
        drawCube(SOLID,0.0,0.0,0.0,0.0,0.0,0.0,10.0,0.2,10.0,0.0);
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
        drawCube(SOLID,0.0,0.0,0.0,0.0,0.0,0.0,10.0,0.2,10.0,0.0);
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

/*-- Museum rooms --*/

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
    //MAIN HALL
    drawFloor(0.0,0.0,-53.0,2.0,1.0,4.3,0.0,0.0,0.0,0.0);
    
    print_materials(blue, blue, blue,100.0);
    glEnable (GL_BLEND);
    glDepthMask (GL_FALSE);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE);
    drawCube(1.0,0.0,1.0,-70.0,0.0,0.0,0.0,10.0,1.0,10.0,0.0);
    glDepthMask (GL_TRUE);
      glDisable (GL_BLEND);
    print_materials(noMat, floorColor, matSpecular,100.0);
    drawCube(1.0,0.0,1.0,-90.0,0.0,0.0,0.0,3.0,1.0,10.0,0.0);
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

    // drawObject(plant,8.0,2.5,23.0,0.0,0.0,0.0,1.5,1.5,1.5,0.0);
    // drawObject(plant,8.0,2.5,18.0,0.0,0.0,0.0,1.5,1.5,1.5,0.0);

    // drawObject(plant,8.0,2.5,43.0,0.0,0.0,0.0,1.5,1.5,1.5,0.0);
    // drawObject(plant,8.0,2.5,38.0,0.0,0.0,0.0,1.5,1.5,1.5,0.0);

    // drawObject(plant,-8.0,2.5,23.0,0.0,0.0,0.0,1.5,1.5,1.5,0.0);
    // drawObject(plant,-8.0,2.5,18.0,0.0,0.0,0.0,1.5,1.5,1.5,0.0);

    // drawObject(plant,-8.0,2.5,43.0,0.0,0.0,0.0,1.5,1.5,1.5,0.0);
    // drawObject(plant,-8.0,2.5,38.0,0.0,0.0,0.0,1.5,1.5,1.5,0.0);

}

/*-- MAIN ROOM --*/

/*
 * Function that draws the library and the auditorium of the museum
 */
void bibliotecaAuditorio() {
    //door to main hall
    drawDoor(1.0,0.0,2.5,-10.0,0.0,0.0,0.0,7.0,3.0,0.5,0.0);
    //door to museum
    drawDoor(1.0,0.0,2.5,10.0,0.0,0.0,0.0,4.0,3.0,0.5,0.0);

    drawRoom(0.0,0.0,0.0,4.0,1.0,1.0,0.0,0.0,0.0,0.0);   
}

/*-- LEFT WING --*/

/*
 * Function that draws the "Culturas del Golfo" exhibition
 */
void salaCulturasDelGolfo() {
    drawRoom(-30.0,0.0,-75.0,1.0,1.0,4.0,0.0,0.0,0.0,0.0);
    
    drawDoor(1.0,-20.0,2.5,-45.0,0.0,0.0,0.0,0.8,3.0,2.0,0.0);
    drawDoor(1.0,-20.0,2.5,-85.0,0.0,0.0,0.0,0.8,3.0,2.0,0.0);
    drawDoor(1.0,-20.0,2.5,-105.0,0.0,0.0,0.0,0.8,3.0,2.0,0.0);
}

/*
 * Function that draws the "Culturas de Oaxaca" exhibition
 */
void salaOaxaca() {
    drawRoom(-30.0,0.0,-25.0,1.0,1.0,1.0,0.0,0.0,0.0,0.0);
    drawDoor(1.0,-30.0,2.5,-35.0,0.0,0.0,0.0,2.0,3.0,0.8,0.0);
    drawDoor(1.0,-20.0,2.5,-25.0,0.0,0.0,0.0,0.8,3.0,2.0,0.0);
}

/*-- RIGHT WING --*/

/*
 * Function that draws the "Culturas del Norte" exhibition
 */
void salaCulturasDelNorte() {    
    drawRoom(30.0,0.0,-30.0,1.0,1.0,1.5,0.0,0.0,0.0,0.0);
    drawDoor(1.0,30.0,2.5,-45.0,0.0,0.0,0.0,3.0,3.0,0.8,0.0);
    drawDoor(1.0,20.0,2.5,-25.0,0.0,0.0,0.0,0.8,3.0,2.0,0.0);
}

/*
 * Function that draws the "Culturas teotihuacana y tolteca" exhibition
 */
void salaTeotihuacanaTolteca () {
    drawRoom(30.0,0.0,-70.0,1.0,1.0,2.5,0.0,0.0,0.0,0.0);
    drawDoor(1.0,20.0,2.5,-55.0,0.0,0.0,0.0,0.8,3.0,2.0,0.0);
    drawDoor(1.0,20.0,2.5,-85.0,0.0,0.0,0.0,0.8,3.0,2.0,0.0); 
}

/*-- BACKROOM --*/

/*
 * Function that draws the "Culturas del Mexica" exhibition
 */
void salaMexica () {
    drawRoom(0.0,0.0,-105.0,2.0,1.0,1.0,0.0,0.0,0.0,0.0);
    drawDoor(1.0,0.0,4.5,-95.0,0.0,0.0,0.0,2.0,3.0,0.5,0.0);
}

/*
 * Function that draws the main structure of the museum
 */
void drawMuseum() {

    glPushMatrix();
        print_materials(green, green,green,100.0);
        glScalef(400.0,0.0,200.0);
        glutSolidCube(1.0);
    glPopMatrix();

    accessoPrincipal();
    patioCentral();

    bibliotecaAuditorio();
    salaCulturasDelGolfo();
    salaOaxaca();
    salaCulturasDelNorte();
    salaTeotihuacanaTolteca();
    salaMexica(); 
}

void drawPaint(float t_x, float t_y, float t_z, float s_x, 
               float s_y, float s_z, float r_x, float r_y, 
               float r_z, float degrees, int index){

    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, texName[index]);
        glTranslatef(t_x,t_y,t_z);
        glRotatef(degrees,r_x,r_y,r_z);
        glScalef(s_x,s_y,s_z);
        glDisable(GL_LIGHTING);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0, 1.0); glVertex3f(-2.0, -1.0, 0.0);
            glTexCoord2f(0.0, 0.0); glVertex3f(-2.0, 1.0, 0.0);
            glTexCoord2f(1.0, 0.0); glVertex3f(0.0, 1.0, 0.0);
            glTexCoord2f(1.0, 1.0); glVertex3f(0.0, -1.0, 0.0);
        glEnd();
        glEnable(GL_LIGHTING);
    glPopMatrix();

}

//Objects to display in the scene
void display(void)
{
    //Mode for the obj files look good
    mode = mode | GLM_MATERIAL;
    mode = mode | GLM_2_SIDED;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity (); 
    glPushMatrix();

        if (VIEW_MODE == inside){
            gluLookAt (camX,camY,camZ,camX+1,camY,camZ+1, 0.0,1.0, 0.0); 
            glRotatef(rotationAngle,0.0,1.0,0.0);
        } else if (VIEW_MODE == outside){
            gluLookAt (0.0,25.0,85.0,0.0,25.0,0.0, 0.0,1.0, 0.0); 
            glRotatef(rotationAngle,0.0,1.0,0.0);
        }
        
        
        //Function to draw the museum structure
        drawMuseum();
        drawPaint(-23.0,5.0,-34.1,1.2,2.0,5.0,0.0,0.0,0.0,0.0,0);
        drawPaint(-33.0,5.0,-34.1,1.2,2.0,5.0,0.0,0.0,0.0,0.0,1);
        drawPaint(-39.5,5.0,-27.1,5.2,3.0,5.0,0.0,1.0,0.0,90.0,2);
        drawPaint(-23.0,5.0,-15.5,6.0,2.0,5.0,0.0,0.0,0.0,0.0,3);



    glPopMatrix();

    HelpDisplay(ww, wh);
    glutSwapBuffers();  
}

void loadObjects(){
   //Read objects
    plant = glmReadOBJ("./home/maceta.obj");
    glmUnitize(plant);
    glmVertexNormals(plant, 90.0, GL_TRUE); 
}

void loadtexture(int index, char file[]){

    glBindTexture(GL_TEXTURE_2D, texName[index]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    int width_1, height_1;
    unsigned char* image_1 = SOIL_load_image(file, &width_1, &height_1, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_1,height_1, 0, GL_RGB, GL_UNSIGNED_BYTE, image_1);


}

//Initialization values
void init(void) {

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glGenTextures(10, texName);

    loadtexture(0,"images/gioconda.jpg");
    loadtexture(1,"images/venus.jpg");
    loadtexture(2,"images/ultima_cena.jpg");
    loadtexture(3,"images/dios.jpg");

    qobj = gluNewQuadric();
    gluQuadricNormals(qobj, GLU_SMOOTH);
    gluQuadricDrawStyle(qobj, GLU_FILL);

    //Lights data 
    GLfloat ambient[] = { 0.980, 0.980, 0.824, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat position[] = { 0.0, 2.0, 3.0, 0.0 };
    GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
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
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    //Turn on lights
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_TEXTURE_2D);

    loadObjects();

    
    
    //Background colors
    glClearColor(0.529, 0.808, 0.922,0.0);
}

//Use keyboard letters to do different moves, sorry for the long function tho
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
        case 'x':
            camX += 0.5;
            glutPostRedisplay();
            break;
        case 'X':
            camX -= 0.5;
            glutPostRedisplay();
            break;
        case 'z':
            camZ += 0.5;
            glutPostRedisplay();
            break;
        case 'Z':
            camZ -= 0.5;
            glutPostRedisplay();
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


void HelpDisplay(GLint ww, GLint wh)
{
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
               linespace, Help_Font, "h/H to show more information");
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
        if (camX <= - 30 && camX >= -60){
            HelpRenderBitmapString(30, linestart +=
            linespace, Help_Font, "Renascement room");
            if (show_info){
                HelpRenderBitmapString(30, linestart +=
                linespace, Help_Font, "Info about Renascement room");
            } 
        } else {
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
    glEnable(GL_TEXTURE_2D);
}

void HelpRenderBitmapString(float x, float y, void *font, char *string)
{
    char *c;
    /*  set position to start drawing fonts */
    glRasterPos2f(x, y);
    /*  loop all the characters in the string */
    for (c = string; *c != '\0'; c++) {
    glutBitmapCharacter(font, *c);
    }
}
