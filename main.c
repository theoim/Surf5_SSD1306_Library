
// include libraries
#include "lib/ssd1306.h"
#include "w7500x.h"
#include "lib/i2c.h"
#include "main.h"
#include "w7500x_gpio.h"
#include "w7500x_uart.h"

/**
 * @desc    Main function
 *
 * @param   void
 *
 * @return  int
 */

/* Private variables ---------------------------------------------------------*/
I2C_ConfigStruct conf;

static void GPIO_Config(void);
static void UART_Config(void);


int main(void)
{
  	SystemInit();
    UART_Config();
    GPIO_Config();


	printf("W7500x Standard Peripheral Library version : %d.%d.%d\r\n", __W7500X_STDPERIPH_VERSION_MAIN, __W7500X_STDPERIPH_VERSION_SUB1, __W7500X_STDPERIPH_VERSION_SUB2);
	
//GPIO setting for I2C

	conf.scl_port = PORT_PA;
	conf.scl_pin = GPIO_Pin_9;
    conf.sda_port = PORT_PA;
	conf.sda_pin = GPIO_Pin_10;
  uint8_t addr = SSD1306_ADDR;

  
  // init ssd1306
  SSD1306_Init (&conf, addr);

  // clear screen
  SSD1306_ClearScreen ();
  // draw line
  SSD1306_DrawLine (0, MAX_X, 4, 4);  
  // set position
  SSD1306_SetPosition (7, 1);
  // draw string
  SSD1306_DrawString ("SSD1306 OLED DRIVER");
  // draw line
  SSD1306_DrawLine (0, MAX_X, 18, 18);
  // set position
  SSD1306_SetPosition (40, 3);
  // draw string
  SSD1306_DrawString ("MATIASUS");
  // set position
  SSD1306_SetPosition (53, 5);
  // draw string
  SSD1306_DrawString ("2021");
  // update
  SSD1306_UpdateScreen (&conf, addr);

  GPIO_ResetBits(GPIOC, GPIO_Pin_15);
  // return value
  return 0;
}


static void GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Direction = GPIO_Direction_OUT;
    GPIO_InitStructure.GPIO_AF = PAD_AF1;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

static void UART_Config(void)
{
    UART_InitTypeDef UART_InitStructure;

    UART_StructInit(&UART_InitStructure);
	
#if defined (USE_WIZWIKI_W7500_EVAL)
    UART_Init(UART1, &UART_InitStructure);
    UART_Cmd(UART1, ENABLE);
#else
    S_UART_Init(115200);
    S_UART_Cmd(ENABLE);
#endif
}
