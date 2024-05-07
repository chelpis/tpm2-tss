#ifndef UTIL_GPIO_H__
#define UTIL_GPIO_H__

#define ENABLE_GPIO     // toggle feature
#ifdef ENABLE_GPIO

#define GPIO_VERBOSE
#define GPIO_ACTIVE     1   //high
#define GPIO_INACTIVE   (1-GPIO_ACTIVE)

/* ASSUMES RASPBERRY PI */
/* Expecting reasonably low latency on ALL raspberry pi models*/
#include "pigpio.h"

/* These pins are not used by IFX TPM SLB 9672 RaspberryPi® Evaluation board */
#define GPIO_PIN_TSS    (17)    // indicat whether TSS is initialized
#define GPIO_PIN_CTX    (27)    // indicate operations on TSS context file (load / save)
#define GPIO_PIN_SCT    (22)    // indicate operation on secret (keygen / sign)


void gpio_init(void);
void gpio_deinit(void);


/* avoid extra latency by directly calling pigpio through macros  */
#ifdef GPIO_VERBOSE
#include "stdio.h"
#define GPIO_INITIALISE()               printf("gpioInitialise() = %d\n", gpioInitialise())
#define GPIO_TERMINATE()                gpioTerminate(); printf("gpioTerminate()\n")
#define GPIO_SET_MODE(_p, _m)           printf("gpioSetMode(%d, %d) = %d\n", _p, _m, gpioSetMode(_p, _m))
#define GPIO_WRITE(_p, _s)              printf("gpioWrite(%d, %d) = %d\n", _p, _s, gpioWrite(_p, _s))
#else   // #ifdef GPIO_VERBOSE
#define GPIO_INITIALISE()               gpioInitialise()
#define GPIO_TERMINATE()                gpioTerminate()
#define GPIO_SET_MODE(_p, _m)           gpioSetMode(_p, _m)
#define GPIO_WRITE(_p, _s)              gpioWrite(_p, _s)
#endif  // #ifdef GPIO_VERBOSE

#define gpio_set_pin_tss()              GPIO_WRITE(GPIO_PIN_TSS, GPIO_ACTIVE)
#define gpio_clear_pin_tss()            GPIO_WRITE(GPIO_PIN_TSS, GPIO_INACTIVE)
#define gpio_clear_pin_tss_if_error(_r) if (_r) {GPIO_WRITE(GPIO_PIN_TSS, GPIO_INACTIVE);}
#define gpio_set_pin_ctx()              GPIO_WRITE(GPIO_PIN_CTX, GPIO_ACTIVE)
#define gpio_clear_pin_ctx()            GPIO_WRITE(GPIO_PIN_CTX, GPIO_INACTIVE)
#define gpio_clear_pin_ctx_if_error(_r) if (_r) {GPIO_WRITE(GPIO_PIN_CTX, GPIO_INACTIVE);}
#define gpio_set_pin_sct()              GPIO_WRITE(GPIO_PIN_SCT, GPIO_ACTIVE)
#define gpio_clear_pin_sct()            GPIO_WRITE(GPIO_PIN_SCT, GPIO_INACTIVE)
#define gpio_clear_pin_sct_if_error(_r) if (_r) {GPIO_WRITE(GPIO_PIN_SCT, GPIO_INACTIVE);}

#else   // #ifdef ENABLE_GPIO

#define gpio_set_pin_tss()
#define gpio_clear_pin_tss()
#define gpio_clear_pin_tss_if_error(_r)
#define gpio_set_pin_ctx()
#define gpio_clear_pin_ctx()
#define gpio_clear_pin_ctx_if_error(_r)
#define gpio_set_pin_sct()
#define gpio_clear_pin_sct()
#define gpio_clear_pin_sct_if_error(_r)

#endif  // #ifdef ENABLE_GPIO

#endif