#include <18F452.h>
#fuses HS,NOWDT,PROTECT,NOLVP
//#use delay(clock=20000000)
#use delay(clock=12000000)
#use rs232(baud=19200, xmit=PIN_C6, rcv=PIN_C7,ERRORS)

#use fast_io(A)
#use fast_io(B)
#use fast_io(C)
#use fast_io(D)
#use fast_io(E)

#define RTC_SDA  PIN_C3
#define RTC_SCL  PIN_C4

#define _b        PIN_A0
#define _a        PIN_A1
#define _clock_d  PIN_A3   // Clock    4094
#define _dat_d    PIN_A2   // Data     4094
#define _strob_d  PIN_A4   // Strobe   4094
#define _dots     PIN_A5

#define _oe       PIN_E0
#define _irs      PIN_E1
#define _bal      PIN_E2

#define _wapda    PIN_C1
#define _noz      PIN_C2
//#define _scl      PIN_C3
//#define _sda      PIN_C4
//#define _dat_k    PIN_C5   // Data     4094

#define  _tm      PIN_D0
//#define _pluser   PIN_D0
#define _51c      PIN_D1
//#define _clock_k  PIN_D2
#define _51_out   PIN_D3
//#define _strob_k  PIN_D4
#define _tm2      PIN_D5
#define _sp2      PIN_D6
#define _sp3      PIN_D7


#define  _p_busy  PIN_C0
#define  _4066    PIN_B0
#define  _s_skip  PIN_B1
#define  _led     PIN_B2
#define  _buz     PIN_B3
#define  _motor   PIN_B4
#define  _sov1    PIN_B5
#define  _sov2    PIN_B6
#define  _encoder PIN_B7

#define  _clear       15

#define  _print_off    output_high(_4066)
#define  _print_on    output_low(_4066)


#define  _buz_on   output_low(_buz)
#define  _buz_off    output_high(_buz)
#define  _motor_on   output_low(_motor)
#define  _motor_off  output_high(_motor)
#define  _sov1_on   output_low(_sov1)
#define  _sov1_off  output_high(_sov1)
#define  _sov2_on   output_low(_sov2)
#define  _sov2_off  output_high(_sov2)
#define  _totelizer_on     output_low(_tm)
#define  _totelizer_off    output_high(_tm)
#define  _tm2_off     output_low(_tm2)
#define  _tm2_on    output_high(_tm2)

#define  _noz_off  input(_noz)
#define  _noz_on  !input(_noz)

#define  _kror       10000000
#define  _ten_lakh   1000000
#define  _lakh       100000
#define  _ten_th     10000
#define  _thou       1000
#define  _hund       100
#define  _ten        10

static unsigned int8 day,month,yr,hrs,min,sec,dow;
static unsigned int8 _code_seq,_sub_id,_code_block,_skip_chk,_skip_var;
static short _clear_fl,_p_deci_fl,_deci_fl,_skip_fl,_disk_fl;
static short _sk_l_fl,_p_fl,_sk_sw_fl;
static int16 _pulses,_factor,_code_id,_ok_rate ;
static unsigned int8 _v_first_val,_rate_fact,_skip_liters,_ok_liters,_key2;
static unsigned int8 _p1,_p2,_p3,_p4,_p5,_P,_l,_C,_t,_r,_s,_add;
static unsigned int8 _num,_code_val,_sov_cut,_skip_val,_first_val,_skip_factor;
static int16  _rate,_skip_rupee,_m_code;
static int32 _rupee,_liters,_price,_petrol,_totel,_last_fill,_last_bill,_date,_to_val,_count;
static int32 _slips,_td,_hang,_dd1d,_dd2d,_totel2;
static unsigned int8  _dig[22],int_count,_d_count,_var1,_key1;
static short _noz_fl,_encoder_st,_on_fl,_incr_fl,_chk_fill,_price_fl,_oil_fl,_tc_fl,_pl_fl;
static short _skip_at_fl,_liter_fl,_change_fl,_rx_fl,_printer_fl,_motor_fl,am_pm;
static unsigned int8 _lasts,_tp,_motor_val,_rs232[5],_ir;

//static unsigned  int8 seg[20]={63,6,91,79,102,109,125,7,127,111,0,115,56,121,80,64,120,57,92,94};
// 0 1 2 3 4 5 6 7 8 9  P L E r - C o d
static unsigned  int8 seg[16]={0,1,4,5,8,9,12,13,2,3,6,7,10,11,14,15};
//0 1 2 3 4 5 6 7 8 9 L H P A - sp
static unsigned  int8 seg_p[16]={0,2,1,3,8,10,9,11,4,6,5,7,12,14,13,15};
//0 1 2 3 4 5 6 7 8 9 L H P A - sp

