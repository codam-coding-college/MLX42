# MLX42

Project still WIP!

My own recreation of the MiniLibX library used by 42, using glfw &amp; glad, running on OpenGL 3.3.
The goal of MLX42 is to replace the outdated and stale MiniLibX library.

## Differences to MiniLibX
#### No Images
Instead of having separate "Images" (textures) theres only a single buffer used to draw the pixels.

#### Custom XPM (XPM42) format
A custom simple to use XPM-like format which is has some minor differences to the XPM3 format.

#### Cross-Platform
The main idea of MLX42 is to be a cross-platform graphics interface, in 42 everything runs (currently) on MacOS but its
very useful to be able to work remotley on different machines. With MiniLibX this is not possible.

#### Misc
 - Yes, MLX42 adheres 100% to the latest norme. 
 - 100% Documented, making it very beginner friendly and easy to use.
 - Running with OpenGL 3.3
 
## Installation

For MacOS:
- Should be straight forward with a simple `make` in the terminal.

The systems below have not been tested yet.

For Linux:
- Make sure you have installed glfw, you need to compile it from source.

For Windows:
- Switch to MacOS or Linux, as there is no CMake or way to compile for it yet.
