#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <chrono>
#include "glut.h"

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

//#include <GL/gl.h>
//#include <GL/glu.h>


using namespace std;

static float angle = 90.0f;

//Angle of rotation for smaller cube as it must be different from the larger one
static float angle2 = 45.0f;
static int num_frames = 0;
static GLuint tex;

static GLfloat light_pos[] = { 1.0f, 1.0f, 1.0f, 1.0f };
static GLfloat ambient[] = { 0.05f, 0.05f, 0.05f, 1.0f };
static GLfloat diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
static GLfloat specular[] = { 0.25f, 0.25f, 0.25f, 1.0f };
static GLfloat spec_color[] = { 1.0f, 1.0f, 1.0f, 1.0f };


//Structure to create multiple raindrops
struct raindrop
{
    float xStart;
    float yStart;
    float zStart;
    float xEnd;
    float yEnd;
    float zEnd;
};


vector<raindrop> rain;
//X, Y and Z coordinates for the vertices of the smaller cube
float xCube2Pos = -6.0;
float yCube2Pos = -4.0;
float zCube2Pos = -12.0;

int windowWidth = 1720;
int windowHeight = 880;

//Var used for frame rate limiting
auto tStart = std::chrono::system_clock::now().time_since_epoch();

void loadFile(std::vector<unsigned char>& buffer, const std::string& filename) ;
int decodePNG(std::vector<unsigned char>& out_image, unsigned long& image_width,
              unsigned long& image_height, const unsigned char* in_png,
              size_t in_size, bool convert_to_rgba32 = true);
void drawLine();
void drawQuad2();
void createVector();
void changeCube2Position();

static void init(int argc, char* argv[], const std::vector<unsigned char> &img,
                 unsigned long w, unsigned long h) {
    glutInit(&argc, argv);
    glutInitWindowSize(windowWidth,windowHeight);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("OpenGL HW2");

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_DST_ALPHA);

    glDepthFunc(GL_LEQUAL);
    glClearDepth(1.0f);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 640.0f / 480.0f, 0.1f, 100.0f);

    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 img.data());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glEnable(GL_LIGHT0);




    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec_color);
}

//Creates a vector of raindrops and populates x and y coordinates for the lines
//For loop is used to offset the values so the lines start at different x values and also change the starting position
void createVector()
{
    raindrop drop;
    for(int i = 0; i < 50; i++)
    {
        drop.xStart = -6.5 + (i/5.0);
        drop.yStart = 4.0 - (i/5.0);
        drop.xEnd = -6.5 + (i/5.0);
        drop.yEnd = drop.yStart - 1.0;
        drop.zStart = -10.0;
        drop.zEnd = -10.0;
        rain.push_back(drop);
    }
}

//Function that draws each "raindrop" as a blue line using data from the rain vector
void drawLine()
{
    glEnable(GL_LIGHTING);
    glEnable (GL_LINE_STIPPLE);

    //NOTE X between -6 and 6
    //NOTE Y between -4 and 4

    glLineStipple(1, 0x0C0F);

    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 1.0f);
    for(int i = 0; i < rain.size(); i++)
    {
        if (rain[i].yStart <= -4.0)
        {
            float random = ((rand() % 144)/12.0) - 6.0;
            rain[i].xStart = random;
            rain[i].xEnd = rain[i].xStart;
            rain[i].yStart = 4.0;
            rain[i].yEnd = 3.0;
        }

        glVertex3f(rain[i].xStart, rain[i].yStart, rain[i].zStart);
        glVertex3f(rain[i].xEnd, rain[i].yEnd, rain[i].zEnd);


        rain[i].yStart -= 1.0;
        rain[i].yEnd -= 1.0;



    }
    glEnd();


}

//Translation function for the smaller cube. Moves the cube around the periphery of the screen
void changeCube2Position()
{
    //Each if statement checks the current position of the cube and changes the direction as needed
    if((xCube2Pos <= 6) && yCube2Pos <= -4.0)
    {
        //translate to the right - Increase x coordinate
        xCube2Pos += 0.05;
        glTranslated(xCube2Pos, -4.0, -12.0);
    }
    else if( xCube2Pos >= 6.0 && yCube2Pos <= 4.0)
    {
        //Translate up - Increase y coordinate
        yCube2Pos += 0.05;
        glTranslatef(xCube2Pos, yCube2Pos, -12.0);

    }
    else if(xCube2Pos >= -6.0 && yCube2Pos >= 4.0)
    {
        //Translate to the left - Decrease x coordinate
        xCube2Pos -= 0.05;
        glTranslatef(xCube2Pos, yCube2Pos, -12.0);

    }
    else if(xCube2Pos <= -6.0 && yCube2Pos >= -4.0)
    {
        //Translate down - Decrease y coordinate
        yCube2Pos -= 0.05;
        glTranslatef(xCube2Pos, yCube2Pos, -12.0);

    }
    else
    {
        xCube2Pos = -6.0;
        yCube2Pos = -4.0;
        zCube2Pos = -12.0;
    }
}

