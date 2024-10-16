/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LED1_H_
#define __LED1_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Macros for Everyone--------------------------------------------------------*/




/*Function definitions---------------------------------------------------------*/
void init_leds(void);
void clear_all_LED(void);
void set_red( void);
void clear_red( void );
void set_green( void);
void clear_green( void );
void set_blue( void);
void clear_blue( void );

#ifdef __cplusplus
}
#endif

#endif /*__LED1_H */
