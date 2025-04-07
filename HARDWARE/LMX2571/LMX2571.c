#include "LMX2571.h"
#include "math.h"
#include "stdint.h"
#include "delay.h"

typedef struct LMX2571_PLL
{
	u8_ FSK_EN;
	u8_ OUTBUF_TX_PWR;
	u8_ OUTBUF_RX_PWR;
	u8_ OUTBUF_TX_EN;
	u8_ OUTBUF_RX_EN;
	u8_ LF_R4;
	u8_ LF_R3;
	u8_ CHDIV2;
	u8_ CHDIV1;
	u8_ PFD_DELAY;
	u8_ MULT;
	u8_ PLL_R;
	u8_ PLL_R_PRE;
	u8_ PLL_N_PRE;
	u8_ FRAC_ORDER;
	u16_ PLL_N;
	u32_ PLL_NUM;
	u32_ PLL_DEN;
	u8_ EXTVCO_SEL;
}_LMX2571_PLL;

struct LMX2571_FUNC
{

	u8_ XTAL_EN;
	u8_ RESET;
	u8_ POWERDOWN;
	u8_ DITHERING;
	u8_ CP_IDN_IDP;
	u8_ CP_GAIN;
	u8_ SDO_LD_SEL;
	u8_ LD_EN;
	u16_ MULT_WAIT;
	u8_ OUTBUF_AUTOMUTE;
	u8_ OUTBUF_TX_TYPE;
	u8_ OUTBUF_RX_TYPE;
	u8_ IPBUFDIFF_TERM;
	u8_ IPBUF_SE_DIFF_SEL;
	u8_ XTAL_PWRCTRL;
	u8_ FSK_I2S_FS_POL;
	u8_ FSK_I2S_CLK_POL;
	u8_ FSK_LEVEL;
	u8_ FSK_DEV_SEL;
	u8_ FSK_MODE_SEL;
	u8_ RXTX_CTRL;
	u8_ RXTX_POL;
	u8_ F1F2_INIT;
	u8_ F1F2_CTRL;
	u8_ F1F2_MODE;
	u8_ F1F2_SEL;
	u8_ FCAL_EN;
}LMX2571_FUNC;

_LMX2571_PLL F[2];

u32_ LMX2571regbuf[61] =
{
	0x000083	,0x010000	,0x020000	,0x030000	,0x042070	,0x050101	,0x069B81	,0x070EC4	,0x08000E	,0x090000	,0x0A0000	,0x0B0000	,
	0x0C0000	,0x0D0000	,0x0E0000	,0x0F0000	,0x100000	,0x110000	,0x120000	,0x132710	,0x142070	,0x150101	,0x169B81	,0x170EC4	,
	0x18000E	,0x190000	,0x1A0000	,0x1B0000	,0x1C0000	,0x1D0000	,0x1E0000	,0x1F0000	,0x200000	,0x210000	,0x221000	,0x230C83	,
	0xFFFFFF	,0xFFFFFF	,0xFFFFFF	,0x2711FB	,0x28101C	,0x290810	,0x2A0210	,0x2B4830	,0xFFFFFF	,0xFFFFFF	,0xFFFFFF	,0x2F4000	,
	0xFFFFFF	,0xFFFFFF	,0xFFFFFF	,0xFFFFFF	,0xFFFFFF	,0xFFFFFF	,0xFFFFFF	,0xFFFFFF	,0xFFFFFF	,0xFFFFFF	,0x3A8C00	,0xFFFFFF	,0x3CA000

};

u32_ LMX2571reg[61];
u64_ nowfre;

void LMX2571_update_data(u8_ write);
void WriteToLMX2571(u32_ buf);

struct LMX2571_platform_data {
	unsigned char		clkin;
	unsigned char		channel_spacing;
	unsigned char		power_up_frequency;

	unsigned char		ref_div_factor; /* 10-bit R counter */
	unsigned char		ref_doubler_en;
	unsigned char		ref_div2_en;

	unsigned char		r2_user_settings;
	unsigned char		r3_user_settings;
	unsigned char 		r4_user_settings;
	int					gpio_lock_detect;
};

