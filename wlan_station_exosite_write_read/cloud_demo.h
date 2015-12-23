//*****************************************************************************
// cloud_demo.h
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

#ifndef CLOUD_DEMO_H_
#define CLOUD_DEMO_H_

void SW1_Pressed(void);
void SW2_Pressed(void);
void Demo_Tick(void);
void cloud_demo(void);

#endif /* CLOUD_DEMO_H_ */
