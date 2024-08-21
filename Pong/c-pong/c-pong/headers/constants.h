#pragma once



/**********************************************************************
 *  Game constants
 **********************************************************************/


#define  WINDOW_WIDTH 800
#define  WINDOW_HEIGHT 600
#define  FPS 60 // the target fps
#define  TIME_PER_FRAME_TARGET_MS (1000/ FPS) //the target time for each frame in ms
#define  FALSE  0
#define  TRUE  1
#define POINTS_GAINED 5



 /**********************************************************************
  *  Ball constants
  **********************************************************************/

#define  BALL_SPEED_X 100.0f
#define  BALL_SPEED_Y 100.0f
#define  BALL_WIDTH 10
#define  BALL_HEIGHT 10
#define  BALL_X_POS (WINDOW_WIDTH / 2 - (BALL_WIDTH / 2))
#define  BALL_Y_POS (WINDOW_HEIGHT / 2 - (BALL_HEIGHT / 2))




  /**********************************************************************
   *  Player / AI constants
   **********************************************************************/

#define  PLAYER_WIDTH 10
#define  PLAYER_HEIGHT 65
#define  PLAYER_MARGIN 10
#define  PLAYER_SPEED 300.0f
#define  PLAYER_Y_POS (WINDOW_HEIGHT / 2 - (PLAYER_HEIGHT / 2))
