#define _strob    PIN_A1   // Strobe   4094
#define _dat      PIN_A3   // Data     4094
#define _clock    PIN_A0   // Clock    4094

static int8 j;

void cd4094(int8 __data) {
//   output_low(_strob);
   for (j=0;j<=7;++j){
      if(bit_test(__data,7)){
         output_high(_dat);
      }
      else{
         output_low(_dat);
      }
      rotate_left(&__data,1);
      output_low(_clock);
      delay_us(10);
      output_high(_clock);
   }
   output_low(_strob);
delay_us(10);
   output_high(_strob);
}
