#ifndef __MUSIC_H__
#define __MUSIC_H__

#include "config.h"

// 音乐播放函数声明
void Music_Init(void);
void Music_PlayNote(uint16 freq, uint16 duration_ms);

// 定时器中断服务 (定义在 music.c 中，此处不声明 interrupt)
void Timer0_ISR(void);

#endif // __MUSIC_H__
