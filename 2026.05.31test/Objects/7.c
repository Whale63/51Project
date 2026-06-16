#include <reg51.h>

// 共阴极七段码表
unsigned char code SEG_TABLE[] = {
    0x3F,  // 0
    0x06,  // 1
    0x5B,  // 2
    0x4F,  // 3
    0x66,  // 4
    0x6D,  // 5
    0x7D,  // 6
    0x07,  // 7
    0x7F,  // 8
    0x6F   // 9
};

void DelayMS(unsigned int x) {
    unsigned char i;
    while(x--) {
        for(i = 120; i > 0; i--);
    }
}

void main() {
    unsigned char num = 9;   // 从9开始
    
    while(1) {
        P0 = ~SEG_TABLE[num];
        DelayMS(500);        // 每个数字显示500ms
        
        if(num == 0) {
            num = 9;         // 到0后回到9
        } else {
            num--;           // 递减
        }
    }
}