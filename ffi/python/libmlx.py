# ============================================================================
# Codam Coding College, Amsterdam 2018-2025, All Rights Reserved.
# See README in the root project for more information.
# ============================================================================
# Python FFI bindings for MLX42
# ============================================================================
# This module provides Python bindings to the MLX42 graphics library using
# the ctypes library. It handles loading the appropriate shared library based
# on the operating system and defines necessary types, constants, and function
# prototypes for interacting with MLX42.
# ============================================================================

import ctypes
from os import path
from logging import critical
from platform import system

# ============================================================================

try: # Load FFI Library
    lib = 'libmlx42'
    system = system()
    if system == "Linux":
        lib_name = f"{lib}.so"
    elif system == "Darwin":
        lib_name = f"{lib}.dylib"
    elif system == "Windows":
        lib_name = f"{lib}.dll"
    else:
        raise RuntimeError("Unsupported operating system")
    # Check if in the current working directory first
    if path.exists(f"./{lib_name}"):
        mlx = ctypes.CDLL(f"./{lib_name}")
    else:
	    mlx = ctypes.CDLL(lib_name)
except OSError as e:
    critical(f"Could not load the MLX42 library '{lib_name}'.")
    critical(e)
    exit(1)

# Type Definitions, Constants, and Enums
# ============================================================================

c_int32 = ctypes.c_int32
c_uint32 = ctypes.c_uint32
c_uint8 = ctypes.c_uint8
c_size_t = ctypes.c_size_t
c_bool = ctypes.c_bool
c_double = ctypes.c_double
c_char_p = ctypes.c_char_p
c_void_p = ctypes.c_void_p

# keys_t
MLX_KEY_SPACE           = 32
MLX_KEY_APOSTROPHE      = 39
MLX_KEY_COMMA           = 44
MLX_KEY_MINUS           = 45
MLX_KEY_PERIOD          = 46
MLX_KEY_SLASH           = 47
MLX_KEY_0               = 48
MLX_KEY_1               = 49
MLX_KEY_2               = 50
MLX_KEY_3               = 51
MLX_KEY_4               = 52
MLX_KEY_5               = 53
MLX_KEY_6               = 54
MLX_KEY_7               = 55
MLX_KEY_8               = 56
MLX_KEY_9               = 57
MLX_KEY_SEMICOLON       = 59
MLX_KEY_EQUAL           = 61
MLX_KEY_A               = 65
MLX_KEY_B               = 66
MLX_KEY_C               = 67
MLX_KEY_D               = 68
MLX_KEY_E               = 69
MLX_KEY_F               = 70
MLX_KEY_G               = 71
MLX_KEY_H               = 72
MLX_KEY_I               = 73
MLX_KEY_J               = 74
MLX_KEY_K               = 75
MLX_KEY_L               = 76
MLX_KEY_M               = 77
MLX_KEY_N               = 78
MLX_KEY_O               = 79
MLX_KEY_P               = 80
MLX_KEY_Q               = 81
MLX_KEY_R               = 82
MLX_KEY_S               = 83
MLX_KEY_T               = 84
MLX_KEY_U               = 85
MLX_KEY_V               = 86
MLX_KEY_W               = 87
MLX_KEY_X               = 88
MLX_KEY_Y               = 89
MLX_KEY_Z               = 90
MLX_KEY_LEFT_BRACKET    = 91
MLX_KEY_BACKSLASH       = 92
MLX_KEY_RIGHT_BRACKET   = 93
MLX_KEY_GRAVE_ACCENT    = 96
MLX_KEY_ESCAPE          = 256
MLX_KEY_ENTER           = 257
MLX_KEY_TAB             = 258
MLX_KEY_BACKSPACE       = 259
MLX_KEY_INSERT          = 260
MLX_KEY_DELETE          = 261
MLX_KEY_RIGHT           = 262
MLX_KEY_LEFT            = 263
MLX_KEY_DOWN            = 264
MLX_KEY_UP              = 265
MLX_KEY_PAGE_UP         = 266
MLX_KEY_PAGE_DOWN       = 267
MLX_KEY_HOME            = 268
MLX_KEY_END             = 269
MLX_KEY_CAPS_LOCK       = 280
MLX_KEY_SCROLL_LOCK     = 281
MLX_KEY_NUM_LOCK        = 282
MLX_KEY_PRINT_SCREEN    = 283
MLX_KEY_PAUSE           = 284
MLX_KEY_F1              = 290
MLX_KEY_F2              = 291
MLX_KEY_F3              = 292
MLX_KEY_F4              = 293
MLX_KEY_F5              = 294
MLX_KEY_F6              = 295
MLX_KEY_F7              = 296
MLX_KEY_F8              = 297
MLX_KEY_F9              = 298
MLX_KEY_F10             = 299
MLX_KEY_F11             = 300
MLX_KEY_F12             = 301
MLX_KEY_F13             = 302
MLX_KEY_F14             = 303
MLX_KEY_F15             = 304
MLX_KEY_F16             = 305
MLX_KEY_F17             = 306
MLX_KEY_F18             = 307
MLX_KEY_F19             = 308
MLX_KEY_F20             = 309
MLX_KEY_F21             = 310
MLX_KEY_F22             = 311
MLX_KEY_F23             = 312
MLX_KEY_F24             = 313
MLX_KEY_F25             = 314
MLX_KEY_KP_0            = 320
MLX_KEY_KP_1            = 321
MLX_KEY_KP_2            = 322
MLX_KEY_KP_3            = 323
MLX_KEY_KP_4            = 324
MLX_KEY_KP_5            = 325
MLX_KEY_KP_6            = 326
MLX_KEY_KP_7            = 327
MLX_KEY_KP_8            = 328
MLX_KEY_KP_9            = 329
MLX_KEY_KP_DECIMAL      = 330
MLX_KEY_KP_DIVIDE       = 331
MLX_KEY_KP_MULTIPLY     = 332
MLX_KEY_KP_SUBTRACT     = 333
MLX_KEY_KP_ADD          = 334
MLX_KEY_KP_ENTER        = 335
MLX_KEY_KP_EQUAL        = 336
MLX_KEY_LEFT_SHIFT      = 340
MLX_KEY_LEFT_CONTROL    = 341
MLX_KEY_LEFT_ALT        = 342
MLX_KEY_LEFT_SUPER      = 343
MLX_KEY_RIGHT_SHIFT     = 344
MLX_KEY_RIGHT_CONTROL   = 345
MLX_KEY_RIGHT_ALT       = 346
MLX_KEY_RIGHT_SUPER     = 347
MLX_KEY_MENU            = 348

