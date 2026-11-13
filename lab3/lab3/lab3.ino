/*
 * Example of a basic FreeRTOS queue
 * https://www.freertos.org/Embedded-RTOS-Queues.html
 */

// Include Arduino FreeRTOS library
#include <Arduino_FreeRTOS.h>

#include <SPI.h>
#include "mcp2515_can.h"

#define SPI_CS_PIN 9
mcp2515_can CAN(SPI_CS_PIN); // Set CS pin

// Add these to read CAN data fields and loop through them in a cyclic mode
#include "CAN_data.h"
int data_counter = 0;

unsigned char buf[8];


void setup() {
  // Init Arduino serial
  Serial.begin(9600);

  // Wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
  while (!Serial) {
    vTaskDelay(1);
  }

  // Init the CAN shield - run at 500 KBPS
  if (CAN.begin(CAN_500KBPS) != 0) {
    Serial.println("CAN-BUS initialization error!");
    while(1);
  }

  CAN.setMode(MODE_LOOPBACK);  // Enable loopback mode to send and receive on the same device
  Serial.println("CAN init ok!");

  // Create the FreeRTOS tasks - see the documentation for what each parameter does

  // Blink blink! This is just here as a demonstration.
  xTaskCreate(TaskBlink, // Task function
              "Blink", // Task name
              128, // Stack size 
              NULL, 
              0, // Priority
              NULL );

  // Read from the CAN_data.h header (implemented)
  // and write to the loopback interface (not implemented - this is your task)
  xTaskCreate(TaskCanWrite, // Task function
              "CanWrite", // Task name
              256, // Stack size 
              NULL, 
              1, // Priority
              NULL );
  
  // Read from the CAN bus and interpret the results
  xTaskCreate(TaskCanRead, // Task function
              "CanRead", // Task name
              128, // Stack size 
              NULL, 
              1, // Priority
              NULL );
 
}

void loop() {}


/* 
 * Blink task. 
 * See Blink_AnalogRead example. 
 */
void TaskBlink(void *pvParameters)
{
  (void) pvParameters;

  pinMode(LED_BUILTIN, OUTPUT);

  for (;;)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    vTaskDelay( 250 *1000/ portTICK_PERIOD_MS );
    digitalWrite(LED_BUILTIN, LOW);
    vTaskDelay( 250*1000 / portTICK_PERIOD_MS );
  }
}

#define MAX_DATA_SIZE 8

void TaskCanWrite(void *&pvParameters)
{
  (void) pvParameters;

  int n = 0;
  char prbuf[128];
  char fstr[6];
  float last_time = 0.0, current_time = 0.0;

  Serial.println("Starting Test_case_1");

  for (;;) {
    last_time = 0.0;
    current_time = 0.0;

    // read as many data fields as needed
    for(int i = 0; i < NUM_ROWS(data_Test_case_1); ++i){
      n = 0;
      current_time = data_Test_case_1[i][0].time;
      // delay sending
      vTaskDelay( (current_time - last_time) / portTICK_PERIOD_MS );
      last_time = current_time;
      dtostrf(current_time, 4, 2, fstr);
      n += sprintf(prbuf + n, "[%s] ", fstr);
  
      for (int j = 0; j < NUM_COLS(data_Test_case_1); ++j) {
        dtostrf(data_Test_case_1[i][j].data, 4, 2, fstr);
        n += sprintf(prbuf + n, "%d:%s ", data_Test_case_1[i][j].msgType, fstr);
      
      }
      Serial.println(prbuf);
      for (int i = 0; i < 128; i++) {
          SERIAL_PORT_MONITOR.print(buf[i]); SERIAL_PORT_MONITOR.print(" ");
          CAN.sendMsgBuf(0x00, 0, 8, buf[i]);
      }
      
    }
    vTaskDelay( 100 *1000/ portTICK_PERIOD_MS );
  }

}

unsigned char stmp[8] = {0, 0, 0, 0, 0, 0, 0, 0};
uint8_t  len;
byte cdata[MAX_DATA_SIZE] = {0};
uint32_t id;
uint8_t  type; // bit0: ext, bit1: rtr

void TaskCanRead(void *&pvParameters)
{
  (void) pvParameters;

  // for scheduling
  TickType_t xLastWakeTime;
  const TickType_t xFrequency = 10;

  // Initialise the xLastWakeTime variable with the current time.
  xLastWakeTime = xTaskGetTickCount();

  for (;;)
  {
    vTaskDelayUntil(&xLastWakeTime, xFrequency);
    
    if (CAN.checkReceive()) {
      int n = 0;
      char prbuf[32 + MAX_DATA_SIZE * 3];
      CAN.readMsgBuf(&len, cdata);

      id = CAN.getCanId();
      type = (CAN.isExtendedFrame() << 0) |
           (CAN.isRemoteRequest() << 1);
      static const byte type2[] = {0x00, 0x02, 0x30, 0x32};
      n += sprintf(prbuf + n, "RX: [%08lX](%02X) ", (unsigned long)id, type2[type]);
      for (int i = 0; i < len; i++) {
        n += sprintf(prbuf + n, "%02X ", cdata[i]);
      }
      Serial.println(prbuf);

      SERIAL_PORT_MONITOR.println("checkReceive");
      CAN.readMsgBuf(&len, buf);
      // print the data
      for (int i = 0; i < len; i++) {
          SERIAL_PORT_MONITOR.print(buf[i]); SERIAL_PORT_MONITOR.print(" ");
      }
      SERIAL_PORT_MONITOR.println();
    }else {
      SERIAL_PORT_MONITOR.println("Error in receiving CAN packets!");
    }
  }
}
