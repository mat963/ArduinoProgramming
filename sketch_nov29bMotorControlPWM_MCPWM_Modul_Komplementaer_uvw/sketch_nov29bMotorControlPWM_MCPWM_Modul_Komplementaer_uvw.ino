#include "driver/mcpwm.h"
#include <math.h>

#define PWM_PIN_U_HIN 18
#define PWM_PIN_U_LIN 19
#define PWM_PIN_V_HIN 25
#define PWM_PIN_V_LIN 26
#define PWM_PIN_W_HIN 32
#define PWM_PIN_W_LIN 33

#define SINUS_STEPS   200
#define SINUS_PERIOD  1   // ms → 50 Hz die Zeit ist wohl in Sekunden nicht ms

void setup() {
  // Pins zuordnen
  mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, PWM_PIN_U_HIN);
  mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0B, PWM_PIN_U_LIN);
  mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM1A, PWM_PIN_V_HIN);
  mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM1B, PWM_PIN_V_LIN);
  mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM2A, PWM_PIN_W_HIN);
  mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM2B, PWM_PIN_W_LIN);
  // Grundkonfiguration
  mcpwm_config_t cfg = {};
  cfg.frequency     = 20000;
  cfg.cmpr_a        = 0.0;
  cfg.cmpr_b        = 0.0;
  cfg.counter_mode  = MCPWM_UP_DOWN_COUNTER;
  cfg.duty_mode     = MCPWM_DUTY_MODE_0;

  mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &cfg);
  mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_1, &cfg);
  mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_2, &cfg);

// Duty-Mode pro Ausgang (Polarität festlegen)
  mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, MCPWM_DUTY_MODE_0); // aktiv = High
  mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, MCPWM_DUTY_MODE_0); // aktiv = High (Komplement + Dead-Time regelt Nicht-Überlappung)

 // Duty-Mode pro Ausgang (Polarität festlegen)
  mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_A, MCPWM_DUTY_MODE_0); // aktiv = High
  mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_B, MCPWM_DUTY_MODE_0); // aktiv = High (Komplement + Dead-Time regelt Nicht-Überlappung)
 
 // Duty-Mode pro Ausgang (Polarität festlegen)
  mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_2, MCPWM_OPR_A, MCPWM_DUTY_MODE_0); // aktiv = High
  mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_2, MCPWM_OPR_B, MCPWM_DUTY_MODE_0); // aktiv = High (Komplement + Dead-Time regelt Nicht-Überlappung)
 /*
mcpwm_sync_enable(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_SELECT_SYNC0, MCPWM_SYNC_UP_DOWN_COUNTER);
mcpwm_sync_enable(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_SELECT_SYNC0, MCPWM_SYNC_UP_DOWN_COUNTER);
mcpwm_sync_enable(MCPWM_UNIT_0, MCPWM_TIMER_2, MCPWM_SELECT_SYNC0, MCPWM_SYNC_UP_DOWN_COUNTER);
*/


  // Komplementäre Ausgabe mit Dead-Time aktivieren
  // RED/FED in ns (z. B. 200 ns je Flanke)
  mcpwm_deadtime_enable(MCPWM_UNIT_0, MCPWM_TIMER_0,
                        MCPWM_ACTIVE_HIGH_COMPLIMENT_MODE,
                        1, 1);// bei 1 entspricht 200ns, 0 entspricht 100ns, 2 entspricht 300ns, 3 entspricht 400ns

  // Komplementäre Ausgabe mit Dead-Time aktivieren
  // RED/FED in ns (z. B. 200 ns je Flanke)
  mcpwm_deadtime_enable(MCPWM_UNIT_0, MCPWM_TIMER_1,
                        MCPWM_ACTIVE_HIGH_COMPLIMENT_MODE,
                        1, 1);// bei 1 entspricht 200ns, 0 entspricht 100ns, 2 entspricht 300ns, 3 entspricht 400ns

  // Komplementäre Ausgabe mit Dead-Time aktivieren
  // RED/FED in ns (z. B. 200 ns je Flanke)
  mcpwm_deadtime_enable(MCPWM_UNIT_0, MCPWM_TIMER_2,
                        MCPWM_ACTIVE_HIGH_COMPLIMENT_MODE,
                        1, 1);// bei 1 entspricht 200ns, 0 entspricht 100ns, 2 entspricht 300ns, 3 entspricht 400ns

}

void loop() {
  static int step = 0;
  float angle = 2.0f * M_PI * step / SINUS_STEPS;

  float dutyU = (sin(angle) * 0.5f + 0.5f) * 100.0f;
  float dutyV = (sin(angle + 2.0f*M_PI/3.0f) * 0.5f + 0.5f) * 100.0f;
  float dutyW = (sin(angle + 4.0f*M_PI/3.0f) * 0.5f + 0.5f) * 100.0f;

  mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, dutyU);
  mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_A, dutyV);
  mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_2, MCPWM_OPR_A, dutyW);

  step++;
  if (step >= SINUS_STEPS) step = 0;

  delay(SINUS_PERIOD * 1000 / SINUS_STEPS);
}
