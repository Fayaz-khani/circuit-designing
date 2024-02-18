//+++++++++++++++++++++++++++++
static int32 _r_e(int8 _eloc ){
int8 _a1,_a2,_a3,_a4;
int32 _e_temp;
 _a1 = read_eeprom(_eloc);
 _a2 = read_eeprom(++_eloc);
 _a3 = read_eeprom(++_eloc);
 _a4 = read_eeprom(++_eloc);
 _e_temp = make32(_a4,_a3,_a2,_a1);
if(_e_temp > 99999999)_e_temp = 0;
return _e_temp;
}
//+++++++++++++++++++++++++++++
void _w_e(int8 _eloc , int32 _e_val ){
int8 _a1,_a2,_a3,_a4;
   _a1 = make8(_e_val,0);
   _a2 = make8(_e_val,1);
   _a3 = make8(_e_val,2);
   _a4 = make8(_e_val,3);
   write_eeprom(_eloc ,_a1);
   write_eeprom(++_eloc,_a2);
   write_eeprom(++_eloc,_a3);
   write_eeprom(++_eloc,_a4);
}
//+++++++++++++++++++++++++++++++
void _w_eerom(void){
int8 _x1,_x2;
   write_eeprom(0,_sov_cut);
   write_eeprom(1,_v_first_val);
   write_eeprom(2,_first_val);
   write_eeprom(3,_skip_rupee);
   write_eeprom(4,_rate_fact);
   write_eeprom(5,_skip_liters);
   write_eeprom(6,_ok_liters);
//   write_eeprom(7,_desi_d1);
//   write_eeprom(8,_desi_d2);
//   write_eeprom(9,_desi_d3);
   _x1 = make8(_rate, 0);
   _x2 = make8(_rate, 1);
   write_eeprom(10 ,_x1);
   write_eeprom(11,_x2);
   _x1 = make8(_ok_rate, 0);
   _x2 = make8(_ok_rate, 1);
   write_eeprom(12 ,_x1);
   write_eeprom(13,_x2);
   _x1 = make8(_pulses, 0);
   _x2 = make8(_pulses, 1);
   write_eeprom(14 ,_x1);
   write_eeprom(15,_x2);
   _w_e(16 , _totel);
   _w_e(20 ,_last_fill);
   _w_e(24 ,_last_bill);
   _w_e(28 , _hang);
   _w_e(32 , _slips);
//   write_eeprom(36,_noz_pad);
   _x1 = make8(_m_code, 0);
   _x2 = make8(_m_code, 1);
   write_eeprom(37 ,_x1);
   write_eeprom(38,_x2);
   write_eeprom(39,_skip_var);
 if(_disk_fl)write_eeprom(40,1);
 else write_eeprom(40,0);
 if(_motor_fl)write_eeprom(41,1);
 else write_eeprom(41,0);

}
//___________________________________
void _r_eerom(void){
int8 _x1,_x2;
 _sov_cut = read_eeprom(0);
if(_sov_cut > 40)_sov_cut = 20;
 _v_first_val = read_eeprom(1);
if(_v_first_val > 10)_v_first_val = 0;
 _first_val = read_eeprom(2);
if(_first_val > 10)_first_val = 0;
 _skip_rupee = read_eeprom(3);
if(_skip_rupee > 30)_skip_rupee = 0;
 _rate_fact = read_eeprom(4);
if(_rate_fact > 10)_rate_fact = 0;
 _skip_liters = read_eeprom(5);
if(_skip_liters > 30)_skip_liters = 0;
 _ok_liters = read_eeprom(6);
if(_ok_liters > 99)_ok_liters = 0;
 //_desi_d1 = read_eeprom(7);
//if(_desi_d1 > 2)_desi_d1 = 2;
// _desi_d2 = read_eeprom(8);
//if(_desi_d2 > 2)_desi_d2 = 2;
// _desi_d3 = read_eeprom(9);
//if(_desi_d3 > 2)_desi_d3 = 2;
 _x1 = read_eeprom(10);
 _x2 = read_eeprom(11);
 _rate = make16(_x2,_x1);
if(_rate > 19999 || _rate == 0)_rate = 10000;
 _x1 = read_eeprom(12);
 _x2 = read_eeprom(13);
 _ok_rate = make16(_x2,_x1);
if(_ok_rate > 19999)_ok_rate = 6500;
 _x1 = read_eeprom(14);
 _x2 = read_eeprom(15);
 _pulses = make16(_x2,_x1);
if( _pulses > 2000) _pulses = 100;
_totel = _r_e(16);
_last_fill = _r_e(20);
_last_bill = _r_e(24);
_hang = _r_e(28);
_slips = _r_e(32);
// _noz_pad = read_eeprom(36);
//if(_noz_pad > 1)_noz_pad = 0;
 _x1 = read_eeprom(37);
 _x2 = read_eeprom(38);
 _m_code = make16(_x2,_x1);
if(_m_code > 9999)_m_code = 2350;
 _skip_var = read_eeprom(39);
if( _skip_var > 1) _skip_var = 0;

if(1 != read_eeprom(40))_disk_fl = 0;
else _disk_fl = 1;
if(1 != read_eeprom(41))_motor_fl = 0;
else _motor_fl = 1;

_lasts = read_eeprom(100);
if(_lasts > 5)_lasts = 0;

}
//SMALL DISPLAY++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void cd4094(int8 __data) {
int8 j;
      for (j=0;j<=7;++j){
      if(bit_test(__data,7)){
         output_high(_dat_d);
      }
      else{
         output_low(_dat_d);
      }
      rotate_left(&__data,1);
      output_high(_clock_d);
      delay_us(5); //5
      output_low(_clock_d);
   }
}
// 22 BIG DISPLAY***************************************************************
void _all_disp(void){
int8 _c_t;

     for(_c_t=1;_c_t<16;++_c_t){
      output_low(_strob_d);
     cd4094(seg_p[_c_t] * 16);
      cd4094(seg[_var1]);
      _dig[_c_t - 1] = _var1;
      output_high(_strob_d);
     }

     for(_c_t=1;_c_t<8;++_c_t){
      output_low(_strob_d);
     cd4094(seg_p[_c_t]);
      cd4094(seg[_var1]);
     _dig[(_c_t -1) + 15] = _var1;
     output_high(_strob_d);
     }
output_low(_strob_d);
output_low(_dat_d);
output_low(_clock_d);
}
//BIG DISPLAY**************************************************************
void _disp_data(void){
int8 _c_t;
     for(_c_t=1;_c_t<16;++_c_t){
      output_low(_strob_d);
     cd4094(seg_p[_c_t] * 16);
      cd4094(seg[_dig[_c_t - 1]]);
     output_high(_strob_d);
     }

     for(_c_t=1;_c_t<8;++_c_t){
     output_low(_strob_d);
     cd4094(seg_p[_c_t]);
     cd4094(seg[_dig[(_c_t -1) + 15]]);
     output_high(_strob_d);
     }
output_low(_strob_d);
output_low(_dat_d);
output_low(_clock_d);
}
/*
//SMALL DISPLAY++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void cd4094(int8 __data) {
int8 j;
      for (j=0;j<=7;++j){
      if(bit_test(__data,7)){
         output_high(_dat_d);
      }
      else{
         output_low(_dat_d);
      }
      rotate_left(&__data,1);
      output_high(_clock_d);
      delay_us(5);
      output_low(_clock_d);
   }
}
// 22 BIG DISPLAY***************************************************************
void _all_disp(void){
int8 _c_t;
output_high(_strob_d);
     for(_c_t=0;_c_t<22;++_c_t){
     _dig[_c_t] = _var1;;
     cd4094(seg[_var1]);
     }
output_low(_strob_d);
}
//BIG DISPLAY**************************************************************
void _disp_data(void){
int8 _c_t;
output_high(_strob_d);
     for(_c_t=0;_c_t<22;++_c_t){
        if(_c_t == (14 +_desi_d1) || _c_t == (6 +_desi_d2)  || _c_t == (0 + _desi_d3) )cd4094(seg[_dig[_c_t]]+128);
        else cd4094(seg[_dig[_c_t]]);
     }
output_low(_strob_d);
}
*/
//******************************************************************************
void _get_time(void){
/////////////////////////////////////GET TIME
ds1307_get_date(day,month,yr,dow);
ds1307_get_time(hrs,min,sec);
/////////////////////////////////////GET TIME
if(hrs > 23){
hrs = 12;
min = 0;
sec = 0;
day = 1;
month = 1;
yr = 17;
dow  = 1;
ds1307_set_date_time(day, month, yr,  dow,  hrs,  min,  sec);
}
//rtc_get_time(_hr,_min,_sec);
//rtc_get_date(_day,_mth,_year,_dow);
}

