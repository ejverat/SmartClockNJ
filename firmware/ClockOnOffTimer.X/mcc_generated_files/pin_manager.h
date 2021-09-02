/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16F18877
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.31 and above
        MPLAB 	          :  MPLAB X 5.45	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set IOEXP_NCS aliases
#define IOEXP_NCS_TRIS                 TRISAbits.TRISA2
#define IOEXP_NCS_LAT                  LATAbits.LATA2
#define IOEXP_NCS_PORT                 PORTAbits.RA2
#define IOEXP_NCS_WPU                  WPUAbits.WPUA2
#define IOEXP_NCS_OD                   ODCONAbits.ODCA2
#define IOEXP_NCS_ANS                  ANSELAbits.ANSA2
#define IOEXP_NCS_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define IOEXP_NCS_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define IOEXP_NCS_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define IOEXP_NCS_GetValue()           PORTAbits.RA2
#define IOEXP_NCS_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define IOEXP_NCS_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define IOEXP_NCS_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define IOEXP_NCS_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define IOEXP_NCS_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define IOEXP_NCS_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define IOEXP_NCS_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define IOEXP_NCS_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set SCL aliases
#define SCL_TRIS                 TRISBbits.TRISB1
#define SCL_LAT                  LATBbits.LATB1
#define SCL_PORT                 PORTBbits.RB1
#define SCL_WPU                  WPUBbits.WPUB1
#define SCL_OD                   ODCONBbits.ODCB1
#define SCL_ANS                  ANSELBbits.ANSB1
#define SCL_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define SCL_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define SCL_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define SCL_GetValue()           PORTBbits.RB1
#define SCL_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define SCL_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define SCL_SetPullup()          do { WPUBbits.WPUB1 = 1; } while(0)
#define SCL_ResetPullup()        do { WPUBbits.WPUB1 = 0; } while(0)
#define SCL_SetPushPull()        do { ODCONBbits.ODCB1 = 0; } while(0)
#define SCL_SetOpenDrain()       do { ODCONBbits.ODCB1 = 1; } while(0)
#define SCL_SetAnalogMode()      do { ANSELBbits.ANSB1 = 1; } while(0)
#define SCL_SetDigitalMode()     do { ANSELBbits.ANSB1 = 0; } while(0)

// get/set SDA aliases
#define SDA_TRIS                 TRISBbits.TRISB2
#define SDA_LAT                  LATBbits.LATB2
#define SDA_PORT                 PORTBbits.RB2
#define SDA_WPU                  WPUBbits.WPUB2
#define SDA_OD                   ODCONBbits.ODCB2
#define SDA_ANS                  ANSELBbits.ANSB2
#define SDA_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define SDA_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define SDA_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define SDA_GetValue()           PORTBbits.RB2
#define SDA_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define SDA_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define SDA_SetPullup()          do { WPUBbits.WPUB2 = 1; } while(0)
#define SDA_ResetPullup()        do { WPUBbits.WPUB2 = 0; } while(0)
#define SDA_SetPushPull()        do { ODCONBbits.ODCB2 = 0; } while(0)
#define SDA_SetOpenDrain()       do { ODCONBbits.ODCB2 = 1; } while(0)
#define SDA_SetAnalogMode()      do { ANSELBbits.ANSB2 = 1; } while(0)
#define SDA_SetDigitalMode()     do { ANSELBbits.ANSB2 = 0; } while(0)

// get/set BUTTON1 aliases
#define BUTTON1_TRIS                 TRISBbits.TRISB3
#define BUTTON1_LAT                  LATBbits.LATB3
#define BUTTON1_PORT                 PORTBbits.RB3
#define BUTTON1_WPU                  WPUBbits.WPUB3
#define BUTTON1_OD                   ODCONBbits.ODCB3
#define BUTTON1_ANS                  ANSELBbits.ANSB3
#define BUTTON1_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define BUTTON1_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define BUTTON1_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define BUTTON1_GetValue()           PORTBbits.RB3
#define BUTTON1_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define BUTTON1_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define BUTTON1_SetPullup()          do { WPUBbits.WPUB3 = 1; } while(0)
#define BUTTON1_ResetPullup()        do { WPUBbits.WPUB3 = 0; } while(0)
#define BUTTON1_SetPushPull()        do { ODCONBbits.ODCB3 = 0; } while(0)
#define BUTTON1_SetOpenDrain()       do { ODCONBbits.ODCB3 = 1; } while(0)
#define BUTTON1_SetAnalogMode()      do { ANSELBbits.ANSB3 = 1; } while(0)
#define BUTTON1_SetDigitalMode()     do { ANSELBbits.ANSB3 = 0; } while(0)

