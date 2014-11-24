#if !defined(BMC_H)
#define BMC_H

#define BCM2708_PERI_BASE        0x20000000
#define GPIO_BASE                (BCM2708_PERI_BASE + 0x200000) /* GPIO controller */
#define MAXTIMINGS 100

#define PIN22 22
#define PIN23 23

void ControlPin(int pin, int state);
void InitPin(int pin);

#endif /* BMC_H */