//******************************************************************************
void _init_p(void){
printf("%c",27);
printf("%c",64);
delay_ms(10);
_rx_fl = 0;
_ir = 0;
_rs232[0] = 0;
printf("%c",16);
printf("%c",4);
printf("%c",4);
delay_ms(20);
_printer_fl = 1;
}
//******************************************************************************
void _align(int8 _al){
printf("%c",27);
printf("%c",97);
if(_al == 1)printf("%c",48);
if(_al == 2)printf("%c",49);
if(_al == 3)printf("%c",50);
delay_ms(10);
}
//******************************************************************************
void _gap(int8 _gp){
printf("%c",27);
printf("%c",100);
printf("%c",_gp);
delay_ms(10);
}
//******************************************************************************
void _cut(){
printf("%c",29);
printf("%c",86);
printf("%c",1);
delay_ms(10);
}
//******************************************************************************
void _fount(int8 _fo){
printf("%c",27);
printf("%c",33);
if(_fo == 1)printf("%c",1);
if(_fo == 2)printf("%c",1);
if(_fo == 3)printf("%c",16);
if(_fo == 4)printf("%c",32);
if(_fo == 5)printf("%c",48);
if(_fo == 6)printf("%c",17);
if(_fo == 7)printf("%c",33);
if(_fo == 8)printf("%c",49);
delay_ms(10);
}
//******************************************************************************
void _get_slip(void){
_p_wait:
if(!input(_p_busy))goto _p_wait;
_print_on;
enable_interrupts(INT_RDA);
set_tris_c(0b10000110);
delay_ms(100);
output_low(_p_busy);
_get_time();
_init_p();
if(_printer_fl){
++_slips;
_fount(3);
_align(2);
//printf("FAST OIL.");
//printf("%c",10);
printf("TOTAL PARCO.");
printf("%c",10);
printf("Ghulam Mustafa Kerio Petroleum Services.");
printf("%c",10);
_gap(1);
_fount(6);
_align(2);
printf("Retodero Bus Terminal.");
printf("%c",10);
printf("larkana.");
printf("%c",10);
_gap(1);
//_fount(7);
//printf("GUJRANWALA.  Tel # 055-3261007");
//printf("Tel 03474704780 / 03004865981");
//printf("%c",10);
//_gap(1);
_fount(4);
_align(1);
printf("DIESEL.");
//printf("PETROL.");
printf("%c",10);
printf("Nozel No   10  ");
printf("%c",10);
printf("Slip  No.  ");
printf("%lu",_slips);
printf("%c",10);
printf("Date:");
printf("%02u-",day);
printf("%02u-20",month);
printf("%02u ",yr);
printf("%02u:",hrs);
printf("%02u:",min);
printf("%02u",sec);
printf("%c",10);
_gap(1);
printf("Vehicle No.  __________");
printf("%c",10);
printf("AMOUNT  Rs.:  ");
printf("%lu.",_rupee / 100);
printf("%02lu  ",_rupee % 100);
printf("%c",10);
printf("QTY. Lit.  :  ");
printf("%lu.",_liters / 100);
printf("%02lu  ",_liters % 100);
printf("%c",10);
printf("RATE / Lit.:  ");
printf("%lu.",_rate / 100);
printf("%02lu  ",_rate % 100);
printf("%c",10);
_gap(1);
_fount(4);
//printf("Contact: Malik Abdul Khaliq.");
printf("Complaint and suggestion.");
printf("%c",10);
_fount(4);
//printf("Mob :  0305-2855082");
//printf("%c",10);
printf("Mob :  0335-3394498");
printf("%c",10);
_gap(1);
_align(2);
printf("24/7 Hours Service.");
printf("%c",10);
_fount(7);
printf("Thank you. Please Come again.");
printf("%c",10);
_gap(5);
_cut();
}
output_high(_p_busy);
_print_off;
set_tris_c(0b10000111);
//disable_interrupts(INT_RDA);
}
//******************************************************************************
void _init_system(void){
   set_tris_a(0b00000000);
   set_tris_b(0b10000010);
   set_tris_c(0b10000111);
   set_tris_d(0b00001000);
   set_tris_e(0b00000000);
//   _d_count = 100;
// SETUP_ADC_PORTS(NO_ANALOGS);
 enable_interrupts(GLOBAL);
enable_interrupts(INT_RDA);
// disable_interrupts(INT_EXT);
 _buz_off;
 disable_interrupts(INT_Timer2);
 setup_timer_2 (T2_DIV_BY_16, 255, 16);
_var1 = _clear;
_all_disp();
ds1307_init();
_get_time();
_r_eerom();
_rupee = 0;
_noz_fl = 1;
_skip_fl = 0;
_motor_off;
_sov1_off;
_sov2_off;
_on_fl=0;
_totelizer_off;
_tm2_off;
_print_off;
_incr_fl = 0;
_pl_fl = 0;
_price = 0;
_petrol = 0;
_oil_fl = 0;
_tc_fl = 0;
_liter_fl = 0;
_price_fl = 0;
//_date = 0512014;
_t =  13;
_c =  11;
_r =  14;
_s =  15;
_l =  16;
_p =  12;
_P1 = 17;
_P2 = 18;
_P3 = 19;
_P4 = 20;
_P5 = 21;
_code_seq = 0;
_code_id  = 0;
}
//******************************************************************************
void _all_disp1(int32  _var_all ){
int32 _pp2;
_dd1d = _var_all;
_pp2 = _dd1d;
IF(_dd1d < _kror){
_d1 = _clear;
}else{
_d1 = _pp2 / _kror;
_pp2 = _pp2 % _kror;
}
IF(_dd1d < _ten_lakh){
_d2 = _clear;
}else{
_d2 = _pp2 /_ten_lakh;
_pp2 = _pp2 % _ten_lakh;
}
IF(_dd1d < _lakh){
_d3 = _clear;
}else{
_d3 = _pp2 /_lakh;
_pp2 = _pp2 % _lakh;
}
IF(_dd1d < _ten_th){
_d4 = _clear;
}else{
_d4 = _pp2 /_ten_th;
_pp2 = _pp2 % _ten_th;
}
IF(_dd1d < _thou){
_d5 = _clear;
}else{
_d5 = _pp2 /_thou;
_pp2 = _pp2 % _thou;
}
_d6 = _pp2 /_hund;
_pp2 = _pp2 % _hund;
_d7 = _pp2 / _ten;
_d8 = _pp2 % _ten;



/*
_dd1d = _var_all;
_pp2 = _dd1d;
IF(_dd1d < _kror)_d1 = _clear;
else _d1 = _pp2 / _kror;
_pp2 = _pp2 % _kror;
IF(_dd1d < _ten_lakh)_d2 = _clear;
else _d2 = _pp2 /_ten_lakh;
_pp2 = _pp2 % _ten_lakh;
IF(_dd1d < _lakh) _d3 = _clear;
else _d3 = _pp2 /_lakh;
_pp2 = _pp2 % _lakh;
IF(_dd1d < _ten_th)_d4 = _clear;
else _d4 = _pp2 /_ten_th;
_pp2 = _pp2 % _ten_th;
IF(_dd1d < _thou)_d5 = _clear;
else _d5 = _pp2 /_thou;
_pp2 = _pp2 % _thou;
_d6 = _pp2 /_hund;
_pp2 = _pp2 % _hund;
_d7 = _pp2 / _ten;
_d8 = _pp2 % _ten;
*/
}
//******************************************************************************
void _all_disp2(int32 _var2_all){
int32 _vv,_d2_r;
_dd2d = _var2_all;
_vv = _dd2d;
if(_dd2d  < _kror){
_d9 = _clear;
}else{
_d9 = _vv / _kror;
_vv = _vv % _kror;
}
if(_dd2d  < _ten_lakh){
_d10 = _clear;
}else{
_d10 = _vv /_ten_lakh;
_vv = _vv % _ten_lakh;
}
if(_dd2d  < _lakh){
_d11 = _clear;
}else{
_d11 = _vv /_lakh;
_vv = _vv % _lakh;
}

if(_dd2d  < _ten_th){
_d12 = _clear;
}else{
_d12 = _vv /_ten_th;
_vv = _vv % _ten_th;
}
if(_dd2d  < _thou){
_d13 = _clear;
}else{
_d13 = _vv /_thou;
_vv = _vv % _thou;
}
_d14 = _vv /_hund;
_vv = _vv % _hund;
_d15 = _vv / _ten;
_d16 = _vv % _ten;




/*
_dd2d = _var2_all;
_vv = _dd2d;
if(_dd2d  < _kror) _d9 = _clear;
else _d9 = _vv / _kror;
_vv = _vv % _kror;

if(_dd2d  < _ten_lakh) _d10 = _clear;
else _d10 = _vv /_ten_lakh;
_vv = _vv % _ten_lakh;

if(_dd2d  < _lakh)_d11 = _clear;
else _d11 = _vv /_lakh;
_vv = _vv % _lakh;

if(_dd2d  < _ten_th) _d12 = _clear;
else _d12 = _vv /_ten_th;
_vv = _vv % _ten_th;

if(_dd2d  < _thou) _d13 = _clear;
else _d13 = _vv /_thou;
_vv = _vv % _thou;

_d14 = _vv /_hund;
_vv = _vv % _hund;
_d15 = _vv / _ten;
_d16 = _vv % _ten;
*/
}
//******************************************************************************
void _disp1b(void){
int32 _d1_r;
if(_price > 999999){
_price = 0;
_code_val = 0;
}
_d1_r = _price  * 100;
_all_disp1(_d1_r);
if(_d1_r < 100000)_d1 = 12;

//IF(_price < _lakh)_d1 = _clear;
//IF(_price < _ten_th)_d2 = _clear;
//IF(_price < _thou) _d3 = _clear;
//IF(_price < _hund)_d4 = _clear;
//IF(_price < _ten)_d5 = _clear;
}

