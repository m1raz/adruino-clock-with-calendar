#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int lcd_key     = 0;
int adc_key_in  = 0;



int year = 2017;
int month = 12;
int day = 12;
int hours = 0;
int minutes = 1;
int sec = 30;
int half_sec = 0;
int brightness_prc = 100;
int selected = 0;

bool pause = false;
bool showSelected = true;
bool allowBtn = true;
bool bright_demo = false;
bool done = false;



#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5
#define LCD_Backlight 10
int read_LCD_buttons()
{
   adc_key_in = analogRead(0);
   if (adc_key_in > 1000) return btnNONE;
   if (adc_key_in < 50)   return btnRIGHT;  
   if (adc_key_in < 250)  return btnUP; 
   if (adc_key_in < 450)  return btnDOWN; 
   if (adc_key_in < 650)  return btnLEFT; 
   if (adc_key_in < 850)  return btnSELECT;  
   return btnNONE;
}
void clearRow(int row){
  for(int pos = 0; pos <= 15; pos++){
    lcd.setCursor(pos, row);
    lcd.print(" ");
  }
}

void printDateTime(){
  //printing date
   clearRow(0);
   clearRow(1);
   if(selected == 1){
     if(!showSelected){
       lcd.setCursor(0,0);
       lcd.print("__");
     }else{
       if(day >= 10){
           lcd.setCursor(0,0);
           lcd.print(day);
       }else{
           lcd.setCursor(0,0);
           lcd.print("0");
           lcd.setCursor(1,0);
           lcd.print(day);
       }
     }
   }else{
     if(day >= 10){
         lcd.setCursor(0,0);
         lcd.print(day);
     }else{
         lcd.setCursor(0,0);
         lcd.print("0");
         lcd.setCursor(1,0);
         lcd.print(day);
     }
   }

   lcd.setCursor(2,0);
   lcd.print(".");  
   
   if(selected == 2){
     if(!showSelected){
       lcd.setCursor(3,0);
       lcd.print("___");
     }else{
       lcd.setCursor(3,0);
       if(month == 1) lcd.print("jan");
       if(month == 2) lcd.print("feb");
       if(month == 3) lcd.print("mar");
       if(month == 4) lcd.print("apr");
       if(month == 5) lcd.print("mai");
       if(month == 6) lcd.print("jun");
       if(month == 7) lcd.print("jul");
       if(month == 8) lcd.print("aug");
       if(month == 9) lcd.print("sept");
       if(month == 10) lcd.print("okt");
       if(month == 11) lcd.print("nov");
       if(month == 12) lcd.print("dec");
     }
   }else{
     lcd.setCursor(3,0);
     if(month == 1) lcd.print("jan");
     if(month == 2) lcd.print("feb");
     if(month == 3) lcd.print("mar");
     if(month == 4) lcd.print("apr");
     if(month == 5) lcd.print("mai");
     if(month == 6) lcd.print("jun");
     if(month == 7) lcd.print("jul");
     if(month == 8) lcd.print("aug");
     if(month == 9) lcd.print("sept");
     if(month == 10) lcd.print("okt");
     if(month == 11) lcd.print("nov");
     if(month == 12) lcd.print("dec");
   }

   
   lcd.setCursor(12,0);
   if(selected == 3){
      if(!showSelected)
        lcd.print("____");
      else
        lcd.print(year);
   }else{
      lcd.print(year);
   }
      
   
   if(selected == 4){
       if(!showSelected){
           lcd.setCursor(0,1);
           lcd.print("__");
       }else{        
           if(hours >= 10){
               lcd.setCursor(0,1);
               lcd.print(hours);
           }else{
               lcd.setCursor(0,1);
               lcd.print("0");
               lcd.setCursor(1,1);
               lcd.print(hours);
           }
       }
   }else{
       if(hours >= 10){
           lcd.setCursor(0,1);
           lcd.print(hours);
       }else{
           lcd.setCursor(0,1);
           lcd.print("0");
           lcd.setCursor(1,1);
           lcd.print(hours);
       }
   }
   lcd.setCursor(2,1);
   lcd.print(":");
   if(selected == 5){
       if(!showSelected){
           lcd.setCursor(3,1);
           lcd.print("__");
       }else{
           if(minutes >= 10){
              lcd.setCursor(3,1);
              lcd.print(minutes);
           }else{
              lcd.setCursor(3,1);
              lcd.print("0");
              lcd.setCursor(4,1);
              lcd.print(minutes);
           }
       }
   }else{
       if(minutes >= 10){
           lcd.setCursor(3,1);
           lcd.print(minutes);
       }else{
           lcd.setCursor(3,1);
           lcd.print("0");
           lcd.setCursor(4,1);
           lcd.print(minutes);
       }
   }
   lcd.setCursor(5,1);
   lcd.print(":");
   if(selected == 6){
       if(!showSelected){
           lcd.setCursor(6,1);
           lcd.print("__");
       }else{
           if(sec >= 10){
               lcd.setCursor(6,1);
               lcd.print(sec);
           }else{
               lcd.setCursor(6,1);
               lcd.print("0");
               lcd.setCursor(7,1);
               lcd.print(sec);
           }
       }
   }else{
       if(sec >= 10){
           lcd.setCursor(6,1);
           lcd.print(sec);
       }else{
           lcd.setCursor(6,1);
           lcd.print("0");
           lcd.setCursor(7,1);
           lcd.print(sec);
       }
   }
   if(selected == 7){
       lcd.setCursor(11,1);
       lcd.print("LIGHT");
   }
}
//
//void changeBacklight(bool show){
//   analogWrite(LCD_Backlight, brightness_prc);
//   if(show == true){
//     lcd.setCursor(12,1);
//     lcd.print(brightness_prc);
//     lcd.setCursor(15,1);
//     lcd.print("%");
//   }
//}

