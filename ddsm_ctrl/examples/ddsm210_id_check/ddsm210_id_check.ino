/*
get the ID of DDSM.
make sure there is only one DDSM connected.
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
	dc.set_ddsm_type(210);

	// clear ddsm serial buffer.
	dc.clear_ddsm_buffer();
}

void loop() {
	Serial.print("DDSM ID: ");
	Serial.println(dc.ddsm_id_check());
	delay(3000);
}