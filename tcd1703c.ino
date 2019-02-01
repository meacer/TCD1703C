// Clock generator to drive a Toshiba TCD1703C CCD sensor.

// Default clock speed is 16MHz on Arduino Uno
#define CLK 16000000UL

#define SH   PORTB0  //digital pin 8
#define PHI1 PORTB1  //digital pin 9 (PWM)
#define PHI2 PORTB2  //digital pin 10 (PWM)
#define RS   PORTB3  //digital pin 11 (PWM)
#define CP   PORTB4  //digital pin 12

#define TOTAL_STEPS (3825)
#define CLK_STEP_US 16

void setup() {
  DDRB = B00011111;
  PORTB = B00000000;
  noInterrupts();
}

void delayCnt(int count) {
  for (int i = 0; i < count; i++) {
    __asm__ __volatile__ ("nop\n\t");
  }
}

// Generates RS and a delayed CP pulse.
void RS_CP() {
  PORTB |= (1 << RS);
  delayCnt(1);

  PORTB &= ~(1 << RS);
  delayCnt(1);

  PORTB |= (1 << CP);
  delayCnt(1);

  PORTB &= ~(1 << CP);
  delayCnt(1);
}

void loop() {
  PORTB = (0 << RS) | (0 << CP) | (1 << PHI1) | (0 << PHI2) | (0 << SH);
  delayCnt(1);

  RS_CP();

  PORTB |= (1 << SH);
  delayCnt(1);

  PORTB &= ~(1 << SH);
  delayCnt(1);

  RS_CP();

  for (int cnt = 0; cnt < TOTAL_STEPS; cnt++) {
    PORTB = (0 << RS) | (0 << CP) | (0 << PHI1) | (1 << PHI2) | (0 << SH);
    delayCnt(2);

    RS_CP();

    PORTB = (0 << RS) | (0 << CP) | (1 << PHI1) | (0 << PHI2) | (0 << SH);
    delayCnt(8);
  }
}
