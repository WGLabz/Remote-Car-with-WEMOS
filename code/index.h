const char *HTML_CONTENT = R"=====(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Car Control</title>
    <!-- Materialize CSS -->
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/materialize/1.0.0/css/materialize.min.css">
    <!-- Font Awesome -->
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0-beta3/css/all.min.css">
    <style>
        body {
            background-color: #f8f9fa;
            font-family: 'Roboto', sans-serif;
        }

        .container {
            max-width: 400px;
            margin: 50px auto;
            position: relative;
        }

        h1 {
            text-align: center;
            margin-bottom: 30px;
        }

        .remote {
            border: 1px solid #6c757d;
            border-radius: 10px;
            padding: 16px;
            background-color: #ffffff;
            box-shadow: 0px 0px 20px rgba(0, 0, 0, 0.3);
            position: relative;
        }

        .direction-controls {
            display: flex;
            justify-content: space-between;
            margin-bottom: 20px;
        }

        .direction-btn {
            width: 60px;
            height: 60px;
            font-size: 24px;
            border: none;
            border-radius: 5px;
            background-color: #007bff;
            color: #fff;
        }

        .direction-btn:focus {
            outline: none;
        }

        .accelerator {
            width: 100%;
            margin-bottom: 20px;
            -webkit-appearance: none;
            height: 15px;
            border-radius: 5px;
            background: #6c757d;
            outline: none;
        }

        .accelerator::-webkit-slider-thumb {
            -webkit-appearance: none;
            width: 20px;
            height: 20px;
            border-radius: 50%;
            background: #007bff;
            cursor: pointer;
        }

        .battery {
            width: 100px;
            height: 20px;
            background-color: #e9ecef;
            border-radius: 5px;
            margin-bottom: 20px;
            position: absolute;
            top: 0;
            left: 50%;
            transform: translateX(-50%);
        }

        .battery-level {
            width: 75%;
            height: 100%;
            background-color: #007bff;
            border-radius: 5px;
        }

        .ws-status {
            position: absolute;
            top: 20px;
            right: 20px;
            color: #fff;
        }

        .headlight-btn {
            width: 100%;
            font-size: 18px;
            padding: 15px;
            border: none;
            border-radius: 5px;
            background-color: #007bff;
            color: #fff;
        }

        .led-icon {
            font-size: 24px;
            margin-right: 10px;
        }

        .led-on {
            color: yellow;
        }

        .led-off {
            color: gray;
        }

        .battery-container {
            width: 100px;
            height: 40px;
            border: 1px solid #a5a5a5;
            border-radius: 5px;
            position: relative;
        }

        .battery-level {
            width: calc(100% - 4px);
            height: calc(100% - 4px);
            background-color: #00ff95;
            border-radius: 3px;
            position: absolute;
            bottom: 2px;
            left: 2px;
        }

        .label-text {
            margin-top: 8px;
            color: rgb(90, 91, 90);
        }
    </style>
</head>

