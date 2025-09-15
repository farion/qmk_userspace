SRC += keyboards/splitkb/halcyon/elora/keymaps/farion_hlc/tapdance.c
#SRC += keyboards/splitkb/halcyon/elora/keymaps/farion_hlc/rgbmatrix.c

#ENCODER_MAP_ENABLE = yes
#RGB_MATRIX_DRIVER = ws2812
CAPS_WORD_ENABLE = yes
TAP_DANCE_ENABLE = yes
CONSOLE_ENABLE = yes
WPM_ENABLE = yes
RAW_ENABLE = yes
LAYER_LOCK_ENABLE = yes
RGB_MATRIX_CUSTOM_USER = yes
COMBO_ENABLE = yes

# This adds module functionality to your keyboard (files found in users/halcyon_modules)
USER_NAME := halcyon_modules
