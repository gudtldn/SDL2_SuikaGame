#pragma once

#define MAJOR_VERSION 0
#define MINOR_VERSION 1
#define PATCH_VERSION 0

#define TARGET_FPS 240
#define FRAME_DELAY 1000 / TARGET_FPS

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define JOYSTICK_DEAD_ZONE 8000

#define STRINGIFY(x) #x
#define CLASS_NAME(x) STRINGIFY(x)
