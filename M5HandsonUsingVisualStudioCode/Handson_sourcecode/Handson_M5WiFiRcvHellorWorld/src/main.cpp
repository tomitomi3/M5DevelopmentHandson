#include <Arduino.h>
#include <M5Unified.h>
#include <WiFi.h>
#include <WiFiUdp.h>

const char *ssid = "";			 // Wi-FiのSSID
const char *password = ""; // Wi-Fiのパスワード

WiFiUDP udp;
unsigned int localUdpPort = 12345;

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
	
	// UDPサーバーを開始
	udp.begin(localUdpPort);
}

void loop()
{
	// WiFiが接続されていない場合はloopを回す
	if (WiFi.status() != WL_CONNECTED)
	{
		return;
	}

	// UDP 受信
	int rcvPacketSize = udp.parsePacket();
	if (rcvPacketSize)
	{
		// UDP 1バイト受信
		char receivedData = 0;
		auto nokoriBufferlen = udp.read(&receivedData, 1);

		// UDP 受信後 バッファをクリア
		udp.flush();

		// 黒背景
		M5.Lcd.startWrite();
		M5.Lcd.fillScreen(TFT_BLACK);

		// 受信データにより処理を変更
		if (receivedData == '1') // 0x31 = 49
		{
			// 文字色とフォントサイズ
			M5.Lcd.setTextColor(TFT_WHITE);
			M5.Lcd.setTextSize(2);

			// 描画
			M5.Lcd.setCursor(0, 0);
			M5.Lcd.println("Hello");
			M5.Lcd.setCursor(0, 20);
			M5.Lcd.println("World");
		}
		else if (receivedData == '2') // 0x31 = 49
		{
			M5.Lcd.fillScreen(TFT_BLUE);
		}
		M5.Lcd.endWrite();
	}

	delay(10);
}
