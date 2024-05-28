/*
speed loop ctrl for DDSM115.
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
	// ACC_TIME:
	// Acceleration Time: This parameter is effective in speed loop mode. 
	// It defines the acceleration time per 1 rpm in units of 0.1 ms. 
	// For instance, if set to 1, the acceleration time is 0.1 ms per 1 rpm; 
	// if set to 10, the acceleration time is 1 ms per 1 rpm (10 * 0.1 ms). 
	// If set to 0, the default value is 1, 
	// meaning the acceleration time is 0.1 ms per 1 rpm. 
	// This parameter only applies to speed loop mode.

	// args: ddsm_ctrl(DDSM_ID, CMD, ACC_TIME)
	dc.ddsm_ctrl(1, 50, 2); // 50 rpm
	delay(3000);

	// args: ddsm_ctrl(DDSM_ID, CMD, ACC_TIME)
	dc.ddsm_ctrl(1, -50, 2); // -50 rpm
	delay(3000);
}