/*
get feedback data from DDSM210.
*/

#include <ddsm_ctrl.h>

DDSM_CTRL dc;

// device settings.
#define DDSM_RX 18
#define DDSM_TX 19

void setup() {
	Serial.begin(115200);

	// ddsm init.
	Serial1.begin(DDSM_BAUDRATE, SERIAL_8N1, DDSM_RX, DDSM_TX);
	dc.pSerial = &Serial1;

	// config the type of ddsm. 
	dc.set_ddsm_type(115);

	// clear ddsm serial buffer.
	dc.clear_ddsm_buffer();
}

void loop() {
	// Each time the ddsm_ctrl() function is called, 
	// it returns information about the motor, 
	// including speed (in 1 rpm units), the mode,
	// torque current (-32767 to 32767 corresponding to -8 to 8 A), 
	// and temperature (in degrees Celsius).

	// ACC_TIME:
	// Acceleration Time: This parameter is effective in speed loop mode. 
	// It defines the acceleration time per 1 rpm in units of 0.1 ms. 
	// For instance, if set to 1, the acceleration time is 0.1 ms per 1 rpm; 
	// if set to 10, the acceleration time is 1 ms per 1 rpm (10 * 0.1 ms). 
	// If set to 0, the default value is 1, 
	// meaning the acceleration time is 0.1 ms per 1 rpm. 
	// This parameter only applies to speed loop mode.

	// args: ddsm_ctrl(DDSM_ID, CMD, ACC_TIME)
	dc.ddsm_ctrl(1, 50, 3); // speed: 50.0rpm (500 * 0.1)
	Serial.print("speed: ");
	Serial.println(dc.speed_data);
	Serial.print("mode: ");
	Serial.println(dc.ddsm_mode);
	Serial.print("torque current: ");
	Serial.println(dc.ddsm_torque);
	delay(3000);

	// args: ddsm_ctrl(DDSM_ID, CMD, ACC_TIME)
	dc.ddsm_ctrl(1, -50, 3); // speed: 50.0rpm
	delay(1500);

	// get temperature
	// args: ddsm_get_info(DDSM_ID)
	dc.ddsm_get_info(1);
	
	Serial.print("temperature: ");
	Serial.println(dc.temperature);
	delay(1500);
}