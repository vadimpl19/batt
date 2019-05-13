NAME get_port
;#include "io8515.h"     ; The #include file must be within the module
PUBLIC get_sp           ; Symbols to be exported to C function
RSEG CODE               ; This code is relocatable, RSEG
get_sp: ;               ;Label, start execution here
  MOVW R17:R16,R29:R28    ;in R17,PIND ; Read in the pinb value
  ret                     ; Return
END