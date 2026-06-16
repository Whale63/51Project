#include <reg51.h>
#include "Delay.h"
#include "tft_cat.h"
#include "buzzer_music.h"


// ========== 所有 sbit 统一定义 ==========
sbit TFT_CS   = P1^0;
sbit TFT_CLK  = P1^1;
sbit TFT_DI   = P1^2;
sbit TFT_DO   = P1^3;
sbit TFT_RST  = P1^4;
sbit TFT_RS   = P1^5;
sbit BUZZER   = P2^0;

#include "tft_cat.h"
#include "buzzer_music.h"

void main(void)
{
		P0=0;
		DelayMS(150);
		P0=1;
		DelayMS(150);
    TFT_Cat_Init();
    Buzzer_Init();
    
    while(1)
    {
				P0=0;
				DelayMS(800);
        Cat_Dance_Animate();
    }
}
