# Textures

Textures on their own simply hold a buffer of pixel data and that buffers width, height and Bytes per pixel. Textures on their own aren't directly displayed to the end user, instead they can be drawn via a function `mlx_texture_to_image` that turns them into an image which can be displayed.

## Textures vs Images

Textures:
* Can be interpreted as a painters "color palette".
* Created by loading an image file FROM disk
* Simply contains Pixels, width, height and BPP.

Images:
* Can be interpreted as a painters "canvas".
* Can be created FROM a texture!
* Carries instance data, that is, copies of itself.
* Also holds pixel data but is shared among its instances, not loaded from disk!

## How to delete textures

```
png -> t_mlx_texture : Use mlx_delete_texture
xpm -> t_xpm (t_mlx_texture wrapper) : Use mlx_delete_xpm42
```