// get/set BUTTON2 aliases
#define BUTTON2_TRIS                 TRISBbits.TRISB4
#define BUTTON2_LAT                  LATBbits.LATB4
#define BUTTON2_PORT                 PORTBbits.RB4
#define BUTTON2_WPU                  WPUBbits.WPUB4
#define BUTTON2_OD                   ODCONBbits.ODCB4
#define BUTTON2_ANS                  ANSELBbits.ANSB4
#define BUTTON2_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define BUTTON2_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define BUTTON2_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define BUTTON2_GetValue()           PORTBbits.RB4
#define BUTTON2_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define BUTTON2_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define BUTTON2_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define BUTTON2_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define BUTTON2_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define BUTTON2_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define BUTTON2_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define BUTTON2_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set IOEXP_NRESET aliases
#define IOEXP_NRESET_TRIS                 TRISBbits.TRISB5
#define IOEXP_NRESET_LAT                  LATBbits.LATB5
#define IOEXP_NRESET_PORT                 PORTBbits.RB5
#define IOEXP_NRESET_WPU                  WPUBbits.WPUB5
#define IOEXP_NRESET_OD                   ODCONBbits.ODCB5
#define IOEXP_NRESET_ANS                  ANSELBbits.ANSB5
#define IOEXP_NRESET_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define IOEXP_NRESET_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define IOEXP_NRESET_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define IOEXP_NRESET_GetValue()           PORTBbits.RB5
#define IOEXP_NRESET_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define IOEXP_NRESET_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define IOEXP_NRESET_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define IOEXP_NRESET_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define IOEXP_NRESET_SetPushPull()        do { ODCONBbits.ODCB5 = 0; } while(0)
#define IOEXP_NRESET_SetOpenDrain()       do { ODCONBbits.ODCB5 = 1; } while(0)
#define IOEXP_NRESET_SetAnalogMode()      do { ANSELBbits.ANSB5 = 1; } while(0)
#define IOEXP_NRESET_SetDigitalMode()     do { ANSELBbits.ANSB5 = 0; } while(0)

// get/set RC3 procedures
#define RC3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define RC3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define RC3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define RC3_GetValue()              PORTCbits.RC3
#define RC3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define RC3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define RC3_SetPullup()             do { WPUCbits.WPUC3 = 1; } while(0)
#define RC3_ResetPullup()           do { WPUCbits.WPUC3 = 0; } while(0)
#define RC3_SetAnalogMode()         do { ANSELCbits.ANSC3 = 1; } while(0)
#define RC3_SetDigitalMode()        do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set RC4 procedures
#define RC4_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define RC4_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define RC4_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define RC4_GetValue()              PORTCbits.RC4
#define RC4_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define RC4_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define RC4_SetPullup()             do { WPUCbits.WPUC4 = 1; } while(0)
#define RC4_ResetPullup()           do { WPUCbits.WPUC4 = 0; } while(0)
#define RC4_SetAnalogMode()         do { ANSELCbits.ANSC4 = 1; } while(0)
#define RC4_SetDigitalMode()        do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set RC5 procedures
#define RC5_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define RC5_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define RC5_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define RC5_GetValue()              PORTCbits.RC5
#define RC5_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define RC5_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define RC5_SetPullup()             do { WPUCbits.WPUC5 = 1; } while(0)
#define RC5_ResetPullup()           do { WPUCbits.WPUC5 = 0; } while(0)
#define RC5_SetAnalogMode()         do { ANSELCbits.ANSC5 = 1; } while(0)
#define RC5_SetDigitalMode()        do { ANSELCbits.ANSC5 = 0; } while(0)

