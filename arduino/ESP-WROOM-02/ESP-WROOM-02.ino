#include "ESP8266.h"
#include <SoftwareSerial.h>

// Wi-Fi SSID
#define SSID        "SSIDを入力してください"
// Wi-Fi PASSWORD
#define PASSWORD    "PASSWORDを入力してください"
// サーバーのホスト名
#define HOST_NAME   "ホスト名を入力してください"
// ポート番号
#define HOST_PORT   80
 
SoftwareSerial mySerial(12, 11); /* RX:12, TX:11 */
ESP8266 wifi(mySerial);

/**
 * 初期設定
 */
void setup(void)
{
  // デジタル13番ピンを出力として設定
  pinMode(13, OUTPUT);
  
  Serial.begin(9600);
  Serial.print("setup begin\r\n");

  Serial.print("FW Version:");
  Serial.println(wifi.getVersion().c_str());

  if (wifi.setOprToStationSoftAP()) {
    Serial.print("to station + softap ok\r\n");
  } else {
    Serial.print("to station + softap err\r\n");
  }

  if (wifi.joinAP(SSID, PASSWORD)) {
    Serial.print("Join AP success\r\n");
    Serial.print("IP:");
    Serial.println( wifi.getLocalIP().c_str());
  } else {
    Serial.print("Join AP failure\r\n");
  }

  if (wifi.disableMUX()) {
    Serial.print("single ok\r\n");
  } else {
    Serial.print("single err\r\n");
  }
 
  Serial.print("setup end\r\n");
}

/**
 * ループ処理
 */
void loop(void)
{
  uint8_t buffer[512] = {0};

  // TCPで接続
  if (wifi.createTCP(HOST_NAME, HOST_PORT)) {
    Serial.print("create tcp ok\r\n");
  } else {
    Serial.print("create tcp err\r\n");
  }

  // サーバーへ渡す情報
  // 例 http://test.co.jp/arduino-esp/ledGet.php
  char *sendStr = "GET /arduino-esp/ledGet.php HTTP/1.0\r\nHost: test.co.jp\r\nUser-Agent: arduino\r\n\r\n";

  wifi.send((const uint8_t*)sendStr, strlen(sendStr));

  //サーバからの文字列を入れるための変数
  String resultCode = "";

  // 取得した文字列の長さ
  uint32_t len = wifi.recv(buffer, sizeof(buffer), 10000);

  // 取得した文字数が0でなければ
  if (len > 0) {
    for(uint32_t i = 0; i < len; i++) {
      resultCode += (char)buffer[i];
    }

    // lastIndexOfでresultCodeの最後から改行を探す
    int lastLF = resultCode.lastIndexOf('\n');

    // resultCodeの長さを求める
    int resultCodeLength = resultCode.length();
  
    // substringで改行コードの次の文字から最後までを求める
    String resultString = resultCode.substring(lastLF+1, resultCodeLength);

    // 前後のスペースを取り除く
    resultString.trim();

    // 取得した文字列がONならば
    if(resultString == "ON") {
      digitalWrite(13, HIGH);
    } else {
      digitalWrite(13, LOW);
    }
  }

  // 200ミリ秒待つ
  delay(200);
}