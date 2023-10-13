#include "util.h"

// ::Road Tiles:: -------------
// Green Tiles -------------
static SDL_Rect T_GRASS = { 0,  0,  32,  64 };
static SDL_Rect T_BUSH_A1 = { 32, 0, 32, 64 };
static SDL_Rect T_BUSH_A2 = { 64, 0, 32, 64 };
static SDL_Rect T_BUSH_B1 = { 96, 0, 32, 64 };
static SDL_Rect T_BUSH_B2 = { 128, 0, 32, 64 };
static SDL_Rect T_TREE_A1 = { 160, 0, 32, 64 };
static SDL_Rect T_TREE_A2 = { 192, 0, 32, 64 };
static SDL_Rect T_TREE_B1 = { 224, 0, 32, 64 };
static SDL_Rect T_TREE_B2 = { 256, 0, 32, 64 };
static SDL_Rect T_TREE_C1 = { 288, 0, 32, 64 };
static SDL_Rect T_TREE_C2 = { 320, 0, 32, 64 };
static SDL_Rect T_TREE_D1 = { 352, 0, 32, 64 };
static SDL_Rect T_TREE_D2 = { 384, 0, 32, 64 };
static SDL_Rect T_TREE_E1 = { 416, 0, 32, 64 };
static SDL_Rect T_TREE_E2 = { 448, 0, 32, 64 };

// Rect Tiles -------------
static SDL_Rect T_ROAD = { 0, 64, 32, 64 };
static SDL_Rect T_SAND = { 32, 64, 32, 64 };
static SDL_Rect T_RECT_A1 = { 64, 64, 32, 64 };
static SDL_Rect T_RECT_A2 = { 96, 64, 32, 64 };
static SDL_Rect T_RECT_B1 = { 128, 64, 32, 64 };
static SDL_Rect T_RECT_B2 = { 160, 64, 32, 64 };

// Road  Minus Tiles -------------
static SDL_Rect T_RMINUS_A1 = { 0, 128, 32, 64 };
static SDL_Rect T_RMINUS_A2 = { 32, 128, 32, 64 };
static SDL_Rect T_RMINUS_B1 = { 64, 128, 32, 64 };
static SDL_Rect T_RMINUS_B2 = { 96, 128, 32, 64 };
static SDL_Rect T_RMINUS_C1 = { 128, 128, 32, 64 };
static SDL_Rect T_RMINUS_C2 = { 160, 128, 32, 64 };
static SDL_Rect T_RMINUS_D1 = { 192, 128, 32, 64 };
static SDL_Rect T_RMINUS_D2 = { 224, 128, 32, 64 };
static SDL_Rect T_RMINUS_E1 = { 256, 128, 32, 64 };
static SDL_Rect T_RMINUS_E2 = { 288, 128, 32, 64 };
static SDL_Rect T_RMINUS_F1 = { 320, 128, 32, 64 };
static SDL_Rect T_RMINUS_F2 = { 352, 128, 32, 64 };
static SDL_Rect T_RMINUS_G1 = { 384, 128, 32, 64 };
static SDL_Rect T_RMINUS_G2 = { 416, 128, 32, 64 };

// Grass Minus Tiles -------------
//static SDL_Rect T_GMINUS_A1 = {0, 192, 32, 64};
//static SDL_Rect T_GMINUS_A2 = {32, 192, 32, 64};
static SDL_Rect T_GMINUS_B1 = { 64, 192, 32, 64 };
static SDL_Rect T_GMINUS_B2 = { 96, 192, 32, 64 };
static SDL_Rect T_GMINUS_C1 = { 128, 192, 32, 64 };
static SDL_Rect T_GMINUS_C2 = { 160, 192, 32, 64 };
static SDL_Rect T_GMINUS_D1 = { 192, 192, 32, 64 };
static SDL_Rect T_GMINUS_D2 = { 224, 192, 32, 64 };
static SDL_Rect T_GMINUS_E1 = { 256, 192, 32, 64 };
static SDL_Rect T_GMINUS_E2 = { 288, 192, 32, 64 };
static SDL_Rect T_GMINUS_F1 = { 320, 192, 32, 64 };
static SDL_Rect T_GMINUS_F2 = { 352, 192, 32, 64 };
static SDL_Rect T_GMINUS_G1 = { 384, 192, 32, 64 };
static SDL_Rect T_GMINUS_G2 = { 416, 192, 32, 64 };

// Curves Tiles (tiles horizontal x tiles vertical) ------------- 
// Road	Curve Left 2 x 1
static SDL_Rect T_RCURL2_A1 = { 0, 256, 32, 64 };
static SDL_Rect T_RCURL2_A2 = { 32, 256, 32, 64 };
static SDL_Rect T_RCURL2_B1 = { 64, 256, 32, 64 };
static SDL_Rect T_RCURL2_B2 = { 96, 256, 32, 64 };

// Road	Curve Right 2 x 1
static SDL_Rect T_RCURR2_A1 = { 128, 256, 32, 64 };
static SDL_Rect T_RCURR2_A2 = { 160, 256, 32, 64 };
static SDL_Rect T_RCURR2_B1 = { 192, 256, 32, 64 };
static SDL_Rect T_RCURR2_B2 = { 224, 256, 32, 64 };

