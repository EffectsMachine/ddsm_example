/*
change ctrl mode for DDSM210.
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

	// you need to config the type of ddsm
	// before you change the mode.
	// ddsm must be stoped to change mode.
	// delay 5ms after changing mdde.
	// ddsm115 MODE_CODE:
	// 1 - current loop
	// 2 - speed loop
	// 3 - position loop
	// args: ddsm_change_mode(DDSM_ID, MODE_CODE)
	dc.ddsm_change_mode(1, 3);
	// change ddsm mode to position loop.
	delay(5);
}

void loop() {
	// --- DDSM115 ---
	// 1 - current loop, cmd: -32767 ~ 32767 -> -8 ~ 8 A (ddsm115 max current < 2.7A)
	// 2 - speed loop, cmd: -200 ~ 200 rpm
	// 3 - position loop, cmd: 0 ~ 32767 -> 0 ~ 360°

	// When the motor is set to position loop mode, 
	// the current position is treated as the zero point. 
	// The target position range is 0 to 32767, 
	// corresponding to 0 to 360°. 

	// The motor will move to the target position following 
	// the shortest path. 

	// For example, 
	// if you want the motor to rotate counterclockwise 
	// from the zero position, 
	// you can set a target position greater than 16383 (32767/2), 
	// and the motor will rotate in the opposite direction.

	// ACC_TIME:
	// Acceleration Time: This parameter is effective in speed loop mode. 
	// It defines the acceleration time per 1 rpm in units of 0.1 ms. 
	// For instance, if set to 1, the acceleration time is 0.1 ms per 1 rpm; 
	// if set to 10, the acceleration time is 1 ms per 1 rpm (10 * 0.1 ms). 
	// If set to 0, the default value is 1, 
	// meaning the acceleration time is 0.1 ms per 1 rpm. 
	// This parameter only applies to speed loop mode.

	// args: ddsm_ctrl(DDSM_ID, CMD, ACC_TIME)
	dc.ddsm_ctrl(1, 0, 0);
	delay(1000);

	// args: ddsm_ctrl(DDSM_ID, CMD, ACC_TIME)
	dc.ddsm_ctrl(1, 5000, 0);
	delay(1000);
}