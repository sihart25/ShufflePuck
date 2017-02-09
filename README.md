# ShufflePuck
The aim of this assessment was to develop a virtual environment for the game of ShufflePuck using physically based modelling techniques. The program has been written in C++ using the OpenGL and GLUT libraries. All of the compulsory components and the extensions have been implemented.  
#2: Program Features
The following list of features has been implemented.
#2.1: Collision Detection (2D)
Cylinders
Blocks

#2.2: Collision Response (2D)
Mass
Moment of inertia
Coefficient of restitution
Coefficient of friction
Damping

#2.3: Game Features
Pitch
Walls
Goals
Posts
Floodlights
Goal detection
On-screen scoring
Multiple pucks
Sound

#2.4: Views
Player
Aerial
Puck
Inset views
Cross-eyed stereo
Offset-parallel stereo

#2.5: Graphics
Reflections
Shadows
Fog
Textures
Fonts
#3: Program Theory
#3.1: Simulation Loop
The simulation loop repeats at about 1000 cycles per second by running at a fixed rate of 16 cycles per frame. An attempt was made to track the frame rate, so that the simulation cycle period would be independent of the processor speed and screen size. However, due to its inherent lag, this had the undesired effect of the simulation loop attempting to speed up after the program had lost processor time. A better technique would be to drive the simulation loop directly from a timer.
In each simulation cycle, all potentially colliding objects are tested for collision. If any collisions are detected, then the motion of the system is updated to the time of the first collision, and the collision response is applied. Further collision tests, motion updates and collision responses are then performed in the time remaining in the current simulation cycle. If no collisions are detected, then the motion is updated to the time of the next simulation cycle. Repeated intersections are avoided by updating the motion of the system to a time slightly before that of the first collision. Collision detection and response is performed in two dimensions only.
#3.2: Collision Detection
The collision test between two cylinders assumes that one of them is stationary with its radius equal to the sum of the two radii, and that the other is a particle with its velocity equal to the relative velocity between the two cylinders. Any point of collision can then be determined as the intersection between the line segment and the circle, corresponding to the particle and the stationary cylinder respectively. This requires the solution of a quadratic equation.
The collision test between a block and a cylinder assumes that the block has its width and height increased by the radius of the cylinder, and that the block has rounded corners. Any point of collision can then be determined as the intersection between a line segment and this complex shape. This requires the solution of four linear and four quadratic equations. The collision test between a block and a cylinder should also take account of the angular velocity of the block. This is achieved by converting the angular velocity into an equivalent linear velocity, according to the position and velocity of the cylinder. As a special case, the collision between a player and a wall is assumed to be equivalent to that of a cylinder and block. This allows players to rotate freely, even when they are in direct contact with a wall.
#3.3: Collision Response
The collision response is determined in terms of the perpendicular and parallel components at the point of collision. Both linear and angular velocities are considered. The density and the coefficients of restitution and friction are specified for each object. The density and dimensions of an object determine its mass and moment of inertia. For convenience, the greater of each of the coefficients of restitution and friction are used for the two objects in collision.
At a collision between two moving objects, the ratio of the magnitude of their relative perpendicular velocities before and after the collision is determined by the coefficient of restitution. The conservation of momentum along the perpendicular axis creates a set of two simultaneous linear equations that can be solved.
The frictional impulse between two moving objects is proportional and in opposition to the relative parallel velocity of their surfaces. This relative parallel velocity is dependent on the linear and angular velocities of the objects. The change in the relative parallel velocity before and after a collision is determined by the coefficient of friction. The conservation of momentum along the parallel axis creates a set of two simultaneous linear equations that can be solved.
The frictional impulse also creates a rotational impulse, which is determined by the perpendicular distance of the point of collision from the centre of the object. This rotational impulse causes a change in the angular momentum and velocity of each object, according to their moments of inertia.
At a collision between a moving object and a fixed stationary object, the conservation of momentum cannot be applied. The perpendicular and parallel velocities are determined directly from the coefficients of restitution and friction respectively.
#3.4: Damping
Damping is applied to both the linear and angular velocities on each simulation cycle, and it is assumed to be proportional and in opposition to them. A simplified version of Euler’s method is used, in which the velocity is assumed to be constant over the period of the simulation cycle. This ensures that the collision detection predictions are consistent with the subsequent motion updates.
#3.5: User Interaction
The user can control the linear and angular accelerations of the player by using the mouse and cursor keys. The players are heavily damped to ensure smooth motion.
#3.6: Multiple Views
Player, aerial and puck camera views are provided. The player camera moves and rotates with the player, the aerial camera is stationary, and the puck camera follows the puck’s velocity vector. Inset player, aerial and puck views are achieved by using a scissor test on the main view before rendering the inset view.
#3.7: Stereo Views
Cross-eyed stereo view is provided by using offset player cameras to render into two view ports, which are separated by a border. Cross-eyed stereoscopy is achieved by rendering the image for the right eye to the left side of the screen, and that for the left eye to the right side of the screen. Moving the camera to the right, and directing it towards the convergence point produces the image for the right eye. The centre of this camera view is rotated to align with the centre of the left view port, and the viewing frustum is offset relative to the camera to cover this view port. The image for the left eye is produced in a similar manner.
Offset-parallel stereo views are provided by using the left and right buffers. Offset-parallel stereoscopy is achieved by rendering the image for the left eye to the left buffer, and that for the right eye to the right buffer. Moving the camera to the right, and directing it towards the convergence point produces the image for the right eye. The centre of this camera view is rotated to the left to obtain an offset-parallel view, and the viewing frustum is offset to the left to obtain zero parallax at the convergence point. The image for the left eye is produced in a similar manner.
#3.8: Fonts
Text can be displayed on the screen by using a texture map, which contains a font of 256 characters. For each character to be displayed, a small rectangle with the relevant section of the texture map is rendered to the screen. Jeff Molofee and Giuseppe D’Agata describe this technique in their tutorial.
#3.9: Reflections
Reflections of objects are rendered as if they were geometrically reflected in the plane of the floor. The stencil buffer is used to limit the extent of the reflections to the area of the floor. The floor is subsequently rendered with its transparency controlling the intensity of the reflections. Mark Kilgard describes a similar technique in his tutorial.
#3.10: Shadows
Planar shadows of objects are projected onto the floor from each of the four floodlights. The stencil buffer is used to limit the extent of the shadows to the area of the floor, and to avoid the effect of multiple shadowing from overlapping objects in the projection from a light source. The shadows are rendered as black silhouettes with their transparencies controlling their intensities. The projection is achieved by multiplying a suitable projection matrix into the model-view matrix. Mark Kilgard describes a similar technique in his tutorial.
#3.11: Textures
Texture maps are read from Windows BMP files into texture objects. Textures can be applied to blocks, cylinders, discs and planes. Texture coordinates can be specified for blocks and planes. Mipmaps are generated automatically.
#3.12: Sound
Sounds are read from WAV files into sound objects. Sounds can be rendered at the time of collision, and their volumes are dependent on the speed of collision. The latest version of the OpenAL library supports both Windows 98 and NT4. Executables with and without links to the sound library are provided. The executable that has been linked to the sound library requires the use of the OpenAL32 dynamic link library.
#4: Program Design
#4.1: Class Architecture
The design has been implemented as the display, control, font, game, collision, node, group, label, reference, screen, camera, light, shape, block, cylinder, disc, plane, line, player, post, puck, wall, transform, material, physical, texture, sound, bitmap, reader, colour and vectors classes.
#4.2: Control Classes
The display and control class provide the interface for user interaction using the mouse and keyboard. The control class delegates the responsibility for maintaining the state of the game to the game class, and the responsibility for rendering a view of the game to the label class. The font class allows text to be displayed on the screen.
The game class maintains an associative container of references to labels. This allows objects representing cameras, lights, shapes, textures and sounds to be read from the data files, and labelled for easy reference. For improved rendering speed this associative container can also reference display lists. The collision class regulates all player and puck movement.
#4.3: Model Classes
The node class is the abstract base class, from which all of the other model classes inherit. This allows objects to be grouped into a hierarchical tree, or labelled and added to an associative container. The node’s interface includes read, update and render operations. The group class provides a hierarchical container of nodes. The label class inherits from the group class and allows labelling of groups of nodes. The reference class allows labelled groups of nodes to be referenced.
The screen class contains the background colour attribute. The camera class contains position, direction, up vector and field of view attributes, and applies these to the projection and view matrices. The light class contains position, ambient, diffuse and specular colour attributes. The shape class contains the material and physical attributes. The block, cylinder, disc and plane classes all derive from the shape class, and add specialized attributes for their specific shapes. The line, player, post, puck and wall classes derive from the block or cylinder classes, and add specialized attributes. The texture and sound classes read into texture and sound objects from BMP and WAV files respectively.
The transform class contains scale, rotate and translate attributes, which are applied to the model matrix in that order. The effect of a transform is local to a group of nodes, and effective from its point of definition onwards. The material class contains ambient, diffuse, specular, shininess and emissive colour attributes. These attributes assume their default values for a shape unless they are explicitly specified. The physical class contains position, velocity, axis, angle, spin, density, restitution, friction and damping attributes.
#5: Conclusions
The assessment has been completed successfully. It has demonstrated the use of OpenGL and collision detection and response algorithms to model and render an interactive view of a physically based virtual environment. Physically based modelling, stereo display, sound, and more advanced graphics features, such as reflections, shadows, fog and textures, all contribute to the effectiveness of the virtual environment
#Appendix 1: Class Diagram
#Appendix 2: User Guide
The program is run from the command line as “ShufflePuck.exe” or “ShufflePuckWithoutSound.exe”. If the program is run with a command line argument, then this specifies the filename of the data file. Otherwise, the program reads the data file from “../Data/Game.txt”. The following menu is displayed in the console window, to summarise the use of the mouse and keyboard.

Escape
Exit
Space
Restart
F1
Player View
F2
Aerial View
F3	
Puck View
F4
Next Puck View
F5
Player Inset View
F6
Aerial Inset View
F7
Puck Inset View
F8
Toggle Score
F9
Cross-Eyed View
F10
Stereo View
F11
Left View
F12
Right View
1
Toggle Reflections
2
Toggle Shadows
3
Toggle Fog
4
Toggle Wireframe
Insert
Add Puck
Delete
Remove Puck
Left, Right or Mouse
Rotate
Down, Up or Mouse
Move
Page Down or Left Mouse
Home Player
Page Up or Right Mouse
Away Player