// get/set PIR1 aliases
#define PIR1_TRIS                 TRISCbits.TRISC6
#define PIR1_LAT                  LATCbits.LATC6
#define PIR1_PORT                 PORTCbits.RC6
#define PIR1_WPU                  WPUCbits.WPUC6
#define PIR1_OD                   ODCONCbits.ODCC6
#define PIR1_ANS                  ANSELCbits.ANSC6
#define PIR1_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define PIR1_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define PIR1_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define PIR1_GetValue()           PORTCbits.RC6
#define PIR1_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define PIR1_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define PIR1_SetPullup()          do { WPUCbits.WPUC6 = 1; } while(0)
#define PIR1_ResetPullup()        do { WPUCbits.WPUC6 = 0; } while(0)
#define PIR1_SetPushPull()        do { ODCONCbits.ODCC6 = 0; } while(0)
#define PIR1_SetOpenDrain()       do { ODCONCbits.ODCC6 = 1; } while(0)
#define PIR1_SetAnalogMode()      do { ANSELCbits.ANSC6 = 1; } while(0)
#define PIR1_SetDigitalMode()     do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set BUTTON0 aliases
#define BUTTON0_TRIS                 TRISCbits.TRISC7
#define BUTTON0_LAT                  LATCbits.LATC7
#define BUTTON0_PORT                 PORTCbits.RC7
#define BUTTON0_WPU                  WPUCbits.WPUC7
#define BUTTON0_OD                   ODCONCbits.ODCC7
#define BUTTON0_ANS                  ANSELCbits.ANSC7
#define BUTTON0_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define BUTTON0_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define BUTTON0_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define BUTTON0_GetValue()           PORTCbits.RC7
#define BUTTON0_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define BUTTON0_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define BUTTON0_SetPullup()          do { WPUCbits.WPUC7 = 1; } while(0)
#define BUTTON0_ResetPullup()        do { WPUCbits.WPUC7 = 0; } while(0)
#define BUTTON0_SetPushPull()        do { ODCONCbits.ODCC7 = 0; } while(0)
#define BUTTON0_SetOpenDrain()       do { ODCONCbits.ODCC7 = 1; } while(0)
#define BUTTON0_SetAnalogMode()      do { ANSELCbits.ANSC7 = 1; } while(0)
#define BUTTON0_SetDigitalMode()     do { ANSELCbits.ANSC7 = 0; } while(0)

// get/set MOTOR1_O1 aliases
#define MOTOR1_O1_TRIS                 TRISDbits.TRISD5
#define MOTOR1_O1_LAT                  LATDbits.LATD5
#define MOTOR1_O1_PORT                 PORTDbits.RD5
#define MOTOR1_O1_WPU                  WPUDbits.WPUD5
#define MOTOR1_O1_OD                   ODCONDbits.ODCD5
#define MOTOR1_O1_ANS                  ANSELDbits.ANSD5
#define MOTOR1_O1_SetHigh()            do { LATDbits.LATD5 = 1; } while(0)
#define MOTOR1_O1_SetLow()             do { LATDbits.LATD5 = 0; } while(0)
#define MOTOR1_O1_Toggle()             do { LATDbits.LATD5 = ~LATDbits.LATD5; } while(0)
#define MOTOR1_O1_GetValue()           PORTDbits.RD5
#define MOTOR1_O1_SetDigitalInput()    do { TRISDbits.TRISD5 = 1; } while(0)
#define MOTOR1_O1_SetDigitalOutput()   do { TRISDbits.TRISD5 = 0; } while(0)
#define MOTOR1_O1_SetPullup()          do { WPUDbits.WPUD5 = 1; } while(0)
#define MOTOR1_O1_ResetPullup()        do { WPUDbits.WPUD5 = 0; } while(0)
#define MOTOR1_O1_SetPushPull()        do { ODCONDbits.ODCD5 = 0; } while(0)
#define MOTOR1_O1_SetOpenDrain()       do { ODCONDbits.ODCD5 = 1; } while(0)
#define MOTOR1_O1_SetAnalogMode()      do { ANSELDbits.ANSD5 = 1; } while(0)
#define MOTOR1_O1_SetDigitalMode()     do { ANSELDbits.ANSD5 = 0; } while(0)

// get/set MOTOR1_O2 aliases
#define MOTOR1_O2_TRIS                 TRISDbits.TRISD6
#define MOTOR1_O2_LAT                  LATDbits.LATD6
#define MOTOR1_O2_PORT                 PORTDbits.RD6
#define MOTOR1_O2_WPU                  WPUDbits.WPUD6
#define MOTOR1_O2_OD                   ODCONDbits.ODCD6
#define MOTOR1_O2_ANS                  ANSELDbits.ANSD6
#define MOTOR1_O2_SetHigh()            do { LATDbits.LATD6 = 1; } while(0)
#define MOTOR1_O2_SetLow()             do { LATDbits.LATD6 = 0; } while(0)
#define MOTOR1_O2_Toggle()             do { LATDbits.LATD6 = ~LATDbits.LATD6; } while(0)
#define MOTOR1_O2_GetValue()           PORTDbits.RD6
#define MOTOR1_O2_SetDigitalInput()    do { TRISDbits.TRISD6 = 1; } while(0)
#define MOTOR1_O2_SetDigitalOutput()   do { TRISDbits.TRISD6 = 0; } while(0)
#define MOTOR1_O2_SetPullup()          do { WPUDbits.WPUD6 = 1; } while(0)
#define MOTOR1_O2_ResetPullup()        do { WPUDbits.WPUD6 = 0; } while(0)
#define MOTOR1_O2_SetPushPull()        do { ODCONDbits.ODCD6 = 0; } while(0)
#define MOTOR1_O2_SetOpenDrain()       do { ODCONDbits.ODCD6 = 1; } while(0)
#define MOTOR1_O2_SetAnalogMode()      do { ANSELDbits.ANSD6 = 1; } while(0)
#define MOTOR1_O2_SetDigitalMode()     do { ANSELDbits.ANSD6 = 0; } while(0)

