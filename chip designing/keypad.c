#define _strob    PIN_D4   // Strobe   4094
#define _dat      PIN_C5   // Data     4094
#define _clock    PIN_D2   // Clock    4094

static int8 j;
void _keys(int8 __data){
   output_low(_strob);
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
//   output_low(_strob);
//delay_us(10);
}
//______________________________________________________________________________
void _key_id(int8 _v1 ,int8 _v3) {
_keys(_v1);
output_high(_strob);
   if(_v3 == 0){
   output_high(_51c);
   output_low(_clock);
   output_low(_dat);
   }
   if(_v3 == 1){
   output_high(_51c);
   output_low(_clock);
   output_high(_dat);
   }
   if(_v3 == 2){
   output_high(_51c);
   output_high(_clock);
   output_high(_dat);
   }
}

//////////////////////////////////////////////////////
void scan_keypad(){
int8 _k;
_key1 = 0;
for (_k=0;_k<3;++_k){
_key_id(253,_k);
if(!input(_51_out)){
if(_k == 0)_key1 = 13;//1
if(_k == 1)_key1 = 10; //2
if(_k == 2)_key1 = 18; //3
goto _return;
}
}
for (_k=0;_k<3;++_k){
_key_id(251,_k);
if(!input(_51_out)){
if(_k == 0)_key1 = 3; //4
if(_k == 1)_key1 = 12; //5
if(_k == 2)_key1 = 11; //6
goto _return;
}
}
for (_k=0;_k<3;++_k){
_key_id(247,_k);
if(!input(_51_out)){
if(_k == 0)_key1 = 6; //7
if(_k == 1)_key1 = 9; //8
if(_k == 2)_key1 = 16; //9
goto _return;
}
}
for (_k=0;_k<3;++_k){
_key_id(239,_k);
if(!input(_51_out)){
if(_k == 0)_key1 = 4; //10
if(_k == 1)_key1 = 15; //11
if(_k == 2)_key1 = 20; //12
goto _return;
}

}
for (_k=0;_k<3;++_k){
_key_id(223,_k);
if(!input(_51_out)){
if(_k == 0)_key1 = 1; //13
if(_k == 1)_key1 = 14;
if(_k == 2)_key1 = 21;
goto _return;
}
}
for (_k=0;_k<3;++_k){
_key_id(191,_k);
if(!input(_51_out)){
if(_k == 0)_key1 = 5; //16
if(_k == 1)_key1 = 7; //
if(_k == 2)_key1 = 17; //
goto _return;
}
}
for (_k=0;_k<3;++_k){
_key_id(127,_k);
if(!input(_51_out)){
if(_k == 0)_key1 = 2; //19
if(_k == 1)_key1 = 8; //
if(_k == 2)_key1 = 19; //
goto _return;
}
}
_return:
if(!input(_51_out)){
   _buz_on;
   delay_ms(20);
_kb:
delay_ms(10);
if(!input(_51_out))goto _kb;
_buz_off;
}
}


