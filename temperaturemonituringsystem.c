#include <xc.h>
#include <stdio.h>

#define _XTAL_FREQ 4000000

// CONFIGURATION BITS
#pragma config FOSC = XT
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF


// LCD control pins
#define RS      RB0
#define EN      RB1

// LED
#define LED     RB2


// Function declarations
void LCD_Command(unsigned char cmd);
void LCD_Data(unsigned char data);
void LCD_Init(void);
void LCD_String(const char *str);

void ADC_Init(void);
unsigned int ADC_Read(void);



// LCD COMMAND

void LCD_Command(unsigned char cmd)
{
    RS = 0;

    // Send upper 4 bits
    PORTB = (PORTB & 0x0F) | (cmd & 0xF0);

    EN = 1;
    __delay_ms(2);
    EN = 0;

    // Send lower 4 bits
    PORTB = (PORTB & 0x0F) | ((cmd << 4) & 0xF0);

    EN = 1;
    __delay_ms(2);
    EN = 0;

    __delay_ms(2);
}


// LCD DATA

void LCD_Data(unsigned char data)
{
    RS = 1;

    // Send upper 4 bits
    PORTB = (PORTB & 0x0F) | (data & 0xF0);

    EN = 1;
    __delay_ms(2);
    EN = 0;

    // Send lower 4 bits
    PORTB = (PORTB & 0x0F) | ((data << 4) & 0xF0);

    EN = 1;
    __delay_ms(2);
    EN = 0;

    __delay_ms(2);
}



// LCD INITIALIZATION

void LCD_Init(void)
{
    __delay_ms(20);

    LCD_Command(0x02);     // 4-bit mode
    LCD_Command(0x28);     // 2 lines, 5x8 matrix
    LCD_Command(0x0C);     // Display ON, cursor OFF
    LCD_Command(0x06);     // Increment cursor
    LCD_Command(0x01);     // Clear display

    __delay_ms(5);
}



// LCD STRING

void LCD_String(const char *str)
{
    while(*str)
    {
        LCD_Data(*str);
        str++;
    }
}



// ADC INITIALIZATION

void ADC_Init(void)
{
    // AN0 = analog
    // Other AN pins = digital
    // Right justified result
    ADCON1 = 0x8E;

    // ADC ON
    // Select AN0
    ADCON0 = 0x81;

    __delay_ms(2);
}



// ADC READ

unsigned int ADC_Read(void)
{
    unsigned int result;

    // Select AN0
    ADCON0 &= 0xC5;

    // Acquisition time
    __delay_us(20);

    // Start ADC conversion
    GO_nDONE = 1;

    // Wait until conversion finishes
    while(GO_nDONE);

    // Combine ADRESH and ADRESL
    result = ((unsigned int)ADRESH << 8) | ADRESL;

    return result;
}



// MAIN

void main(void)
{
    unsigned int adc_value;
    unsigned int temperature;
    char text[16];

    // RA0 = input
    TRISA = 0xFF;

    // PORTB = output
    TRISB = 0x00;

    // Clear ports
    PORTA = 0x00;
    PORTB = 0x00;

    // Initialize ADC
    ADC_Init();

    // Initialize LCD
    LCD_Init();

    // LED initially OFF
    LED = 0;

    while(1)
    {
        // Read LM35
        adc_value = ADC_Read();

        // Convert ADC value to temperature
        //
        // ADC voltage = ADC value × 5 / 1023
        //
        // LM35 = 10mV per °C
        //
        // Temperature = ADC value × 500 / 1023

        temperature = (adc_value * 500UL) / 1023;

        // Display temperature
        LCD_Command(0x80);
        LCD_String("Temperature:");

        LCD_Command(0xC0);

        sprintf(text, "%u C       ", temperature);
        LCD_String(text);


        
        // TEMPERATURE ALERT
        

        if(temperature >= 35)
        {
            // LED ON
            LED = 1;
            __delay_ms(500);

            // LED OFF
            LED = 0;
            __delay_ms(500);
        }
        else
        {
            // Temperature normal
            LED = 0;

            __delay_ms(500);
        }
    }
}