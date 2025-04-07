#ifndef _LMX2571_H_
#define _LMX2571_H_

#include "PLL.h"
#include "main.h"
#include "gpio.h"

void LMX2571_Init(void);
void SetOutFre(u8_ f, u64_ fre);
u16_ LMX2571_CaluateDetraFre(long int detraFre);
void LMX2571_FASTFSKWrite(u16_ data);
void LMX2571_FASTFSK(long int detraFre);

#define LMX2571_FDV_1 	HAL_GPIO_WritePin(GPIOA,FDV_Pin,GPIO_PIN_SET);
#define LMX2571_FDV_0 	HAL_GPIO_WritePin(GPIOA,FDV_Pin,GPIO_PIN_RESET);

#define LMX2571_FD0_1 	HAL_GPIO_WritePin(GPIOB,FD0_Pin,GPIO_PIN_SET);
#define LMX2571_FD0_0 	HAL_GPIO_WritePin(GPIOB,FD0_Pin,GPIO_PIN_RESET);

#define LMX2571_FD1_1 	HAL_GPIO_WritePin(GPIOB,FD1_Pin,GPIO_PIN_SET);
#define LMX2571_FD1_0 	HAL_GPIO_WritePin(GPIOB,FD1_Pin,GPIO_PIN_RESET);

#define LMX2571_FD2_1 	HAL_GPIO_WritePin(GPIOA,FD2_Pin,GPIO_PIN_SET);
#define LMX2571_FD2_0 	HAL_GPIO_WritePin(GPIOA,FD2_Pin,GPIO_PIN_RESET);

#define LMX2571_MUX_1 	HAL_GPIO_WritePin(GPIOA,MUX_Pin,GPIO_PIN_SET);
#define LMX2571_MUX_0 	HAL_GPIO_WritePin(GPIOA,MUX_Pin,GPIO_PIN_RESET);

#define LMX2571_TRCTL_1   HAL_GPIO_WritePin(GPIOA,CTL_Pin,GPIO_PIN_SET);
#define LMX2571_TRCTL_0   HAL_GPIO_WritePin(GPIOA,CTL_Pin,GPIO_PIN_RESET);

#define LMX2571_CLK_1 	HAL_GPIO_WritePin(GPIOB,CLK_Pin,GPIO_PIN_SET);
#define LMX2571_CLK_0 	HAL_GPIO_WritePin(GPIOB,CLK_Pin,GPIO_PIN_RESET);

#define LMX2571_LE_1 	HAL_GPIO_WritePin(GPIOB,LE_Pin,GPIO_PIN_SET);
#define LMX2571_LE_0 	HAL_GPIO_WritePin(GPIOB,LE_Pin,GPIO_PIN_RESET);

#define LMX2571_DATA_1 	HAL_GPIO_WritePin(GPIOA,DAT_Pin,GPIO_PIN_SET);
#define LMX2571_DATA_0 	HAL_GPIO_WritePin(GPIOA,DAT_Pin,GPIO_PIN_RESET);

#define LMX2571_CE_1 	HAL_GPIO_WritePin(GPIOA,CE_Pin,GPIO_PIN_SET);
#define LMX2571_CE_0 	HAL_GPIO_WritePin(GPIOA,CE_Pin,GPIO_PIN_RESET);

#define LMX2571_F1 0
#define LMX2571_F2 1
//R47
#define LMX2571_DITHERING(x)               ((x<<13)&0x6000)
#define LMX2571_DITHERING_Disabled                0
#define LMX2571_DITHERING_Weak                    1
#define LMX2571_DITHERING_Medium                  2
#define LMX2571_DITHERING_Strong                  3

//R42
#define LMX2571_EXTVCO_CP_POL                  (1<<5)
#define LMX2571_EXTVCO_CP_POL_Positive            0
#define LMX2571_EXTVCO_CP_POL_Negative            1
#define LMX2571_EXTVCO_CP_IDN(x)            ((x<<0)&0x001F)

//R41
#define LMX2571_EXTVCO_CP_IUP(x)            ((x<<7)&0x0F80)
#define LMX2571_EXTVCO_CP_GAIN(x)           ((x<<5)&0x0060)
#define LMX2571_EXTVCO_CP_GAIN_1x                 0
#define LMX2571_EXTVCO_CP_GAIN_2x                 1
#define LMX2571_EXTVCO_CP_GAIN_1_5x               2       //1.5x
#define LMX2571_EXTVCO_CP_GAIN_2_5x               3       //2.5x
#define LMX2571_CP_IDN(x)                   ((x<<0)&0x001F)