void SetOutFre(u8_ f, u64_ fre)
{
	_PLL_state val;

//	fre+=1000;
	if (PLL_Calulate(fre) == 0)
	{
		nowfre = fre;
		val = GetPLLNum();

		F[f].CHDIV2 = val.PLL.CHDIV2;
		F[f].CHDIV1 = val.PLL.CHDIV1 - 4;
		F[f].MULT = val.PLL.MULT;
		F[f].PLL_R = val.PLL.POST_R_Divier;
		F[f].PLL_R_PRE = val.PLL.PRE_R_Divier;
		F[f].PLL_N_PRE = 1 - val.PLL.Prescalar / 2;
		F[f].PLL_N = val.PLL.N_Divier;
		F[f].PLL_NUM = val.PLL.NUM_Divier;
		F[f].PLL_DEN = val.PLL.DEN_Divier;
		if(F[f].PLL_DEN == 1)F[f].PLL_DEN = 0;
		
		LMX2571regbuf[1 + (f== LMX2571_F1 ? 0:16)] = LMX2571_PLL_DEN_F1_23_16(F[f].PLL_DEN >> 16) | LMX2571_PLL_NUM_F1_23_16(F[f].PLL_NUM >> 16);
		LMX2571regbuf[2 + (f == LMX2571_F1 ? 0 : 16)] = (u16_)F[f].PLL_NUM;
		LMX2571regbuf[3 + (f == LMX2571_F1 ? 0 : 16)] = (u16_)F[f].PLL_DEN;
		LMX2571regbuf[4 + (f == LMX2571_F1 ? 0 : 16)] = LMX2571_PLL_N_F1(F[f].PLL_N) | LMX2571_PLL_N_PRE_F1(F[f].PLL_N_PRE) | (LMX2571_FRAC_ORDER_F1(F[f].FRAC_ORDER));
		LMX2571regbuf[5 + (f == LMX2571_F1 ? 0 : 16)] = LMX2571_PLL_R_PRE_F1(F[f].PLL_R_PRE) | LMX2571_PLL_R_F1(F[f].PLL_R);
		LMX2571regbuf[6 + (f == LMX2571_F1 ? 0 : 16)] = LMX2571_MULT_F1(F[f].MULT) | LMX2571_PFD_DELAY_F1(F[f].PFD_DELAY) | LMX2571_CHDIV1_F1(F[f].CHDIV1) | LMX2571_CHDIV2_F1(F[f].CHDIV2) | LMX2571_LF_R3_F1(F[f].LF_R3);
		LMX2571regbuf[7 + (f == LMX2571_F1 ? 0 : 16)] = LMX2571_LF_R4_F1(F[f].LF_R4) | LMX2571_OUTBUF_RX_EN_F1(F[f].OUTBUF_RX_EN) | LMX2571_OUTBUF_TX_EN_F1(F[f].OUTBUF_TX_EN) | LMX2571_OUTBUF_RX_PWR_F1(F[f].OUTBUF_RX_PWR);
		LMX2571regbuf[8 + (f == LMX2571_F1 ? 0 : 16)] = LMX2571_OUTBUF_TX_PWR_F1(F[f].OUTBUF_TX_PWR) | LMX2571_EXTVCO_SEL_F1(F[f].EXTVCO_SEL) | LMX2571_EXTVCO_CHDIV_F1(0) | LMX2571_FSK_EN_F1(F[f].FSK_EN);
		LMX2571_update_data(1);
	}
	WriteToLMX2571(LMX2571regbuf[0]);
}

void WriteToLMX2571(u32_ buf)
{
	u8_ i = 0;

	LMX2571_LE_0;
	delay_us(1);
	LMX2571_CLK_0;

	for (i = 24; i>0; i--)
	{
		if (0x800000 == (buf & 0x800000))
		{
			LMX2571_DATA_1;
		}
		else
		{
			LMX2571_DATA_0;
		}
		LMX2571_CLK_1;
		buf <<= 1;
		LMX2571_CLK_0;
	}
	LMX2571_DATA_0;
	LMX2571_LE_1;
}
u16_ LMX2571_CaluateDetraFre(long int detraFre)
{
	long double sfsd;
	long int dF = detraFre;
	_PLL_state val;
	u16_ ruturnvalue;
	val = GetPLLNum();
	if(detraFre < 0)dF = -dF;
	
	sfsd= ((long double)dF*16777216/val.PLL.nowfpd)*((long double)(1<<val.PLL.CHDIV2)*val.PLL.CHDIV1/val.PLL.Prescalar);
	
	if(sfsd > 65535)return 0;
	
	if(sfsd * 10 > ((long int)sfsd)*10 +5)
	{
		ruturnvalue = (u16_)sfsd+1;
	}else ruturnvalue = (u16_)sfsd;

	if(detraFre < 0)
		{
			return (u16_)(-ruturnvalue-1);
		}else
		{
			return (u16_)ruturnvalue;
		}
}

void LMX2571_FASTFSKWrite(u16_ data)
{
	WriteToLMX2571((u32_)data|0x210000);
}
void LMX2571_FASTFSK(long int detraFre)
{
	u16_ cdata;
	
	cdata = LMX2571_CaluateDetraFre(detraFre);
	LMX2571_FASTFSKWrite(cdata);
}
void LMX2571_Reset(void)
{
	u8_ i = 0;

	LMX2571_FUNC.RESET = LMX2571_Enabled;
	LMX2571_update_data(0);
	WriteToLMX2571(LMX2571regbuf[0]);
	LMX2571_FUNC.RESET = LMX2571_Disabled;

	for (i = 60; i < 250; i--)LMX2571reg[i] = 0;
	delay_ms(2);
}

