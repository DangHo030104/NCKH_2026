#ifndef APP_CONFIG_H
#define APP_CONFIG_H

/* ------ Chứa toàn bộ cấu hình dùng chung ------ */

#include "main.h"

#define DHT11_PORT 		GPIOB
#define DHT11_PIN 		GPIO_PIN_14

#define RELAY1_PORT 	GPIOA
#define RELAY1_PIN 		GPIO_PIN_5       /* Van Zone 1 */
#define RELAY2_PORT 	GPIOA
#define RELAY2_PIN 		GPIO_PIN_6       /* Van Zone 2 */
#define RELAY3_PORT 	GPIOA
#define RELAY3_PIN 		GPIO_PIN_7       /* Pump */
#define LED_PORT 		GPIOC
#define LED_PIN 		GPIO_PIN_13         /* Sáng khi STM32 thức, tắt khi STOP (active-low) */

// Van Active Low
#define VALVE_RELAY_ON 	GPIO_PIN_RESET
#define VALVE_RELAY_OFF GPIO_PIN_SET

// Pump Active High
#define PUMP_RELAY_ON 	GPIO_PIN_SET
#define PUMP_RELAY_OFF 	GPIO_PIN_RESET

#define LORA_AUX_PORT 	GPIOA
#define LORA_AUX_PIN 	GPIO_PIN_15
#define LORA_M0_PORT 	GPIOA
#define LORA_M0_PIN 	GPIO_PIN_11
#define LORA_M1_PORT 	GPIOA
#define LORA_M1_PIN 	GPIO_PIN_12

#define BATTERY_ADC_CHANNEL 		ADC_CHANNEL_4  /* PA4 */
#define SENSOR_ADC_SAMPLING_TIME 	ADC_SAMPLETIME_239CYCLES_5
#define SOIL_ADC_SAMPLE_COUNT 		16U

#define FRAME_TIMEOUT_MS 		1000U
#define CMD_DUPLICATE_MS 		30000U          /* ESP32 retry window: tránh thực thi lại cùng CMD. */
#define MANUAL_WATER_TIMEOUT_MS 60000U   		/* Tự dừng tưới MANUAL sau 60 giây. */
#define AUTO_SENSOR_INTERVAL_MS 15000U    		/* Demo: đo lại sensor sau mỗi 15 giây khi AUTO đang IDLE. */

/* Mỗi thread flag dùng một bit riêng -> Giao tiếp giữa các Task */
#define SENSOR_READ_SIGNAL 		0x01U         	/* LoRaTask yêu cầu SensorTask đọc cho REQ. */
#define SENSOR_READY_SIGNAL 	0x02U
#define CONTROL_EXEC_SIGNAL 	0x04U        	/* LoRaTask yêu cầu IrrigationTask thực thi CMD. */
#define CONTROL_OK_SIGNAL 		0x08U
#define CONTROL_ERROR_SIGNAL 	0x10U
#define IRRIGATION_READ_SIGNAL 	0x20U     		/* IrrigationTask yêu cầu SensorTask đọc cho AUTO. */
#define IRRIGATION_READY_SIGNAL 0x40U
#define TELEMETRY_READ_SIGNAL 	0x80U      		/* LoRaTask yêu cầu snapshot cho streaming. */

/* Giá trị tham khảo, cần hiệu chỉnh lại trên từng cảm biến đất thực tế. */
#define SOIL1_ADC_DRY 4025U
#define SOIL1_ADC_WET 1915U

#define SOIL2_ADC_DRY 4012U
#define SOIL2_ADC_WET 1900U

/* SM < 35%: cần tưới; SM >= 55%: đủ nước.
 * Khoảng 35%..55% là hysteresis để relay không đóng/ngắt liên tục. */
#define SOIL_START_THRESHOLD 	35.0f
#define SOIL_STOP_THRESHOLD 	55.0f

/* Tưới theo xung, nghỉ cho nước thấm rồi đo lại; giới hạn tối đa 10 chu kỳ. */
#define WATER_PULSE_MS 			5000U
#define SOAK_TIME_MS 			10000U
#define MEASURE_MIN_DISPLAY_MS 	1000U
#define MAX_IRRIGATION_CYCLE 	10U

/* Demo STOP mode: RTC đánh thức STM32 sau mỗi 15 giây. */
#define RTC_WAKEUP_INTERVAL_SEC 15U

/* Live telemetry chỉ chạy khi một chu kỳ tưới đang hoạt động. */
#define TELEMETRY_INTERVAL_MS 	1000U     /* Yêu cầu snapshot mới mỗi 1 giây khi đang tưới. */
#define TELEMETRY_TX_GUARD_MS 	1000U     /* Không cho STM32 gửi telemetry quá gần một gói DATA hoặc ACK vừa gửi
										   * -> Ngăn hai frame LoRa bị dính vào nhau. */
#define LORA_RX_TO_TX_GUARD_MS  30U       /* Giữ đường truyền ổn định sau byte RX cuối trước khi phát telemetry */

/* Đặt bằng 1 để không vào STOP khi debug bằng CubeIDE. */
#define DEBUG_NO_STOP 0

/* Bật log chi tiết quá trình RTC/LoRa đánh thức STM32 qua UART2. */
#define WAKE_DEBUG_LOG_ENABLE 0

#endif
