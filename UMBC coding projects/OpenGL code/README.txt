Project Summary: OpenGL Rain and Textured Cube Visualization

This OpenGL project showcases a dynamic 3D scene featuring animated rain and a textured rotating cube. The project uses the GLUT library for window management and OpenGL for rendering. The project features various OpenGL concepts, including:

Texturing: 
A PNG texture (crate.png) is applied to one face of a central cube using OpenGL's texture mapping techniques. The project includes texture loading, binding, and configuring texture parameters.

Lighting and Materials: 
The scene employs ambient, diffuse, and specular lighting to enhance realism, along with configurable material properties using glMaterialfv and glLightfv.

3D Geometry: 
The main visual elements are a large rotating cube with a textured face and a smaller cube that translates along the periphery of the scene. The project uses GL_QUADS to construct the cube faces and applies transformations for rotation and translation.

Animation: 
The project features animated rain, represented by blue lines that fall from the top of the scene and reset at random horizontal positions when reaching the bottom. The smaller cube also moves along a set path using incremental transformations.

Frame Rate Management: 
The rendering loop is optimized using std::chrono to cap the frame rate, ensuring smooth performance across different systems.
The final output is a visually engaging 3D animation that combines textured rendering, animated geometry, and basic particle effects to create an immersive OpenGL demonstration.



For assignment we were given a template of starting code written by our professor. The following features were added by me:

The code is written in such a way that the window size can be adjusted

Png crate texture - 
This was implemented using the picoPNG PNG decoder by Lode Vandevenne. It converts a PNG into raw RGBA pixel data, which is then used by openGL to render the PNG onto an object. 

Rain effect - 
The rain effect is achieved using a particle system where each raindrop is represented as a struct with x, y and z values which is used to draw a blue line(representing the raindrop). At the start of the scene an array of raindrop structs is created and their positions are randomized. Every frame the y position of the line is changed so they move to the bottom of the screen. When the end of a line reaches the bottom of the screen the line moves to a random location at the top of the screen and moves down again.

Cube moving around the periphery of the window -
The same code used to create the spinning cube in the middle of the screen is implemented here with slight changes to size values and face colors. When the cube "collides" with the border of the window it will change direction. This is achieved by changing the values of the x or y coordinates depending on the location of the cube. Furthermore, the border that the cube collides with is dynamically determined by window size, so the scene will just adjust as the window size is changed. 







