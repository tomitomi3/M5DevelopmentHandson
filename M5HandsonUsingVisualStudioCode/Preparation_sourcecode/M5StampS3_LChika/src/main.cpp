#include <Arduino.h>
#include <M5Unified.h>
#include <FastLED.h>

CRGB leds[1];

void setup()
{
	// 初期化
	auto cfg = M5.config();
	M5.begin(cfg);

	// ボード識別
	// https://github.com/m5stack/M5Unified/blob/8b25496e8026935b0fec8bf424fdca9158c79d28/examples/Basic/HowToUse/HowToUse.ino#L257
	switch (M5.getBoard())
	{
#if defined(CONFIG_IDF_TARGET_ESP32S3)
	case m5::board_t::board_M5StampS3:
		FastLED.addLeds<WS2812, GPIO_NUM_21, GRB>(leds, 1);
		break;
	case m5::board_t::board_M5AtomS3:
		FastLED.addLeds<WS2812, GPIO_NUM_35, GRB>(leds, 1);
		break;
	case m5::board_t::board_M5Dial:
		FastLED.addLeds<WS2812, GPIO_NUM_21, GRB>(leds, 1);
		break;
#elif defined(CONFIG_IDF_TARGET_ESP32C3)
#else
	case m5::board_t::board_M5Stack:
		break;
	case m5::board_t::board_M5StickC:
		break;
	case m5::board_t::board_M5StickCPlus:
		break;
#endif
	default:
		break;
	}
}

bool state;

void loop()
{
	M5.update();

	state ^= M5.BtnA.wasPressed();
	if(state)
	{
		leds[0] = CRGB(64, 0, 0);
	}
	else
	{
		leds[0] = CRGB(0, 64, 64);
	}

	FastLED.show(); // フルカラーLED指定色で点灯
	M5.delay(50);
}
