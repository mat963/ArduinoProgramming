#include "driver/mcpwm.h"
#include <math.h>

#define PWM_PIN_HIN 18   // IR2110 HIN
#define PWM_PIN_LIN 19   // IR2110 LIN

// Parameter für Sinus-PWM
#define SINUS_STEPS   200          // Anzahl Schritte pro Periode
#define SINUS_PERIOD  20           // Periodendauer in ms (entspricht 50 Hz)

void setup() {
  mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, PWM_PIN_HIN);
  mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0B, PWM_PIN_LIN);

  mcpwm_config_t cfg = {};
  cfg.frequency     = 20000;                 // 20 kHz PWM
  cfg.cmpr_a        = 0.0;                   // Startwert Duty
  cfg.cmpr_b        = 0.0;
  cfg.counter_mode  = MCPWM_UP_DOWN_COUNTER; // Center-aligned
  cfg.duty_mode     = MCPWM_DUTY_MODE_0;
  mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &cfg);

  mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, MCPWM_DUTY_MODE_0);
  mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, MCPWM_DUTY_MODE_0);

  mcpwm_deadtime_enable(MCPWM_UNIT_0, MCPWM_TIMER_0,
                        MCPWM_ACTIVE_HIGH_COMPLIMENT_MODE,
                        1, 1); // 200 ns Dead-Time
}

void loop() {
  static int step = 0;

  // Sinuswert berechnen (0…100%)
  float angle = 2.0f * M_PI * step / SINUS_STEPS;
  float duty  = (sin(angle) * 0.5f + 0.5f) * 100.0f; // Normiert auf 0…100%

  // Duty setzen
  mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, duty);

  // Schritt erhöhen
  step++;
  if (step >= SINUS_STEPS) step = 0;

  // Zeit zwischen Schritten (Periodendauer / Anzahl Schritte)
  delay(SINUS_PERIOD * 1000 / SINUS_STEPS);
}
