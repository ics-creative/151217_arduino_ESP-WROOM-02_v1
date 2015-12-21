# ArduinoとESP-WROOM-02でLチカ
ICS MEDIA記事「[Arduinoと数百円のWi-Fiモジュールで爆安IoTをはじめよう](https://ics.media/entry/10457)」にて解説しています。

# 構成
Arduino UNO R3にESP-WROOM-02をWi-Fiモジュールとしてシリアル通信で接続。  
Webブラウザのボタンをタップすることにより、ON/OFF情報がPHPへ送信されPHPと同階層の「ledLog.txt」に値が保持されます。その値をArduinoから一定間隔(サンプルでは200ミリ秒)ごとに取得し、ONならLEDを点灯させるという仕組みです。

## フォルダー構成
```
151217_arduino_ESP-WROOM-02_v1
├── arduino
|   └── ESP-WROOM-02
|       └── ESP-WROOM-02.ino --- Arduinoスケッチ
└── html
|   ├── css -------------------- css
|   ├── index.html ------------- 操作用HTML
|   ├── js --------------------- JavaScript
|   ├── ledGet.php ------------- 値を保存するPHP
|   ├── ledLog.txt ------------- 値が保存されるテキストファイル
|   └── ledSet.php ------------- 保存された値を取得するPHP
|   
└── README.md ------------------ このドキュメントが書いているファイル
```