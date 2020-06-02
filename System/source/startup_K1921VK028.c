/**
  ******************************************************************************
  * @file      startup_K1921VK028.c
  * @version   V1.0
  * @date      26/03/2019
  * @brief     1921VK028 Devices vector table
  *            This module performs:
  *                - Set the initial SP
  *                - Set the initial PC == Reset_Handler,
  *                - Set the vector table entries with the exceptions ISR address
  *                - Configure the clock system
  *                - Branches to main in the C library (which eventually calls main()).
  *            After Reset the Cortex-M4 processor is in Thread mode,
  *            priority is Privileged, and the Stack is set to Main.
  *******************************************************************************/

/*----------Includes files------- ------------------------------------------ */
#include "K1921VK028.h"
#include "core_cm4.h"
#include "startup_K1921VK028.h"


/*----------Interrupt Vector Table ---------------------------------------- */
ISRVectorsTables g_pfnVectors __attribute__((section (".isr_vector"))) =
{
  /*----------Cortex-M4F Processor Exceptions Numbers-----------------------*/
  (void *)&_estack,     	/*!< The initial stack pointer         			*/
  Reset_Handler,            /*!< -15: Reset Handler                         */
  NMI_Handler,              /*!< -14: NMI Handler                           */
  HardFault_Handler,        /*!< -13: Hard Fault Handler                    */
  MemManage_Handler,        /*!< -12: MPU Fault Handler                     */
  BusFault_Handler,         /*!< -11: Bus Fault Handler                     */
  UsageFault_Handler,       /*!< -10: Usage Fault Handler                   */
  0,0,0,0,                  /*!< -9...-6: Reserved                          */
  SVC_Handler,              /*!< -5: SVCall Handler                         */
  DebugMon_Handler,         /*!< -4: Debug Monitor Handler                  */
  0,                        /*!< -3: Reserved                               */
  PendSV_Handler,           /*!< -2: PendSV Handler                         */
  SysTick_Handler,          /*!< -1: SysTick Handler                        */

  /*----------Device specific Interrupt Numbers-----------------------------*/
  WDT_IRQHandler,           /*!<  0: Watchdog timer interrupt               */
  RCU_IRQHandler,           /*!<  1: Reset and clock unit interrupt         */
  RTC_IRQHandler,           /*!<  2: RTC interrupt                      	*/
  MFLASH_IRQHandler,        /*!<  3: MFLASH interrupt                   	*/
  BFLASH_IRQHandler,        /*!<  4: BFLASH interrupt                   	*/
  GPIOA_IRQHandler,         /*!<  5: GPIO A interrupt                   	*/
  GPIOB_IRQHandler,         /*!<  6: GPIO B interrupt                   	*/
  GPIOC_IRQHandler,         /*!<  7: GPIO C interrupt                   	*/
  GPIOD_IRQHandler,         /*!<  8: GPIO D interrupt                   	*/
  GPIOE_IRQHandler,         /*!<  9: GPIO E interrupt                   	*/
  GPIOF_IRQHandler,         /*!< 10: GPIO F interrupt                   	*/
  GPIOG_IRQHandler,         /*!< 11: GPIO G interrupt                   	*/
  GPIOH_IRQHandler,         /*!< 12: GPIO H interrupt                   	*/
  GPIOJ_IRQHandler,         /*!< 13: GPIO J interrupt                   	*/
  GPIOK_IRQHandler,         /*!< 14: GPIO K interrupt                   	*/
  GPIOL_IRQHandler,         /*!< 15: GPIO L interrupt                   	*/
  GPIOM_IRQHandler,         /*!< 16: GPIO M interrupt                   	*/
  DMA_CH0_IRQHandler,       /*!< 17: DMA channel 0 interrupt            	*/
  DMA_CH1_IRQHandler,       /*!< 18: DMA channel 1 interrupt            	*/
  DMA_CH2_IRQHandler,       /*!< 19: DMA channel 2 interrupt            	*/
  DMA_CH3_IRQHandler,       /*!< 20: DMA channel 3 interrupt            	*/
  DMA_CH4_IRQHandler,       /*!< 21: DMA channel 4 interrupt            	*/
  DMA_CH5_IRQHandler,       /*!< 22: DMA channel 5 interrupt            	*/
  DMA_CH6_IRQHandler,       /*!< 23: DMA channel 6 interrupt            	*/
  DMA_CH7_IRQHandler,       /*!< 24: DMA channel 7 interrupt            	*/
  DMA_CH8_IRQHandler,       /*!< 25: DMA channel 8 interrupt            	*/
  DMA_CH9_IRQHandler,       /*!< 26: DMA channel 9 interrupt            	*/
  DMA_CH10_IRQHandler,      /*!< 27: DMA channel 10 interrupt           	*/
  DMA_CH11_IRQHandler,      /*!< 28: DMA channel 11 interrupt           	*/
  DMA_CH12_IRQHandler,      /*!< 29: DMA channel 12 interrupt           	*/
  DMA_CH13_IRQHandler,      /*!< 30: DMA channel 13 interrupt           	*/
  DMA_CH14_IRQHandler,      /*!< 31: DMA channel 14 interrupt           	*/
  DMA_CH15_IRQHandler,      /*!< 32: DMA channel 15 interrupt           	*/
  DMA_CH16_IRQHandler,      /*!< 33: DMA channel 16 interrupt           	*/
  DMA_CH17_IRQHandler,      /*!< 34: DMA channel 17 interrupt           	*/
  DMA_CH18_IRQHandler,      /*!< 35: DMA channel 18 interrupt           	*/
  DMA_CH19_IRQHandler,      /*!< 36: DMA channel 19 interrupt           	*/
  DMA_CH20_IRQHandler,      /*!< 37: DMA channel 20 interrupt           	*/
  DMA_CH21_IRQHandler,      /*!< 38: DMA channel 21 interrupt           	*/
  DMA_CH22_IRQHandler,      /*!< 39: DMA channel 22 interrupt           	*/
  DMA_CH23_IRQHandler,      /*!< 40: DMA channel 23 interrupt           	*/
  DMA_CH24_IRQHandler,      /*!< 41: DMA channel 24 interrupt           	*/
  DMA_CH25_IRQHandler,      /*!< 42: DMA channel 25 interrupt           	*/
  DMA_CH26_IRQHandler,      /*!< 43: DMA channel 26 interrupt           	*/
  DMA_CH27_IRQHandler,      /*!< 44: DMA channel 27 interrupt           	*/
  DMA_CH28_IRQHandler,      /*!< 45: DMA channel 28 interrupt           	*/
  DMA_CH29_IRQHandler,      /*!< 46: DMA channel 29 interrupt           	*/
  DMA_CH30_IRQHandler,      /*!< 47: DMA channel 30 interrupt           	*/
  DMA_CH31_IRQHandler,      /*!< 48: DMA channel 31 interrupt           	*/
  TMR0_IRQHandler,          /*!< 49: Timer 0 interrupt                  	*/
  TMR1_IRQHandler,          /*!< 50: Timer 1 interrupt                  	*/
  TMR2_IRQHandler,          /*!< 51: Timer 2 interrupt                  	*/
  TMR3_IRQHandler,          /*!< 52: Timer 3 interrupt                  	*/
  ETMR0_IRQHandler,         /*!< 53: Enhanced Timer 0 interrupt         	*/
  ETMR1_IRQHandler,         /*!< 54: Enhanced Timer 1 interrupt         	*/
  ETMR2_IRQHandler,         /*!< 55: Enhanced Timer 2 interrupt         	*/
  ETMR3_IRQHandler,         /*!< 56: Enhanced Timer 3 interrupt         	*/
  UART0_TD_IRQHandler,      /*!< 57: UART0 Transmit Done interrupt      	*/
  UART0_MS_IRQHandler,      /*!< 58: UART0 Modem interrupt              	*/
  UART0_RX_IRQHandler,      /*!< 59: UART0 Recieve interrupt            	*/
  UART0_TX_IRQHandler,      /*!< 60: UART0 Transmit interrupt           	*/
  UART0_RT_IRQHandler,      /*!< 61: UART0 Recieve interrupt            	*/
  UART0_E_IRQHandler,       /*!< 62: UART0 Error interrupt              	*/
  UART0_IRQHandler,         /*!< 63: UART0 interrupt                    	*/
  UART1_TD_IRQHandler,      /*!< 64: UART1 Transmit Done interrupt      	*/
  UART1_MS_IRQHandler,      /*!< 65: UART1 Modem interrupt              	*/
  UART1_RX_IRQHandler,      /*!< 66: UART1 Recieve interrupt            	*/
  UART1_TX_IRQHandler,      /*!< 67: UART1 Transmit interrupt           	*/
  UART1_RT_IRQHandler,      /*!< 68: UART1 Recieve interrupt            	*/
  UART1_E_IRQHandler,       /*!< 69: UART1 Error interrupt              	*/
  UART1_IRQHandler,         /*!< 70: UART1 interrupt                    	*/
  UART2_TD_IRQHandler,      /*!< 71: UART2 Transmit Done interrupt      	*/
  UART2_MS_IRQHandler,      /*!< 72: UART2 Modem interrupt              	*/
  UART2_RX_IRQHandler,      /*!< 73: UART2 Recieve interrupt            	*/
  UART2_TX_IRQHandler,      /*!< 74: UART2 Transmit interrupt           	*/
  UART2_RT_IRQHandler,      /*!< 75: UART2 Recieve interrupt            	*/
  UART2_E_IRQHandler,       /*!< 76: UART2 Error interrupt              	*/
  UART2_IRQHandler,         /*!< 77: UART2 interrupt                    	*/
  UART3_TD_IRQHandler,      /*!< 78: UART3 Transmit Done interrupt      	*/
  UART3_MS_IRQHandler,      /*!< 79: UART3 Modem interrupt              	*/
  UART3_RX_IRQHandler,      /*!< 80: UART3 Recieve interrupt            	*/
  UART3_TX_IRQHandler,      /*!< 81: UART3 Transmit interrupt           	*/
  UART3_RT_IRQHandler,      /*!< 82: UART3 Recieve interrupt            	*/
  UART3_E_IRQHandler,       /*!< 83: UART3 Error interrupt              	*/
  UART3_IRQHandler,         /*!< 84: UART3 interrupt                    	*/
  TUART0_RX_IRQHandler,     /*!< 85: Tiny UART0 Receive interrupt       	*/
  TUART0_TX_IRQHandler,     /*!< 86: Tiny UART0 Transmit interrupt      	*/
  TUART0_RO_IRQHandler,     /*!< 87: Tiny UART0 Receive Overrun interrupt	*/
  TUART0_TO_IRQHandler,     /*!< 88: Tiny UART0 Transmit Overrun interrupt	*/
  TUART0_IRQHandler,        /*!< 89: Tiny UART0 interrupt               	*/
  TUART1_RX_IRQHandler,     /*!< 90: Tiny UART1 Receive interrupt      		*/
  TUART1_TX_IRQHandler,     /*!< 91: Tiny UART1 Transmit interrupt      	*/
  TUART1_RO_IRQHandler,     /*!< 92: Tiny UART1 Receive Overrun interrupt	*/
  TUART1_TO_IRQHandler,     /*!< 93: Tiny UART1 Transmit Overrun interrupt	*/
  TUART1_IRQHandler,        /*!< 94: Tiny UART1 interrupt               	*/
  SPI0_IRQHandler,          /*!< 95: SPI0 interrupt                     	*/
  SPI0_RX_IRQHandler,       /*!< 96: SPI0 Receive interrupt             	*/
  SPI0_TX_IRQHandler,       /*!< 97: SPI0 Transmit interrupt            	*/
  SPI0_RO_IRQHandler,       /*!< 98: SPI0 Receive Overrun interrupt     	*/
  SPI0_RT_IRQHandler,       /*!< 99: SPI0 Receive Timeout interrupt     	*/
  SPI1_IRQHandler,          /*!< 100: SPI1 interrupt                     	*/
  SPI1_RX_IRQHandler,       /*!< 101: SPI1 Receive interrupt             	*/
  SPI1_TX_IRQHandler,       /*!< 102: SPI1 Transmit interrupt            	*/
  SPI1_RO_IRQHandler,       /*!< 103: SPI1 Receive Overrun interrupt     	*/
  SPI1_RT_IRQHandler,       /*!< 104: SPI1 Receive Timeout interrupt     	*/
  SPI2_IRQHandler,          /*!< 105: SPI2 interrupt                     	*/
  SPI2_RX_IRQHandler,       /*!< 106: SPI2 Receive interrupt             	*/
  SPI2_TX_IRQHandler,       /*!< 107: SPI2 Transmit interrupt            	*/
  SPI2_RO_IRQHandler,       /*!< 108: SPI2 Receive Overrun interrupt     	*/
  SPI2_RT_IRQHandler,       /*!< 109: SPI2 Receive Timeout interrupt     	*/
  SPI3_IRQHandler,          /*!< 110: SPI3 interrupt                     	*/
  SPI3_RX_IRQHandler,       /*!< 111: SPI3 Receive interrupt             	*/
  SPI3_TX_IRQHandler,       /*!< 112: SPI3 Transmit interrupt            	*/
  SPI3_RO_IRQHandler,       /*!< 113: SPI3 Receive Overrun interrupt     	*/
  SPI3_RT_IRQHandler,       /*!< 114: SPI3 Receive Timeout interrupt     	*/
  I2C0_IRQHandler,          /*!< 115: I2C0 interrupt                     	*/
  I2C1_IRQHandler,          /*!< 116: I2C1 interrupt                     	*/
  SPWR0_IRQHandler,         /*!< 117: SpaceWire0 interrupt               	*/
  SPWR1_IRQHandler,         /*!< 118: SpaceWire1 interrupt               	*/
  MILSTD0_IRQHandler,       /*!< 119: MIL-STD 1553 0 interrupt           	*/
  MILSTD1_IRQHandler,       /*!< 120: MIL-STD 1553 1 interrupt           	*/
  ECAP0_IRQHandler,         /*!< 121: Capture Unit 0 interrupt           	*/
  ECAP1_IRQHandler,         /*!< 122: Capture Unit 1 interrupt           	*/
  ECAP2_IRQHandler,         /*!< 123: Capture Unit 2 interrupt           	*/
  ECAP3_IRQHandler,         /*!< 124: Capture Unit 3 interrupt           	*/
  ECAP4_IRQHandler,         /*!< 125: Capture Unit 4 interrupt           	*/
  ECAP5_IRQHandler,         /*!< 126: Capture Unit 5 interrupt           	*/
  PWM0_IRQHandler,          /*!< 127: PWM0 interrupt                     	*/
  PWM0_HD_IRQHandler,       /*!< 128: PWM0 HD interrupt                  	*/
  PWM0_TZ_IRQHandler,       /*!< 129: PWM0 TZ interrupt                  	*/
  PWM1_IRQHandler,          /*!< 130: PWM1 interrupt                     	*/
  PWM1_HD_IRQHandler,       /*!< 131: PWM1 HD interrupt                  	*/
  PWM1_TZ_IRQHandler,       /*!< 132: PWM1 TZ interrupt                  	*/
  PWM2_IRQHandler,          /*!< 133: PWM2 interrupt                     	*/
  PWM2_HD_IRQHandler,       /*!< 134: PWM2 HD interrupt                  	*/
  PWM2_TZ_IRQHandler,       /*!< 135: PWM2 TZ interrupt                  	*/
  PWM3_IRQHandler,          /*!< 136: PWM3 interrupt                     	*/
  PWM3_HD_IRQHandler,       /*!< 137: PWM3 HD interrupt                  	*/
  PWM3_TZ_IRQHandler,       /*!< 138: PWM3 TZ interrupt                  	*/
  PWM4_IRQHandler,          /*!< 139: PWM4 interrupt                     	*/
  PWM4_HD_IRQHandler,       /*!< 140: PWM4 HD interrupt                  	*/
  PWM4_TZ_IRQHandler,       /*!< 141: PWM4 TZ interrupt                  	*/
  PWM5_IRQHandler,          /*!< 142: PWM5 interrupt                     	*/
  PWM5_HD_IRQHandler,       /*!< 143: PWM5 HD interrupt                  	*/
  PWM5_TZ_IRQHandler,       /*!< 144: PWM5 TZ interrupt                  	*/
  PWM6_IRQHandler,          /*!< 145: PWM6 interrupt                     	*/
  PWM6_HD_IRQHandler,       /*!< 146: PWM6 HD interrupt                  	*/
  PWM6_TZ_IRQHandler,       /*!< 147: PWM6 TZ interrupt                  	*/
  PWM7_IRQHandler,          /*!< 148: PWM7 interrupt                     	*/
  PWM7_HD_IRQHandler,       /*!< 149: PWM7 HD interrupt                  	*/
  PWM7_TZ_IRQHandler,       /*!< 150: PWM7 TZ interrupt                  	*/
  PWM8_IRQHandler,          /*!< 151: PWM8 interrupt                     	*/
  PWM8_HD_IRQHandler,       /*!< 152: PWM8 HD interrupt                  	*/
  PWM8_TZ_IRQHandler,       /*!< 153: PWM8 TZ interrupt                  	*/
  PWM9_IRQHandler,          /*!< 154: PWM9 interrupt                     	*/
  PWM9_HD_IRQHandler,       /*!< 155: PWM9 HD interrupt                  	*/
  PWM9_TZ_IRQHandler,       /*!< 156: PWM9 TZ interrupt                  	*/
  QEP0_IRQHandler,          /*!< 157: QEP0 interrupt                     	*/
  QEP1_IRQHandler,          /*!< 158: QEP1 interrupt                     	*/
  QEP2_IRQHandler,          /*!< 159: QEP2 interrupt                     	*/
  QEP3_IRQHandler,          /*!< 160: QEP3 interrupt                     	*/
  ADC_SEQ0_IRQHandler,      /*!< 161: ADC Sequencer 0 interrupt          	*/
  ADC_SEQ1_IRQHandler,      /*!< 162: ADC Sequencer 1 interrupt          	*/
  ADC_SEQ2_IRQHandler,      /*!< 163: ADC Sequencer 2 interrupt          	*/
  ADC_SEQ3_IRQHandler,      /*!< 164: ADC Sequencer 3 interrupt          	*/
  ADC_SEQ4_IRQHandler,      /*!< 165: ADC Sequencer 4 interrupt          	*/
  ADC_SEQ5_IRQHandler,      /*!< 166: ADC Sequencer 5 interrupt          	*/
  ADC_SEQ6_IRQHandler,      /*!< 167: ADC Sequencer 6 interrupt          	*/
  ADC_SEQ7_IRQHandler,      /*!< 168: ADC Sequencer 7 interrupt          	*/
  ADC_DC_IRQHandler,        /*!< 169: ADC Digital Comparator interrupt  	*/
  ETH_IRQHandler,           /*!< 170: Ethernet interrupt                 	*/
  CAN0_IRQHandler,          /*!< 171: CAN0 interrupt                     	*/
  CAN1_IRQHandler,          /*!< 172: CAN1 interrupt                     	*/
  CAN2_IRQHandler,          /*!< 173: CAN2 interrupt                     	*/
  CAN3_IRQHandler,          /*!< 174: CAN3 interrupt                     	*/
  CAN4_IRQHandler,          /*!< 175: CAN4 interrupt                     	*/
  CAN5_IRQHandler,          /*!< 176: CAN5 interrupt                     	*/
  CAN6_IRQHandler,          /*!< 177: CAN6 interrupt                     	*/
  CAN7_IRQHandler,          /*!< 178: CAN7 interrupt                     	*/
  CAN8_IRQHandler,          /*!< 179: CAN8 interrupt                     	*/
  CAN9_IRQHandler,          /*!< 180: CAN9 interrupt                     	*/
  CAN10_IRQHandler,         /*!< 181: CAN10 interrupt                    	*/
  CAN11_IRQHandler,         /*!< 182: CAN11 interrupt                    	*/
  CAN12_IRQHandler,         /*!< 183: CAN12 interrupt                    	*/
  CAN13_IRQHandler,         /*!< 184: CAN13 interrupt                    	*/
  CAN14_IRQHandler,         /*!< 185: CAN14 interrupt                    	*/
  CAN15_IRQHandler,         /*!< 186: CAN15 interrupt                    	*/
  FPU_IRQHandler,           /*!< 187: FPU exception interrupt            	*/
  TMU_IRQHandler,           /*!< 188: TMU interrupt                      	*/
  LAU_IRQHandler,           /*!< 189: LAU interrupt                      	*/
  SDFM_IRQHandler,          /*!< 190: SDFM interrupt                     	*/
  OWI0_IRQHandler,          /*!< 191: OWI0 interrupt                     	*/
  OWI1_IRQHandler           /*!< 192: OWI1 interrupt                     	*/
};

