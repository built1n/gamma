#include <stdbool.h>
void init_isr();
void register_handler(unsigned int number, void(*fnPtr)(int));
void unregister_handler(unsigned int number);
void set_unhandled_panic(bool);
