// Designed for Waveshare 1.85" round lcd without touch screen
// https://www.waveshare.com/wiki/ESP32-S3-LCD-1.85
// 
// LVGL version is 8.3.11
// Display_ST77916, esp_lcd_st77916, I2C_Driver files sourced from WaveShare's demo code for the display

#define DCSBIOS_DEFAULT_SERIAL
#define DCSBIOS_DISABLE_SERVO 
#include <DcsBios.h>


#include <Arduino.h>
#include "Display_ST77916.h"
#include <lvgl.h>

// LVGL bitmaps
#include "airSpeedIndicatorBG.c"
#include "airspeedNeedle.c"

#define DISP_WIDTH  360
#define DISP_HEIGHT 360


// LVGL draw buffers
static lv_color_t buf1[DISP_WIDTH * 40];
static lv_color_t buf2[DISP_WIDTH * 40];


// ===== Globals =====
lv_obj_t *img_airSpeedIndicatorBG;
lv_obj_t *img_airspeedNeedle;


// Center and radius
const int16_t center_x = DISP_WIDTH / 2;
const int16_t center_y = DISP_HEIGHT / 2;

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
    LCD_addWindow(area->x1, area->y1, area->x2, area->y2, (uint16_t*)color_p);
    lv_disp_flush_ready(disp);
}

void onStbyAsiAirspeedChange(unsigned int newValue) {
    lv_img_set_angle(img_airspeedNeedle, map(newValue, 0, 65530, 0, 3500));
}
DcsBios::IntegerBuffer stbyAsiAirspeedBuffer(0x74f0, 0xffff, 0, onStbyAsiAirspeedChange);


void setup() {
  DcsBios::setup();

    ST77916_Init();
    Backlight_Init();
    Set_Backlight(25);

    lv_init();

    static lv_disp_draw_buf_t draw_buf;
    lv_disp_draw_buf_init(&draw_buf, buf1, buf2, DISP_WIDTH * 40);

    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = DISP_WIDTH;
    disp_drv.ver_res = DISP_HEIGHT;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    // ===== Black background =====
    lv_obj_t *bg_rect = lv_obj_create(lv_scr_act());
    lv_obj_set_size(bg_rect, DISP_WIDTH, DISP_HEIGHT);
    lv_obj_set_style_bg_color(bg_rect, lv_color_hex(0x000000), 0);
    lv_obj_set_style_border_width(bg_rect, 0, 0);
    lv_obj_clear_flag(bg_rect, LV_OBJ_FLAG_SCROLLABLE);


    // ===== Altimeter background =====
    img_airSpeedIndicatorBG = lv_img_create(lv_scr_act());
    lv_img_set_src(img_airSpeedIndicatorBG, &airSpeedIndicatorBG);
    lv_obj_align(img_airSpeedIndicatorBG, LV_ALIGN_CENTER, 0, 0);

    // ===== Needle =====
    img_airspeedNeedle = lv_img_create(lv_scr_act());
    lv_img_set_src(img_airspeedNeedle, &airspeedNeedle);

    // Set the pivot to the bottom center of the image
    lv_point_t pivot = {
        airspeedNeedle.header.w / 2,   // horizontally centered
        airspeedNeedle.header.h / 2       // very bottom
    };
    lv_img_set_pivot(img_airspeedNeedle, pivot.x, pivot.y);

    // Align so the pivot (bottom center) is at the gauge center
    lv_obj_align(img_airspeedNeedle, LV_ALIGN_CENTER, 0, 0);

}

void loop() {
    DcsBios::loop();
    lv_timer_handler();
}
