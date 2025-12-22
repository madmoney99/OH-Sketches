/*
F/A-18 Brake Pressure Gauge — GC9A01 1.28" Round TFT (240x240) + ESP32 (originall based on Tanarg board)
Library: TFT_eSPI (configure GC9A01 + pins in User_Setup.h)

Stable ISR-safe version:
- DCS-BIOS callbacks only store new values and mark dirty (no SPI drawing)
- Sprites created once and reused (vs create/delete churn)
- 30 FPS render throttle + watchdog keeps screen alive while DCS active
*/

#define USE_HSPI_PORT  // Ensure SPI2_HOST on ESP32-S3 via TFT_eSPI

#include <Arduino.h>
#include <TFT_eSPI.h>

#define DCSBIOS_DEFAULT_SERIAL
#define DCSBIOS_DISABLE_SERVO
#include <DcsBios.h>

#include "brakePressBackground.h"  // uint16_t brakePressBackground[240*240]
#include "brakePressNeedle.h"      // uint16_t brakePressNeedle[15*150]

// ── Display constants ──────────────────────────────────────────────────────────
static const uint8_t  COLOR_DEPTH = 16;
static const uint16_t CANVAS_W = 240, CANVAS_H = 240;

// ── TFT & Sprites ──────────────────────────────────────────────────────────────
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprBack(&tft);   
TFT_eSprite sprNeedle(&tft);

// ── DCS state ─────────────────────────────────────────────────────────────────
static volatile uint16_t rawBrake = 0;
static volatile bool     dirtyBrake = true;
static volatile uint32_t lastDcsMs = 0;

// ── Render scheduler ───────────────────────────────────────────────────────────
static uint32_t lastFrameMs = 0;
static const uint32_t FRAME_INTERVAL_MS = 33;   // ~30 FPS
static const uint32_t WATCHDOG_MS       = 500;  // refresh safety timer

// ── Mapping: DCS raw → gauge angle ─────────────────────────────────────────────
static inline int16_t map_brake(uint16_t v) {
  return map(v, 0, 65535, -25, 25);
}

// ── Forward decls ──────────────────────────────────────────────────────────────
void renderGauge(int16_t angleDeg);
void bitTest();

// ── DCS-BIOS callback (ISR-safe) ──────────────────────────────────────────────
void onHydIndBrakeChange(unsigned int v) {
  rawBrake = (uint16_t)v;
  dirtyBrake = true;
  lastDcsMs = millis();
}
DcsBios::IntegerBuffer hydIndBrakeBuffer(0x7506, 0xffff, 0, onHydIndBrakeChange);

// ── Setup ──────────────────────────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);
  DcsBios::setup();

  tft.init();
  tft.fillScreen(TFT_BLACK);

  // background canvas
  sprBack.setColorDepth(COLOR_DEPTH);
  sprBack.createSprite(CANVAS_W, CANVAS_H);
  sprBack.setSwapBytes(true);
  sprBack.setPivot(CANVAS_W/2, CANVAS_H - 5);

  // needle sprite (restored original geometry)
  sprNeedle.setColorDepth(COLOR_DEPTH);
  sprNeedle.createSprite(15, 150);
  sprNeedle.setSwapBytes(true);
  sprNeedle.setPivot(7, 150);
  sprNeedle.pushImage(0, 0, 15, 150, brakePressNeedle);

  renderGauge(map_brake(rawBrake));
  bitTest();   // optional boot-time sweep
}

// ── Main loop ──────────────────────────────────────────────────────────────────
void loop() {
  DcsBios::loop();

  const uint32_t now = millis();
  const bool frameDue = (now - lastFrameMs) >= FRAME_INTERVAL_MS;
  const bool dcsActive = (now - lastDcsMs) < 2000;
  const bool watchdogKick = dcsActive && ((now - lastFrameMs) >= WATCHDOG_MS);

  if ((dirtyBrake && frameDue) || watchdogKick) {
    noInterrupts();
    const uint16_t rb = rawBrake;
    dirtyBrake = false;
    interrupts();

    renderGauge(map_brake(rb));
    lastFrameMs = now;
  }

  yield();
  
}

// ── Rendering ──────────────────────────────────────────────────────────────────
void renderGauge(int16_t angleDeg) {
  //sprBack.fillSprite(TFT_BLACK);
  sprBack.pushImage(0, 0, CANVAS_W, CANVAS_H, brakePressBackground);
  sprNeedle.pushRotated(&sprBack, angleDeg, TFT_TRANSPARENT);
  sprBack.pushSprite(0, 0);
}

// ── Manual sweep test ──────────────────────────────────────────────────────────
void bitTest() {
  for (int i = 0; i <= 50; i += 2) {
    renderGauge(map(i, 0, 50, -25, 25));
    delay(10);
  }
  for (int i = 50; i >= 0; i -= 2) {
    renderGauge(map(i, 0, 50, -25, 25));
    delay(10);
  }
}
