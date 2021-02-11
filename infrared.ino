void setup_infared() {
  pinMode(infrared_1, INPUT);
  pinMode(infrared_2, INPUT);
  pinMode(infrared_3, INPUT);
  pinMode(infrared_4, INPUT);
}
boolean infrared_test(int inf_){
  int oldValue1 = 0;
  int pirValue1 = 0;
  int ch = 0;

  oldValue1 = digitalRead(inf_);
  pirValue1 = 0;
  ch = 0;
  int ch_summ = 0;
  while (ch != 8 ) {
    pirValue1 = digitalRead(inf_);
    if (oldValue1 == pirValue1)
      ch++;
    else
      ch = 0;
    oldValue1 = pirValue1;
    delay(10);
    ch_summ += pirValue1;
  }
  if (ch_summ >= 3) {
    Serial.println("people_inf_found!");
    return true;
  }
  else {
    Serial.println("people_inf_NOTfound!");
    return false;
  }
}
