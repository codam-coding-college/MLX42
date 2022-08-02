# XPM42

XPM42 is MLX42's own custom modified format in order to replace the outdated and messy XPM3 format. XPM42 is very similar to XPM3 (which is very similar to XPM2, surprise surprise!) so conversion is straight forward.

XPM overall is a weird format, and introduces some artefacts due to color limitation but if you want to convert an XPM3 file to XPM42 you can use the python script in the tools directory.

## Layout

The file format looks like this:

```
!XPM42            <- File declaration
16 7 2 1 c        <- Width | Height | Color count | Characters per Pixel | Mode (C: Color or M: Monochrome)
* #FF0000FF       <- Entry always: <Char> <Space> <Hexadecimal> Colors MUST have all four channels (RGBA)
. #00000000
**..*...........  <- Literal pixel data
*.*.*...........
**..*..**.**..**
*.*.*.*.*.*..*.*
**..*..**.*...**
...............*
.............**.
```
## Inner workings

Reading a XPM42 does a whole bunch of stuff but in essence it reads the file header and inserts each color entry into a hash table for fast lookups of the color value, the hash used is FNV-1a, why ? Because its an easy to use hash and also my favorite. After the header is read and the color values are inserted into the table each line is then read and each character is proccessed and inserted into the pixel buffer of the XPM.

## Tools

MLX offers a few simple tools and functions to use XPM42, you can draw multiple XPMs on a single image or import an XPM directly as an image. Once an XPM is drawn it can be safely deleted.

## Example

![Example](./assets/XPM_Demo.png)
