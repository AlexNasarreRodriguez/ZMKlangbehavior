# Add your custom behavior source files here.
# For each behavior, you'll need a line like the one below.
# Replace MY_BEHAVIOR with the actual name of your behavior and update the source file path.

if ((NOT CONFIG_ZMK_SPLIT) OR CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
  target_sources_ifdef(CONFIG_ZMK_BEHAVIOR_LANG_TOGGLE app PRIVATE behaviors/behavior_lang_toggle.c)
endif()
