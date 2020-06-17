#ifndef CONSTANTS_H
#define CONSTANTS_H

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define LEVEL_WIDTH 30
#define LEVEL_HEIGHT 20

#define SPRITE_HEIGHT 48
#define SPRITE_WIDTH 48

#define TILE_WIDTH 24
#define TILE_HEIGHT 24

#define FRAMETIME 1000/60.0

#define LEVEL_ORDER "levelorder.ord"
#define LEVEL_SUFFIX ".lvl"

//gameplay constants
#define NORMAL_SPEED 2
#define PILL_SPEED 1
#define EAT_DIST 8

#define FRUITTIME 30000
#define FRUIT_SCORE 100
#define GHOSTEAT_SCORE 300

#define GHOST_SCARED ":/images/ghost_scared.png"

#define RELEASE_THRESHOLDS {1.0, 0.7, 0.5, 0.4}

#endif // CONSTANTS_H
