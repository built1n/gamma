void init_isr();
void register_handler(unsigned char number, void(*fnPtr)(int));
void unregister_handler(unsigned char number);