//R40
#define LMX2571_CP_IUP(x)                   ((x<<8)&0x1F00)
#define LMX2571_CP_GAIN(x)                  ((x<<6)&0x00C0)
#define LMX2571_CP_GAIN_1x                        0
#define LMX2571_CP_GAIN_2x                        1
#define LMX2571_CP_GAIN_1_5x                      2       //1.5x
#define LMX2571_CP_GAIN_2_5x                      3       //2.5x

//R39
#define LMX2571_SDO_LD_SEL(x)                      ((x<<3))
#define LMX2571_SDO_LD_SEL_Register_readback_serial_data_output 0
#define LMX2571_SDO_LD_SEL_Lock_detect_output     1
#define LMX2571_LD_EN(x)                          ((x<<0))
#define LMX2571_LD_EN_Disabled                    0   
#define LMX2571_LD_EN_Enabled                     1

//R35
#define LMX2571_MULT_WAIT(x)                ((x<<3)&0x3FF8)
#define LMX2571_OUTBUF_AUTOMUTE(x)                ((x<<2))
#define LMX2571_OUTBUF_TX_TYPE(x)                 ((x<<1))
#define LMX2571_OUTBUF_RX_TYPE(x)                 ((x<<0))
#define Open_drain 0
#define Push_pull  1
//R34
#define LMX2571_IPBUFDIFF_TERM(x)                 ((x<<15))
#define LMX2571_IPBUFDIFF_TERM_Disabled           0
#define LMX2571_IPBUFDIFF_TERM_Enabled            1
#define LMX2571_IPBUF_SE_DIFF_SEL(x)              ((x<<14))
#define LMX2571_IPBUF_SE_DIFF_SEL_Single_ended_input 0
#define LMX2571_IPBUF_SE_DIFF_SEL_Differential_input 1
#define LMX2571_XTAL_PWRCTRL(x)            ((x<<11)&0x3800)
#define LMX2571_XTAL_PWRCTRL_0o                   0  
#define LMX2571_XTAL_PWRCTRL_100o                 1
#define LMX2571_XTAL_PWRCTRL_200o                 2
#define LMX2571_XTAL_PWRCTRL_300o                 3
/*
0 = 0 O
1 = 100 O
2 = 200 O
3 = 300 O
4-7 = Reserved
*/
#define LMX2571_XTAL_EN(x)                        ((x<<10))
#define LMX2571_XTAL_EN_Disabled                  0
#define LMX2571_XTAL_EN_Enabled                   1
#define LMX2571_FSK_I2S_FS_POL(x)                 ((x<<8))
#define LMX2571_FSK_I2S_FS_POL_Active_HIGH        0
#define LMX2571_FSK_I2S_FS_POL_Active_LOW         1
#define LMX2571_FSK_I2S_CLK_POL(x)                ((x<<7))
#define LMX2571_FSK_I2S_CLK_POL_Rising_edge_strobe 0
#define LMX2571_FSK_I2S_CLK_POL_Falling_edge_strobe 1
#define LMX2571_FSK_LEVEL(x)                ((x<<6)&0x0060)
#define LMX2571_FSK_LEVEL_Disabled                0
#define LMX2571_FSK_LEVEL_2FSK                    1
#define LMX2571_FSK_LEVEL_4FSK                    2
#define LMX2571_FSK_LEVEL_8FSK                    3
#define LMX2571_FSK_DEV_SEL(x)              ((x<<2)&0x001C)
#define LMX2571_FSK_DEV_SEL_FSK_DEV0_Fx           0
#define LMX2571_FSK_DEV_SEL_FSK_DEV1_Fx           1
#define LMX2571_FSK_DEV_SEL_FSK_DEV2_Fx           2
#define LMX2571_FSK_DEV_SEL_FSK_DEV3_Fx           3
#define LMX2571_FSK_DEV_SEL_FSK_DEV4_Fx           4
#define LMX2571_FSK_DEV_SEL_FSK_DEV5_Fx           5
#define LMX2571_FSK_DEV_SEL_FSK_DEV6_Fx           6
#define LMX2571_FSK_DEV_SEL_FSK_DEV7_Fx           7
#define LMX2571_FSK_MODE_SEL(x)                  ((x<<0))
#define LMX2571_FSK_MODE_SEL_FSK_PIN_mode         0
#define LMX2571_FSK_MODE_SEL_FSK_SPI_mode         1
#define LMX2571_FSK_MODE_SEL_FSK_I2S_mode         2
#define LMX2571_FSK_MODE_SEL_FSK_SPI_FAST_mode    3

