/*
  bling-heart.c - STC89C52RC based Heart shaped LED PCB kit firmware code

  Copyright (C) 2022  Jeevas Vasudevan

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*********************************************************************************************\
 * STC15F204EA based Star shaped LED PCB widely available in kit form
 *
 * STC15F204EA in one of the fast implementation(1 instruction per clock) of the classic intel 80C51 micro
 * controller. This chip comes with many classic peripherals like ADC's UART, Timers, Interrupts etc but don't
 * include any modern purpose built ports like I2C,SPI,PWM etc. The key 
 * features are 4 ttl-level ports(P0-2bits, P1-8bits, P2-8bits and P3-8bits), and the killer feature is the easy 
 * programmability using very minimal ttl-level serial port.
 * 
 * If you have a board with any STC 8-bit controller like this 89C52 or any of the 12x or 15x
 * series the only thing you need to program is a $2 USB-Serial converter and connect the 4
 * wires as below:
 * 
 * STC Micro ---   USB Serial converter
 * VCC       ---   VCC
 * GND       ---   GND
 * RX(P3.0)  ---   TX
 * TX(P3.1)  ---   RX
 * 
 * This a bare basic code which aim the replicate the effects that these PCB kit's comes 
 * pre-programmed with. This code can be easily developed using the fully opensource VSCodium IDE
 * with PlatformIO extension which inturn uses the fully open source excellent sdcc toolchain along
 * with the open source python based stcgal programmer or the C based stc8prog.
 * 
\*********************************************************************************************/

#define FOSC 11952000UL //11.952 Mhz
#define FDIV 70


#include <stdint.h>
#include <stdio.h>
#include <stc15fxx.h>

#define HEART_UL P0
#define HEART_LL P1
#define HEART_UR P2
#define HEART_LR P3

#define SEG_OFF 0xFF
#define SEG_ON 0x0


/*********************************************************************************************/
void delay_ms(unsigned int ms)
{
    unsigned int i;
    do
    {
        i = FDIV;
        while (--i)
            ;
    } while (--ms);
}

/*********************************************************************************************/
void bh_all_off()
{
        HEART_LR = SEG_OFF;
        HEART_LL = SEG_OFF;
        HEART_UR = SEG_OFF;
        HEART_UL = SEG_OFF;
     
}

/*********************************************************************************************/
void bh_all_on()
{
        HEART_LR = SEG_ON;
        HEART_LL = SEG_ON;
        HEART_UR = SEG_ON;
        HEART_UL = SEG_ON;
     
}

/*********************************************************************************************/
void bh_all_toggle()
{
        HEART_LR = ~HEART_LR;
        HEART_LL = ~HEART_LL;
        HEART_UR = ~HEART_UR;
        HEART_UL = ~HEART_UL;
     
}

/*********************************************************************************************/
void bh_setup()
{
        bh_all_off();
        delay_ms(50);
   
}

/*********************************************************************************************/
void bh_quadrant_dance(unsigned int count)
{
        for (unsigned int i=0; i<count; i++){  

        bh_all_off();
        delay_ms(250);

        HEART_UL = SEG_ON;
        HEART_LR = SEG_ON;        
        delay_ms(250);
        bh_all_toggle();
        delay_ms(250);
        
        bh_all_off();  
        delay_ms(250);

        HEART_LL = SEG_ON;
        HEART_UR = SEG_ON;        
        delay_ms(250);
        bh_all_toggle(); 
        delay_ms(250);
 
     } 

}

/*********************************************************************************************/
void bh_quadrant_chase(unsigned int count)
{
    bh_all_off();
    for (unsigned int i=0; i<count; i++){  
        HEART_UL = SEG_ON;
         delay_ms(250);
        HEART_LL = SEG_ON;
         delay_ms(250);
        HEART_UR = SEG_ON;
         delay_ms(250);
        HEART_LR = SEG_ON;        
        delay_ms(250);

        HEART_UL = SEG_OFF;
         delay_ms(250);
        HEART_LL = SEG_OFF;
         delay_ms(250);
        HEART_UR = SEG_OFF;
         delay_ms(250);
        HEART_LR = SEG_OFF;        
        delay_ms(250);
     }    
}   

