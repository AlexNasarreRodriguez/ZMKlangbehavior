#define DT_DRV_COMPAT zmk_behavior_lang_toggle

#include <zephyr/device.h>
#include <drivers/behavior.h>
#include <zephyr/logging/log.h>

#include "behavior_lang_toggle.h"

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

// Global variable to hold the current language state.
atomic_t zmk_lang_state = ATOMIC_INIT(LANG_FIRST);

enum language zmk_lang_toggle_get_state(void) {
    return (enum language)atomic_get(&zmk_lang_state);
}

static int behavior_lang_toggle_init(const struct device *dev) {
    // Initialize the language state to the first language.
    atomic_set(&zmk_lang_state, LANG_FIRST);
    return 0;
}

static int on_keymap_binding_pressed(struct zmk_behavior_binding *binding,
                                     const struct zmk_position_state_changed *position_state) {
    // Toggle the language state
    LOG_DBG("Toggling language state");
    atomic_t current_state = atomic_get(&zmk_lang_state);
    atomic_set(&zmk_lang_state, (current_state + 1) % LANG_COUNT);
    return ZMK_BEHAVIOR_OPAQUE;
}

static const struct behavior_driver_api behavior_lang_toggle_driver_api = {
    .binding_pressed = on_keymap_binding_pressed,
};

DEVICE_DT_INST_DEFINE(0, behavior_lang_toggle_init, NULL, NULL, NULL,
                      APPLICATION, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,
                      &behavior_lang_toggle_driver_api);
