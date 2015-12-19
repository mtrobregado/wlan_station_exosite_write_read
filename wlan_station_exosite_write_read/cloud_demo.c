//*****************************************************************************
//
// Write and Read data to Exosite Cloud using Tiva Connected Launchpad + CC3100 BP + Sensor Hub BP,
// Connects to AP through WiFi
//
// Maker/Author - Markel T. Robregado *
// Modification Details : Write and read data to Exosite.
// Sends Temperature data from TMP006 sensor to Exosite Cloud
// Sends switch press count to Exosite Cloud
// on-board led on-off, from Exosite Dashboard Switches
//
// Device Setup: Tiva Connected Launchpad + CC3100 Booster pack + Sensor Hub Booster Pack 
//
//*****************************************************************************

#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "sl_common.h"
#include "exosite.h"
#include "exosite_pal.h"
#include "cloud_demo.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "drivers/pinout.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "drivers/pinout.h"
#include "sensorlib/i2cm_drv.h"
#include "sensorlib/tmp006.h"

#define TEMP_ALIAS          "sensortemp"
#define LED2_ALIAS          "ledd2"
#define LED3_ALIAS          "ledd3"
#define SW1_ALIAS           "usrsw1"
#define SW2_ALIAS           "usrsw2"

#define TEMP_ALIAS_LENGTH          10
#define LED2_ALIAS_LENGTH          5
#define LED3_ALIAS_LENGTH          5
#define SW1_ALIAS_LENGTH           6
#define SW2_ALIAS_LENGTH           6

// Global instance structure for the TMP006 sensor driver.
extern tTMP006 g_sTMP006Inst;
extern unsigned long ui32SysClock;
extern unsigned long g_Status;

volatile int sw1_button_on = 0;
volatile int sw2_button_on = 0;

// Global new data flag to alert main that TMP006 data is ready.
extern volatile uint_fast8_t g_vui8DataFlag;
// Global new error flag to store the error condition if encountered.
extern volatile uint_fast8_t g_vui8ErrorFlag;

extern void TMP006AppErrorHandler(char *pcFilename, uint_fast32_t ui32Line);

/*****************************************************************************
*
* blinky_led1
*
*  \param  times - count times
*
*  \return None
*
*  \brief  control the led7 blinky times
*
*****************************************************************************/
void blinky_led1(int times)
{
	int intern_cnt = times;

	while (intern_cnt > 0)
	{
		LEDWrite(CLP_D1, CLP_D1);
		SysCtlDelay(ui32SysClock / (4 * 3)); // 250 ms
		LEDWrite(CLP_D1, ~CLP_D1);
		SysCtlDelay(ui32SysClock / (4 * 3)); // 250 ms
		intern_cnt--;
	}
}

/*****************************************************************************
*
* SW2_Pressed
*
*  \param  None
*
*  \return None
*
*  \brief  Handle the Switch 2 press event
*
*****************************************************************************/
void SW1_Pressed(void)
{
	sw1_button_on++;
	if(sw1_button_on == 15 )
	{
		sw1_button_on = 0;
	}
	UARTprintf(" SW1 pressed.\r\n");
}

/*****************************************************************************
*
* SW3_Pressed
*
*  \param  None
*
*  \return None
*
*  \brief  Handle the Switch 3 press event
*
*****************************************************************************/
void SW2_Pressed(void)
{
	sw2_button_on++;
	if(sw2_button_on == 15 )
	{
		sw2_button_on = 0;
	}
	UARTprintf(" SW2 pressed.\r\n");
}

/*****************************************************************************
*
* Status_Indicate
*
*  \param  None
*
*  \return None
*
*  \brief  Blinky the LED D7 to indicate the current status
*
*****************************************************************************/
void Status_Indicate(void)
{
  int state = Exosite_StatusCode();

  if (EXO_STATE_R_W_ERROR == state)
  {
    blinky_led1(2);
  }

}

/*****************************************************************************
*
* Cloud_Read
*
*  \param  None
*
*  \return None
*
*  \brief  Reads data from Exosite Cloud, and turn ON/OFF led .. etc. from Cloud
*
*****************************************************************************/
void Cloud_Read(void)
{

	char ledx[10] = "DEADBEEFDE";
	int32_t Read_status = 0;
	int32_t	switch1_data = 0;
	int32_t	switch2_data = 0;
	uint16_t response_length = 0;


	//use exosite_read to read multiple aliases values
	//returns "ledd2=0"
	Read_status = exosite_read("ledd2", ledx, 10, &response_length);

	if (Read_status == 0)
	{
		switch1_data = exoPal_atoi(&ledx[strlen(LED2_ALIAS) + 1]);
		if (switch1_data == 1)
		{
			LEDWrite(CLP_D2, CLP_D2);
		}
		if (switch1_data == 0)
		{
			LEDWrite(CLP_D2, ~CLP_D2);
		}
		UARTprintf(" Exosite Read:  %s=%d\r\n", LED2_ALIAS, switch1_data);
	}

	Read_status = exosite_read("ledd3", ledx, 10, &response_length);

	if (Read_status == 0)
	{
		switch2_data = exoPal_atoi(&ledx[strlen(LED3_ALIAS) + 1]);
		if (switch2_data == 1)
		{
			LEDWrite(CLP_D3, CLP_D3);
		}
		if (switch2_data == 0)
		{
			LEDWrite(CLP_D3, ~CLP_D3);
		}
		UARTprintf(" Exosite Read:  %s=%d\r\n", LED3_ALIAS, switch2_data);
	}
}

