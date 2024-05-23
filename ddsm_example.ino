#include <ArduinoJson.h>
StaticJsonDocument<256> jsonCmdReceive;
StaticJsonDocument<256> jsonInfoSend;

// device settings.
#define DDSM_RX 18
#define DDSM_TX 19
#define SERIAL_BAUDRATE 115200
#define DDSM_BAUDRATE 115200
#define TIME_BETWEEN_CMD 4

#define TYPE_DDSM115  1
#define TYPE_DDSM210  2

const size_t packet_length = 10;     
uint8_t packet_move[packet_length] = {0x01, 0x64, 0xff, 0xce, 0x00, 0x00, 0x00, 0x00, 0x00, 0xda};

int heartbeat_time_ms = 2000;
unsigned long prev_time = millis();
bool stop_flag = false;

// 115: ddsm 115
// 210: ddsm 210
uint8_t ddsm_type = TYPE_DDSM115;
bool get_info_flag = false;


// func to print the packet_move data as HEX.
void print_packet(uint8_t *packet, size_t length) {
  for (size_t i = 0; i < length; i++) {
    if (i > 0) Serial.print(", ");
    Serial.print("0x");
    if (packet[i] < 0x10) Serial.print("0");
    Serial.print(packet[i], HEX);
  }
  Serial.println();
}


// CRC-8/MAXIM
uint8_t crc8_update(uint8_t crc, uint8_t data) {
  uint8_t i;
  crc = crc ^ data;
  for (i = 0; i < 8; ++i) {
    if (crc & 0x01) {
      crc = (crc >> 1) ^ 0x8c;
    } else {
      crc >>= 1;
    }
  }
  return crc;
}


// clear ddsm serial buffer
void clear_ddsm_buffer() {
  while (Serial1.available() > 0) {
    Serial1.read();
  }
}


// ddsm speed ctrl (closed-loop)
void ddsm_ctrl(uint8_t id, int cmd, uint8_t act) {
  packet_move[0] = id;
  packet_move[1] = 0x64;

  packet_move[2] = (cmd >> 8) & 0xFF;
  packet_move[3] = cmd & 0xFF;

  packet_move[4] = 0x00;
  packet_move[5] = 0x00;

  packet_move[6] = act;
  packet_move[7] = 0x00;

  // CRC-8/MAXIM
  uint8_t crc = 0;
  for (size_t i = 0; i < packet_length - 1; ++i) {
    crc = crc8_update(crc, packet_move[i]);
  }
  packet_move[9] = crc;

  Serial1.write(packet_move, packet_length);
}


// change ddsm id
void ddsm_change_id(uint8_t id) {
  packet_move[0] = 0xAA;
  
  packet_move[1] = 0x55;
  packet_move[2] = 0x53;
  
  packet_move[3] = id;
  
  packet_move[4] = 0x00;
  packet_move[5] = 0x00;
  packet_move[6] = 0x00;
  packet_move[7] = 0x00;
  packet_move[8] = 0x00;

  // CRC-8/MAXIM
  uint8_t crc = 0;
  for (size_t i = 0; i < packet_length - 1; ++i) {
    crc = crc8_update(crc, packet_move[i]);
  }
  packet_move[9] = crc;

  for (int i = 0;i < 5;i++) {
    Serial1.write(packet_move, packet_length);
    delay(TIME_BETWEEN_CMD);
  }
  print_packet(packet_move, packet_length);
}


