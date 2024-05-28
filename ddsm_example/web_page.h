const char index_html[] PROGMEM = R"rawliteral(
<!doctype html>
<html>
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1.0">
<title>DDSM Driver HAT</title>
<style type="text/css">
    
    body {
        background-image: linear-gradient(#3F424F, #1E212E);
        background-image: -o-linear-gradient(#3F424F, #1E212E);
        background-image: -moz-linear-gradient(#3F424F, #1E212E);
        background-image: -webkit-linear-gradient(#3F424F, #1E212E);
        background-image: -ms-linear-gradient(#3F424F, #1E212E);
        font-family: "roboto",helt "sans-serif";
        font-weight: lighter;
        color: rgba(216,216,216,0.8);
        background-size: cover;
        background-position: center 0;
        background-attachment: fixed;
        color: rgba(255,255,255,0.6);
        border: 0px;
        margin: 0;
        padding: 0;
        font-size: 14px;
    }
    main{
        width: 516px;
        margin: auto;
        margin-bottom: 80px;
    }
    section > div{
        width: 516px;
    }
    button {
        -webkit-touch-callout: none;
        -webkit-user-select: none;
        -khtml-user-select: none;
        -moz-user-select: none;
        -ms-user-select: none;
        user-select: none;
    }
    .btn-all, .btn-of, .btn-num, .btn-num-lr, .servo-btn-num, .btn-stop, .btn-set{cursor: pointer}
    .tittle-h2{
        text-align: center;
        font-weight: normal;
        font-size: 1.8em;
        color: rgba(255,255,255,0.8);
        text-transform: uppercase;
    }
    .set-btn-frame{
        display: flex;
        justify-content: space-between;
        align-items: flex-end;
    }
    .set-btn-frame-i{
        width: 360px;
        display: inline-flex;
        justify-content: space-between;
        text-align: center;
    }
    .set-btn-sections{width: 48px;}
    .btn-num{
        width: 48px;
        height: 48px;
        margin: 1px 0 0 0;
        font-size: 14px;
        font-weight: lighter;
    }
    .btn-num-lr{
        width: 48px;
        height: 46px;
        font-size: 14px;
    }
    .btn-num-up{border-radius: 4px 4px 0 0}
    .btn-num-down{border-radius: 0 0 4px 4px}
    .btn-num-bg{
        background-color: rgba(255,255,255,0.06);
        border: none;
        color: rgba(255,255,255,0.5);
    }
    .btn-num-bg:hover{background-color: rgba(255,255,255,0.02);}
    .btn-all, .btn-of{
        background-color: rgba(164,169,186,0.25);
        border: none;
        border-radius: 4px;
        font-size: 14px;
        color: rgba(255,255,255,0.5);
        font-weight: lighter;
    }
    .btn-of-active{
        background-color: rgba(38,152,234,0.1);
        color: #1EA1FF;
        border: 1px solid #1EA1FF;
        border-radius: 4px;
        font-size: 14px;
        
    }
    .btn-all:hover, .btn-of:hover{background-color:rgba(164,169,186,0.15);}
    .btn-main-l{
        width: 126px;
        height: 97px;
    }
    .init-posit{
        vertical-align: bottom;
    }
    .record-mum-set > div {
        display: flex;
        justify-content: space-between;
        margin-top: 54px;
    }
    .record-mum-set > div > div:last-child {
        width: 320px;
        display: flex;
        justify-content: space-between;
        align-items: flex-start;
    }
    .record-mum-set > div > div:last-child > div {
        display: flex;
        width: 164px;
        border: 1px solid rgba(206,206,206,0.15);
        border-radius: 4px;
    }
    .num-insert{
        background-color: rgba(0,0,0,0.01);
        border: 0px;
        width: 68px;
        text-align: center;
        color: rgba(255,255,255,0.8);
        font-size: 14px;
        font-weight: lighter;
    }
    .btn-main-s{
        width: 126px;
        height: 48px;
    }
    .two-btn > div{
        display: flex;
        justify-content: space-between;
        margin: 10px 0;
    }
    .btn-main-m{
        width: 49%;
        height: 48px;
    }
    .two-btn1{
        border-top:1px dashed rgba(216,216,216,0.24) ;
        border-bottom:1px dashed rgba(216,216,216,0.24) ;
        padding: 30px 0;
        margin: 30px 0;
    }
    .Servo-set > div{
        display: flex;
        justify-content: space-between;
    }
    .Servo-set > P{
        font-size: 1.5em;
        text-align: center;
    }
    .servo-btn-num{
        height: 48px;
        width: 126px;
        border-radius: 4px;
        font-size: 14px;
        font-weight: lighter;
    }
    .servo-btn-num + button{margin-left: 30px;}
    .Servo-set{margin: 30px 0;}
    .sec-5{
        position: fixed;
        bottom: 0px;
        width: 100%;
        display: flex;
        justify-content: center;
        padding: 40px 0;
        background-image: linear-gradient(rgba(30,33,46,0),rgba(30,33,46,1));
        
    }
    .sec-5 button{margin: 0 14px;}
    .btn-stop{
        width: 204px;
        height: 48px;
        background-color: rgba(181,104,108,1);
        color: white;
        border-radius: 1000px;
        border: none;
    }
    .btn-set{
        width: 48px;
        height: 48px;
        background-color: rgba(115,134,151,1);
        border-radius: 1000px;
        border: none;
    }
    .btn-set:hover{background-color: rgba(115,134,151,0.5);}
    .record-tt{
        color: rgba(255,255,255,0.5);
        font-size: 14px;
        
    }
    .record-height{height: 1px;}
    .sec-infotext{
        font-size: 14px;
        text-align: center;
        color: rgba(255,255,255,0.4)
    }
    .btn-stop:hover{background-color: rgba(181,104,108,0.5);}
    input::-webkit-outer-spin-button,input::-webkit-inner-spin-button {
        -webkit-appearance: none;
    }
    input[type='number']{
        -moz-appearance: textfield;
    }
    .sec-infotext p{word-break:break-all;}
    .feedb-p textarea{
        width: 100%;
        height: 80px;
        padding: 10px;
        background-color: rgba(0,0,0,0);
        border: 1px solid rgba(194,196,201,0.15);
        border-radius: 4px;
        color: rgba(255, 255, 255, 0.8);
        font-size: 1.2em;
        resize: vertical;
        margin-bottom: 10px;
    }
    .feedb-p > div {
        display: flex;
        justify-content: center;
    }
    .info-box{
        /* border: 1px solid rgba(194,196,201,0.15); */
        padding: 10px;
        margin: 10px 0;
        border-radius: 4px;
        background-color: rgba(255,255,255,0.06);
        border: none;
        color: rgba(255,255,255,0.5);
    }
    .info-box p{
        margin: 0;
        word-break: break-all;
    }
    .info-box > div{margin-right: 20px;}
    .json-cmd-info{cursor: pointer;}
    .json-cmd-info:hover{background-color: rgba(255,255,255,0.02);}
    .w-btn{
        background-color: rgba(0,0,0,0);
        border: 0;
        color: inherit;
    }
    .cmd-value{color: rgba(255,255,255,0.8);}
    @media screen and (min-width: 768px) and (max-width: 1200px){
        main{
            width: 516px;
            display: block;
            margin-bottom: 150px;
        }
        main section{
            margin-bottom: 30px;
        }
        .record-mum-set > div{margin-top: 30px;}
        .sec-2{padding-bottom: 30px;}
    }
    @media screen and (min-width: 360px) and (max-width: 767px){
        main{
            width: 94vw;
            display: block;
        }
        section > div{width: auto;}
        .set-btn-frame{
            display: block;
        }
        .set-btn-frame-i{width: 100%;}
        .btn-main-l{
            width: 100%;
            height: 48px;
        }
        .init-posit{
            margin-top: 30px;
        }
        .record-mum-set > div{display: block;}
        .record-mum-set > div > div:last-child{
            width: 100%;
        }
        .sec-5 button{
            margin: 0 4px;
        }
        .two-btn button:first-child{margin-right: 10px;}
        .servo-btn-num{
            flex: 1;
        }
        .btn-main-s{width: 33.333%;}
        .servo-btn-num + button{margin-left: 10px;}
        .btn-main-m{
            flex: 1;
            width: auto;
        }
        .record-mum-set > div{margin:  30px 0}
        main section{
            margin-bottom: 30px;
        }
        .record-mum-set > div{margin-top: 30px;}
        .record-height{display: none;}
    }
</style>
</head>

<body>
    <main>
        <div>
            <section>
                <div>
                    <div class="fb-input-info">
                        <h2 class="tittle-h2">Infomation</h2>
                        <div class="sec-infotext">
                            <p id="GetInfoText">Json infomation shows here.</p>
                        </div>
                        <div class="feedb-p">
                            <div>
                                <textarea id="jsonData" placeholder="Input json cmd here." rows="4"></textarea>
                            </div>
                            <div><button class="btn-of btn-main-m btn-all-bg" onclick="jsonSend();">SEND</button></div>
                        </div>
                        <div class="Servo-set">
                            <p>WIFI SETTINGS</p>

                            <div class="info-box json-cmd-info">
                                <div>
                                    <p>CMD_WIFI_CONFIG_CREATE_BY_INPUT</p>
                                    <p class="cmd-value">{"T":10407,"mode":3,"ap_ssid":"ESP32-AP","ap_password":"12345678","sta_ssid":"yourWifi","sta_password":"yourPassword"}</p>
                                </div>
                                <button class="w-btn">INPUT</button>
                            </div>

                            <p>DDSM CTRL</p>

                            <div class="info-box json-cmd-info">
                                <div>
                                    <p>CMD_TYPE_DDSM115</p>
                                    <p class="cmd-value">{"T":11002,"type":115}</p>
                                </div>
                                <button class="w-btn">INPUT</button>
                            </div>
                            <div class="info-box json-cmd-info">
                                <div>
                                    <p>CMD_TYPE_DDSM210</p>
                                    <p class="cmd-value">{"T":11002,"type":210}</p>
                                </div>
                                <button class="w-btn">INPUT</button>
                            </div>
                            <div class="info-box json-cmd-info">
                                <div>
                                    <p>CMD_DDSM_CTRL</p>
                                    <p class="cmd-value">{"T":10010,"id":1,"cmd":50,"act":3}</p>
                                </div>
                                <button class="w-btn">INPUT</button>
                            </div>
                            <div class="info-box json-cmd-info">
                                <div>
                                    <p>CMD_DDSM_CHANGE_ID</p>
                                    <p class="cmd-value">{"T":10011,"id":1}</p>
                                </div>
                                <button class="w-btn">INPUT</button>
                            </div>
                            <div class="info-box json-cmd-info">
                                <div>
                                    <p>CMD_DDSM_ID_CHECK</p>
                                    <p class="cmd-value">{"T":10031}</p>
                                </div>
                                <button class="w-btn">INPUT</button>
                            </div>
                            <div class="info-box json-cmd-info">
                                <div>
                                    <p>CMD_CHANGE_MODE</p>
                                    <p class="cmd-value">{"T":10012,"id":1,"mode":2}</p>
                                </div>
                                <button class="w-btn">INPUT</button>
                            </div>
                            <div class="info-box json-cmd-info">
                                <div>
                                    <p>CMD_DDSM_INFO</p>
                                    <p class="cmd-value">{"T":10032,"id":1}</p>
                                </div>
                                <button class="w-btn">INPUT</button>
                            </div>
                            <div class="info-box json-cmd-info">
                                <div>
                                    <p>CMD_HEARTBEAT_TIME</p>
                                    <p class="cmd-value">{"T":11001,"time":2000}</p>
                                </div>
                                <button class="w-btn">INPUT</button>
                            </div>

                            <p>ESP32 SYS CTRL</p>
                            <div class="info-box json-cmd-info">
                                <div>
                                    <p>CMD_REBOOT</p>
                                    <p class="cmd-value">{"T":600}</p>
                                </div>
                                <button class="w-btn">INPUT</button>
                            </div>
                            <div class="info-box json-cmd-info">
                                <div>
                                    <p>CMD_FREE_FLASH_SPACE</p>
                                    <p class="cmd-value">{"T":601}</p>
                                </div>
                                <button class="w-btn">INPUT</button>
                            </div>
                            <div class="info-box json-cmd-info">
                                <div>
                                    <p>CMD_RESET_BOOT_MISSION</p>
                                    <p class="cmd-value">{"T":603}</p>
                                </div>
                                <button class="w-btn">INPUT</button>
                            </div>
                            <div class="info-box json-cmd-info">
                                <div>
                                    <p>CMD_NVS_CLEAR</p>
                                    <p class="cmd-value">{"T":604}</p>
                                </div>
                                <button class="w-btn">INPUT</button>
                            </div>
                        </div>
                    </div>
                </div>
            </section>
        </div>
    </main>
    <script>
        document.onkeydown = function (event) {
            var e = event || window.event || arguments.callee.caller.arguments[0];
            if (e && e.keyCode == 13) {
                // alert ("Enter down");
                jsonSend();
            }
        }
        document.addEventListener('DOMContentLoaded', function() {
            var jsonData = document.getElementById('jsonData');
            var infoDiv = document.querySelectorAll('.json-cmd-info');
            for (var i = 0; i < infoDiv.length; i++) {
                var element = infoDiv[i];
                element.addEventListener('click', function() {
                    var cmdValue = this.querySelector('.cmd-value');
                    if (cmdValue) {
                    var cmdValueText = cmdValue.textContent;
                    jsonData.value = cmdValueText;
                    }
                });
            }
        });

        function jsonSend() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                  document.getElementById("GetInfoText").innerHTML =
                  this.responseText;
                }
            };
            xhttp.open("GET", "js?json="+document.getElementById('jsonData').value, true);
            xhttp.send();
        }

        function webCtrl(inputJoint, inputCmd) {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                  document.getElementById("GetInfoText").innerHTML =
                  this.responseText;
                }
            };
            var jsonData = JSON.stringify({"T": 10008, "joint": inputJoint, "cmd": inputCmd});
            xhttp.open("GET", "js?json="+encodeURIComponent(jsonData), true);
            xhttp.send();
        }

        function ledCmd(inputCmd) {
            var jsonCmd = {
                "T":114,
                "led":inputCmd
            }
            var jsonString = JSON.stringify(jsonCmd);
            var xhr = new XMLHttpRequest();
            xhr.open("GET", "js?json=" + jsonString, true);
            xhr.send();
            getData();
        }

        function dynamicCmd(inputCmd) {
            var jsonCmd = {
                "T":112,
                "mode":inputCmd,
                "b":60,
                "s":110,
                "e":50,
                "h":50
            }
            var jsonString = JSON.stringify(jsonCmd);
            var xhr = new XMLHttpRequest();
            xhr.open("GET", "js?json=" + jsonString, true);
            xhr.send();
            getData();
        }

        function torqueCmd(inputCmd) {
            var jsonCmd = {
                "T":210,
                "cmd":inputCmd
            }
            var jsonString = JSON.stringify(jsonCmd);
            var xhr = new XMLHttpRequest();
            xhr.open("GET", "js?json=" + jsonString, true);
            xhr.send();
            getData();
        }

        function cmdInit() {
            var jsonCmd = {
                "T":102,
                "base":0,
                "shoulder":0,
                "elbow":1.5707965,
                "hand":3.1415926,
                "spd":0,
                "acc":0
            }
            var jsonString = JSON.stringify(jsonCmd);
            var xhr = new XMLHttpRequest();
            xhr.open("GET", "js?json=" + jsonString, true);
            xhr.send();
            getData();
        }

        function cmdSend(inputT, inputA, inputB) {
            var jsonCmd = {
                "T": 123,
                "m": inputT,
             "axis": inputA,
              "cmd": inputB,
              "spd": 10
            }
            var jsonString = JSON.stringify(jsonCmd);
            var xhr = new XMLHttpRequest();
            xhr.open("GET", "js?json=" + jsonString, true);
            xhr.send();
            getData();
        }

        function getData() {
            var jsonCmd = {
                "T": 105
            }
            var jsonString = JSON.stringify(jsonCmd);
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                  document.getElementById("GetInfoText").innerHTML = this.responseText;
                  var jsonResponse = JSON.parse(this.responseText);

                  document.getElementById("anglectrl-t1").innerHTML = jsonResponse.b.toFixed(2);;
                  document.getElementById("anglectrl-t2").innerHTML = jsonResponse.s.toFixed(2);;
                  document.getElementById("anglectrl-t3").innerHTML = jsonResponse.e.toFixed(2);;
                  document.getElementById("anglectrl-t4").innerHTML = jsonResponse.t.toFixed(2);;

                  document.getElementById("coordCtrl-t1").innerHTML = jsonResponse.x.toFixed(2);
                  document.getElementById("coordCtrl-t2").innerHTML = jsonResponse.y.toFixed(2);
                  document.getElementById("coordCtrl-t3").innerHTML = jsonResponse.z.toFixed(2);
                  document.getElementById("coordCtrl-t4").innerHTML = jsonResponse.t.toFixed(2);
                }
            };
            xhttp.open("GET", "js?json=" + jsonString, true);
            xhttp.send();
        }

        function getDevInfo() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                  document.getElementById("GetInfoText").innerHTML = this.responseText;
                }
            };
            xhttp.open("GET", "getDevInfo", true);
            xhttp.send();
        }

        function opera(x, y) {
            var rs = new Number(document.getElementById(x).value);

            if (y) {
                document.getElementById(x).value = rs + 1;
            } else if( rs >0) {
                document.getElementById(x).value = rs - 1;
            }
       }
        function opera1(x, y) {
            var rs = new Number(document.getElementById(x).value);

            if (y) {
                document.getElementById(x).value = rs + 1;
            } else if( rs >-1) {
                document.getElementById(x).value = rs - 1;
            }
       }
        function opera100(x, y) {
            var rs = new Number(document.getElementById(x).value);

            if (y) {
                document.getElementById(x).value = rs + 100;
            } else if( rs >0) {
                document.getElementById(x).value = rs - 100;
            }
       }
    </script>
</body>
</html>
)rawliteral";