void setup()
{
   Serial.begin(9600);
   lcd.begin(16, 2);
   lcd.setCursor(0, 0);
   lcd.print("Loading...");  
//   changeBacklight(true);
   
  // initialize timer1 
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;

//  OCR1A = 62500;            // compare match register 16MHz/256/2Hz
  OCR1A = 31250;            // compare match register 16MHz/256/2Hz
//  OCR1A = 15625;            // compare match register 16MHz/256/2Hz
  TCCR1B |= (1 << WGM12);   // CTC mode
  TCCR1B |= (1 << CS12);    // 256 prescaler 
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
  interrupts();             // enable all interrupts
}

ISR(TIMER1_COMPA_vect)          // timer compare interrupt service routine
{
    half_sec++;
    if(half_sec >= 2){
      done = true;
      if(!pause) sec++;
      showSelected = !showSelected;
      half_sec = 0;
    }
}
int current_sec = 0;
void loop()
{
   if(done){
       done = false;
       printDateTime();
       current_sec = sec;
       if(bright_demo){
          brightness_prc = brightness_prc + 10;
          if(brightness_prc >= 101) brightness_prc = 10;
  //      changeBacklight(false);
       }
  
       if(sec >= 59){
            sec = 0;
            current_sec = 0;
            minutes++;
            if(minutes >= 59){
                minutes = 0;
                hours++;
                if(hours >= 23){
                    hours = 0;
                    day++;
                    if(month == 1 && day >= 31){
                        month++;
                        day = 1;
                    }else if(month == 2 && day >= 29 && year % 4 == 0){
                        month++;
                        day = 1;
                    }else if(month == 2 && day >= 28 && year % 4 != 0){
                        month++;
                        day = 1;
                    }else if(month == 3 && day >= 31){
                        month++;
                        day = 1;
                    }else if(month == 4 && day >= 30){
                        month++;
                        day = 1;
                    }else if(month == 5 && day >= 31){
                        month++;
                        day = 1;
                    }else if(month == 6 && day >= 30){
                        month++;
                        day = 1;
                    }else if(month == 7 && day >= 31){
                        month++;
                        day = 1;
                    }else if(month == 8 && day >= 31){
                        month++;
                        day = 1;
                    }else if(month == 9 && day >= 30){
                        month++;
                        day = 1;
                    }else if(month == 10 && day >= 31){
                        month++;
                        day = 1;
                    }else if(month == 11 && day >= 30){
                        month++;
                        day = 1;
                    }else if(month == 12 && day >= 31){
                        month = 1;
                        day = 1;
                        year++;
                    }
                }
            }
       }
   }
   
   if(read_LCD_buttons() == btnSELECT){
        pause = true;
        selected++;
        delay(10); //prevent double ++
        if(selected >= 8){
          selected = 0;
          pause = false;
        }
   }

   if(read_LCD_buttons() == btnUP){
       switch(selected){
           case 0:
               brightness_prc++;
               if(brightness_prc >= 101) brightness_prc = 10;
//               changeBacklight(true);
               delay(30);
               break;
           case 1:
               day++;

               if(month == 1 && day >= 32) day = 1;
               else if(month == 2 && day >= 30 && year % 4 == 0) day = 1;
               else if(month == 2 && day >= 29 && year % 4 != 0) day = 1;
               else if(month == 3 && day >= 32) day = 1;
               else if(month == 4 && day >= 31) day = 1;
               else if(month == 5 && day >= 32) day = 1; 
               else if(month == 6 && day >= 31) day = 1;
               else if(month == 7 && day >= 32) day = 1;
               else if(month == 8 && day >= 32) day = 1;
               else if(month == 9 && day >= 31) day = 1;
               else if(month == 10 && day >= 32) day = 1;
               else if(month == 11 && day >= 31) day = 1;
               else if(month == 12 && day >= 32) day = 1;
               showSelected = true;
               delay(300);
               
               break;
           case 2:
               month++;
               if(month >= 13) month = 1;
               showSelected = true;
               delay(300);
               break;
           case 3:
               year++;
               delay(300);
               break;
           case 4:
               hours++;
               if(hours >= 24) hours = 0;
               showSelected = true;
               delay(300);
               break;
           case 5:
               minutes++;
               if(minutes >= 60) minutes = 0;
               showSelected = true;
               delay(300);
               break;
           case 6:
               sec++;
               if(sec >= 60) sec = 0;
               showSelected = true;
               delay(300);
               break;
           case 7:
               lcd.setCursor(8,1);
               lcd.print("DEMO  ON");
               bright_demo = true;
//               delay(MSINSEC);
               break;
               
       }
       printDateTime();
   }

   if(read_LCD_buttons() == btnDOWN){
       switch(selected){
           case 0:
               brightness_prc--;
               if(brightness_prc <= 9) brightness_prc = 100;
//               changeBacklight(true);
               delay(30);
               break;
           case 1:
               day--;
               if(month == 1 && day <= 0) day = 31;
               else if(month == 2 && day <= 0 && year % 4 == 0) day = 29;
               else if(month == 2 && day <= 0 && year % 4 != 0) day = 28;
               else if(month == 3 && day <= 0) day = 31;
               else if(month == 4 && day <= 0) day = 30;
               else if(month == 5 && day <= 0) day = 31; 
               else if(month == 6 && day <= 0) day = 30;
               else if(month == 7 && day <= 0) day = 31;
               else if(month == 8 && day <= 0) day = 31;
               else if(month == 9 && day <= 0) day = 30;
               else if(month == 10 && day <= 0) day = 31;
               else if(month == 11 && day <= 0) day = 30;
               else if(month == 12 && day <= 0) day = 31;
               delay(300);
               break;
           case 2:
               month--;
               if(month <= 0) month = 12;
               delay(300);
               break;
           case 3:
               year--;
               delay(300);
               break;
           case 4:
               hours--;
               if(hours <= 0) hours = 23;
               delay(300);
               break;
           case 5:
               minutes--;
               if(minutes <= 0) minutes = 59;
               delay(300);
               break;
           case 6:
               sec--;
               if(sec <= 0) sec = 59;
               delay(300);
               break;
           case 7:
               lcd.setCursor(8,1);
               lcd.print("DEMO OFF");
               bright_demo = false;
//               delay(MSINSEC);
               break;
       }
       printDateTime();
   }
}