// change mode
// ddsm115:
// 1 - current loop
// 2 - speed loop
// 3 - position loop
// C8 64 00 00 00 00 00 00 00 DE
// 01 A0 00 00 00 00 00 00 00 01
// ddsm210:
// 0 - open loop
// 2 - speed loop
// 3 - position loop
// 
void ddsm_change_mode(uint8_t id, uint8_t mode) {
  if (ddsm_type == TYPE_DDSM115) {
    packet_move[0] = id;
    packet_move[1] = 0xA0;
    packet_move[2] = 0x00;
    packet_move[3] = 0x00;
    packet_move[4] = 0x00;
    packet_move[5] = 0x00;
    packet_move[6] = 0x00;
    packet_move[7] = 0x00;
    packet_move[8] = 0x00;
    packet_move[9] = mode;
  } else if (ddsm_type == TYPE_DDSM210) {
    packet_move[0] = id;
    packet_move[1] = 0xA0;
    packet_move[2] = mode;
    packet_move[3] = 0x00; 
    packet_move[4] = 0x00;
    packet_move[5] = 0x00;
    packet_move[6] = 0x00;
    packet_move[7] = 0x00;
    packet_move[8] = 0x00;
    // CRC-8/MAXIM
    uint8_t crc = 0;
    for (size_t i = 0; i < packet_length - 1; ++i) {
      crc = crc8_update(crc, packet_move[i]);
    }
    packet_move[9] = crc;
  }
  Serial1.write(packet_move, packet_length);
  print_packet(packet_move, packet_length);
}


// id check
// there must be only one ddsm connected when you check
// ddsm115 feedback:
// 0  1    2        3        4       5       6          7          8     9
// ID MODE TORQUE_H TORQUE_L SPEED_H SPEED_L POSITION_H POSITION_L ERROR CRC8
// ddsm210 feedback:
// 0  1    2        3        4       5       6          7          8     9
void ddsm_id_check() {
  packet_move[0] = 0xC8;
  packet_move[1] = 0x64;
  packet_move[2] = 0x00;
  packet_move[3] = 0x00;

  packet_move[4] = 0x00;
  packet_move[5] = 0x00;
  packet_move[6] = 0x00;
  packet_move[7] = 0x00;

  packet_move[8] = 0x00;
  packet_move[9] = 0xDE;
  Serial1.write(packet_move, packet_length);
}


// get info
// DDSM115 feedback:
// 0  1    2        3        4       5       6    7  8     9 
// ID MODE TORQUE_H TORQUE_L SPEED_H SPEED_L TEMP U8 ERROR CRC8
void ddsm_get_info(uint8_t id) {
  get_info_flag = true;
  packet_move[0] = id;
  packet_move[1] = 0x74;
  packet_move[2] = 0x00;
  packet_move[3] = 0x00;

  packet_move[4] = 0x00;
  packet_move[5] = 0x00;
  packet_move[6] = 0x00;
  packet_move[7] = 0x00;

  packet_move[8] = 0x00;
  // CRC-8/MAXIM
  uint8_t crc = 0;
  for (size_t i = 0; i < packet_length - 1; ++i) {
    crc = crc8_update(crc, packet_move[i]);
  }
  packet_move[9] = crc;
  Serial1.write(packet_move, packet_length);
}


// stop a single ddsm.
void ddsm_stop(uint8_t id) {
  ddsm_ctrl(id, 0, 0);
}


// set the heartbeat time.
void set_heartbeat_time(int time_ms) {
  heartbeat_time_ms = time_ms;
}


// change ddsm type.
void set_ddsm_type(int inputType) {
  if (inputType == 115) {
    ddsm_type = TYPE_DDSM115;
    Serial.println("DDSM115");
  } else if (inputType == 210) {
    ddsm_type = TYPE_DDSM210;
    Serial.println("DDSM210");
  }
}

// heartbeat ctrl
void heartbeat_ctrl() {
  unsigned long curr_time = millis();
  if (curr_time - prev_time > heartbeat_time_ms && !stop_flag) {
    ddsm_stop(1);
    delay(TIME_BETWEEN_CMD);
    ddsm_stop(2);
    delay(TIME_BETWEEN_CMD);
    ddsm_stop(3);
    delay(TIME_BETWEEN_CMD);
    ddsm_stop(4);
    delay(TIME_BETWEEN_CMD);
    stop_flag = true;
    Serial.println("Heartbeat Stop");
  }
}


// json cmds.
#include "json_cmd.h"

// uart ctrl funcs.
#include "uart_ctrl.h"


void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  Serial1.begin(DDSM_BAUDRATE, SERIAL_8N1, DDSM_RX, DDSM_TX);
  clear_ddsm_buffer();
}


void loop() {
  heartbeat_ctrl();
  ddsm115_fb();
  serialCtrl();
}