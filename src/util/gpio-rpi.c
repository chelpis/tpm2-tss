#include "gpio-rpi.h"
#include "stdlib.h"


#define SETUP_PIN(_p)   \
    GPIO_SET_MODE(_p, PI_OUTPUT);   \
    GPIO_WRITE(_p, GPIO_INACTIVE)


void gpio_init(void)
{
    GPIO_INITIALISE();
    SETUP_PIN(GPIO_PIN_TSS);
    SETUP_PIN(GPIO_PIN_CTX);
    SETUP_PIN(GPIO_PIN_SCT);
    atexit(gpio_deinit);
}

void gpio_deinit(void)
{
    GPIO_SET_MODE(GPIO_PIN_TSS, PI_INPUT);
    GPIO_SET_MODE(GPIO_PIN_CTX, PI_INPUT);
    GPIO_SET_MODE(GPIO_PIN_SCT, PI_INPUT);
}