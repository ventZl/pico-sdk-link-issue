#include <pico/stdlib.h>
#include "library.h"

void libmain()
{
    while (1) {
        gpio_put(PICO_DEFAULT_LED_PIN, 1);
        sleep_us(500000);
        gpio_put(PICO_DEFAULT_LED_PIN, 0);
        sleep_us(500000);

    }
}