/**
  * @brief  This is the code that gets called when the processor first
  *         starts execution following a reset event. Only the absolutely
  *         necessary set is performed, after which the application
  *         supplied main() routine is called.
  * @param  None
  * @retval None
  */
void Reset_Handler(void)
{
	/* Initialize data and bss */
	unsigned int *pulSrc, *pulDest;

	/* Copy the data segment initializers from FLASH to SRAM */
	pulSrc = &_sidata;

	for(pulDest = &_sdata; pulDest < &_edata; )	{
	  *(pulDest++) = *(pulSrc++);
	}
  
 	/* Zero fill the bss segment */
	for(pulDest = &_sbss; pulDest < &_ebss; )	{
	  *(pulDest++) = 0;
	}

	/* System clock init */
	SystemInit();

	/* Call the application's entry point */
	main();
  
	/* If return from main(), go into an infinite loop */
	while(1){};
}
/*----------------------------------------------------------------------------*/

/**
  * @brief  This is the code that gets called when the processor receives an
  *         unexpected interrupt.  This simply enters an infinite loop,
  *         preserving the system state for examination by a debugger.
  * @param  None
  * @retval None
  *
  */
void Default_Handler(void)
{
	/* Go into an infinite loop. */
	while (1){}
}
/*----------------------------------------------------------------------------*/

/*@}*/

