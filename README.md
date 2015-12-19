# wlan_station_exosite_write_read
Write and Read data to Exosite Cloud using Tiva Connected Launchpad + CC3100 BP + Sensor Hub BP

 * Maker/Author - Markel T. Robregado
 *
 * Modification Details : Write and read data to Exosite.
 *                        The Program sends temperature data from Sensor Hub, switch press count status
 *                        to Exosite using TI SimpleLink CC3100. It also reads Exosite portal dashboard,
 *                        if the dasboard switches has been pressed. If dashboard switch has been pressed
 *                        a Tiva Connected Launchpad on-board led will be turned on. Two Exosite portal
 *                        dashboards are available to turn on two on-board leds. *
 * Device Setup: Tiva Connected Launchpad + CC3100 Booster pack + Sensor Hub Booster Pack
 *
 */

Need to do:

Import wlan_station_exosite_write_read to your CCS workspace. Set correct CCS Include Paths and Path Variables
as needed. If any problem doing this, ask help at TI E2E Code Composer Studio Forum. I recommend use the latest CCS 
Version.

Install CC3100 SDK, and Tivaware at your PC.


SSID_NAME, SEC_TYPE, PASSKEY should be updated as per AP details at sl_common.h. 
File Location: C:\ti\CC3100SDK_1.1.0\cc3100-sdk\examples\common\sl_common.h 

/*
 * Values for below macros shall be modified per the access-point's (AP) properties
 * SimpleLink device will connect to following AP when the application is executed
 */
#define SSID_NAME       "jefwifi"         /* Access point name to connect to. */
#define SEC_TYPE        SL_SEC_TYPE_WPA    /* Security type of the Access piont */
#define PASSKEY         "abcde12345"                  /* Password in case of secure AP */
#define PASSKEY_LEN     pal_Strlen(PASSKEY)  /* Password length in case of secure AP */

Set your CIK at exosite.c

static char cikBuffer[CIK_LENGTH] = "YOUR EXOSITE CIK HERE";
