#pragma once

#include <zephyr/kernel.h>

// Enum for language states
enum language {
    LANG_FIRST, // Represents the first language (e.g., Spanish)
    LANG_SECOND, // Represents the second language (e.g., English)
    LANG_COUNT // Total number of languages
};

/**
 * @brief Holds the current language state.
 * 
 * This is an atomic variable to ensure thread-safe access from different parts
 * of the ZMK firmware.
 */
extern atomic_t zmk_lang_state;

/**
 * @brief Get the current language state.
 * 
 * @return The current language as the enum `language`.
 */
enum language zmk_lang_toggle_get_state(void);