// Road	Curve Right 3 x 1
static SDL_Rect T_RCURR3_A1 = { 256, 256, 32, 64 };
static SDL_Rect T_RCURR3_A2 = { 288, 256, 32, 64 };
static SDL_Rect T_RCURR3_B1 = { 320, 256, 32, 64 };
static SDL_Rect T_RCURR3_B2 = { 352, 256, 32, 64 };
static SDL_Rect T_RCURR3_C1 = { 384, 256, 32, 64 };
static SDL_Rect T_RCURR3_C2 = { 416, 256, 32, 64 };

// Road	Curve Left 3 x 1
static SDL_Rect T_RCURL3_A1 = { 448, 256, 32, 64 };
static SDL_Rect T_RCURL3_A2 = { 480, 256, 32, 64 };
static SDL_Rect T_RCURL3_B1 = { 512, 256, 32, 64 };
static SDL_Rect T_RCURL3_B2 = { 544, 256, 32, 64 };
static SDL_Rect T_RCURL3_C1 = { 576, 256, 32, 64 };
static SDL_Rect T_RCURL3_C2 = { 608, 256, 32, 64 };

// Grass Curve Left 2 x 1
static SDL_Rect T_GCURL2_A1 = { 0, 320, 32, 64 };
static SDL_Rect T_GCURL2_A2 = { 32, 320, 32, 64 };
static SDL_Rect T_GCURL2_B1 = { 64, 320, 32, 64 };
static SDL_Rect T_GCURL2_B2 = { 96, 320, 32, 64 };

// Grass Curve Right 2 x 1
static SDL_Rect T_GCURR2_A1 = { 128, 320, 32, 64 };
static SDL_Rect T_GCURR2_A2 = { 160, 320, 32, 64 };
static SDL_Rect T_GCURR2_B1 = { 192, 320, 32, 64 };
static SDL_Rect T_GCURR2_B2 = { 224, 320, 32, 64 };

// Grass Curve Right 3 x 1
static SDL_Rect T_GCURR3_A1 = { 256, 320, 32, 64 };
static SDL_Rect T_GCURR3_A2 = { 288, 320, 32, 64 };
static SDL_Rect T_GCURR3_B1 = { 320, 320, 32, 64 };
static SDL_Rect T_GCURR3_B2 = { 352, 320, 32, 64 };
static SDL_Rect T_GCURR3_C1 = { 384, 320, 32, 64 };
static SDL_Rect T_GCURR3_C2 = { 416, 320, 32, 64 };

// Grass Curve Left 3 x 1
static SDL_Rect T_GCURL3_A1 = { 448, 320, 32, 64 };
static SDL_Rect T_GCURL3_A2 = { 480, 320, 32, 64 };
static SDL_Rect T_GCURL3_B1 = { 512, 320, 32, 64 };
static SDL_Rect T_GCURL3_B2 = { 544, 320, 32, 64 };
static SDL_Rect T_GCURL3_C1 = { 576, 320, 32, 64 };
static SDL_Rect T_GCURL3_C2 = { 608, 320, 32, 64 };

// Escape Tiles to Rigth-------------
static SDL_Rect T_ESCR_END_A = { 0, 384, 32, 64 };
static SDL_Rect T_ESCR_END_B1 = { 32, 384, 32, 64 };
static SDL_Rect T_ESCR_END_B2 = { 64, 384, 32, 64 };
static SDL_Rect T_ESCR_END_C1 = { 96, 384, 32, 64 };
static SDL_Rect T_ESCR_END_C2 = { 128, 384, 32, 64 };
static SDL_Rect T_ESCR_END_C3 = { 160, 384, 32, 64 };
static SDL_Rect T_ESCR_CUR_A1 = { 192, 384, 32, 64 };
static SDL_Rect T_ESCR_CUR_A2 = { 224, 384, 32, 64 };
static SDL_Rect T_ESCR_CUR_A3 = { 256, 384, 32, 64 };
static SDL_Rect T_ESCR_CUR_A4 = { 288, 384, 32, 64 };
static SDL_Rect T_ESCR_CUR_B1 = { 320, 384, 32, 64 };
static SDL_Rect T_ESCR_CUR_B2 = { 352, 384, 32, 64 };
static SDL_Rect T_ESCR_CUR_B3 = { 384, 384, 32, 64 };
static SDL_Rect T_ESCR_RECT_L = { 416, 384, 32, 64 };
static SDL_Rect T_ESCR_RECT = { 448, 384, 32, 64 };
static SDL_Rect T_ESCR_RECT_R = { 480, 384, 32, 64 };
static SDL_Rect T_ESCR_START = { 512, 384, 32, 64 };