# cursor_t
MLX_CURSOR_ARROW		= 0x00036001
MLX_CURSOR_IBEAM		= 0x00036002
MLX_CURSOR_CROSSHAIR	= 0x00036003
MLX_CURSOR_HAND			= 0x00036004
MLX_CURSOR_HRESIZE		= 0x00036005
MLX_CURSOR_VRESIZE		= 0x00036006

# mouse_mode_t
MLX_MOUSE_NORMAL	= 0x00034001
MLX_MOUSE_HIDDEN	= 0x00034002
MLX_MOUSE_DISABLED	= 0x00034003

# mouse_key_t
MLX_MOUSE_BUTTON_LEFT	= 0
MLX_MOUSE_BUTTON_RIGHT	= 1
MLX_MOUSE_BUTTON_MIDDLE	= 2

# modifier_key_t
MLX_SHIFT		= 0x0001
MLX_CONTROL		= 0x0002
MLX_ALT			= 0x0004
MLX_SUPERKEY	= 0x0008
MLX_CAPSLOCK	= 0x0010
MLX_NUMLOCK		= 0x0020

MLX_RELEASE = 0
MLX_PRESS	= 1
MLX_REPEAT	= 2

MLX_STRETCH_IMAGE = 0,	# Should images resize with the window as it's being resized or not. Default: false
MLX_FULLSCREEN = 1,			# Should the window be in Fullscreen, note it will fullscreen at the given resolution. Default: false
MLX_MAXIMIZED = 2,			# Start the window in a maximized state, overwrites the fullscreen state if this is true. Default: false
MLX_DECORATED = 3,			# Have the window be decorated with a window bar. Default: true
MLX_HEADLESS = 4,			# Run in headless mode, no window is created. (NOTE: Still requires some form of window manager such as xvfb)
MLX_SETTINGS_MAX = 5,		# Setting count.

# Structures
# ============================================================================

class mlx_texture_t(ctypes.Structure):
    _fields_ = [
        ("width", c_uint32),
        ("height", c_uint32),
        ("bytes_per_pixel", c_uint8),
        ("pixels", ctypes.POINTER(c_uint8))
    ]

class mlx_instance_t(ctypes.Structure):
    _fields_ = [
        ("x", c_int32),
        ("y", c_int32),
        ("z", c_int32),
        ("enabled", c_bool)
    ]

