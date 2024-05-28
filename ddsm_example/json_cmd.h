#define FB_MOTOR 20010
#define FB_INFO	 20011

// {"T":10000,"id":1}
// ddsm_stop(id)
#define CMD_DDSM_STOP	10000

// {"T":10010,"id":1,"cmd":50,"act":3}
// ddsm_ctrl(id, cmd, act)
#define CMD_DDSM_CTRL 10010

// {"T":10011,"id":2}
// ddsm_change_id(id)
#define CMD_DDSM_CHANGE_ID	10011

// ddsm115
// 1: current loop
// 2: speed loop
// 3: position loop
// ddsm210
// 0: open loop
// 2: speed loop
// 3: position loop
// {"T":10012,"id":1,"mode":2}
// ddsm_change_mode(id, mode)
#define CMD_CHANGE_MODE	10012


// {"T":10031}
// get id from ddsm 115
// there must be only one ddsm connected
// when you check
// ddsm_id_check()
#define CMD_DDSM_ID_CHECK	10031

// get other info
// {"T":10032,"id":1}
// ddsm_get_info(id)
#define CMD_DDSM_INFO	10032

// {"T":11001,"time":2000}
// {"T":11001,"time":-1}
// set_heartbeat_time(time_ms)
#define CMD_HEARTBEAT_TIME	11001

// type:
//		115 - ddsm115 [default]
//		210 - ddsm210 		
// {"T":11002,"type":115}
// set_ddsm_type(type)
#define CMD_TYPE	11002


// === === === wifi settings. === === ===

// config the wifi mode on boot.
// 0 - off
// 1 - ap
// 2 - sta
// 3 - ap+sta
// {"T":10401,"cmd":3}
#define CMD_WIFI_ON_BOOT 10401

// config ap mode.
// {"T":10402,"ssid":"ESP32-AP","password":"12345678"}
#define CMD_SET_AP  10402

// config sta mode.
// {"T":10403,"ssid":"EM","password":"bubu6788"}
#define CMD_SET_STA 10403

// config ap/sta mode.
// {"T":10404,"ap_ssid":"ESP32-AP","ap_password":"12345678","sta_ssid":"JSBZY-2.4G","sta_password":"waveshare0755"}
#define CMD_WIFI_APSTA   10404

// get wifi info.
// {"T":10405}
#define CMD_WIFI_INFO    10405

// create a wifiConfig.json file
// from the args already be using.
// {"T":10406}
#define CMD_WIFI_CONFIG_CREATE_BY_STATUS 10406

// create a wifiConfig.json file
// from the args input.
// {"T":10407,"mode":3,"ap_ssid":"ESP32-AP","ap_password":"12345678","sta_ssid":"JSBZY-2.4G","sta_password":"waveshare0755"}
#define CMD_WIFI_CONFIG_CREATE_BY_INPUT 10407

// disconnect wifi.
// {"T":10408}
#define CMD_WIFI_STOP 10408


// === === === esp32 settings. === === ===

// esp-32 ctrl.
// reboot device.
// {"T":600}
#define CMD_REBOOT 600

// get the size of free flash space
// {"T":601}
#define CMD_FREE_FLASH_SPACE 601

// reset boot mission.
// {"T":603}
#define CMD_RESET_WIFI_SETTINGS 603

// if there is something wrong with wifi funcs, clear the nvs.
// {"T":604}
#define CMD_NVS_CLEAR 604