long duration, DUR;

void setup_ult_sound() {
  pinMode(ultrasound_1_trig, OUTPUT);
  pinMode(ultrasound_1_echo, INPUT);
  
  pinMode(ultrasound_2_trig, OUTPUT);
  pinMode(ultrasound_2_echo, INPUT);
  
  pinMode(ultrasound_3_trig, OUTPUT);
  pinMode(ultrasound_3_echo, INPUT);
  
  pinMode(ultrasound_4_trig, OUTPUT);
  pinMode(ultrasound_4_echo, INPUT);
}
boolean test_ult_sound(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(5);
  digitalWrite(trig, HIGH);

  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  DUR = (duration / 2) / 29.1;
  duration = 0;

  Serial.print(DUR);
  Serial.print("cm");
  Serial.println();

  if (DUR < ObjDistErrCount) {
    Serial.println("people_ult_sound_found!");
    return true;
  }
  else {
    Serial.println("NOT found ult sound!");
    return false;
  }
}