#define  _d1     _dig[10]
#define  _d2     _dig[7]
#define  _d3     _dig[8]
#define  _d4     _dig[13]
#define  _d5     _dig[14]
#define  _d6     _dig[11]
#define  _d7     _dig[12]
#define  _d8     _dig[6]

#define  _d9     _dig[9]
#define  _d11     _dig[15]
#define  _d10     _dig[16]
#define  _d12    _dig[17]
#define  _d13     _dig[2]
#define  _d14     _dig[3]
#define  _d15     _dig[5]
#define  _d16     _dig[4]
#define  _d17     _dig[18]
#define  _d18     _dig[19]
#define  _d19     _dig[20]
#define  _d20     _dig[21]
#define  _d21     _dig[1]
#define  _d22     _dig[0]

#include "keypad.c"
#include "ds1307.c"
#include "methods.c"
/*
#INT_EXT
 _int0(){
 int32 _sq;
   if(_chk_fill && _liters >= _petrol -1){
   ++_liters;
   ++_totel;
   _motor_off;
   _sov1_off;
   goto _pas;
   }
_count = _count + (int32)_factor;
_add = _count / 100;
   if(_add > 0){
      _count = _count % 100;
      _liters = _liters + _add;
      _totel = _totel + _add;
      _sq = _liters  % 100;
      _pas:
      _change_fl = 1;
  }//ADD
 }//pulser

*/
#INT_RB
void _encoder_isr() {
int32 _sq;
if(_encoder_st != input(_encoder) ){
if(!_disk_fl)_encoder_st = input(_encoder);
//   if(_chk_fill && _liters >= _petrol -1){
//   ++_liters;
//   ++_totel;
//   _motor_off;
//   _sov1_off;
//   goto _pas;
//   }
_count = _count + (int32)_factor;
_add = _count / 100;
   if(_add > 0){
      _count = _count % 100;
      _liters = _liters + _add;
      _totel = _totel + _add;
      _sq = _liters  % 100;
      _pas:
      _change_fl = 1;
  }//ADD
 }//pulser
}//main



#INT_TIMER2
void clock_isr(){
if(++int_count > 3){
_totelizer_off;
_tm2_off;
_buz_off;
}
}


#INT_RDA
rda_handler(){
_rs232[_ir] = getc();
if(_ir < 4)++_ir;
_rx_fl = 1;
}


