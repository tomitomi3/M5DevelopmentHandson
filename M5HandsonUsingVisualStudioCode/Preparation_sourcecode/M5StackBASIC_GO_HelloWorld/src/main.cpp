#include <Arduino.h>
#include <M5Unified.h>

void setup(void)
{
	// 初期化
	auto cfg = M5.config();
	M5.begin(cfg);

	// HelloWorldの表示
	{
		M5.Display.setBrightness(128);

		if (M5.Display.width() < M5.Display.height())
		{
			M5.Display.setRotation(M5.Display.getRotation() ^ 1);
		}

		M5.Display.startWrite();

		// モニタ背景 M5.Lcd.fillScreen(TFT_BLACK) と等価
		auto bgColor = M5.Lcd.color888(0, 0, 0); // RGB指定
		M5.Lcd.fillScreen(bgColor);

		// 「HelloWorld」をセンタリングして表示
		String text1 = "Hello";
		String text2 = "World!";

		// 文字色とフォントサイズ
		M5.Lcd.setTextColor(TFT_WHITE);
		M5.Lcd.setTextSize(2);

		// 描画位置を決める
		int textWidth1 = M5.Lcd.textWidth(text1);
		int textWidth2 = M5.Lcd.textWidth(text2);
		int textHeight = M5.Lcd.fontHeight();

		int cursorX1 = (M5.Lcd.width() - textWidth1) / 2;
		int cursorX2 = (M5.Lcd.width() - textWidth2) / 2;

		int totalHeight = 2 * textHeight;
		int cursorY1 = (M5.Lcd.height() - totalHeight) / 2;
		int cursorY2 = cursorY1 + textHeight;

		// 描画
		M5.Lcd.setCursor(cursorX1, cursorY1);
		M5.Lcd.println(text1);
		M5.Lcd.setCursor(cursorX2, cursorY2);
		M5.Lcd.println(text2);

		M5.Display.endWrite();
	}
}

void loop(void)
{
	M5.update();
}
