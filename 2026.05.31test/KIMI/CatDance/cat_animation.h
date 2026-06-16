#ifndef __CAT_ANIMATION_H__
#define __CAT_ANIMATION_H__

#include "config.h"

// 小猫动画函数声明
void Cat_DrawFrame(uint8 frame, uint16 center_x, uint16 center_y, uint16 scale);
void Cat_ClearArea(uint16 center_x, uint16 center_y, uint16 scale);

#endif // __CAT_ANIMATION_H__
