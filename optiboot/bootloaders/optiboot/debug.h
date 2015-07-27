// Macros for debug
#ifdef DEBUG_ENABLED
  #define DEBUG(x) putch(x)
#else
  #define DEBUG(x)
#endif