// Escape Tiles to Left-------------
static SDL_Rect T_ESCL_END_A = { 0, 448, 32, 64 };
static SDL_Rect T_ESCL_END_B1 = { 32, 448, 32, 64 };
static SDL_Rect T_ESCL_END_B2 = { 64, 448, 32, 64 };
static SDL_Rect T_ESCL_END_C1 = { 96, 448, 32, 64 };
static SDL_Rect T_ESCL_END_C2 = { 128, 448, 32, 64 };
static SDL_Rect T_ESCL_END_C3 = { 160, 448, 32, 64 };
static SDL_Rect T_ESCL_CUR_A1 = { 192, 448, 32, 64 };
static SDL_Rect T_ESCL_CUR_A2 = { 224, 448, 32, 64 };
static SDL_Rect T_ESCL_CUR_A3 = { 256, 448, 32, 64 };
static SDL_Rect T_ESCL_CUR_A4 = { 288, 448, 32, 64 };
static SDL_Rect T_ESCL_CUR_B1 = { 320, 448, 32, 64 };
static SDL_Rect T_ESCL_CUR_B2 = { 352, 448, 32, 64 };
static SDL_Rect T_ESCL_CUR_B3 = { 384, 448, 32, 64 };
static SDL_Rect T_ESCL_RECT_L = { 416, 448, 32, 64 };
static SDL_Rect T_ESCL_RECT = { 448, 448, 32, 64 };
static SDL_Rect T_ESCL_RECT_R = { 480, 448, 32, 64 };
static SDL_Rect T_ESCL_START = { 512, 448, 32, 64 };

// Water Tiles -------------
static SDL_Rect T_WATER = { 0, 512, 32, 64 };
static SDL_Rect T_BRIDGE_A2 = { 32, 512, 32, 64 };
static SDL_Rect T_BRIDGE_A1 = { 64, 512, 32, 64 };
static SDL_Rect T_RAIL_A1 = { 96, 512, 32, 64 };
static SDL_Rect T_RAIL_A2 = { 128, 512, 32, 64 };
static SDL_Rect T_RAIL_B1 = { 160, 512, 32, 64 };
static SDL_Rect T_RAIL_B2 = { 192, 512, 32, 64 };
static SDL_Rect T_RAIL_C1 = { 224, 512, 32, 64 };
static SDL_Rect T_RAIL_C2 = { 256, 512, 32, 64 };
static SDL_Rect T_WATER_TRANS_A1 = { 288, 512, 32, 64 };
static SDL_Rect T_WATER_TRANS_A2 = { 320, 512, 32, 64 };
static SDL_Rect T_WATER_TRANS_A3 = { 352, 512, 32, 64 };
static SDL_Rect T_WATER_TRANS_A4 = { 384, 512, 32, 64 };
static SDL_Rect T_WATER_TRANS_B1 = { 416, 512, 32, 64 };
static SDL_Rect T_WATER_TRANS_B2 = { 448, 512, 32, 64 };
static SDL_Rect T_WATER_TRANS_B3 = { 480, 512, 32, 64 };
static SDL_Rect T_WATER_TRANS_B4 = { 512, 512, 32, 64 };

// Bifurcartion Tiles -------------
static SDL_Rect T_BIF_A1 = { 0, 576, 32, 64 };
static SDL_Rect T_BIF_A = { 32, 576, 32, 64 };
static SDL_Rect T_BIF_A2 = { 64, 576, 32, 64 };
static SDL_Rect T_BIF_B1 = { 96, 576, 32, 64 };
static SDL_Rect T_BIF_B = { 128, 576, 32, 64 };
static SDL_Rect T_BIF_B2 = { 160, 576, 32, 64 };
static SDL_Rect T_BIF_C1 = { 192, 576, 32, 64 };
static SDL_Rect T_BIF_C = { 224, 576, 32, 64 };
static SDL_Rect T_BIF_C2 = { 256, 576, 32, 64 };
static SDL_Rect T_BIF_D1 = { 288, 576, 32, 64 };
static SDL_Rect T_BIF_D = { 320, 576, 32, 64 };
static SDL_Rect T_BIF_D2 = { 352, 576, 32, 64 };
static SDL_Rect T_BIF_E1 = { 384, 576, 32, 64 };
static SDL_Rect T_BIF_E = { 416, 576, 32, 64 };
static SDL_Rect T_BIF_E2 = { 448, 576, 32, 64 };
static SDL_Rect T_BIF_F1 = { 480, 576, 32, 64 };
static SDL_Rect T_BIF_F = { 512, 576, 32, 64 };
static SDL_Rect T_BIF_F2 = { 544, 576, 32, 64 };

// ::Car Tiles:: -------------
static SDL_Rect CAR_DEFAULT = { 21,  0,  24,  43 };
static SDL_Rect CAR_NITRO = { 789,  0,  26,  60 };
static SDL_Rect CAR_L = { 145,  0,  33,  45 };
static SDL_Rect CAR_R = { 209,  0,  33,  45 };

static SDL_Rect CAR_ENEMY = { 21, 63, 24, 42 };
static SDL_Rect CAR_PEACEFUL = { 21, 126, 24, 42 };

static SDL_Rect DAMAGED = { 336, 144, 30, 33 };

static SDL_Rect other_cars[] = { CAR_ENEMY, CAR_PEACEFUL };

static SDL_Rect BULLET = { 515, 512, 13, 2 };