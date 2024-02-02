#include <Arduino.h>
#include <M5Unified.h>

void setup()
{
	// 初期化
	auto cfg = M5.config();
	M5.begin(cfg);
}

void loop()
{
	// ボタン入力を更新するために呼び出す
	M5.update();

	M5.Display.startWrite();

	if (M5.BtnA.isPressed())
	{
		// ボタンが押されている
		// 文字色とフォントサイズ
		auto fColor = M5.Lcd.color888(255, 255, 255);
		M5.Lcd.setTextColor(fColor); // TFT_WHITE というマクロもある
		M5.Lcd.setTextSize(2);

		// 描画
		M5.Lcd.setCursor(0, 0);
		M5.Lcd.println("Hello");
		M5.Lcd.setCursor(0, 20);
		M5.Lcd.println("World");
	}
	else
	{
		// ボタンが押されていない
		// 背景色 黒で塗りつぶす
		auto bgColor = M5.Lcd.color888(0, 0, 0);
		M5.Lcd.fillScreen(bgColor);
	}

	M5.Display.endWrite();
}
