void jsonCmdReceiveHandler(){
	int cmdType = jsonCmdReceive["T"].as<int>();
	switch(cmdType){
	case CMD_DDSM_STOP:
                ddsm_stop(
								jsonCmdReceive["id"]);break;
	case CMD_DDSM_SPEED_CTRL:
                ddsm_ctrl(
								jsonCmdReceive["id"],
								jsonCmdReceive["cmd"],
								jsonCmdReceive["act"]);break;
  case CMD_DDSM_CHANGE_ID:
                ddsm_change_id(
                jsonCmdReceive["id"]);break;
  case CMD_CHANGE_MODE:
                ddsm_change_mode(
                jsonCmdReceive["id"],
                jsonCmdReceive["mode"]);break;
  case CMD_DDSM_ID_CHECK:
                ddsm_id_check();break;
  case CMD_DDSM_INFO:
                ddsm_get_info(
                jsonCmdReceive["id"]);break;
	case CMD_HEARTBEAT_TIME:
                set_heartbeat_time(
								jsonCmdReceive["time"]);break;
  case CMD_TYPE:
                set_ddsm_type(
                jsonCmdReceive["type"]);break;
	}
}

void serialCtrl() {
  static String receivedData;

  while (Serial.available() > 0) {
    char receivedChar = Serial.read();
    receivedData += receivedChar;

    // Detect the end of the JSON string based on a specific termination character
    if (receivedChar == '\n') {
      // Now we have received the complete JSON string
      DeserializationError err = deserializeJson(jsonCmdReceive, receivedData);
      if (err == DeserializationError::Ok) {
      	prev_time = millis();
      	if (stop_flag) {
      		stop_flag = false;
      	}
      	clear_ddsm_buffer();
        jsonCmdReceiveHandler();
      } else {
        // Handle JSON parsing error here
      }
      // Reset the receivedData for the next JSON string
      receivedData = "";
    }
  }
}


void ddsm210_fb() {
  if (Serial1.available() >= 10) {
    uint8_t data[10];
    Serial1.readBytes(data, 10);

    uint8_t ID = data[0];
    int fb_data = (data[2] << 8) | data[3];
    if (fb_data & 0x8000) {
      fb_data = -(0x10000 - fb_data);
    }

    int current = (data[4] << 8) | data[5];
    if (current & 0x8000) {
      current = -(0x10000 - current);
    }

    int acceleration_time = data[6];
    int temperature = data[7];
    int fault_code = data[8];
    int crc = data[9];

    jsonInfoSend.clear();
    jsonInfoSend["T"] = FB_MOTOR;
    jsonInfoSend["id"]  = ID;
    jsonInfoSend["fb"] = fb_data;
    jsonInfoSend["crt"] = current;
    jsonInfoSend["act"] = acceleration_time;
    jsonInfoSend["tep"] = temperature;
    jsonInfoSend["err"] = fault_code;
    jsonInfoSend["crc"] = crc;
    String getInfoJsonString;
    serializeJson(jsonInfoSend, getInfoJsonString);
    Serial.println(getInfoJsonString);
  }
}

void ddsm115_fb() {
  if (Serial1.available() >= 10) {
    uint8_t data[10];
    Serial1.readBytes(data, 10);

    uint8_t ddsm_id = data[0];

    // CRC-8/MAXIM
    uint8_t crc = 0;
    for (size_t i = 0; i < packet_length - 1; ++i) {
      crc = crc8_update(crc, data[i]);
    }
    if (crc != data[9]){
      jsonInfoSend.clear();
      jsonInfoSend["T"] = FB_MOTOR;
      jsonInfoSend["crc"] = 0;
      String getInfoJsonString;
      serializeJson(jsonInfoSend, getInfoJsonString);
      Serial.println(getInfoJsonString);
      return;
    }

    int ddsm_mode = data[1];

    int ddsm_torque = (data[2] << 8) | data[3];
    if (ddsm_torque & 0x8000) {
      ddsm_torque = -(0x10000 - ddsm_torque);
    }

    int ddsm_spd = (data[4] << 8) | data[5];
    if (ddsm_spd & 0x8000) {
      ddsm_spd = -(0x10000 - ddsm_spd);
    }

    if (get_info_flag) {
      get_info_flag = false;
      int ddsm_temp = data[6];
      int ddsm_u8 = data[7];

      int ddsm_error = data[8];

      jsonInfoSend.clear();
      jsonInfoSend["T"] = FB_MOTOR;
      jsonInfoSend["id"] = ddsm_id;
      jsonInfoSend["typ"] = 115;
      jsonInfoSend["mode"] = ddsm_mode;
      jsonInfoSend["tor"] = ddsm_torque;
      jsonInfoSend["spd"] = ddsm_spd;
      jsonInfoSend["temp"] = ddsm_temp;
      jsonInfoSend["u8"] = ddsm_u8;
      jsonInfoSend["err"] = ddsm_error;
      String getInfoJsonString;
      serializeJson(jsonInfoSend, getInfoJsonString);
      Serial.println(getInfoJsonString);
      print_packet(data, 10);
    } else {
      int ddsm_pos = (data[6] << 8) | data[7];
      if (ddsm_pos & 0x8000) {
        ddsm_pos = -(0x10000 - ddsm_pos);
      }

      int ddsm_error = data[8];

      jsonInfoSend.clear();
      jsonInfoSend["T"] = FB_MOTOR;
      jsonInfoSend["id"] = ddsm_id;
      jsonInfoSend["typ"] = 115;
      jsonInfoSend["mode"] = ddsm_mode;
      jsonInfoSend["tor"] = ddsm_torque;
      jsonInfoSend["spd"] = ddsm_spd;
      jsonInfoSend["pos"] = ddsm_pos;
      jsonInfoSend["err"] = ddsm_error;
      String getInfoJsonString;
      serializeJson(jsonInfoSend, getInfoJsonString);
      Serial.println(getInfoJsonString);
      print_packet(data, 10);
    }
  }
}


void ddsm_fb() {
  if (ddsm_type == TYPE_DDSM115) {
    ddsm115_fb();
  } else if (ddsm_type == TYPE_DDSM210) {
    ddsm210_fb();
    Serial.println("210");
  }
}