//******************************************************************************
void _disp1a(void){
int32 _d1_r;
_d1_r = _price ;
_all_disp1(_d1_r);
IF(_d1_r < _kror)_d1 = 12;
}
//******************************************************************************
void _disp3(int16 _d_rate){
int16 _t_rate;
 _t_rate = _d_rate;
_d17 = _clear;
if(_d_rate < _ten_th )_d18 = _clear;
else _d18 = _t_rate /_ten_th;
_t_rate = _t_rate % _ten_th;
_d19 = _t_rate /_thou;
_t_rate = _t_rate % _thou;
_d20 = _t_rate / _hund;
_t_rate = _t_rate % _hund;
_d21 = _t_rate /_ten;
_d22 = _t_rate %_ten;
}
//******************************************************************************
void _disp2(void){
Int32 _dd2_r;
_dd2_r = _liters;
_all_disp2(_dd2_r);

/*
int32 _d1_l,_ll;
_ll = _liters;
_d1_l = _ll;
IF(_ll < _kror)_d9 = _clear;
else _d9 = _d1_l / _kror;

_d1_l = _d1_l % _kror;
IF(_ll < _ten_lakh)_d10 = _clear;
else _d10 = _d1_l / _ten_lakh;

_d1_l = _d1_l % _ten_lakh;
IF(_ll < _lakh)_d11 = _clear;
else _d11 = _d1_l / _lakh;

_d1_l = _d1_l % _lakh;
IF(_ll < _ten_th) _d12 = _clear;
else _d12 = _d1_l /_ten_th;

_d1_l = _d1_l % _ten_th;
IF(_ll < _thou)_d13 = _clear;
else _d13 = _d1_l /_thou;
_d1_l = _d1_l % _thou;
_d14 = _d1_l /_hund;
_d1_l = _d1_l % _hund;
_d15 = _d1_l / 10;
_d16 = _d1_l % 10;
*/
}
//******************************************************************************

