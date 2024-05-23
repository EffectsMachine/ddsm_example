#define FB_MOTOR 20010
#define FB_INFO	 20011

// {"T":10000,"id":1}
#define CMD_DDSM_STOP	10000

// {"T":10010,"id":1,"cmd":50,"act":3}
#define CMD_DDSM_SPEED_CTRL 10010

// {"T":10011,"id":2}
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
#define CMD_CHANGE_MODE	10012


// {"T":10031}
// get id from ddsm 115
// there must be only one ddsm connected
// when you check
#define CMD_DDSM_ID_CHECK	10031

// get other info
// {"T":10032,"id":1}
#define CMD_DDSM_INFO	10032

// {"T":11001,"time":2000}
#define CMD_HEARTBEAT_TIME	11001

// type:
//		115 - ddsm115 [default]
//		210 - ddsm210 		
// {"T":11002,"type":115}
#define CMD_TYPE	11002