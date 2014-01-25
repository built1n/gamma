#define panic(a) kpanic(a, __FILE__, __LINE__)
void kpanic(const char*, const char*, int);