void _disp1(void){
Int32 _d1_r,_rr;
//_d1_r = _rupee / 10;
//_rr = _rupee / 10;
//_d1_r = _rupee;
//_rr = _rupee;
//_all_disp1(_d1_r);
_d1_r = _rupee;
_all_disp1(_d1_r);

//IF(_rr <  _kror)_d1 = _clear;
//IF(_rr < _ten_lakh)_d2 = _clear;
//IF(_rr < _lakh) _d3 = _clear;
//IF(_rr < _ten_th)_d4 = _clear;
//IF(_rr <  _thou )_d5 = _clear;
}
//******************************************************************************
void _totel_disp(void){
int32 _d1_r ;
_all_disp1(_totel % 100);
_all_disp2(_totel / 100);
//_d1 = _clear;
//_d2 = _clear;
//_d3 = _clear;
//_d4 = _clear;
//_d5 = _clear;
_d6 = _clear;
_disp_data();
}
//******************************************************************************
/*
void _td_disp(void){
int32 _d1_r ;
_all_disp2(_td);
_d1 = _clear;
_d2 = _clear;
_d3 = _clear;
_d4 = _clear;
_d5 = _clear;
_d6 = _clear;
_d7 = _clear;
_d8 = _clear;
_disp_data();
}
*/
//******************************************************************************
/*
void _hang_disp(void){
int32 _d1_r ;
_all_disp2(_hang/ _hund);
_d1_r = _hang % _hund;
_d7 = _d1_r / _ten;
_d8 = _d1_r % _ten;
_d1 = _clear;
_d2 = _clear;
_d3 = _clear;
_d4 = _clear;
_d5 = _clear;
_d6 = _clear;
_disp_data();
}
*/
//******************************************************************************
void _disp2a(void){
int32 _d2_r ;
/*
if(_petrol > 999999 && !_deci_fl){
_petrol = 0;
_code_val = 0;
}
if(_petrol > 99999999 && _deci_fl){
_petrol = 0;
_code_val = 0;
}
if(!_deci_fl)_d2_r = _petrol * 100;
else _d2_r = _petrol;
*/
if(_petrol > 999999){
_petrol = 0;
_code_val = 0;
}
_d2_r = _petrol * 100;
_all_disp2(_d2_r);
if(_d2_r < 10000000) _d9 = 10;

/*
IF(_d2_r < _kror) _d9 = _clear;
IF(_d2_r < _ten_lakh) _d10 = _clear;
IF(_d2_r < _lakh)_d11 = _clear;
IF(_d2_r < _ten_th) _d12 = _clear;
IF(_d2_r < _thou) _d13 = _clear;
*/
}
//******************************************************************************
void _price_enter(void){
if(_key1 == _p1)_price = 10000;
if(_key1 == _p2)_price = 20000;
if(_key1 == _p3)_price = 30000;
if(_key1 == _p4)_price = 40000;
if(_key1 == _p5)_price = 50000;
_liters = 0;
_code_val  = 0;
_disp1a();
_d9 = _clear;
_d10 = _clear;
_d11 = _clear;
_d12 = _clear;
_d13 = _clear;
_d14 = _clear;
_d15 = _clear;
_d16 = _clear;
_d1 = 12;
_disp_data();
_key1 = 0;
}
//******************************************************************************
void _petrol_enter(void){
//_deci_fl = 0;
if(_key1 == _p1)_petrol = 10;
if(_key1 == _p2)_petrol = 20;
if(_key1 == _p3)_petrol = 30;
if(_key1 == _p4)_petrol = 40;
if(_key1 == _p5)_petrol = 50;
_price = 0;
_disp2a();
_d1 = _clear;
_d2 = _clear;
_d3 = _clear;
_d4 = _clear;
_d5 = _clear;
_d6 = _clear;
_d7 = _clear;
_d8 = _clear;
_disp_data();
_key1 = 0;
_code_val  = 0;
}
//******************************************************************************
void _rst(void){
_on_fl = 0;
 _p_deci_fl = 0;
_liters = _last_fill;
_rupee = _last_bill;
_disp1();
_disp2();
_disp3(_rate);
_disp_data();
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void _set_skip(void){
int16 _pu,_pd;
_pu = _ok_rate + (int16)_rate_fact * 100;
if(_ok_rate > ((int16)_rate_fact * 100))_pd = _ok_rate - (int16)_rate_fact * 100;
if(_price_fl){
   if(_price < _pu && _price > _pd )_skip_val = 0;
   else _skip_val = _skip_rupee;
}else{
   if(_ok_liters == 0){
   _skip_val = _skip_liters;
   _sk_l_fl = 1;
   }else{
   _skip_val = 0;
   _sk_l_fl = 0;
   }
 }

}
//******************************************************************************
void _initilize(void){
int32 _temp_cal;
//enable_interrupts(GLOBAL);
//enable_interrupts(INT_RB);
//enable_interrupts(INT_Timer2);
//setup_timer_2(T2_DIV_BY_16, 255, 16);
////if(!input(pin_b0))ext_int_edge( 0, L_TO_H);
////else ext_int_edge( 0, H_TO_L);
if(_price > 0){
_temp_cal  = _price * 100;
_temp_cal = _temp_cal / (int32)_rate;
_petrol = _temp_cal;
_chk_fill = 1;
_liters = (int32)_first_val;
_price_fl = 1;
_w_e(71 ,_price);
}
if(_petrol > 0 && !_price_fl)_liter_fl = 1;
if(_petrol > 0)_chk_fill = 1;
if(_chk_fill)_w_e(61 ,_petrol);
else _w_e(61 ,0);
_set_skip();
_skip_factor = 0;
_to_val = _totel / 100;
_skip_at_fl = 0;
_liters = 0;
_rupee = 0 ;
/////////// pulser
if(input(_s_skip)){
_factor = 10000 / (_pulses - (int16)_skip_val);
_sk_sw_fl = 1;
}else{
_factor = 10000 / _pulses;
_sk_sw_fl = 0;
}
_count = 0;
_add = 0;
_skip_chk = 0;
//////////
}
//********************  LAST % FILL
void _last5_fill(void){
++_lasts;
if(_lasts > 5)_lasts = 1;
if(_lasts == 1)_tp = 101;
if(_lasts == 2)_tp = 111;
if(_lasts == 3)_tp = 121;
if(_lasts == 4)_tp = 131;
if(_lasts == 5)_tp = 141;
_w_e(_tp ,_last_fill);
_w_e((_tp + 5) ,_last_bill);
write_eeprom(100,_lasts);
}
//******************************************************************************
void _stop_fill(void){
_buz_on;
_motor_off;
_sov1_off;
_sov2_off;
_skip_fl = 0;
//disable_interrupts(INT_EXT);
disable_interrupts(INT_RB);
disable_interrupts(INT_Timer2);
if(_liters > 0){
_last_fill = _liters;
_last_bill = _rupee;
//_totel = _totel2  + _liters;
   if(_p_fl){
   _last5_fill();
   _p_fl = 0;
   }
//_get_slip();///////////////////////////////////PRINTER
}
_chk_fill = 0;
_price_fl = 0;
_liter_fl = 0;
_price = 0;
_petrol = 0;
_w_e(51 ,0);
_w_e(61 ,0);
_w_e(71 ,0);
 _w_eerom();
//if(_noz_pad !=  1){
if(_noz_off)_rst();
//}else{
//scan_keypad2();
//if(_key2 == _s)_rst();
//}
delay_ms(300);
_buz_off;
}
//******************************************************************************
void _power_down(void){
_w_fail_c:
if(input(_wapda)){
//disable_interrupts(INT_EXT);
disable_interrupts(INT_RB);
_d9 = 12;
_motor_off;
_sov1_off;
_sov2_off;
_disp_data();
delay_ms(500);
_d9 = _clear;
_disp_data();
delay_ms(500);
goto _w_fail_c;
}
//if(_noz_pad !=  1){
if(_noz_off || !_on_fl)return;//nnnnnnnnnnnnnnnnnnnn
//}else{
//scan_keypad2();
//if(_key2 == _s)return;;
//}
_disp_data();
_motor_on;
delay_ms(500);
_sov1_on;
enable_interrupts(INT_RB);
//enable_interrupts(INT_EXT);
//if(!input(pin_b0))ext_int_edge( 0, L_TO_H);
//else ext_int_edge( 0, H_TO_L);
delay_ms(500);
_sov2_on;
}
//******************************************************************************
void _control(void){
_liters = 0;
_count = 0;
_add = 0;
_steps:
if(input(_wapda))_power_down();
//////////////////////
//if(_noz_pad == 1){
//scan_keypad2();
//if(_key2 == _s)goto _end_fill;
//}
////////////////////
//if(_noz_off && _noz_pad != 1)goto _end_fill;
if(_noz_off)goto _end_fill;
if(_liters > _first_val){
_rupee = _liters *_rate/100;
_disp2();
_disp1();
_disp_data();
}

if(_liters < _v_first_val )goto _steps;
if(_petrol  > _sov_cut || _petrol == 0)_sov2_on;
if(_liters <= _first_val)goto _steps;
//if(_price_fl )++_liters;


_fill:
if(input(_wapda))_power_down();
if(_noz_off){
delay_ms(115);
   if(_noz_off)   goto _end_fill;
}

if(_change_fl){
_rupee = (_liters *(int32)_rate )/ 100;
//   if(_liters > _first_val+1){
     _disp2();
     _disp1();
    _disp_data();
   _change_fl = 0;
//   }
if(_totel / 100  >  _to_val ){
_to_val = _totel / 100;
int_count = 0;
_totelizer_on;
_tm2_on;
_buz_on;
}
///////////////////////////ok vals
if(!_sk_l_fl){
   if(_liters > (int32)_ok_liters * 100){
   _skip_val = _skip_liters;
   _factor = 10000 / (_pulses - (int16)_skip_val);
   _sk_l_fl = 1;
   _sk_sw_fl = 1;
   }
}

////////////////////////////////Button
if(input(_s_skip)){
   if(!_sk_sw_fl){
   _factor = 10000 / (_pulses - (int16)_skip_val);
   _sk_sw_fl = 1;
   }
}else{
   if(_sk_sw_fl){
   _factor = 10000 / _pulses;
   _sk_sw_fl = 0;
   }
}
////////////////////////////////
if(_chk_fill){
   if(_liters > _petrol - (int32)_sov_cut)_sov2_off;
   if(_liters >= _petrol){
   disable_interrupts(INT_RB);
   _motor_off;
   _sov1_off;
   _sov2_off;
   _chk_fill = 0;
   delay_ms(200);
   _liters = _petrol;
  _rupee = (_liters *(int32)_rate )/ 100;
   if(_price_fl)_rupee = _price;
   goto _end_fill;
   }
 }
}

goto _fill;
_end_fill:
   disable_interrupts(INT_RB);
   _motor_off;
   _sov1_off;
   _sov2_off;

   _totel = _totel2  + _liters;
   if(_totel / 100  >  _to_val ){
   _to_val = _totel / 100;
   int_count = 0;
   _totelizer_on;
   _tm2_on;
   _buz_on;
   }

_disp2();
_disp1();

//if(input(_s_skip))_d9 = 15;
//else _d9 = 14;

_disp_data();
_stop_fill();
delay_ms(15);
_totelizer_off;
_tm2_off;
_close_all:
if(_noz_on)goto _close_all;
return;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++
void _num_press(void){
_num = 0;
if(_key1 < 11 && _key1 > 0)_num =_key1;
}
//******************************************************************************
void _price_set(void){
_oil_fl = 0;
_p_deci_fl = 0;
_code_val = 0;
_rupee = 0;
_petrol = 0;
_liters = 0;
_disp2();
_d9 = _clear;
_d10 = _clear;
_d11 = _clear;
_d12 = _clear;
_d13 = _clear;
_d14 = _clear;
_d15 = _clear;
_d16 = _clear;
_disp1b();
_disp_data();
_p_set:
if(_key1 != 0){
   if(_key1 > 16 && _key1 < 22 ){
   _price_enter();
   _price = _price / 100;
   }
   _num_press();
   if(_num < 11 && _num != 0 && _code_val < 6){
   if(_num == 10)_num = 0;
   if(_code_val == 0){
   _price = (int32)_num;
   }
    if(_code_val > 0){
    _price = _price * 10;
    _price = _price +(int32)_num;
    }
     _disp1b();
     IF(_price < 100000)_d1 = 12;
    _disp_data();
    ++_code_val;
    delay_ms(300);
  }
}
scan_keypad();
if(_key1 == _c || _key1 == _l)return;

//if(_noz_pad == 1){
//   if(_key1 == _r)goto _kps1;
//}
//if(_noz_on && _noz_pad != 1){
if(_noz_on){
_kps1:
_price = _price * 100;
if((_price * 100)/_rate < 3){
_noz_fl = 1;//////////////////////////////////////
_price = 0;
_disp1b();
_disp_data();
delay_ms(300);
}
return;
}
goto _p_set;
}
//******************************************************************************
void _petrol_set(void){
_oil_fl = 1;
_rupee = 0;
_petrol = 0;
_price = 0;
_disp1();
_d1 = _clear;
_d2 = _clear;
_d3 = _clear;
_d4 = _clear;
_d5 = _clear;
_d6 = _clear;
_d7 = _clear;
_d8 = _clear;
_disp2a();
_disp_data();
_l_set:
if(_key1 != 0){
//   if(_key1 > 16 && _key1 < 22 ){
  if(_key1  > 16 && _key1 < 22 && _oil_fl == 1 ){
   _petrol_enter();
   }
   _num_press();
   if(_num < 11 && _num != 0 && _code_val < 6){
    if(_num == 10)_num = 0;
   if(_code_val == 0){
   _petrol = (int32)_num;
   }
    if(_code_val > 0){
    _petrol = _petrol * 10;
    _petrol = _petrol +(int32)_num;
    }
    _disp2a();
    _disp_data();
    ++_code_val;
    delay_ms(300);
  }
}
scan_keypad();
if(_key1 == _c || _key1 == _p)return;

//if(_noz_pad == 1){
//   if(_key1 == _r){
//      if(!_deci_fl)_petrol = _petrol * 100;
//      return;
// }
//}
//if(_noz_on && _noz_pad != 1){
if(_noz_on){
//if(!_deci_fl)_petrol = _petrol * 100;
_petrol = _petrol * 100;
return;
}
goto _l_set;
}
//******************************************************************************
void _main_code_enter(void){
int16 _all_codes = 0;
_code_val = 0;
_code_block = 0;
_aa:
scan_keypad();
if(_key1 != 0){
   _num_press();
   if(_num < 11 && _num != 0 && _code_val < 4){
   if(_num == 10)_num = 0;
   if(_code_val == 0){
   _all_codes = (int32)_num;
   }
    if(_code_val > 0){
    _all_codes = _all_codes * 10;
    _all_codes = _all_codes +(int32)_num;
    }
   if(_code_val == 0)_d13 = 0;
   if(_code_val == 1)_d14 = 0;
   if(_code_val == 2)_d15 = 0;
   if(_code_val == 3)_d16 = 0;
    ++_code_val;
    _disp_data();
    delay_ms(300);
    if(_all_codes > 9999){
    _all_codes = 0;
    _code_val = 0;
    }
  }
//   if(_key1 == _L){
//   _code_id = 0;
//   _code_block = 0;
//      if(_all_codes == 71777554)_code_block = 3;
//      if(_all_codes == 2222)_code_block = 2;
   if(_all_codes == _m_code || _all_codes == 1122){
   _code_block = 1;
   goto _c_pass;
   }

   if(_key1 == _C){
   _c_pass:
   _rst();
   _key1 = 0;
   _code_val = 0;
   return;
   }
} // key > 0
goto _aa;
}
//******************************************************************************
void _edit_value(void){
int32 _to;
delay_ms(1500);
_code_val = 0;
_v_set:
scan_keypad();
if(_key1 != 0){
   _num_press();
   if(_num < 11 && _num > 0 && _code_val < 8){
   if(_num == 10)_num = 0;
   if(_code_val == 0){
   _liters = (int32)_num;
   }
    if(_code_val > 0){
    _liters = _liters * 10;
    _liters = _liters +(int32)_num;
    }
    _disp2();
//    _disp3((int16)_code_id * 100);
//   _d21 = 10;
//   _d22 = _code_val + 1;
   _disp_data();
   delay_ms(250);
    ++_code_val;
  }
}
if(_key1 == _C){
_ws:
_key1 = 0;
_liters = 0;
_code_val = 0;
_code_block = 0;
_disp2();
//_disp3((int16)_code_id * 100);
//_d21 = 10;
//_d22 = _code_val + 1;
_disp_data();
delay_ms(300);
}

if(_key1 == _s){
      if(_code_id == 7860){
         if(_liters > 19999) goto _ws;
         else _rate = _liters;
      }
      if(_code_id == 4850){
         if(_liters > 99999999){
         goto _ws;
         }else{
//         _to = _totel % 100;
         _totel = _liters * 100;
//         _totel = _totel + _to;
         }
      }
      if(_code_id == 2850){
         if(_liters > 30 || _liters < 5 ) goto _ws;
         else _sov_cut = _liters;
      }
      if(_code_id == 6550){
         if(_liters > 2000 || _liters < 40) goto _ws;
         else _pulses = _liters;
      }
      if(_code_id == 7850){
         if(_liters > 10) goto _ws;
         else _first_val = _liters;
      }
      if(_code_id == 8550){
         if(_liters > 10) goto _ws;
         else _v_first_val = _liters;
      }
      if(_code_id == 1750){
         if(_liters > 19999) goto _ws;
         else _ok_rate = _liters;
      }
      if(_code_id == 1850){
         if(_liters > 10) goto _ws;
         else _rate_fact = _liters;
      }
      if(_code_id == 1350){
         if(_liters > 20) goto _ws;
         else _skip_rupee = _liters;
      }
      if(_code_id == 2050){
         if(_liters > 99) goto _ws;
         else _ok_liters = _liters;
      }
      if(_code_id == 2150){
         if(_liters > 20) goto _ws;
         else _skip_liters = _liters;
      }
      if(_code_id == 9850){
         if(_liters > 9999999) goto _ws;
         else _hang = _liters;
      }
      if(_code_id == 6050){
         if(_liters != 1)_disk_fl = 0;
         else _disk_fl = 1;
      }
      if(_code_id == 7050){
         if(_liters != 1)_motor_fl = 0;
         else _motor_fl = 1;
      }

//      if(_code_id == 1204){
//         if(_liters > 2) goto _ws;
//         else _noz_pad = _liters;
//      }
      if(_code_id == _m_code){
         if(_liters > 9999) goto _ws;
         else _m_code = _liters;
      }
//     if(_code_id == 2450){
//         if(_liters > 1) goto _ws;
//         else _skip_var = _liters;
//     }
      if(_code_id == 2550){
//      _get_time();
      hrs = _liters / 100;
      min = _liters % 100;
      if(hrs > 23 || min >  59 )goto _ws;
//      rtc_set_datetime(_day,_mth,_year,_dow,_hr,_min);
ds1307_set_date_time(day, month, yr,  dow,  hrs,  min,  sec);

      }
      if(_code_id == 2650){
//      _get_time();
      day = _liters / 10000;
      yr = _liters % 100;
      _liters = _liters % 10000;
      month = _liters / 100;
      if(day > 31 || month >  12 || yr > 99)goto _ws;
//      rtc_set_datetime(_day,_mth,_year,_dow,_hr,_min);
ds1307_set_date_time(day, month, yr,  dow,  hrs,  min,  sec);
      }
 _buz_on;
delay_ms(700);
_key1 = 0;
 _buz_off;
return;
}
goto _v_set;
}

//******************************************************************************
void _code_id_value(void){
_sub_id  = 0;
_var1 =_clear;
_all_disp();
_liters = 111;
///////////////////////////////BLOCK 1 start
//if(_code_block == 1){
   if(_code_id == 7860)_liters = (int32)_rate;
   if(_code_id == 4850)_liters = _totel / 100;
   if(_code_id == 2850)_liters = (int32)_sov_cut;
   if(_code_id == 6550)_liters = (int32)_pulses;
   if(_code_id == 7850)_liters = (int32)_first_val;
   if(_code_id == 8550)_liters = (int32)_v_first_val;
   if(_code_id == 1750)_liters = (int32)_ok_rate;// rupee_val
   if(_code_id == 1850)_liters = (int32)_rate_fact;// + - val
   if(_code_id == 1350)_liters = (int32)_skip_rupee;// rupee lines
   if(_code_id == 2050)_liters = (int32)_ok_liters;// petrol val
   if(_code_id == 2150)_liters = (int32)_skip_liters;// lines
   if(_code_id == 9850)_liters = (int32)_hang;// hang
   if(_code_id == 6050){
      if(_disk_fl)_liters = 1;
      else _liters = 0;
   }
   if(_code_id == 7050){
      if(_motor_fl)_liters = 1;
      else _liters = 0;
   }

//   if(_code_id == 1204)_liters = (int32)_noz_pad;//start stop
   if(_code_id == _m_code)_liters = (int32)_m_code;// main code
//   if(_code_id == 2450)_liters = (int32)_skip_var;//start stop
   if(_code_id == 2550){// time
//   _get_time();
   _td = (int32)hrs * 100;
   _td = _td + (int32)min;
      if(_td > 2359)_td = 1200;
   _liters = _td;
   }

   if(_code_id == 2650){// date
//   _get_time();
   _td = (int32)day * 10000;
   _td = _td + (int32)month * 100;
   _td = _td + (int32)yr;
      if(_td > 311299)_td = 70816;
   _liters = _td;
   }
//}

if(_liters != 111)_disp2();
//_passd:
// _disp3((int16)_code_id);
 _disp_data();
 delay_ms(300);
}
//****************************************************
void _code_id_enter(void){
_pk:
_code_val = 0;
_var1 =_clear;
_all_disp();
_d9  = 13;
_d10 = 0;
_disp_data();
_cid:
scan_keypad();
if(_key1 != 0){
_num_press();
   if(_num < 11 && _num != 0 && _code_val < 4){
   if(_num == 10)_num = 0;
   if(_code_val == 0){
    _code_id = (int16)_num;
    _d16 = 0;
   }
    if(_code_val > 0){
     _code_id =  _code_id * 10;
     _code_id =  _code_id +(int16)_num;
    }
    if(_code_val == 1)_d15 = 0;
    if(_code_val == 2)_d14 = 0;
    if(_code_val == 3)_d13 = 0;
    _disp_data();
    ++_code_val;
    delay_ms(500);
      if(_code_val == 4){
      _code_id_value();
         if(_liters == 111)goto _exit_id;
      }
   }

   if(_key1 == _C){
      if(_code_val < 4)goto _pk;
   _liters = 0;
   _disp2();
   _disp_data();
   _edit_value();
   _w_eerom();
//   _key1 = _c;
    delay_ms(300);
    goto _pk;
   }

   if(_key1 == _s){
   _exit_id:
   _rst();
   _key1 = 0;
   _code_val = 0;
   _code_block = 0;
   return;
   }
}
goto _cid;
}
//******************************************************************************
/*
void _last_10(void){
int1 _show = 0;
int8 _id = 0;
_last5_stay:
scan_keypad();
   if(_key1 == _p1){
   if(_lasts == 5)_tp = 101;
   if(_lasts == 1)_tp = 111;
   if(_lasts == 2)_tp = 121;
   if(_lasts == 3)_tp = 131;
   if(_lasts == 4)_tp = 141;
   _show = 1;
   }
   if(_key1 == _p2){
   if(_lasts == 5)_tp = 111;
   if(_lasts == 1)_tp = 121;
   if(_lasts == 2)_tp = 131;
   if(_lasts == 3)_tp = 141;
   if(_lasts == 4)_tp = 101;
   _show = 1;
   }
   if(_key1 == _p3){
   if(_lasts == 5)_tp = 121;
   if(_lasts == 1)_tp = 131;
   if(_lasts == 2)_tp = 141;
   if(_lasts == 3)_tp = 101;
   if(_lasts == 4)_tp = 111;
   _show = 1;
   }
   if(_key1 == _p4){
   if(_lasts == 5)_tp = 131;
   if(_lasts == 1)_tp = 141;
   if(_lasts == 2)_tp = 101;
   if(_lasts == 3)_tp = 111;
   if(_lasts == 4)_tp = 121;
   _show = 1;
   }
   if(_key1 == _p5){
   if(_lasts == 5)_tp = 141;
   if(_lasts == 1)_tp = 101;
   if(_lasts == 2)_tp = 111;
   if(_lasts == 3)_tp = 121;
   if(_lasts == 4)_tp = 131;
   _show = 1;
   }

if(_show){
_liters = _r_e(_tp);
_rupee = _r_e(_tp + 5);
_noz_fl = 1;
_disp1();
_noz_fl = 0;
_disp2();
_disp3(_rate);
_disp_data();
_show = 0;
}
   if(_key1 == _c){
   _key1 = 0;
   _code_val = 0;
   _code_seq = 0;
   _pl_fl = 0;
   return;
   }
goto _last5_stay;
}// lasts
*/
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*
void _code_enter(void){
int8 _fifteen =10;
if(_key1 != 0){
_num_press();
   if(_num < 11 && _num != 0 && _code_val < 4){
   if(_num == 10)_num = 0;
   if(_code_val == 0){
   _codes = (int16)_num;
    _dig[0] = _fifteen;
   }
    if(_code_val > 0){
    _codes = _codes * 10;
    _codes = _codes +(int16)_num;
    }
    _d17 = _fifteen;
    _d18 = _fifteen;
    if(_code_val == 1)_d21 = _fifteen;
    if(_code_val == 2)_d20 = _fifteen;
    if(_code_val == 3)_d19 = _fifteen;
    if(_tc_fl == 0)_code_disp();
    _disp_data();
    ++_code_val;
  }
}
}

//**************************************************************
void _sov_enter(void){
if(_key1 != 0){
_num_press();
   if(_num < 11 && _code_val < 3){
   if(_num == 10)_num = 0;
   if(_code_val == 0){
    _sov_cut = (int16)_num;
   }else{
    _sov_cut = _sov_cut * 10;
    _sov_cut = _sov_cut +_num;
    }
    _disp3a();
    _disp_data();
    ++_code_val;
  }
}
}

//******************************************************************************

void _rate_enter(void){
int1 _th_fl;
_th_fl = 0;
if(_key1 != 0){
_num_press();
   if(_num < 11 && _code_val < 6){
   if(_num == 10)_num = 0;
   if(_code_val == 0) _rate = (int16)_num;

    if(_code_val > 0){
    _rate = _rate * 10;
    _rate = _rate +(int16)_num;
    }
    if(_rate > _rate_limit){
    _rate = 0;
    _code_val = 0;
    }
    _disp3(_rate);
    _disp_data();
    ++_code_val;
  }
}
}

//******************************************************************************
void _round_enter(void){
if(_key1 != 0){
_num_press();
   if(_num < 11 && _code_val < 6){
   if(_num == 10)_num = 0;
   if(_code_val == 0) _pulses = (int16)_num;
    if(_code_val > 0){
    _pulses = _pulses * 10;
    _pulses = _pulses +(int16)_num;
    }
    _disp3d();
    _disp_data();

    ++_code_val;
  }
}
}

//******************************************************************************
void _skip_enter(void){
if(_key1 != 0){
_num_press();
   if(_num < 11 && _code_val < 3){
   if(_num == 10)_num = 0;
   if(_code_val == 0)_skip_val = (int16)_num;
    if(_code_val > 0){
    _skip_val = _skip_val * 10;
    _skip_val = _skip_val +(int16)_num;
    if(_skip_val > 10 ){
    _skip_val = 0;
    _code_val = 0;
    }
    }
    _disp3b();
    _disp_data();
    ++_code_val;
  }
}
}
//******************************************************************************
void _first_enter(void){
if(_key1 != 0){
_num_press();
   if(_num < 11 && _code_val < 3){
   if(_num == 10)_num = 0;
   if(_code_val == 0)_first_val = (int16)_num;
    if(_code_val > 0){
    _first_val = _first_val * 10;
    _first_val = _first_val +(int16)_num;
       if(_first_val > 10 ){
       _code_val = 0;
       _first_val = 0;
       }
    }
    _disp3c();
    _disp_data();
     ++_code_val;
  }
}
}
//******************************************************************************
void _v_first_enter(void){
if(_key1 != 0){
_num_press();
   if(_num < 11 && _code_val < 3){
   if(_num == 10)_num = 0;
   if(_code_val == 0)_v_first_val = (int16)_num;
    if(_code_val > 0){
    _v_first_val = _v_first_val * 10;
    _v_first_val = _v_first_val +(int16)_num;
       if(_v_first_val > 10 ){
       _v_first_val = 0;
       _code_val = 0;
       }
    }
    _disp3e();
    _disp_data();
    ++_code_val;
  }
}
}
//******************************************************************************
void _motor_enter(void){
if(_key1 != 0){
_num_press();
   if(_num < 11 && _code_val < 3){
   if(_num == 10)_num = 0;
   if(_code_val == 0)_motor_val = _num;
    _disp3f();
    _disp_data();
  }
 }
}
//******************************************************************************
void _t_c_enter(void){
if(_key1 != 0){
_num_press();
   if(_num < 11 && _code_val < 6){
   if(_num == 10)_num = 0;
   if(_code_val == 0) _totel_code = (int16)_num;

    if(_code_val > 0){
    _totel_code = _totel_code * 10;
    _totel_code = _totel_code +(int16)_num;
    }
    if(_totel_code > 9999){
    _totel_code = 0;
    _code_val = 0;
    }
    _disp3g();
    _disp_data();
    ++_code_val;
  }
}
}
//******************************************************************************
void _p_limit_set(void){
if(_key1 != 0){
_num_press();
   if(_num < 11 && _code_val < 6){
   if(_num == 10)_num = 0;
   if(_code_val == 0) _rate_limit = (int16)_num;
   if(_code_val > 0){
      if(_code_val == 4 || _code_val == 5 ){
         if( _rate_limit > 6500){
         _rate_limit = 65000;
         return;
         }
      }
   _rate_limit = _rate_limit * 10;
   _rate_limit = _rate_limit +(int16)_num;
   }
    ++_code_val;
   _disp3(_rate_limit);
    _disp_data();
  }
 }
}

//******************************************************************************
void _r_s_enter(void){
if(_key1 != 0){
_num_press();
   if(_num < 11 && _code_val < 6){
   if(_num == 10)_num = 0;
   if(_code_val == 0) _rate_code = (int16)_num;

    if(_code_val > 0){
    _rate_code = _rate_code * 10;
    _rate_code = _rate_code +(int16)_num;
    }
    if(_rate_code > 9999){
    _rate_code = 0;
    _code_val = 0;
    }
    _disp3h();
    _disp_data();
    ++_code_val;
  }
}
}

//******************************************************************************
void _varify_code(void){
if(_codes == _rate_code){
_codes = 0;
++_code_counter;
_code_disp();
_disp3(_rate);
_disp_data();
_r_c_stay:
_key1 = scan_keypad();
   if(_key1 == _C || _rate > _rate_limit){
   _rate = 0 ;
   _code_val = 0;
   _disp3(_rate);
   _disp_data();
   }
   if(_key1 == _F){
   _ok();
   return;
   }
_rate_enter();
goto _r_c_stay;
}// Rate

if(_codes == _p_limit_code){
_codes = 0;
++_code_counter;
_code_disp();
_disp3(_rate_limit);
_disp_data();
_pl_c_stay:
_key1 = scan_keypad();
   if(_key1 == _C || _rate_limit > 59999){
   _rate_limit = 0;
   _code_val = 0;
   _disp3(_rate_limit);
   _disp_data();
   }
   if(_key1 == _F){
       if(_rate > _rate_limit)_rate = _rate_limit;
   _ok();
   return;
   }
_p_limit_set();
goto _pl_c_stay;
}// Rate limit

if(_codes == _sov_code){
_codes = 0;
++_code_counter;
_code_disp();
_disp3a();
_disp_data();
_s_c_stay:
_key1 = scan_keypad();
   if(_key1 == _C){
   _sov_cut = 0 ;
   _code_val = 0;
   _disp3a();
   _disp_data();
   }
   if(_key1 == _F){
   _ok();
   return;
   }
_sov_enter();
goto _s_c_stay;
}// SOV

/*
if(_codes == _skip_code){
_codes = 0;
++_code_counter;
_code_disp();
   _disp3b();
_disp_data();
_skip_stay:
_key1 = scan_keypad();
   if(_key1 == _C){
   _skip_val = 0;
   _code_val = 0;
   _disp3b();
   _disp_data();
   }
   if(_key1 == _F){
   _skip_sel_fl = 0;
   _ok();
   return;
   }
   if(_key1 == _L){
   _skip_sel_fl = 1;
   _ok();
   return;
   }
_skip_enter();
goto _skip_stay;
}// SKIP
*/
/*
if(_codes == _skip_all){
_codes = 0;
++_code_counter;
_code_disp();
_skip_val = read_eeprom(201);
if(_skip_val > 10)_skip_val = 0;
   _disp3b();
_disp_data();
_skip_stay:
_key1 = scan_keypad();
   if(_key1 == _C){
   _skip_val = 0;
   _code_val = 0;
   _disp3b();
   _disp_data();
   }
   if(_key1 == _F){
   _skip_sel_fl = 0;
   _ok();
   write_eeprom(201,_skip_val);
   return;
   }
   if(_key1 == _L){
   _skip_sel_fl = 1;
   _ok();
   write_eeprom(201,_skip_val);
   return;
   }
_skip_enter();
goto _skip_stay;
}// SKIP
if(_codes == _skip_liter){
_codes = 0;
++_code_counter;
_code_disp();
_skip_val = read_eeprom(202);
if(_skip_val > 10)_skip_val = 0;
   _disp3b();
_disp_data();
_skip_stay1:
_key1 = scan_keypad();
   if(_key1 == _C){
   _skip_val = 0;
   _code_val = 0;
   _disp3b();
   _disp_data();
   }
   if(_key1 == _F){
   _skip_sel_fl = 0;
   _ok();
   write_eeprom(202,_skip_val);
   return;
   }
   if(_key1 == _L){
   _skip_sel_fl = 1;
   _ok();
   write_eeprom(202,_skip_val);
   return;
   }
_skip_enter();
goto _skip_stay1;
}// SKIP

if(_codes == _skip_rupee){
_codes = 0;
++_code_counter;
_code_disp();
_skip_val = read_eeprom(203);
if(_skip_val > 10)_skip_val = 0;
   _disp3b();
_disp_data();
_skip_stay2:
_key1 = scan_keypad();
   if(_key1 == _C){
   _skip_val = 0;
   _code_val = 0;
   _disp3b();
   _disp_data();
   }
   if(_key1 == _F){
   _skip_sel_fl = 0;
   _ok();
   write_eeprom(203,_skip_val);
   return;
   }
   if(_key1 == _L){
   _skip_sel_fl = 1;
   _ok();
   write_eeprom(203,_skip_val);
   return;
   }
_skip_enter();
goto _skip_stay2;
}// SKIP

if(_codes == _skip_any){
_codes = 0;
++_code_counter;
_code_disp();
_skip_val = read_eeprom(204);
if(_skip_val > 10)_skip_val = 0;
   _disp3b();
_disp_data();
_skip_stay3:
_key1 = scan_keypad();
   if(_key1 == _C){
   _skip_val = 0;
   _code_val = 0;
   _disp3b();
   _disp_data();
   }
   if(_key1 == _F){
   _skip_sel_fl = 0;
   _ok();
   write_eeprom(204,_skip_val);
   return;
   }
   if(_key1 == _L){
   _skip_sel_fl = 1;
   _ok();
   write_eeprom(204,_skip_val);
   return;
   }
_skip_enter();
goto _skip_stay3;
}// SKIP
//////////////////////////////////////// F Function

if(_codes == _skip_all_f){
_codes = 0;
++_code_counter;
_code_disp();
_skip_val = read_eeprom(206);
if(_skip_val > 10)_skip_val = 0;
   _disp3b();
_disp_data();
_skip_stay4:
_key1 = scan_keypad();
   if(_key1 == _C){
   _skip_val = 0;
   _code_val = 0;
   _disp3b();
_disp_data();
   }
   if(_key1 == _F){
   _skip_sel_fl = 0;
   _ok();
   write_eeprom(206,_skip_val);
   return;
   }
   if(_key1 == _L){
   _skip_sel_fl = 1;
   _ok();
   write_eeprom(206,_skip_val);
   return;
   }
_skip_enter();
goto _skip_stay4;
}// SKIP

if(_codes == _skip_liter_f){
_codes = 0;
++_code_counter;
_code_disp();
_skip_val = read_eeprom(207);
if(_skip_val > 10)_skip_val = 0;
   _disp3b();
_disp_data();
_skip_stay5:
_key1 = scan_keypad();
   if(_key1 == _C){
   _skip_val = 0;
   _code_val = 0;
   _disp3b();
   _disp_data();
   }
   if(_key1 == _F){
   _skip_sel_fl = 0;
   _ok();
   write_eeprom(207,_skip_val);
   return;
   }
   if(_key1 == _L){
   _skip_sel_fl = 1;
   _ok();
   write_eeprom(207,_skip_val);
   return;
   }
_skip_enter();
goto _skip_stay5;
}// SKIP

if(_codes == _skip_rupee_f){
_codes = 0;
++_code_counter;
_code_disp();
_skip_val = read_eeprom(208);
if(_skip_val > 10)_skip_val = 0;
   _disp3b();
_disp_data();
_skip_stay6:
_key1 = scan_keypad();
   if(_key1 == _C){
   _skip_val = 0;
   _code_val = 0;
   _disp3b();
_disp_data();
   }
   if(_key1 == _F){
   _skip_sel_fl = 0;
   _ok();
   write_eeprom(208,_skip_val);
   return;
   }
   if(_key1 == _L){
   _skip_sel_fl = 1;
   _ok();
   write_eeprom(208,_skip_val);
   return;
   }
_skip_enter();
goto _skip_stay6;
}// SKIP

if(_codes == _skip_any_f){
_codes = 0;
++_code_counter;
_code_disp();
_skip_val = read_eeprom(209);
if(_skip_val > 10)_skip_val = 0;
   _disp3b();
_disp_data();
_skip_stay7:
_key1 = scan_keypad();
   if(_key1 == _C){
   _skip_val = 0;
   _code_val = 0;
   _disp3b();
_disp_data();
   }
   if(_key1 == _F){
   _skip_sel_fl = 0;
   _ok();
   write_eeprom(209,_skip_val);
   return;
   }
   if(_key1 == _L){
   _skip_sel_fl = 1;
   _ok();
   write_eeprom(209,_skip_val);
   return;
   }
_skip_enter();
goto _skip_stay7;
}// SKIP

////////////////////////////////////////////////////
if(_codes == _skip_error){
_codes = 0;
++_code_counter;
_code_disp();
_skip_val = read_eeprom(205);
if(_skip_val > 5){
_code_val = 0;
_skip_val = 0;
}
   _disp3b();
_disp_data();
_skip_stay8:
_key1 = scan_keypad();
   if(_key1 == _C){
   _skip_val = 0;
   _code_val = 0;
   _disp3b();
   _disp_data();
   }
   if(_key1 == _F){
   _ok();
   write_eeprom(205,_skip_val);
   return;
   }
_skip_enter();
goto _skip_stay8;
}// SKIP


if(_codes == _first_code){
_codes = 0;
++_code_counter;
_code_disp();
   _disp3c();
_disp_data();
_first_stay:
_key1 = scan_keypad();
   if(_key1 == _C){
   _first_val = 0;
   _code_val = 0;
   _disp3c();
   _disp_data();
   }
   if(_key1 == _F){
   _ok();
   return;
   }
_first_enter();
goto _first_stay;
}// first



if(_codes == _hang_code){
_hang_stay:
   if(_key1 == _C){
   _hang = 0;
   _code_val = 0;
   _hang_disp();
   _disp_data();
   }
   if(_key1 == _f){
   _ok();
   return;
   }
_key1 = scan_keypad();
_hang_set();
goto _hang_stay;
}//  hang code



if(_codes == _vf_code){
_codes = 0;
++_code_counter;
_code_disp();
   _disp3e();
_disp_data();
_vfirst_stay:
_key1 = scan_keypad();
   if(_key1 == _C){
   _v_first_val = 0;
   _code_val = 0;
   _disp3e();
   _disp_data();
   }
   if(_key1 == _F){
   _ok();
   return;
   }
_v_first_enter();
goto _vfirst_stay;
}//  very first



if(_codes == _round_code){
_codes = 0;
++_code_counter;
_code_disp();
   _disp3d();
_disp_data();
_round_stay:
_key1 = scan_keypad();
   if(_key1 == _C || _pulses > 2000){
   _pulses = 100;
   _code_val = 0;
   _disp3d();
   _disp_data();
   }
   if(_key1 == _F){
   if(_pulses > 2000 || _pulses < 30)_pulses = 100;
   _ok();
   return;
   }
_round_enter();
goto _round_stay;
}// round


if(_codes == _motor_code){
_codes = 0;
++_code_counter;
_code_disp();
   _disp3f();
_disp_data();
_motor_stay:
_key1 = scan_keypad();
   if(_key1 == _C){
   _code_val = 0;
   _motor_val = 0;
   _disp3f();
   _disp_data();
   }
   if(_key1 == _F){
   if(_motor_val != 1)write_eeprom(27,0);
   else   write_eeprom(27,1);
   _ok();
   return;
   }
_motor_enter();
goto _motor_stay;
}// motor

if(_codes == _t_c_change){
_codes = 0;
++_code_counter;
_code_disp();
   _disp3g();
_disp_data();
_t_c_stay:
_key1 = scan_keypad();
   if(_key1 == _C || _totel_code > 9999){
   _totel_code = 0;
   _code_val = 0;
   _disp3g();
   _disp_data();
    }
   if(_key1 == _F){
   _ok();
   return;
   }
_t_c_enter();
goto _t_c_stay;
}// Totel code change

if(_codes == _time_code){
_get_time();
_td = (int32)_hr * 10000;
_td = _td + (int32)(_min * 100);
_td = _td + (int32)_sec;
_td_disp();
_disp_data();
_time_stay:
   if(_key1 == _C){
   _ag_time:
   _td = 0;
   _code_val = 0;
   _td_disp();
   _disp_data();
   }
   if(_key1 == _f){
   _get_time();
   _hr = _td / 10000;
   _sec = _td % 100;
   _td = _td % 10000;
   _min = _td / 100;
   if(_hr > 23 || _min >  59 || _sec > 59)goto _ag_time;
   rtc_set_datetime(_day,_mth,_year,_dow,_hr,_min);
   _ok();
   return;
   }
_key1 = scan_keypad();
_td_set();
goto _time_stay;
}//  time code
if(_codes == _date_code){
_get_time();
_td = (int32)_day * 10000;
_td = _td + (int32)_mth * 100;
_td = _td + (int32)_year;
_td_disp();
_disp_data();
_date_stay:
   if(_key1 == _C){
   _ag_date:
   _td = 0;
   _code_val = 0;
   _td_disp();
   _disp_data();
      }
   if(_key1 == _f){
   _get_time();
   _day = _td / 10000;
   _year = _td % 100;
   _td = _td % 10000;
   _mth = _td / 100;
   if(_day > 31 || _day < 1 || _mth >  12 || _mth <  1)goto _ag_date;
   rtc_set_datetime(_day,_mth,_year,_dow,_hr,_min);
   _ok();
   return;
   }
_key1 = scan_keypad();
_td_set();
goto _date_stay;
}//  date code


//+++++++++++++++++++++++++++++++++
if(_codes == _last5){
int1 _show = 0;

_codes = 0;
++_code_counter;

_last5_stay:
_key1 = scan_keypad();
   if(_key1 == _p1){
   if(_lasts == 5)_tp = 101;
   if(_lasts == 1)_tp = 111;
   if(_lasts == 2)_tp = 121;
   if(_lasts == 3)_tp = 131;
   if(_lasts == 4)_tp = 141;
   _show = 1;
   }
   if(_key1 == _p2){
   if(_lasts == 5)_tp = 111;
   if(_lasts == 1)_tp = 121;
   if(_lasts == 2)_tp = 131;
   if(_lasts == 3)_tp = 141;
   if(_lasts == 4)_tp = 101;
   _show = 1;
   }
   if(_key1 == _p3){
   if(_lasts == 5)_tp = 121;
   if(_lasts == 1)_tp = 131;
   if(_lasts == 2)_tp = 141;
   if(_lasts == 3)_tp = 101;
   if(_lasts == 4)_tp = 111;
   _show = 1;
   }
   if(_key1 == _p4){
   if(_lasts == 5)_tp = 131;
   if(_lasts == 1)_tp = 141;
   if(_lasts == 2)_tp = 101;
   if(_lasts == 3)_tp = 111;
   if(_lasts == 4)_tp = 121;
   _show = 1;
   }
   if(_key1 == _p5){
   if(_lasts == 5)_tp = 141;
   if(_lasts == 1)_tp = 101;
   if(_lasts == 2)_tp = 111;
   if(_lasts == 3)_tp = 121;
   if(_lasts == 4)_tp = 131;
   _show = 1;
   }

if(_show){
_liters = _r_e(_tp);
_rupee = _r_e(_tp + 5);

_noz_fl = 1;
_disp1();
_noz_fl = 0;
_disp2();
_disp_data();
_disp3(_rate);
_show = 0;

}
if(_key1 == _C)return;
goto _last5_stay;
}// lasts


//++++++++++++ last 5
_err:
_error();
_key1 = scan_keypad();
if(_key1 == _C)return;
goto _err;
}
//******************************************************************************
void _varify_tcode(void){
int8 _t_remander,_f_counter;
if(_codes == _totel_code){
_f_counter = 0;
_t_remander = _totel % 100;
_codes = 0;
if(_totel_counter > 9999)_totel_counter = 0;
_tcode_disp();
_disp_data();
_totel_stay:
_key1 = scan_keypad();
   if(_key1 == _C)return;
   if(_key1 == _F){
   ++_f_counter;
      if(_f_counter == 1){
       _code_val=0;
      _totel_set();
      ++_f_counter;
      }
      if(_f_counter == 2){
      _totel = _totel +(int32)_t_remander;
      ++_totel_counter;
       _w_eerom();
      _tcode_disp();
      _disp_data();

      delay_ms(500);
      _disp_d();
      delay_ms(500);
      _key1 = _c;
      return;
      }
        _totel_disp();
   }
goto _totel_stay;
}// TOTEL
_terr:
_error();
_key1 = scan_keypad();
if(_key1 == _C)return;
goto _terr;
}
//******************************************************************************
void _code_menu(void){
_var1 =_clear;
_all_disp();
_disp_d();
_code_disp();
_disp_data();

_code_val = 0;
_stay:
_key1 = scan_keypad();
if(_key1 == _C)return;
_code_enter();
if(_code_val == 4)_varify_code();
if(_key1 == _C)return;
goto _stay;
}
//******************************************************************************
void _totel_menu(void){
_totel_disp();
_code_val=0;
_disp_d();
_tc_fl = 1;
_TC_stay:
_key1 = scan_keypad();
if(_key1 == _C)return;
_code_enter();
if(_code_val == 4)_varify_tcode();
if(_key1 == _C)return;
goto _TC_stay;
}
*/
//******************************************************************************
