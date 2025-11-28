#include "driver/mcpwm.h"

#define PWM_PIN_HIN 18   // IR2110 HIN
#define PWM_PIN_LIN 19   // IR2110 LIN

void setup() {
  // Pins den Operatoren zuordnen
  mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, PWM_PIN_HIN);
  mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0B, PWM_PIN_LIN);

  // Grundkonfiguration
  mcpwm_config_t cfg = {};
  cfg.frequency     = 20000;                 // 20 kHz
  cfg.cmpr_a        = 60.0;                  // 60% für A
  cfg.cmpr_b        = 0.0;                   // B wird komplementär erzeugt
  cfg.counter_mode  = MCPWM_UP_DOWN_COUNTER; // Center-aligned
  cfg.duty_mode     = MCPWM_DUTY_MODE_0;     // "aktiv = High" (A)
  mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &cfg);

  // Duty-Mode pro Ausgang (Polarität festlegen)
  mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, MCPWM_DUTY_MODE_0); // aktiv = High
  mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, MCPWM_DUTY_MODE_0); // aktiv = High (Komplement + Dead-Time regelt Nicht-Überlappung)

  // Komplementäre Ausgabe mit Dead-Time aktivieren
  // RED/FED in ns (z. B. 200 ns je Flanke)
  mcpwm_deadtime_enable(MCPWM_UNIT_0, MCPWM_TIMER_0,
                        MCPWM_ACTIVE_HIGH_COMPLIMENT_MODE,
                        1, 1);// bei 1 entspricht 200ns, 0 entspricht 100ns, 2 entspricht 300ns, 3 entspricht 400ns
}

void loop() {
  // Duty für A ändern, B folgt komplementär mit Dead-Time
  mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, 60.0);
  delay(1000);
}