void LMX2571_default_pdata(void)
{

	LMX2571_Reset();
	LMX2571_update_data(1);

}
void LMX2571_update_data(u8_ write)
{
	u8_ i = 0;

	LMX2571regbuf[47] = LMX2571_DITHERING(LMX2571_FUNC.DITHERING);
	LMX2571regbuf[41] = (LMX2571regbuf[41]&0xFFF0)|LMX2571_CP_IDN(LMX2571_FUNC.CP_IDN_IDP);
	LMX2571regbuf[40] = 0x1C|LMX2571_CP_IUP(LMX2571_FUNC.CP_IDN_IDP)| LMX2571_CP_GAIN(LMX2571_FUNC.CP_GAIN);
	LMX2571regbuf[39] = 0x11F2|LMX2571_SDO_LD_SEL(LMX2571_FUNC.SDO_LD_SEL) | LMX2571_LD_EN(LMX2571_FUNC.LD_EN);
	LMX2571regbuf[35] = LMX2571_MULT_WAIT(LMX2571_FUNC.MULT_WAIT) | LMX2571_OUTBUF_AUTOMUTE(LMX2571_FUNC.OUTBUF_AUTOMUTE) | LMX2571_OUTBUF_TX_TYPE(LMX2571_FUNC.OUTBUF_TX_TYPE) | LMX2571_OUTBUF_RX_TYPE(LMX2571_FUNC.OUTBUF_RX_TYPE);
	LMX2571regbuf[34] = LMX2571_IPBUFDIFF_TERM(LMX2571_FUNC.IPBUFDIFF_TERM) | LMX2571_IPBUF_SE_DIFF_SEL(LMX2571_FUNC.IPBUF_SE_DIFF_SEL) | LMX2571_XTAL_PWRCTRL(LMX2571_FUNC.XTAL_PWRCTRL)| LMX2571_XTAL_EN(LMX2571_FUNC.XTAL_EN)|
		LMX2571_FSK_I2S_FS_POL(LMX2571_FUNC.FSK_I2S_FS_POL)| LMX2571_FSK_I2S_CLK_POL(LMX2571_FUNC.FSK_I2S_CLK_POL) | LMX2571_FSK_LEVEL(LMX2571_FUNC.FSK_LEVEL) | LMX2571_FSK_DEV_SEL(LMX2571_FUNC.FSK_DEV_SEL) | LMX2571_FSK_MODE_SEL(LMX2571_FUNC.FSK_MODE_SEL);
	LMX2571regbuf[0] = 0x0002 | LMX2571_RESET(LMX2571_FUNC.RESET) | LMX2571_POWERDOWN(LMX2571_FUNC.POWERDOWN) | LMX2571_RXTX_CTRL(LMX2571_FUNC.RXTX_CTRL) | LMX2571_RXTX_POL(LMX2571_FUNC.RXTX_POL) |
		LMX2571_F1F2_INIT(LMX2571_FUNC.F1F2_INIT) | LMX2571_F1F2_CTRL(LMX2571_FUNC.F1F2_CTRL) | LMX2571_F1F2_MODE(LMX2571_FUNC.F1F2_MODE) | LMX2571_F1F2_SEL(LMX2571_FUNC.F1F2_SEL) | LMX2571_FCAL_EN(LMX2571_FUNC.FCAL_EN);

	if (write)
	{
		for (i = 60; i < 250; i--)
			if (LMX2571regbuf[i] != LMX2571reg[i])
			{
				LMX2571reg[i] = LMX2571regbuf[i];
				if(LMX2571regbuf[i]!=0xffffff)	WriteToLMX2571((LMX2571reg[i]&0x0000ffff)|(i<<16));
			}
	}

}