/*****************************************************************************
*
* Report_Sensors
*
*  \param  None
*
*  \return None
*
*  \brief  Posts the data to Exosite Cloud
*
*****************************************************************************/
void Report_Sensors(void)
{
	char post_str[200];
	int post_len = 0;
	float fAmbient, fObject;
    int_fast32_t i32IntegerPart;
    int_fast32_t i32FractionPart;

	//
	// Put the processor to sleep while we wait for the TMP006 to
	// signal that data is ready.  Also continue to sleep while I2C
	// transactions get the raw data from the TMP006
	//

	while((g_vui8DataFlag == 0) && (g_vui8ErrorFlag == 0))
	{
		//ROM_SysCtlSleep();
	}


	//
	// If an error occurred call the error handler immediately.
	//
	if(g_vui8ErrorFlag)
	{
		TMP006AppErrorHandler(__FILE__, __LINE__);
	}

	//
	// Reset the flag
	//
	g_vui8DataFlag = 0;

	//
	// Get a local copy of the latest data in float format.
	//
	TMP006DataTemperatureGetFloat(&g_sTMP006Inst, &fAmbient, &fObject);

    // Convert the floating point ambient temperature  to an integer part
    // and fraction part for easy printing.
    //
    i32IntegerPart = (int32_t)fAmbient;
    i32FractionPart = (int32_t)(fAmbient * 1000.0f);
    i32FractionPart = i32FractionPart - (i32IntegerPart * 1000);
    if(i32FractionPart < 0)
    {
        i32FractionPart *= -1;
    }

	memcpy(&post_str[post_len], SW1_ALIAS, SW1_ALIAS_LENGTH);
	post_len += strlen(SW1_ALIAS);
	post_str[post_len] = '=';
	post_len++;
	sprintf(&post_str[post_len], "%d", (char)sw1_button_on);

	post_len = strlen(post_str);
	post_str[post_len] = '&';
	post_len++;

	memcpy(&post_str[post_len], SW2_ALIAS, SW2_ALIAS_LENGTH);
	post_len += strlen(SW2_ALIAS);
	post_str[post_len] = '=';
	post_len++;
	sprintf(&post_str[post_len], "%d", (char)sw2_button_on);

	post_len = strlen(post_str);
	post_str[post_len] = '&';
	post_len++;

	//last
	memcpy(&post_str[post_len], TEMP_ALIAS, TEMP_ALIAS_LENGTH);
	post_len += strlen(TEMP_ALIAS);
	post_str[post_len] = '=';
	post_len++;
	post_len += snprintf(&post_str[post_len], 10, "%2d.%02d", i32IntegerPart, i32FractionPart);

	UARTprintf(" Exosite Write: %s\r\n", post_str);

	exosite_write(post_str, post_len);

}

/*****************************************************************************
*
* cloud_demo
*
*  \param  None
*
*  \return None
*
*  \brief  The Exosite Cloud main application
*
*****************************************************************************/
void cloud_demo(void)
{

	int exo_state = -1;
	unsigned int delay_multiplier = 1;
	unsigned int read_interval = 2;
	unsigned int write_interval = 4;
	unsigned int interval_counter = 0;

	UARTprintf("\r\n\r\n");
	UARTprintf(" Exosite Cloud App Start.\r\n");

	exo_state = EXO_STATUS_OK; //No status code return yet from Exosite

	while (1)
	{
		if (IS_CONNECTED(g_Status))
		{
			if (EXO_STATUS_OK == exo_state)
			{
				if(interval_counter % write_interval == 0)
				{
					Report_Sensors();
				}

				if(interval_counter % read_interval == 0)
				{
					Cloud_Read();
				}
			}

			if (EXO_STATE_R_W_ERROR == exo_state)
            {
				UARTprintf(" Unable to connect to Exosite check CIK\r\n");
            }


			delay_multiplier = 1;

		}
		else
		{
			UARTprintf(" WiFi Disconnected\r\n");
			UARTprintf(" Check connections and restart device . . .\r\n");
			delay_multiplier = 60;
		}

		Status_Indicate();
		SysCtlDelay(delay_multiplier * (ui32SysClock / (2 * 3))); //    * 500 ms

		if(interval_counter == UINT_MAX) //UINT_MAX from limits.h value 65536
		{
			interval_counter = 0;
		}

		interval_counter++;
	}
}

