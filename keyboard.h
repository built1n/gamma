void init_ps2();
void register_keyboard_handler(void(*fnPtr)(char)); // register 1 function to call when a key is pressed
void *get_keyboard_handler();
