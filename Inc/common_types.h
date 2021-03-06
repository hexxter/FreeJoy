/**
  ******************************************************************************
  * @file           : common_types.h
  * @brief          : This file contains the common types for the app.                  
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __COMMON_TYPES_H__
#define __COMMON_TYPES_H__

#include "stdint.h"
#include "common_defines.h"

enum
{
	FILTER_NO = 0,
	FILTER_LOW,
	FILTER_MEDIUM,
	FILTER_HIGH,
	FILTER_VERY_HIGH,
}; 
typedef uint8_t filter_t;

typedef int16_t analog_data_t;

enum
{
	NO_FUNCTION = 0,
	FUNCTION_PLUS_ABS,
	FUNCTION_PLUS_REL,
	FUNCTION_MINUS_ABS,
	FUNCTION_MINUS_REL,
};

typedef struct
{
	analog_data_t 	calib_min;
	analog_data_t		calib_center;
	analog_data_t 	calib_max;
	uint8_t					out_enabled: 1;
	uint8_t					magnet_offset: 1;
	uint8_t					inverted: 1;
	uint8_t 				filter: 3;
	uint8_t					:0;
	int8_t				 	curve_shape[11];
	uint8_t					resolution;
	uint8_t					dead_zone;
	
	int8_t					source_main;
	uint8_t					function:	3;
	uint8_t					source_secondary: 5;
	
	int8_t					decrement_button;
	int8_t					center_button;
	int8_t					increment_button;
	uint8_t					step;
	uint8_t					reserved[4];
	
} axis_config_t;

typedef struct
{
	uint8_t 	data[6];
	uint8_t 	rx_complete;
	uint8_t 	tx_complete;
	int8_t 		cs_pin;
	uint32_t	ok_cnt;
	uint32_t 	err_cnt;
} tle_t;

enum
{
	NOT_USED = 0,
	
	BUTTON_GND,
	BUTTON_VCC,
	BUTTON_ROW,
	BUTTON_COLUMN,
	
	AXIS_ANALOG,
	
//	RESERVED,
	
	SPI_SCK = 7,

  TLE5011_CS,
  SPI_DATA,
  TLE5011_GEN,

  SHIFT_REG_CS,
  SHIFT_REG_DATA,

};
typedef uint8_t pin_t;

enum
{
	BUTTON_NORMAL = 0,
	BUTTON_INVERTED,
	BUTTON_TOGGLE,
	TOGGLE_SWITCH,
	TOGGLE_SWITCH_ON,
	TOGGLE_SWITCH_OFF,
	
	POV1_UP,
	POV1_RIGHT,
	POV1_DOWN,
	POV1_LEFT,
	POV2_UP,
	POV2_RIGHT,
	POV2_DOWN,
	POV2_LEFT,
	POV3_UP,
	POV3_RIGHT,
	POV3_DOWN,
	POV3_LEFT,
	POV4_UP,
	POV4_RIGHT,
	POV4_DOWN,
	POV4_LEFT,
	
	ENCODER_INPUT_A,
	ENCODER_INPUT_B,
	
	RADIO_BUTTON1,
	RADIO_BUTTON2,
	RADIO_BUTTON3,
	RADIO_BUTTON4,
	
};
typedef uint8_t button_type_t;

typedef struct button_t
{
	int8_t					physical_num;
	button_type_t 	type : 5;
	uint8_t					shift_modificator: 3;	
	
}	button_t;

typedef struct buttons_state_t
{
  uint64_t time_last;	
	uint8_t pin_state;
	//uint8_t pin_prev_state;
	uint8_t prev_state;
	uint8_t current_state;
	uint8_t changed;	
	uint8_t cnt;
	
} buttons_state_t;


typedef struct
{
  uint64_t 				time_last;
	uint8_t 				state;
	int16_t 				cnt;	
	int8_t 					pin_a;
	int8_t 					pin_b;
	int8_t					dir;
	int8_t					last_dir;
	
} encoder_t;

typedef struct
{
	int8_t points[13];
	uint8_t buttons_cnt;
	uint8_t is_enabled;
	
} axis_to_buttons_t;

enum
{
	HC165_PULL_DOWN = 0,
	CD4021_PULL_DOWN,
	HC165_PULL_UP,
	CD4021_PULL_UP,
};	
typedef uint8_t shift_reg_config_type_t;

typedef struct
{	
	uint8_t 			type;
	uint8_t 			button_cnt;	
	int8_t 				pin_cs;
	int8_t 				pin_data;
	
} shift_reg_config_t;

enum
{
	SHIFT_NORMAL = 0,
	SHIFT_INVERTED,
	
};

typedef struct 
{
	int8_t 				button;
	
} shift_modificator_t;

typedef struct 
{
	// config 1
	uint16_t 						firmware_version;
	char 								device_name[20];
	uint16_t						button_debounce_ms;
	uint16_t						toggle_press_time_ms;
	uint16_t						encoder_press_time_ms;
	uint16_t 						exchange_period_ms;	
	uint8_t							reserved_1[2];
	pin_t 							pins[USED_PINS_NUM];
	
	
	// config 2-5
	axis_config_t 			axis_config[MAX_AXIS_NUM];
	
	// config 6-7-8-9-10
	button_t 						buttons[MAX_BUTTONS_NUM];
	
	// config 10-11-12
	axis_to_buttons_t		axes_to_buttons[MAX_AXIS_NUM];
	
	// config 12	
	shift_reg_config_t	shift_registers[4];
	shift_modificator_t	shift_config[5];
	uint16_t						vid;
	uint16_t						pid;
	uint8_t							is_dynamic_config; 
	uint8_t							reserved_10[26];
}dev_config_t;

typedef struct
{
	uint8_t							axes;
	uint8_t							buttons_cnt;
	uint8_t							povs;
	
} app_config_t;

typedef struct
{
	uint8_t					dummy;		// alighning
	uint8_t 				id;
	int16_t					raw_axis_data[MAX_AXIS_NUM];
	uint8_t					raw_button_data[9];
	uint8_t					shift_button_data;	
	int16_t			 		axis_data[MAX_AXIS_NUM];
	uint8_t 				pov_data[MAX_POVS_NUM];
	uint8_t 				button_data[MAX_BUTTONS_NUM/8];
	
} joy_report_t;




#endif 	/* __COMMON_TYPES_H__ */