/*********************************************************************************************/
void bh_fullon_chase_cw(unsigned int count)
{
    bh_all_off(); 
    for (unsigned int i=0; i<count; i++){ 

        for (unsigned int j=0; j<8; j++){  
            HEART_UR = ~(0x1U << (7-j));
            delay_ms(50);      

        }
        HEART_UR = SEG_OFF;

        for (unsigned int j=0; j<8; j++){  
            HEART_LR = ~(0x1U << (7-j)); 
            delay_ms(50);     
        }
        HEART_LR = SEG_OFF;

        for (unsigned int j=0; j<8; j++){  
            HEART_LL = ~(0x1U << (7-j));  
            delay_ms(50);    
        }
        HEART_LL = SEG_OFF;

        for (unsigned int j=0; j<8; j++){  
            HEART_UL = ~(0x1U << j); 
            delay_ms(50);     

        }
        HEART_UL = SEG_OFF;

    }   
}

/*********************************************************************************************/
void bh_fullon_chase_ccw(unsigned int count)
{
    bh_all_off();
    for (unsigned int i=0; i<count; i++){ 

        for (unsigned int j=0; j<8; j++){  
            HEART_UL = ~(0x1U << (7-j)); 
            delay_ms(50);     

        }
        HEART_UL = SEG_OFF;
            
        for (unsigned int j=0; j<8; j++){  
           HEART_LL = ~(0x1U << (j));  
           delay_ms(50);    
        }
        HEART_LL = SEG_OFF;    
        
        for (unsigned int j=0; j<8; j++){  
           HEART_LR = ~(0x1U << (j)); 
            delay_ms(50);     
        }
        HEART_LR = SEG_OFF;

        for (unsigned int j=0; j<8; j++){  
            HEART_UR = ~(0x1U << (j));
            delay_ms(50);      

        }
        HEART_UR = SEG_OFF;

    } 

}

/*********************************************************************************************/
void bh_fullon_trace_cw(unsigned int count)
{
    bh_all_off();
    for (unsigned int i=0; i<count; i++){ 

        for (unsigned int j=0; j<8; j++){  
            HEART_UR &= ~(0x1U << (7-j));
            delay_ms(50);      

        }

        for (unsigned int j=0; j<8; j++){  
            HEART_LR &= ~(0x1U << (7-j)); 
            delay_ms(50);     

        }

        for (unsigned int j=0; j<8; j++){  
            HEART_LL &= ~(0x1U << (7-j));  
            delay_ms(50);    

        }

        for (unsigned int j=0; j<8; j++){  
            HEART_UL &= ~(0x1U << j); 
            delay_ms(50);     

        }
        bh_all_off();
        delay_ms(50);

    }   
}

/*********************************************************************************************/
void bh_fullon_trace_ccw(unsigned int count)
{
    bh_all_off();
    for (unsigned int i=0; i<count; i++){ 

        for (unsigned int j=0; j<8; j++){  
            HEART_UL &= ~(0x1U << (7-j)); 
            delay_ms(50);     

        }
            
        for (unsigned int j=0; j<8; j++){  
           HEART_LL &= ~(0x1U << (j));  
           delay_ms(50);    
        }
        
        for (unsigned int j=0; j<8; j++){  
           HEART_LR &= ~(0x1U << (j)); 
            delay_ms(50);     
        }

        for (unsigned int j=0; j<8; j++){  
            HEART_UR &= ~(0x1U << (j));
            delay_ms(50);      

        }
        bh_all_off();
        delay_ms(50);

    } 

}

/*********************************************************************************************/
void bh_solid_flash(unsigned int count)
{
    bh_all_off();
    for (unsigned int i=0; i<count; i++){
        bh_all_on();
        delay_ms(250);
        bh_all_off();      
        delay_ms(250);
    }    

}

/*********************************************************************************************/
void bh_trace_top_to_bottom(unsigned int count)
{
    bh_all_off();
    for (unsigned int i=0; i<count; i++){
            for (unsigned int j=0; j<8; j++){  
            HEART_UR &= ~(0x1U << (7-j));
            HEART_UL &= ~(0x1U << (7-j));
            delay_ms(50);      

        }

        for (unsigned int j=0; j<8; j++){  
            HEART_LR &= ~(0x1U << (7-j));
            HEART_LL &= ~(0x1U << j);  
            delay_ms(50);
        }
        bh_all_off();
        delay_ms(50);
    }
}

/*********************************************************************************************/
void bh_trace_bottom_to_top(unsigned int count)
{
    bh_all_off();
    for (unsigned int i=0; i<count; i++){
        for (unsigned int j=0; j<8; j++){  
           HEART_LL &= ~(0x1U << (7-j));
           HEART_LR &= ~(0x1U << j);  
           delay_ms(50);    
        }


        for (unsigned int j=0; j<8; j++){  
            HEART_UL &= ~(0x1U << j);
            HEART_UR &= ~(0x1U << j); 
            delay_ms(50);     

        }
        bh_all_off();
        delay_ms(50);
    }    

}

