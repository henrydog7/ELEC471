/*
    This is an example of sending and receiving on the same CANBUS shield.
    Run this to test the CAN controller's internal functionality by internally 
    looping the transmitted signal back to its receiver (loopback mode)
*/

#include <SPI.h>
#include "mcp2515_can.h"

// Set SPI CS Pin according to your hardware
// For Wio Terminal w/ MCP2518FD RPi Hat：
// Channel 0 SPI_CS Pin: BCM 8
// Channel 1 SPI_CS Pin: BCM 7
// Interupt Pin: BCM25
// *****************************************
// For Arduino MCP2515 Hat:
// SPI_CS Pin: D9

const int SPI_CS_PIN_SEND = 9;

mcp2515_can CAN(SPI_CS_PIN_SEND);

unsigned char len = 0;
unsigned char buf[8];

void setup() {
    SERIAL_PORT_MONITOR.begin(9600);
    while(!Serial); // wait for Serial

    if (CAN.begin(CAN_500KBPS) != 0) {
      SERIAL_PORT_MONITOR.println("CAN-BUS initialization error!");
      while(1);
    }
    
    CAN.setMode(MODE_LOOPBACK);  // Enable loopback mode to send and receive on the same device
    SERIAL_PORT_MONITOR.println("CAN init ok!");
}

unsigned char stmp[8] = {0, 0, 0, 0, 0, 0, 0, 0};
void loop() {
    // send data:  id = 0x00, standrad frame, data len = 8, stmp: data buf
    stmp[7] = stmp[7] + 1;
    if (stmp[7] == 100) {
        stmp[7] = 0;
        stmp[6] = stmp[6] + 1;

        if (stmp[6] == 100) {
            stmp[6] = 0;
            stmp[5] = stmp[5] + 1;
        }
    }

    int sendStat = CAN.sendMsgBuf(0x00, 0, 8, stmp);
    delay(300);     // send data every 300ms (not taking print delays into account)
    char strBuf[50];
    if(sendStat == CAN_OK) {
        sprintf(strBuf, "CAN BUS sendMsgBuf ok! (return status: %d)", sendStat);
    }
    else{
        sprintf(strBuf, "CAN BUS sendMsgBuf NOT ok! (return status: %d)", sendStat);
    }
    SERIAL_PORT_MONITOR.println(strBuf);

    // ---------------------
        
    if (CAN_MSGAVAIL == CAN.checkReceive()) {
      // read data,  len: data length, buf: data buf
        SERIAL_PORT_MONITOR.println("checkReceive");
        CAN.readMsgBuf(&len, buf);
      // print the data
      for (int i = 0; i < len; i++) {
          SERIAL_PORT_MONITOR.print(buf[i]); SERIAL_PORT_MONITOR.print(" ");
      }
      SERIAL_PORT_MONITOR.println();
    }
    else {
      SERIAL_PORT_MONITOR.println("Error in receiving CAN packets!");
    }

    SERIAL_PORT_MONITOR.println("---LOOP END---");
}

// END FILE
