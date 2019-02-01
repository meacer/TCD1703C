// Clock generator to drive a Toshiba TCD1703C CCD sensor.

// Default clock speed is 16MHz on Arduino Uno.
#define CLK 16000000UL

#define SH   PORTB0  // Digital pin 8.
#define PHI1 PORTB1  // Digital pin 9 (PWM).
#define PHI2 PORTB2  // Digital pin 10 (PWM).
#define RS   PORTB3  // Digital pin 11 (PWM).
#define CP   PORTB4  // Digital pin 12.

#define TOTAL_STEPS (3825)

#define NOP __asm__ __volatile__ ("nop\n\t")
#define DELAY1 NOP;
#define DELAY2 NOP; NOP;
#define DELAY4 DELAY2; DELAY2;
#define DELAY8 DELAY4; DELAY4;

void setup() {
  DDRB = B00011111;
  PORTB = B00000000;
  noInterrupts();
}

// Generates RS and a delayed CP pulse.
void RS_CP() {
  PORTB |= (1 << RS);
  DELAY1;

  PORTB &= ~(1 << RS);
  DELAY1;

  PORTB |= (1 << CP);
  DELAY1;

  PORTB &= ~(1 << CP);
  DELAY1;
}

void loop() {
  PORTB = (0 << RS) | (0 << CP) | (1 << PHI1) | (0 << PHI2) | (0 << SH);
  DELAY1;

  RS_CP();

  PORTB |= (1 << SH);
  DELAY1;

  PORTB &= ~(1 << SH);
  DELAY1;

  RS_CP();

  for (int cnt = 0; cnt < TOTAL_STEPS; cnt++) {
    PORTB = (0 << RS) | (0 << CP) | (0 << PHI1) | (1 << PHI2) | (0 << SH);
    DELAY2;

    RS_CP();

    PORTB = (0 << RS) | (0 << CP) | (1 << PHI1) | (0 << PHI2) | (0 << SH);
    DELAY8;
  }
}