class xpm_t(ctypes.Structure):
    _fields_ = [
        ("texture", mlx_texture_t),
        ("color_count", c_int32),
        ("cpp", c_int32),
        ("mode", ctypes.c_char)
    ]

class mlx_key_data_t(ctypes.Structure):
    _fields_ = [
        ("key", c_int32), # ENUM
        ("action", c_int32), # ENUM
        ("os_key", c_int32),
        ("modifier", c_int32) # ENUM
    ]

class mlx_image_t(ctypes.Structure):
    _fields_ = [
        ("width", c_uint32),
        ("height", c_uint32),
        ("pixels", ctypes.POINTER(c_uint8)),
        ("instances", ctypes.POINTER(mlx_instance_t)),
        ("count", c_size_t),
        ("enabled", c_bool),
        ("context", c_void_p)
    ]

class mlx_instance_t(ctypes.Structure):
    _fields_ = [
        ("x", c_int32),
        ("y", c_int32),
        ("z", c_int32),
        ("enabled", c_bool)
    ]

class mlx_t(ctypes.Structure):
    _fields_ = [
        ("window", c_void_p),
        ("context", c_void_p),
        ("width", c_int32),
        ("height", c_int32),
        ("delta_time", c_double)
    ]

# Function Callbacks
# ============================================================================

mlx_scrollfunc = ctypes.CFUNCTYPE(None, c_double, c_double, c_void_p)
mlx_mousefunc = ctypes.CFUNCTYPE(None, c_int32, c_int32, c_int32, c_void_p)
mlx_cursorfunc = ctypes.CFUNCTYPE(None, c_double, c_double, c_void_p)
mlx_keyfunc = ctypes.CFUNCTYPE(None, mlx_key_data_t, c_void_p)
mlx_resizefunc = ctypes.CFUNCTYPE(None, c_int32, c_int32, c_void_p)
mlx_closefunc = ctypes.CFUNCTYPE(None, c_void_p)
mlx_loop_hook_func = ctypes.CFUNCTYPE(None, c_void_p)

# Function Signatures
# ============================================================================

# Error
mlx.mlx_strerror.argtypes = [c_int32] # errno_t enum
mlx.mlx_strerror.restype = c_char_p

mlx.mlx_get_errno.argtypes = []
mlx.mlx_get_errno.restype = c_int32 # errno_t enum


# Generic MLX Functions
mlx.mlx_init.argtypes = [c_int32, c_int32, c_char_p, c_bool]
mlx.mlx_init.restype = ctypes.POINTER(mlx_t)

mlx.mlx_set_setting.argtypes = [ctypes.c_int, c_int32] # mlx_settings_t
mlx.mlx_set_setting.restype = None

mlx.mlx_close_window.argtypes = [ctypes.POINTER(mlx_t)]
mlx.mlx_close_window.restype = None

mlx.mlx_loop.argtypes = [ctypes.POINTER(mlx_t)]
mlx.mlx_loop.restype = None

mlx.mlx_terminate.argtypes = [ctypes.POINTER(mlx_t)]
mlx.mlx_terminate.restype = None

mlx.mlx_get_time.argtypes = []
mlx.mlx_get_time.restype = c_double


# Image Functions
mlx.mlx_put_pixel.argtypes = [ctypes.POINTER(mlx_image_t), c_uint32, c_uint32, c_uint32]
mlx.mlx_put_pixel.restype = None

mlx.mlx_new_image.argtypes = [ctypes.POINTER(mlx_t), c_uint32, c_uint32]
mlx.mlx_new_image.restype = ctypes.POINTER(mlx_image_t)

mlx.mlx_image_to_window.argtypes = [ctypes.POINTER(mlx_t), ctypes.POINTER(mlx_image_t), c_int32, c_int32]
mlx.mlx_image_to_window.restype = c_int32

mlx.mlx_delete_image.argtypes = [ctypes.POINTER(mlx_t), ctypes.POINTER(mlx_image_t)]
mlx.mlx_delete_image.restype = None

# Input
mlx.mlx_is_key_down.argtypes = [ctypes.POINTER(mlx_t), ctypes.c_int] # keys_t
mlx.mlx_is_key_down.restype = c_bool

# Hooks
mlx.mlx_loop_hook.argtypes = [ctypes.POINTER(mlx_t), mlx_loop_hook_func, c_void_p]
mlx.mlx_loop_hook.restype = c_bool