/*********************************************************************************************/
void bh_trace_top_and_bottom(unsigned int count)
{
    bh_all_off();
    for (unsigned int i=0; i<count; i++){
            for (unsigned int j=0; j<8; j++){  
            HEART_UR &= ~(0x1U << (7-j));
            HEART_UL &= ~(0x1U << (7-j));
            HEART_LL &= ~(0x1U << (7-j));
            HEART_LR &= ~(0x1U << j);
            delay_ms(100);      

        }

        bh_all_off();
        delay_ms(50);
    }
}

/*********************************************************************************************/
void bh_trace_middle_to_bt(unsigned int count)
{
    bh_all_off();
    for (unsigned int i=0; i<count; i++){
            for (unsigned int j=0; j<8; j++){  
            HEART_UR &= ~(0x1U << j);
            HEART_UL &= ~(0x1U << j);
            HEART_LL &= ~(0x1U << j);
            HEART_LR &= ~(0x1U << (7-j));
            delay_ms(100);      

        }

        bh_all_off();
        delay_ms(50);
    }
}

/*********************************************************************************************/
void bh_trace_left_to_right(unsigned int count)
{
    bh_all_off();
    for (unsigned int i=0; i<count; i++){

            for (unsigned int j=0; j<8; j++){  
            HEART_LL &= ~(0x1U << j); 
            HEART_UL &= ~(0x1U << j);
            delay_ms(50);      
        }

        for (unsigned int j=0; j<8; j++){  
            HEART_LR &= ~(0x1U << j);
            HEART_UR &= ~(0x1U << (7-j)); 
            delay_ms(50);
        }
        bh_all_off();
        delay_ms(50);
    }
}
/*********************************************************************************************/

void bh_trace_right_to_left(unsigned int count)
{
    bh_all_off();
    for (unsigned int i=0; i<count; i++){
        for (unsigned int j=0; j<8; j++){  
           HEART_UR &= ~(0x1U << j); 
           HEART_LR &= ~(0x1U << (7-j));  
           delay_ms(50);    
        }


        for (unsigned int j=0; j<8; j++){  
            HEART_UL &= ~(0x1U << (7-j));
            HEART_LL &= ~(0x1U << (7-j));
            delay_ms(50);     

        }
        bh_all_off();
        delay_ms(50);
    }    

}

/*********************************************************************************************/
void bh_trace_left_and_right(unsigned int count)
{
    bh_all_off();
    for (unsigned int i=0; i<count; i++){
            for (unsigned int j=0; j<8; j++){  
            HEART_UR &= ~(0x1U << (7-j));
            HEART_UL &= ~(0x1U << (7-j));
            HEART_LL &= ~(0x1U << (7-j));
            HEART_LR &= ~(0x1U << j);
            delay_ms(100);      

        }

        bh_all_off();
        delay_ms(50);
    }
}

/*********************************************************************************************/
void bh_trace_middle_to_lr(unsigned int count)
{
    bh_all_off();
    for (unsigned int i=0; i<count; i++){
            for (unsigned int j=0; j<8; j++){  
            HEART_UR &= ~(0x1U << j);
            HEART_UL &= ~(0x1U << j);
            HEART_LL &= ~(0x1U << j);
            HEART_LR &= ~(0x1U << (7-j));
            delay_ms(100);      

        }

        bh_all_off();
        delay_ms(50);
    }
}

/*********************************************************************************************/
int main()
{


    bh_setup();

    while(1)
    {                
  

        bh_solid_flash(3);
        
        bh_quadrant_chase(3);
        bh_quadrant_dance(3);
        
        bh_fullon_chase_cw(3);
        bh_fullon_chase_ccw(3);
        
        bh_fullon_trace_cw(3);
        bh_fullon_trace_ccw(3);
        
        bh_trace_top_to_bottom(3);
        bh_trace_bottom_to_top(3);
        bh_trace_top_and_bottom(3);
        bh_trace_middle_to_bt(3);

        bh_trace_left_to_right(3);
        bh_trace_right_to_left(3);
        bh_trace_left_and_right(3);
        bh_trace_middle_to_lr(3);

        WDT_CONTR |= 1 << 4; // clear wdt
    }
}

/*********************************************************************************************/
/*********************************************************************************************/
