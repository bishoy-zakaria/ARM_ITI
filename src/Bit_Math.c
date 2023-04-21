#include "Bit_Math.h"

u32 WriteBinaryVal(u32 reg ,u32 value, u32 startbit, u32 len)
{
   u32 mask   = 0;
   startbit++;
   mask = ((-1u)<<((32)-(startbit+len)));
   mask = ((mask)>>(32-len));
   mask = ((mask)<<(startbit-1));
   mask = ~mask;
   reg  = reg & mask;
   value = value <<(startbit-1);
   return reg|value;
}