void LMX2571_FuncInitOnlyfreCreat(void)
{
	LMX2571_FUNC.DITHERING = LMX2571_DITHERING_Medium;
	LMX2571_FUNC.CP_IDN_IDP = 16;//8 = 1250 µA
	LMX2571_FUNC.CP_GAIN = LMX2571_CP_GAIN_1x;
	LMX2571_FUNC.SDO_LD_SEL = LMX2571_SDO_LD_SEL_Lock_detect_output;
	LMX2571_FUNC.LD_EN = LMX2571_LD_EN_Enabled;
	LMX2571_FUNC.MULT_WAIT = 520;//520 = 20 µs
	LMX2571_FUNC.OUTBUF_AUTOMUTE = LMX2571_Disabled;
	LMX2571_FUNC.OUTBUF_TX_TYPE = Push_pull;
	LMX2571_FUNC.OUTBUF_RX_TYPE = Push_pull;
	LMX2571_FUNC.IPBUFDIFF_TERM = LMX2571_Disabled;
	LMX2571_FUNC.IPBUF_SE_DIFF_SEL = LMX2571_Disabled;
	LMX2571_FUNC.XTAL_PWRCTRL = LMX2571_XTAL_PWRCTRL_0o;
	LMX2571_FUNC.XTAL_EN = LMX2571_Disabled;
	LMX2571_FUNC.FSK_I2S_FS_POL = LMX2571_FSK_I2S_FS_POL_Active_HIGH;
	LMX2571_FUNC.FSK_I2S_CLK_POL = LMX2571_FSK_I2S_CLK_POL_Rising_edge_strobe;
	LMX2571_FUNC.FSK_LEVEL = LMX2571_FSK_LEVEL_Disabled;
	LMX2571_FUNC.FSK_DEV_SEL = LMX2571_FSK_DEV_SEL_FSK_DEV0_Fx;
	LMX2571_FUNC.FSK_MODE_SEL = LMX2571_FSK_MODE_SEL_FSK_SPI_FAST_mode;
	LMX2571_FUNC.RESET = LMX2571_Disabled;
	LMX2571_FUNC.POWERDOWN = LMX2571_Disabled;
	LMX2571_FUNC.RXTX_CTRL = LMX2571_register_programming;
	LMX2571_FUNC.RXTX_POL = LMX2571_RXTX_POL_Active_LOW;
	LMX2571_FUNC.F1F2_INIT = LMX2571_F1F2_INIT_Clear_bit_value;
	LMX2571_FUNC.F1F2_CTRL = LMX2571_register_programming;
	LMX2571_FUNC.F1F2_MODE = LMX2571_F1F2_Enable_F1F2_calibration;
	LMX2571_FUNC.F1F2_SEL = LMX2571_F1F2_SEL_F1_registers;
	LMX2571_FUNC.FCAL_EN = LMX2571_Enabled;

	F[LMX2571_F1].FSK_EN = LMX2571_Enabled;
	F[LMX2571_F1].OUTBUF_TX_PWR = 9;
	F[LMX2571_F1].OUTBUF_RX_PWR = 9;
	F[LMX2571_F1].OUTBUF_TX_EN = LMX2571_Enabled;
	F[LMX2571_F1].OUTBUF_RX_EN = LMX2571_Enabled;
	F[LMX2571_F1].LF_R4 = 4;
	F[LMX2571_F1].LF_R3 = 4;
	F[LMX2571_F1].CHDIV2 = 1;
	F[LMX2571_F1].CHDIV1 = 1;
	F[LMX2571_F1].PFD_DELAY = 4;
	F[LMX2571_F1].MULT = 1;
	F[LMX2571_F1].PLL_R = 1;
	F[LMX2571_F1].PLL_R_PRE = 1;
	F[LMX2571_F1].PLL_N_PRE = 1;
	F[LMX2571_F1].FRAC_ORDER = 3;
	F[LMX2571_F1].PLL_N = 1;
	F[LMX2571_F1].PLL_NUM = 1;
	F[LMX2571_F1].PLL_DEN = 1;
	F[LMX2571_F1].EXTVCO_SEL = LMX2571_Disabled;
	F[1] = F[0];
}
void Set_PLL(void)
{
	_PLL_state val;

	val.clkin 			 = 100000000;
	val.fpd 			 = 100000000;
	val.N_Divier_BIT 	 = 12;
	val.NUM_Divier_BIT   = 24;
	val.DEN_Divier_BIT 	 = 24;
	val.PRE_R_Divier_BIT = 8;
	val.POST_R_Divier_BIT= 8;
	val.MULT_Divier_BIT  = 4;
	val.min_fpfd_freq 	 = 100000;
	val.max_fpfd_freq 	 = 150000000;
	val.min_VCO_freq 	 = 4300000000;
	val.max_VCO_freq 	 = 5376000000;

	LMX2571_FuncInitOnlyfreCreat();
	PLL_Data_Init(val);
	LMX2571_default_pdata();
}

void LMX2571_Init(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/*Configure GPIO pins : PAPin PAPin PAPin PAPin */
	GPIO_InitStruct.Pin = FDV_Pin|FD2_Pin|FD1_Pin|FD0_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pins : PBPin PBPin PBPin PBPin
						   PBPin PBPin */
	GPIO_InitStruct.Pin = CLK_Pin|LE_Pin|CE_Pin|CTL_Pin
						  |DAT_Pin|MUX_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	LMX2571_CE_1;
	
	Set_PLL();
}
