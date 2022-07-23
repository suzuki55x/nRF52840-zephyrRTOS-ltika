#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>

#define SLEEP_TIME_MS 1000

#define LED0_NODE DT_ALIAS(led0)

#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
  #define LED0 DT_GPIO_LABEL(LED0_NODE, gpios)
  #define PIN DT_GPIO_PIN(LED0_NODE, gpios)
  #define FLAGS DT_GPIO_FLAGS(LED0_NODE, gpios)
#else
  #error "Unsupported board: led0 devicetree alias is not defined"
  #define LED0 ""
  #define PIN 0
  #define FLAGS 0
#endif


void main(void)
{

  const struct device *dev;
  bool led_is_on = true;
  int ret;

  dev = device_get_binding(LED0);
  if (dev == NULL) {
    return;
  }

  ret = gpio_pin_configure(dev, PIN, GPIO_OUTPUT_ACTIVE | FLAGS);
  if (ret < 0) {
    return;
  }

  while (1) {
    gpio_pin_set(dev, PIN, (int)led_is_on);
    led_is_on = !led_is_on;
    k_msleep(SLEEP_TIME_MS);
  }

}