// get/set RD7 procedures
#define RD7_SetHigh()            do { LATDbits.LATD7 = 1; } while(0)
#define RD7_SetLow()             do { LATDbits.LATD7 = 0; } while(0)
#define RD7_Toggle()             do { LATDbits.LATD7 = ~LATDbits.LATD7; } while(0)
#define RD7_GetValue()              PORTDbits.RD7
#define RD7_SetDigitalInput()    do { TRISDbits.TRISD7 = 1; } while(0)
#define RD7_SetDigitalOutput()   do { TRISDbits.TRISD7 = 0; } while(0)
#define RD7_SetPullup()             do { WPUDbits.WPUD7 = 1; } while(0)
#define RD7_ResetPullup()           do { WPUDbits.WPUD7 = 0; } while(0)
#define RD7_SetAnalogMode()         do { ANSELDbits.ANSD7 = 1; } while(0)
#define RD7_SetDigitalMode()        do { ANSELDbits.ANSD7 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCBF3 pin functionality
 * @Example
    IOCBF3_ISR();
 */
void IOCBF3_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCBF3 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCBF3 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCBF3_SetInterruptHandler(MyInterruptHandler);

*/
void IOCBF3_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCBF3 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCBF3_SetInterruptHandler() method.
    This handler is called every time the IOCBF3 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCBF3_SetInterruptHandler(IOCBF3_InterruptHandler);

*/
extern void (*IOCBF3_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCBF3 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCBF3_SetInterruptHandler() method.
    This handler is called every time the IOCBF3 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCBF3_SetInterruptHandler(IOCBF3_DefaultInterruptHandler);

*/
void IOCBF3_DefaultInterruptHandler(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCBF4 pin functionality
 * @Example
    IOCBF4_ISR();
 */
void IOCBF4_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCBF4 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCBF4 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCBF4_SetInterruptHandler(MyInterruptHandler);

*/
void IOCBF4_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCBF4 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCBF4_SetInterruptHandler() method.
    This handler is called every time the IOCBF4 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCBF4_SetInterruptHandler(IOCBF4_InterruptHandler);

*/
extern void (*IOCBF4_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCBF4 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCBF4_SetInterruptHandler() method.
    This handler is called every time the IOCBF4 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCBF4_SetInterruptHandler(IOCBF4_DefaultInterruptHandler);

*/
void IOCBF4_DefaultInterruptHandler(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCCF6 pin functionality
 * @Example
    IOCCF6_ISR();
 */
void IOCCF6_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCCF6 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCCF6 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF6_SetInterruptHandler(MyInterruptHandler);

*/
void IOCCF6_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCCF6 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCCF6_SetInterruptHandler() method.
    This handler is called every time the IOCCF6 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF6_SetInterruptHandler(IOCCF6_InterruptHandler);

*/
extern void (*IOCCF6_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCCF6 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCCF6_SetInterruptHandler() method.
    This handler is called every time the IOCCF6 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF6_SetInterruptHandler(IOCCF6_DefaultInterruptHandler);

*/
void IOCCF6_DefaultInterruptHandler(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCCF7 pin functionality
 * @Example
    IOCCF7_ISR();
 */
void IOCCF7_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCCF7 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCCF7 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF7_SetInterruptHandler(MyInterruptHandler);

*/
void IOCCF7_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCCF7 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCCF7_SetInterruptHandler() method.
    This handler is called every time the IOCCF7 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF7_SetInterruptHandler(IOCCF7_InterruptHandler);

*/
extern void (*IOCCF7_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCCF7 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCCF7_SetInterruptHandler() method.
    This handler is called every time the IOCCF7 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF7_SetInterruptHandler(IOCCF7_DefaultInterruptHandler);

*/
void IOCCF7_DefaultInterruptHandler(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/