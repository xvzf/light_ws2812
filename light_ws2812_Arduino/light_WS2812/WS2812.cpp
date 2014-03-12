/*
* light weight WS2812 lib V2.1 - Arduino support
*
* Controls WS2811/WS2812/WS2812B RGB-LEDs
* Author: Matthias Riegler
*
* Mar 07 2014: Added Arduino and C++ Library
*
* License: GNU GPL v2 (see License.txt)
*/

#include "WS2812.h"
#include <stdlib.h>

WS2812::WS2812(uint16_t num_leds) {
	count_led = num_leds;
	
	pixels = (uint8_t*)malloc(count_led);
	
}

cRGB WS2812::get_crgb_at(uint16_t index) {
	
	cRGB px_value;
	
	if(index < count_led) {
		
		uint16_t tmp;
		tmp = index * 3;
		
		px_value.g = pixels[tmp];
		px_value.r = pixels[tmp+1];
		px_value.b = pixels[tmp+2];
	}
	
	return px_value;
}

uint8_t WS2812::set_crgb_at(uint16_t index, cRGB px_value) {
	
	if(index < count_led) {
		
		uint16_t tmp;
		tmp = index * 3;
		
		pixels[tmp] = px_value.g;
		pixels[tmp+1] = px_value.r;
		pixels[tmp+2] = px_value.b;
		
		return 0;
	} 
	return 1;
}


uint8_t WS2812::set_rgb_at(uint16_t index, uint8_t R, uint8_t G, uint8_t B) {
	if(index < count_led) {
		
		uint16_t tmp;
		tmp = index * 3;
		
		pixels[tmp] = G;
		pixels[tmp+1] = R;
		pixels[tmp+2] = B;
		
		return 0;
	} 
	return 1;	
}
	
	
	
	
void WS2812::rainbow() {
	
	
}


void WS2812::pulse_color(uint16_t index, uint16_t duration, cRGB px_value) {
	uint8_t r = px_value.r, g = px_value.g, b = px_value.b;
	delay_time = duration / (255*2); // Time for each delay, if the complete cycle dures {duration}
	
	for(int i = 0; i < 255, i++) {
		set_rgb_at(index, r*i, g*i, b*i);
		delay(delay_time);
	}
	
	for(int i = 255; i > 0, i--) {
		set_rgb_at(index, r*i, g*i, b*i);
	}
	
} 
	
void WS2812::pulse_color(uint16_t index, uint16_t duration, uint8_t R, uint8_t G, uint8_t B) {
	uint8_t r = R, g = G, b = B;
	delay_time = duration / (255*2); // Time for each delay, if the complete cycle dures {duration}
	
	for(int i = 0; i < 255, i++) {
		set_rgb_at(index, r*i, g*i, b*i);
		delay(delay_time);
	}
	
	for(int i = 255; i > 0, i--) {
		set_rgb_at(index, r*i, g*i, b*i);
	}
}
	

void WS2812::sync() {
	*ws2812_port_reg |= (1<<7); // Enable DDR
	ws2812_sendarray_mask(pixels,3*count_led,pinMask,(uint8_t*) ws2812_port,(uint8_t*) ws2812_port_reg );	
}

WS2812::~WS2812() {
	
	
}

#ifndef ARDUINO
void WS2812::setOutput(const volatile uint8_t* port, volatile uint8_t* reg, uint8_t pin) {
	pinMask = (1<<pin);
	ws2812_port = port;
	ws2812_port_reg = reg;
}
#else
void WS2812::setOutput(uint8_t pin) {
	pinMask = digitalPinToBitMask(pin);
	ws2812_port = portOutputRegister(digitalPinToPort(pin));
	ws2812_port_reg = portModeRegister(digitalPinToPort(pin));
}
#endif 