//Function to draw the second smaller cube
void drawQuad2()
{

    glBegin(GL_QUADS);
    /* Back */
    glNormal3f(0.0f, 0.0f, -1.0f);
    glColor4f(0.5f, 0.0f, 1.0f, 0.0f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5);

    /* Top */
    glNormal3f(0.0f, 1.0f, 0.0f);
    glColor4f(0.5f, 1.0f, 0.5, 1.0f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);

    /* Bottom */
    glNormal3f(0.0f, -1.0f, 0.0f);
    glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);

    /* Left */
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glColor4f(1.0f, 0.0f, 0.5f, 1.0f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);

    /* Right */
    glNormal3f(1.0f, 0.0f, 0.0f);
    glColor4f(1.0f, 0.7f, 0.0f, 1.0f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);

    /*Front*/
    glNormal3f(0.0f, 0.0f, 1.0f);
    glColor4f(0.7f, 0.0f, 0.5f, 1.0f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glEnd();
}

static void display(void) {

/////////////////////////////////////////////////////////////////////////////
    //Limit the frame rate

    //End timer
    auto tEnd = std::chrono::system_clock::now().time_since_epoch();
    auto duration = tEnd - tStart;
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();


    if(millis < 10)
    {
        Sleep(10 - millis);
    }

    //Start timer
    tStart = std::chrono::system_clock::now().time_since_epoch();
///////////////////////////////////////////////////////////////////////////

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -10.0f);
    glRotatef(angle, 1.0f, 1.0f, 1.0f);

    //glEnable(GL_BLEND);
    glEnable(GL_LIGHTING);
    glBegin(GL_QUADS);

    /* Back */
    glNormal3f(0.0f, 0.0f, -1.0f);
    glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);

    /* Top */
    glNormal3f(0.0f, 1.0f, 0.0f);
    glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);

    /* Bottom */
    glNormal3f(0.0f, -1.0f, 0.0f);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);

    /* Left */
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glColor4f(1.0f, 0.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);

    /* Right */
    glNormal3f(1.0f, 0.0f, 0.0f);
    glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);

    /* In the middle. */
    glNormal3f(0.0f, 0.0f, 1.0f);
    glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glEnd();

    /* Front */
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glBindTexture(GL_TEXTURE_2D, tex);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();

////////////////////////////////////////////////////////////////////////
    /*HW2 start*/

    /*Rain effect*/

    glPushMatrix();
    drawLine();
    glPopMatrix();

/////////////////////////////////////////////////////////////////////////
    /*Moving cube*/
    glPushMatrix();

    //Translate first then rotate the second cube
    changeCube2Position();
    glRotatef(-angle2, 1.0f, 1.0f, 0.0f);
    drawQuad2();

    glPopMatrix();

////////////////////////////////////////////////////////////////////


    glFlush();

}



static void idle(void) {
    ++num_frames;
    glutPostRedisplay();

    angle += 1.0f;
    if(angle >= 360) {
        angle = 0.0f;
    }

///////////////////////////////////////////////////////////
    angle2 += 5.0f;
    if(angle2 >= 360) {
        angle2 = 0.0f;
    }
//////////////////////////////////////////////////////////

    // if((num_frames % 100) == 0) {
    //     printf("Num Frames: %d\n", num_frames);
    // }
}


int main(int argc, char *argv[]) {
    string filename = "crate.png";
    std::vector<unsigned char> raw_png;
    std::vector<unsigned char> dec_png;
    unsigned long w, h;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
    createVector();
    //Loop through the vector a few times to prevent an initial repeating pattern when drawing the "rain"
    for(int i = 0; i < 50; i++)
    {
        for(int j = 0; j < rain.size(); j++)
        {
            //When the top point of the line reaches the bottom of the screen reset the position
            if (rain[j].yStart <= -4.0)
            {
                float random = ((rand() % 144)/12.0) - 6.0;
                rain[j].xStart = random;
                rain[j].xEnd = rain[j].xStart;
                rain[j].yStart = 4.0;
                rain[j].yEnd = 3.0;
            }
            rain[j].yStart -= 1.0;
            rain[j].yEnd -= 1.0;
        }
    }

/////////////////////////////////////////////////////////////////////////////////////////////////////////
    if(argc > 1) {
        filename = argv[1];
    }

    loadFile(raw_png, filename);
    /*if(raw_png.size() == 0) {
        fprintf(stderr, "Cannot load file '%s'\n", filename.c_str());
        return -1;
    }*/

    decodePNG(dec_png, w, h, raw_png.data(), raw_png.size());

    raw_png.clear();

    init(argc, argv, dec_png, w, h);


    glutDisplayFunc(&display);
    glutIdleFunc(&idle);



    glutMainLoop();

    return 0;
}