//R33
#define LMX2571_FSK_DEV_SPI_FAST(x)         ((x<<0)&0xFFFF)

//R25 to R32
#define LMX2571_FSK_DEV0_F2_to_FSK_DEV7_F2(x)((x<<0)&0xFFFF)

//R24
#define LMX2571_FSK_EN_F2                      ((x<<10))
#define LMX2571_FSK_EN_F2_Disabled                0
#define LMX2571_FSK_EN_F2_Enabled                 1
#define LMX2571_EXTVCO_CHDIV_F2(x)          ((x<<6)&0x03C0)
#define LMX2571_EXTVCO_SEL_F2                  ((x<<5))
#define LMX2571_EXTVCO_SEL_F2_Synthesizer_mode    0
#define LMX2571_EXTVCO_SEL_F2_PLL_mode            1
#define LMX2571_OUTBUF_TX_PWR_F2(x)         ((x<<0)&0x001F)

//R23
#define LMX2571_OUTBUF_RX_PWR_F2(x)         ((x<<8)&0x1F00)
#define LMX2571_OUTBUF_TX_EN_F2                ((x<<7))
#define LMX2571_OUTBUF_TX_EN_F2_Disabled          0
#define LMX2571_OUTBUF_TX_EN_F2_Enabled           1
//0 = Bypass  1 = 3.2 kO 2 = 1.6 kO  3 = 1.1 kO  4 = 800 O
//5 = 640 O  6 = 533 O  7 = 457 O
#define LMX2571_LF_R4_F2(x)                 ((x<<0)&0x0007)

//R22
//0 = Bypass  1 = 3.2 kO 2 = 1.6 kO  3 = 1.1 kO  4 = 800 O
//5 = 640 O  6 = 533 O  7 = 457 O
#define LMX2571_LF_R3_F2(x)                ((x<<13)&0xE000)
//0 = Divide by 1   1 = Divide by 2   2 = Divide by 4   3 = Divide by 8
//4 = Divide by 16   5 = Divide by 32   6 = Divide by 64
#define LMX2571_CHDIV2_F2(x)               ((x<<10)&0x1C00)
#define LMX2571_CHDIV1_F2(x)                ((x<<8)&0x0300)
#define LMX2571_CHDIV1_F2_Divide_by_4             0
#define LMX2571_CHDIV1_F2_Divide_by_5             1
#define LMX2571_CHDIV1_F2_Divide_by_6             2
#define LMX2571_CHDIV1_F2_Divide_by_7             3
#define LMX2571_PFD_DELAY_F2(x)             ((x<<5)&0x00E0)
//0 = Reserved   1 = Bypass   2 = 2x   ...
//13 = 13x       14 - 31 = Reserved
#define LMX2571_MULT_F2(x)                  ((x<<0)&0x001F)

//R21
#define LMX2571_PLL_R_F2(x)                 ((x<<8)&0xFF00)
#define LMX2571_PLL_R_PRE_F2(x)             ((x<<0)&0x00FF)

//R20
#define LMX2571_PLL_N_PRE_F2                   (1<<15)
#define LMX2571_PLL_N_PRE_F2_Divide_by_2          0
#define LMX2571_PLL_N_PRE_F2_Divide_by_4          1
/*
0 = Integer mode
1 = 1st order
2 = 2nd order
3 = 3rd order
4 - 7 = 4th order
*/
#define LMX2571_FRAC_ORDER_F2(x)           ((x<<12)&0x7000)
#define LMX2571_PLL_N_F2(x)                 ((x<<0)&0x0FFF)

//R19
#define LMX2571_PLL_DEN_F2_15_0(x)          ((x<<0)&0xFFFF)

//R18 
#define LMX2571_PLL_NUM_F2_15_0(x)          ((x<<0)&0xFFFF)