void main() {
_init_system();
//_short2:
//if(_totel > (_hang * 100) && _hang > 0)goto _short2;
_buz_on;
delay_ms(300);
_buz_off;
delay_ms(200);
_buz_on;
delay_ms(500);
_buz_off;
//goto _bv;
////////////////////////////////////

_on_fl = 0;
_d1 = day / 10;
_d2 = day % 10;
_d3 = _clear;
_d4 = month / 10;
_d5 = month % 10;
_d6 = _clear;
_d7 = yr / 10;
_d8 = yr % 10;

_d9 = hrs / 10;
_d10 = hrs % 10;
_d11 = _clear;
_d12 = min / 10;
_d13 = min % 10;
_d14 = _clear;
_d15 = sec / 10;
_d16 = sec % 10;
_disp_data();
delay_ms(3500);
///////////////////////////////////
//_rupee = _date;
_liters = _r_e(51);
_petrol = _r_e(61);
if(_liters > 0)_rupee = _liters *_rate / 100;
_price =_r_e(71);
_var1 = _clear;
_all_disp();
_noz_fl = 1;
_disp1();
_noz_fl = 0;
_disp2();
_disp3(_rate);
_disp_data();

if(_liters > 0){
delay_ms(3000);
_totel = _totel + _liters;
_noz_fl = 1;
//   if(_noz_on && _noz_pad !=  1){
   if(_noz_on ){
   _to_val = _totel / 100;
   _factor = 10000 / (_pulses - (int16)_skip_val);
   _count = 0;
   _add = 0;
      if(_petrol > 0){
      _chk_fill = 1;
         if(_price >  0)_price_fl = 1;
         else _liter_fl = 1;
      _set_skip();
      }
      if(input(_wapda)){
      _stop_fill();
      goto _w_fail;
      }
   _motor_on;
   goto _continue;
   }else{
   _stop_fill();
   }
}
delay_ms(_thou);
for(_var1=0;_var1<10;++_var1){
_all_disp();
delay_ms(200);
}

_rset:
_var1 = _clear;
_all_disp();
_noz_fl = 1;
_rst();
 while(TRUE){
_short2:
if(_totel > (_hang * 100) && _hang > 0)goto _short2;

// _short:
//if((_totel / 100) > _hang && _hang > 0)goto _short;
//if((_totel / 100) > 3128)goto _short;

if(_on_fl){
   if(_liters <  8){
   _liters = 0;
   _rupee = 0;
   }
_control();
goto _rr;
}

_w_fail:
if(input(_wapda)){
_power_down();
}


//if(_noz_on && _noz_pad != 1){ ///nnnnnnnnnnnnnnnnnnnnnn
if(_noz_on){ ///nnnnnnnnnnnnnnnnnnnnnn
_of_pad:
delay_ms(500);
   if(_noz_fl == 0 ){
//   _buz_on;
   _rupee = 0;
   _liters = 0;
   _noz_fl = 1;
   _var1 = 8;
   _all_disp();
   _disp_data();
    delay_ms(700);
//    _buz_off;
//    delay_ms(200);
    _buz_on;
   _var1 = _clear;
   _all_disp();
   _disp_data();
    delay_ms(200);
    _buz_off;
   _disp1();
   _disp2();
   _disp3(_rate);
   _disp_data();
    delay_ms(70);
   _buz_on;
   delay_ms(200);
_continue:
_totel2 = _totel;
   _on_fl = 1;
   _p_fl = 1;
   if(_liters == 0)_initilize();
   _sov1_on;
   delay_ms(30);
   _buz_off;
   if(!_motor_fl){
   _motor_on;
   }else{
   delay_ms(1500);
   _motor_on;
   }
_encoder_st = input(_encoder);
   delay_ms(100);
enable_interrupts(GLOBAL);
enable_interrupts(INT_RB);
enable_interrupts(INT_Timer2);
setup_timer_2(T2_DIV_BY_16, 255, 16);

//set_tris_b(0b11110111);
//enable_interrupts(INT_RB);
  }
 }else{
_rr:
_on_fl = 0;
_noz_fl = 0;
_motor_off;
_sov1_off;
_sov2_off;
scan_keypad();
//if(_key1 > 0){
//_liters = (int32)_key1;
//_disp2();
//_disp_data();
//}
if(_key1 != 0){
_key_p:
//if(_key1 == _f4){
//_get_slip();
//delay_ms(1000);
//}
   if(_key1 > 16 && _key1 < 22 ){
      if(!_oil_fl)_price_enter();
   }
  if(_key1 > 0 && _key1 < 10)  _price_set();
  if(_key1 == _p) _price_enter();

  if(_key1 == 10){
   _buz_on;
   _get_slip();///////////////////////////////////PRINTER
   _buz_off;
   delay_ms(1000);
   _key1 = 0;
  }

   if(_key1 == _r ){
   _var1 =_clear;
   _all_disp();
   delay_ms(100);
   _d9  = 12;
   _d10 = 5;
//   _d19 = 0;
//   _d20 = 0;
//   _d21 = 0;
//   _d22 = 0;
   _disp_data();
   _main_code_enter();
   if(_code_block > 0)_code_id_enter();
   delay_ms(1000);
   goto _kp;
   }
   _num_press();
   if(_num > 0){
   _code_val = 0;
   _price_set();
   }

  if(_key1 == _l){
  _deci_fl = 0;
  _code_val = 0;
  _petrol_set();
  _oil_fl = 0;
  }
    if(_key1 == _t ){
   _var1 =_clear;
   _all_disp();
   _totel_disp();
   }

   if(_key1 == _r && _skip_var == 1){
   _skip_fl = 1;
   _var1 =_clear;
   _all_disp();
   }

   if(_key1 == _C){
   _c_rst:
   _petrol = 0;
   _price = 0;
   goto _rset;
   }

//   if(_noz_pad == 1){
//      if(_key1 == _r)goto _of_pad;
//   }

   if (_key1 == _p ) goto _key_p;
}
_kp:
delay_ms(50);
output_toggle(_led);
 }
 }// #END while(TRUE)
}// #END main()






//****************************************************************************//
//********************************* END **************************************//
//****************************************************************************//

