#include <Arduino.h>
#include <M5Unified.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char *ssid = "";			 // Wi-FiのSSID
const char *password = ""; // Wi-Fiのパスワード

// LINE Notify URL
const char *LINE_NOTIFY_URL = "https://notify-api.line.me/api/notify";
// LINE Notifyのトークン
const char *LINE_NOTIFY_TOKEN = "";

void setup()
{
	// 初期化
	auto cfg = M5.config();
	M5.begin(cfg);

	// WiFiの初期化
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(500);
		M5.Lcd.print(".");
	}
	M5.Lcd.println("Connected!");

	// IPアドレス表示
	IPAddress ip = WiFi.localIP();
	M5.Lcd.println("IP Address:");
	M5.Lcd.println(ip);
}

void loop()
{
	M5.update();

	// WiFiが接続されていない場合はloopを回す
	if (WiFi.status() != WL_CONNECTED)
		return;

	// ボタン確認
	if (M5.BtnA.wasPressed())
	{
		HTTPClient http;

		// メッセージ
		String myMessage("PushBtn");

		// POST
		http.begin(LINE_NOTIFY_URL);
		http.addHeader("Authorization", "Bearer " + String(LINE_NOTIFY_TOKEN));
		http.addHeader("Content-Type", "application/x-www-form-urlencoded");
		int httpCode = http.POST("message=" + myMessage);
		String payload = http.getString();

		M5.Lcd.fillScreen(TFT_BLACK);
		M5.Lcd.setCursor(0, 0);
		M5.Lcd.println(payload);

		http.end();
	}

	// M5リセット
	if (M5.BtnB.wasPressed())
		ESP.restart();

	delay(10);
}
