#include <Wire.h>
#include <TroykaRTC.h>
RTC clock;
#define LEN_TIME 12
#define LEN_DATE 12
#define LEN_DOW 12

int ultrasound_1_trig = 4;
int ultrasound_1_echo = 3;
int infrared_1 = 43;

int ultrasound_2_trig = 2;
int ultrasound_2_echo = 1;
int infrared_2 = 45;

int ultrasound_3_trig = 52;
int ultrasound_3_echo = 48;
int infrared_3 = 43;

int ultrasound_4_trig = 50;
int ultrasound_4_echo = 46;
int infrared_4 = 45;

int ObjDistErrCount = 5;

int feed_1 = 0;
int feed_2 = 0;
int feed_3 = 22;
int feed_4 = 24;

int clock_pin = 51;

String time;
String date;
String weekDay;

unsigned long saved_time_1 = millis();
unsigned long saved_time_2 = millis();
unsigned long old_saved_time = millis();
boolean flag_ = false;
boolean flag_2 = false;

boolean stop_ = false;

int light_on_fuild = 50; /*lx при хорошем освещении*/
int light_on_night_porog = 6000; /*lx при хорошем освещении*/

String data_scr[] = {"9:00","17:00","7:30","18:00","8:00","18:30","6:30","19:30","5:00","20:30","4:30","21:30","4:00","21:45","5:00","20:45","6:30","18:10","6:30","16:54","7:30","16:00","8:30","16:00"};

unsigned long oldTime;
unsigned long currentTime;

struct holidays {
  String start_;
  String end_;
  String date_; //
};

holidays holidays_list[] = {
{"9:00", "23:59", "31.12.2020"}
};

void setup() {
  Serial.begin (9600);
  clock.begin();
  clock.set(__TIMESTAMP__);
  /*setup_feed();
  setup_infared();
  setup_lx();
  setup_ult_sound();*/
}
void ClockRead(){
  clock.read();
  clock.getTimeStamp(time, date, weekDay);
}
unsigned long CalculateDeltaTime(){
  unsigned long currentTime = millis();
  unsigned long deltaTime = currentTime - oldTime;
  oldTime = currentTime;
  return deltaTime;
}
void loop() {
  ClockRead();
  if (!stop_){
    boolean night = false;
    String str7(date[3]);
    String str8(date[4]);
    int date_ind = (str7+str8).toInt();
    String str(time[0]);
    String str2(time[1]);
    float first_1 = (str+str2).toInt();
    String str3(time[3]);
    String str4(time[4]);
    int first_2 = (str3+str4).toInt();
    String str5(time[6]);
    String str6(time[7]);
    int first_3 = (str5+str6).toInt();
    float first_4 = (first_1*60*60) + (first_2*60) + first_3;
    unsigned long deltaTime = CalculateDeltaTime();

    String time_2 = data_scr[date_ind*2-1];
    float first_5 = (String(time_2[0])+String(time_2[1])).toInt();
    int first_6 = (String(time_2[3])+String(time_2[4])).toInt();
    float first_7 = (first_5*60*60) + (first_6*60);
    boolean is_dark = true;
    
    for (int i = 0; i < sizeof(holidays_list)/18; i++){
      Serial.print("i-");
      Serial.println(i);
      if (date ==  holidays_list[i].date_){
        time = holidays_list[i].start_;
        String str7(date[3]);
        String str8(date[4]);
        int date_ind = (str7+str8).toInt();
        String str(time[0]);
        String str2(time[1]);
        float first_1 = (str+str2).toInt();
        String str3(time[3]);
        String str4(time[4]);
        int first_2 = (str3+str4).toInt();
        String str5(time[6]);
        String str6(time[7]);
        int first_3 = (str5+str6).toInt();
        float first_4 = (first_1*60*60) + (first_2*60) + first_3;
        
        String time_2 = holidays_list[i].end_;
        float first_5 = (String(time_2[0])+String(time_2[1])).toInt();
        int first_6 = (String(time_2[3])+String(time_2[4])).toInt();
        float first_7 = (first_5*60*60) + (first_6*60);
      }
    }

    if (light_on_fuild >= ul_2()){
        is_dark = true;
      }
    if (first_4 > first_7-light_on_night_porog || is_dark){
      //Serial.println("сейчас темно");
      if(test_ult_sound(ultrasound_3_trig, ultrasound_3_echo)){
        if (is_dark){
          on_(feed_3);
          flag_2 = true;
          Serial.println("flag_ = true;");
          saved_time_2 = millis();
        }
        else{
          flag_2 = false;
        }
      }
      else{
          flag_2 = false;
        }
      if(test_ult_sound(ultrasound_4_trig, ultrasound_4_echo)){
        if (is_dark){
          on_(feed_4);
          flag_ = true;
          Serial.println("flag_ = true;");
          saved_time_1 = millis();
          //Serial.println();
          //Serial.println();
          //Serial.println("feed_4 on");
        }
        else{
          flag_ = false;
        }
      }
      else{
          flag_ = false;
        }
    }
  }
  if(millis()>=saved_time_1+4500 && flag_ == false){
    off_(feed_4);
  }
  else{
    Serial.println(millis()-saved_time_1);
  }
  if(millis()>=saved_time_2+4500 && flag_2 == false){
    off_(feed_3);
  }
  else{
    Serial.println(millis()-saved_time_2);
  }
  //delay(1000); 
}