//R17
#define LMX2571_PLL_DEN_F2_23_16(x)         ((x<<8)&0xFF00)
#define LMX2571_PLL_NUM_F2_23_16(x)         ((x<<0)&0x00FF)

//R16
#define FSK_DEV0_F1_to_FSK_DEV7_F1(x)       ((x<<0)&0xFFFF)

//R8
#define LMX2571_FSK_EN_F1(x)   (x<<10)
#define LMX2571_EXTVCO_CHDIV_F1(x)          ((x<<6)&0x03C0)
#define LMX2571_EXTVCO_SEL_F1(x)   (x<<5)
#define LMX2571_OUTBUF_TX_PWR_F1(x)         ((x<<0)&0x001F)

//R7
#define LMX2571_OUTBUF_RX_PWR_F1(x)         ((x<<8)&0x1F00)
#define LMX2571_OUTBUF_TX_EN_F1(x)                ((x<<7))
#define LMX2571_OUTBUF_RX_EN_F1(x)                ((x<<6))
#define LMX2571_LF_R4_F1(x)                 ((x<<0)&0x0007)

//R6
#define LMX2571_LF_R3_F1(x)                ((x<<13)&0xE000)
#define LMX2571_CHDIV2_F1(x)               ((x<<10)&0x1C00)
#define LMX2571_CHDIV1_F1(x)                ((x<<8)&0x0300)
#define LMX2571_PFD_DELAY_F1(x)             ((x<<5)&0x00E0)
#define LMX2571_MULT_F1(x)                  ((x<<0)&0x001F)

//R5
#define LMX2571_PLL_R_F1(x)                 ((x<<8)&0xFF00)
#define LMX2571_PLL_R_PRE_F1(x)             ((x<<0)&0x00FF)

//R4
#define LMX2571_PLL_N_PRE_F1(x)                   ((x<<15))
#define LMX2571_FRAC_ORDER_F1(x)           ((x<<12)&0x7000)
#define LMX2571_PLL_N_F1(x)                 ((x<<0)&0x0FFF)

//R3
#define LMX2571_PLL_DEN_F1_15_0(x)          ((x<<0)&0xFFFF)

//R2
#define LMX2571_PLL_NUM_F1_15_0(x)          ((x<<0)&0xFFFF)

//R1
#define LMX2571_PLL_DEN_F1_23_16(x)         ((x<<8)&0xFF00)
#define LMX2571_PLL_NUM_F1_23_16(x)         ((x<<0)&0x00FF)

//R0
#define LMX2571_RESET(x)                          ((x<<13))
#define LMX2571_RESET_Normal_operation            0
#define LMX2571_RESET_Reset                       1
#define LMX2571_POWERDOWN(x)                      ((x<<12))
#define LMX2571_POWERDOWN_Normal_operation        0
#define LMX2571_POWERDOWN_Power_down              1
#define LMX2571_RXTX_CTRL(x)                       ((x<<11))
#define LMX2571_register_programming              0
#define LMX2571_toggling_the_TrCtl_pin            1
/*
0 = Switching is controlled by register programming
1 = Switching is controlled by toggling the TrCtl pin
*/
#define LMX2571_RXTX_POL(x)                       ((x<<10))
#define LMX2571_RXTX_POL_Active_LOW               0
#define LMX2571_RXTX_POL_Active_HIGH              1
#define LMX2571_F1F2_INIT(x)                      ((x<<9))
#define LMX2571_F1F2_INIT_Clear_bit_value         0
#define LMX2571_F1F2_INIT_Re_calibrate            1
#define LMX2571_F1F2_CTRL(x)                      ((x<<8))
//#define LMX2571_F1F2_CTRL_programming 0
//#define LMX2571_toggling_the_TrCtl_pin 1
#define LMX2571_F1F2_MODE(x)                      ((x<<7))
#define LMX2571_F1F2_Disable_F1F2_calibration     0
#define LMX2571_F1F2_Enable_F1F2_calibration      1
#define LMX2571_F1F2_SEL(x)                       ((x<<6))
#define LMX2571_F1F2_SEL_F1_registers             0
#define LMX2571_F1F2_SEL_F2_registers             1
#define LMX2571_FCAL_EN(x)                        ((x<<0))
#define LMX2571_Disabled                  0
#define LMX2571_Enabled                   1





#endif

