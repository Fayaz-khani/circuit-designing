
#use i2c(master, sda=RTC_SDA, scl=RTC_SCL)

BYTE bin2bcd(BYTE binary_value);
BYTE bcd2bin(BYTE bcd_value);

#define AM  0
#define PM  1
//am_pm = 0;

void ds1307_init(void)
{
   BYTE seconds = 0;
   i2c_start();
   i2c_write(0xD0);      // WR to RTC
   i2c_write(0x00);      // REG 0
   i2c_start();
   i2c_write(0xD1);      // RD from RTC
   seconds = bcd2bin(i2c_read(0)); // Read current "seconds" in DS1307
   i2c_stop();
   seconds &= 0x7F;

   delay_us(3);

   i2c_start();
   i2c_write(0xD0);      // WR to RTC
   i2c_write(0x00);      // REG 0
   i2c_write(bin2bcd(seconds));     // Start oscillator with current "seconds value
   i2c_start();
   i2c_write(0xD0);      // WR to RTC
   i2c_write(0x07);      // Control Register
   i2c_write(0x10);     // ENABLE squarewave output pin
   i2c_stop();

}


void write_DS1307(unsigned int8 address, unsigned int8 _data)
{
   I2C_Start();
   I2C_Write(0xd0);
   I2C_Write(address);
   I2C_Write(_data);
   I2C_Stop();
}
unsigned int8 read_ds1307(unsigned short address) {
unsigned int8 _data_;

   I2C_Start();
   I2C_Write(0xd0);           // b0 is write
   I2C_Write(address);
   I2C_Start();
   I2C_Write(0xd1);           // b1 is read
   _data_=I2C_Read();         // Read with NACK.
   I2C_stop();
   return(_data_);
}
void ds1307_set_date_time(BYTE day, BYTE mth, BYTE year, BYTE dow, BYTE hr, BYTE min, BYTE sec)
{
  sec &= 0x7F;
//  hr &= 0x3F;
  i2c_start();
  i2c_write(0xD0);            // I2C write address
  i2c_write(0x00);            // Start at REG 0 - Seconds
  i2c_write(bin2bcd(sec));      // REG 0
  i2c_write(bin2bcd(min));      // REG 1
  if (am_pm == 1)
  {
   hr = bin2bcd(hr)| 0x60;
  }
  else
  {
   hr = bin2bcd(hr)| 0x40;
  }
//  printf("%x",hr);
//  WHILE(1);
  i2c_write(hr);  // REG 2
  i2c_write(bin2bcd(dow));      // REG 3
  i2c_write(bin2bcd(day));      // REG 4
  i2c_write(bin2bcd(mth));      // REG 5
  i2c_write(bin2bcd(year));     // REG 6
  write_DS1307(0X07, 0X10);
  //i2c_write(0x80);            // REG 7 - Disable squarewave output pin
  i2c_stop();
}

void ds1307_get_date(BYTE &day, BYTE &mth, BYTE &year, BYTE &dow)
{
  i2c_start();
  i2c_write(0xD0);
  i2c_write(0x03);            // Start at REG 3 - Day of week
  i2c_start();
  i2c_write(0xD1);
  dow  = bcd2bin(i2c_read() & 0x7f);   // REG 3
  day  = bcd2bin(i2c_read() & 0x3f);   // REG 4
  mth  = bcd2bin(i2c_read() & 0x1f);   // REG 5
  year = bcd2bin(i2c_read(0));            // REG 6
  i2c_stop();
}

void ds1307_get_time(BYTE &hr, BYTE &min, BYTE &sec)
{
  i2c_start();
  i2c_write(0xD0);
  i2c_write(0x00);            // Start at REG 0 - Seconds
  i2c_start();
  i2c_write(0xD1);
  sec = bcd2bin(i2c_read() & 0x7f);
  min = bcd2bin(i2c_read() & 0x7f);
//  hr  = bcd2bin(i2c_read(0) & 0x3f);
  hr  = i2c_read(0);
  AM_PM = bit_test (hr, 5);
  hr  = bcd2bin(hr & 0x1f);
  i2c_stop();
}

void daufal_time()
{
 int8 data_retain;
 data_retain=read_ds1307(0x3F);  // cheak last ram address
 if (data_retain==5)
 {
 return;
 }
else
 {
  ds1307_init();   // ds1307 initial
  ds1307_set_date_time(10,3,16,5,11,59,55);
  write_ds1307(0x3F,5); // save 5 last ram address
 }
}


BYTE bin2bcd(BYTE binary_value)
{
  BYTE temp;
  BYTE retval;

  temp = binary_value;
  retval = 0;

  while(1)
  {
    // Get the tens digit by doing multiple subtraction
    // of 10 from the binary value.
    if(temp >= 10)
    {
      temp -= 10;
      retval += 0x10;
    }
    else // Get the ones digit by adding the remainder.
    {
      retval += temp;
      break;
    }
  }

  return(retval);
}


// Input range - 00 to 99.
BYTE bcd2bin(BYTE bcd_value)
{
  BYTE temp;
  temp = bcd_value;
  // Shifting upper digit right by 1 is same as multiplying by 8.
  temp >>= 1;
  // Isolate the bits for the upper digit.
  temp &= 0x78;
  // Now return: (Tens * 8) + (Tens * 2) + Ones
  return(temp + (temp >> 2) + (bcd_value & 0x0f));
}



//!  ds1307_init();
//!
//!  // Set date for -> 15 June 2005 Tuesday
//!  // Set time for -> 15:20:55
//!  ds1307_set_date_time(15,6,5,2,15,20,55);
//!
//!  while(1)
//!  {
//!    delay_ms(1000);
//!
//!    ds1307_get_date(day,month,yr,dow);
//!    ds1307_get_time(hrs,min,sec);
//!   LCD_GOTOXY(29,2);
//!   printf(LCD_OUT5X7,"\f\%02d/\%02d/\%02d\r\n",day,month,yr);
//!   LCD_GOTOXY(29,3);
//!   printf(LCD_OUT5X7,"\%02d:\%02d:\%02d", hrs,min,sec);
//!  }

