#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <inttypes.h>

#define X_LIMIT  639
#define Y_LIMIT  479
#define ROW      480
#define COLOUMN  640
#define COLOUR_LIMIT 31

(uint16_t *) OverlayMousePointer (uint16_t * const c, uint32_t *const mouse_pointer_buffer,uint16_t x_value,uint16_t y_value)
{

int i,temp; 
uint8_t red_m,green_m,blue_m,alpha_m;
uint8_t red,green,blue;

uint16_t *source = (uint16_t *)malloc( 64 * sizeof(uint16_t));
for (i = 0; i < 64; i++ )
{
    
   alpha_m  = ( ( ( ((*mouse_pointer_buffer) & 0x000000FF) >> 0 ) * 255 ) / (100)  );  // alpha to range of 0 to 100
   red_m    = ( (((*mouse_pointer_buffer) >> 24) * 31 ) / (255)  );  //linearlyscaling 8 bit to 5 bit
   green_m  = ( ( ( ((*mouse_pointer_buffer) & 0x00FF0000) >> 16) * 63 ) / (255)  );  //linearly scaling 8 bit to 6 bit
   blue_m   = ( ( ( ((*mouse_pointer_buffer) & 0x0000FF00) >> 8 ) * 31 ) / (255)  );  //linearlyscaling 8 bit to 5 bit

    
   temp =  ( *(frame_buffer +  ( (ROW * y_value) + ((x_value) + i)  ) ) ); // getting frame buffer value to a temp
   red    = (((temp) >> 11) );  //linearly scaling 8 bit to 5 bit   //
   green  = ( ( ((temp) & 0x07E0) >> 5) );  //linearly scaling 8 bit to 5 bit
   blue   = ( ((temp) & 0x001F) );  //linearly scaling 8 bit to 5 bit
   
 
   red =   ( (red_m * alpha_m) + (red * (100 - alpha_m)) );
   green = ( (red_m * alpha_m) + (red * (100 - alpha_m)) );
   blue =  ( (red_m * alpha_m) + (red * (100 - alpha_m)) );
   
   red = (red > COLOUR_LIMIT) ? COLOUR_LIMIT : red;
   green = (green  > 63) ? 63 : green;   
   blue = (blue > COLOUR_LIMIT) ? COLOUR_LIMIT : blue; 
   
   temp = ((red << 11) | (green << 5) | (blue & 001F));
   
   ( *(frame_buffer +  ((ROW * y_value) + ((x_value) + i))))  = temp;

    
    return frame_buffer;
    
}    

