#pragma once

#define WINDOW_TYPE_BUTTON 1

#define BUTTON_STATE_NORMAL  0
#define BUTTON_STATE_PRESS   1

#define BTN_BACKGROUND_COLOR 				0xCCCCCC
#define BTN_FRAME_COLOR 						0x333333
#define BTN_BACKGROUND_PRESS_COLOR 	0xCCCCCC
#define BTN_FRAME_PRESS_COLOR 			0x777777
#define BTN_TEXT_COLOR 							0x000033

#define TEXT_FONT_WIDTH(str) (strlen(str)*8)
#define TEXT_FONT_HEIGHT(str) (8)

#define button_t window_t

window_t *button_create(window_t *parent, int x, int y, int width, int height, char* title, int id);
bool button_default_procedure(window_t *win, struct message_struct *msg);
void on_button_predraw(window_t *win);