<body>
    <div class="container">
        <div class="row remote " style="margin-bottom: 16px;">
            <div class="col s4 center-align">
                <div class="battery-container">
                    <div class="battery-level" style="width: 75%;" id="bat_percentage"></div>
                </div>
                <span class="label-text" id="bat_txt">0% | 0V</span>
            </div>
            <div class="col s4 center-align">
                <button class="btn-floating waves-effect waves-light small-btn " id="btn-light" onclick="togglelight()">
                    <i class="fas fa-lightbulb" id="light"></i></button><br />
                <span class="label-text" id="light_status">Off</span>
            </div>
            <div class="col s4 center-align">
                <button class="btn-floating waves-effect waves-light small-btn" style="background-color: red;"
                    id="wc_conn" onclick="wc_onclick();">
                    <i class="fas fa-wifi"></i></button><br />
                <span class="label-text" id="ws_status">Disconnected</span>
            </div>
        </div>

        <div class="remote " style="margin-bottom: 16px;">
            <div class="direction-controls" id="container">
                <button class="btn-floating waves-effect waves-light direction-btn" id="0" onclick="motion(1)"><i
                        class="fas fa-arrow-up"></i></button>
                <button class="btn-floating waves-effect waves-light direction-btn" id="1" onclick="motion(4)"><i
                        class="fas fa-arrow-left"></i></button>
                <button class="btn-floating waves-effect waves-light direction-btn" id="2" onclick="motion(8)"><i
                        class="fas fa-arrow-right"></i></button>
            </div>
            <button class="btn-floating waves-effect waves-light direction-btn" id="3" onclick="motion(2)"><i
                    class="fas fa-arrow-down"></i></button>
            <button class="btn-floating waves-effect waves-light direction-btn" style="background-color: red;" id="2"
                onclick="motion(0)"><i class="fas fa-stop"></i></button>


        </div>
        <div class="row remote " style="margin-bottom: 16px;">
            <div class="col s4 center-align"><button class="btn-floating waves-effect waves-light small-container"
                    id="3" onclick="speeddown()"><i class="fas fa-minus"></i></button>
            </div>
            <div class="col s4 center-align"> <button class="btn-floating waves-effect waves-light small-container" id="speed" disabled>4</button>
            </div>
            <div class="col s4 center-align">
                <button class="btn-floating waves-effect waves-light small-container" id="2" onclick="speedup()"><i
                        class="fas fa-plus"></i></button>
            </div>
        </div>


    </div>

    <!-- jQuery -->
    <script src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script>
    <!-- Materialize JS -->
    <script src="https://cdnjs.cloudflare.com/ajax/libs/materialize/1.0.0/js/materialize.min.js"></script>
    <!-- Font Awesome -->
    <script src="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0-beta3/js/all.min.js"></script>
    <script>
        var CMD_STOP = 0;
        var CMD_FORWARD = 1;
        var CMD_BACKWARD = 2;
        var CMD_LEFT = 4;
        var CMD_RIGHT = 8;

        var ws = null;
        function ws_onmessage(e_msg) {
            e_msg = e_msg || window.event; // MessageEvent
            console.log(e_msg)
            var jsonData = JSON.parse('' + e_msg.data);

            var batteryPercent = jsonData.per;
            console.log(jsonData)
            document.getElementById('bat_percentage').setAttribute("style", 'width:' + batteryPercent + 'px');
            document.getElementById("speed").innerHTML = jsonData.speed;
            var light = jsonData.light;

            if (light == 1)
                document.getElementById('light').setAttribute("style", 'color:yellow');
            else
                document.getElementById('light').setAttribute("style", 'color:white');

                document.getElementById('light_status').innerHTML = light == 1 ? 'ON' : 'OFF';
            document.getElementById('bat_txt').innerHTML = `${(batteryPercent).toFixed(0)}% | ${ (jsonData.voltage).toFixed(1)}V`;
            // alert("msg : " + e_msg.data + " " + bat_percentage);
        }


        function ws_onopen() {
            document.getElementById("wc_conn").setAttribute("style", 'background-color: green')
            send_command(0);
        }
        function ws_onclose() {
            document.getElementById("wc_conn").setAttribute("style", 'background-color: red')
            console.log("socket was closed");
            ws.onopen = null;
            ws.onclose = null;
            ws.onmessage = null;
            ws = null;
        }
        function wc_onclick() {
            if (ws == null) {
                ws = new WebSocket("ws://" + window.location.host + ":81");
                ws.onopen = ws_onopen;
                ws.onclose = ws_onclose;
                ws.onmessage = ws_onmessage;
            }
            else
                ws.close();
        }
        function motion(direction) {
            send_command(direction);
            if (direction == 4 || direction == 8) {
                setTimeout(function () {
                    send_command(3)
                }, 200);

            }
        }

        function togglelight() { send_command(9) }
        function speeddown() { send_command(7) }
        function speedup() { send_command(6) }
        function send_command(cmd) {
            if (ws != null)
                if (ws.readyState == 1)
                    ws.send(cmd + "\r\n");
        }

    </script>
</body>

</html>
)=====";
