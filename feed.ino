
void setup_feed() {
  pinMode(feed_1, OUTPUT);
  digitalWrite(feed_1, HIGH);
  pinMode(feed_2, OUTPUT);
  digitalWrite(feed_2, HIGH);
  pinMode(feed_3, OUTPUT);
  digitalWrite(feed_3, HIGH);
  pinMode(feed_4, OUTPUT);
  digitalWrite(feed_4, HIGH);
}
void test_rele(){
  digitalWrite(feed_1, LOW); // Включаем реле - посылаем низкий уровень сигнала
  delay(500);
  digitalWrite(feed_1, HIGH); // Отключаем реле - посылаем высокий уровень сигнала
  delay(500);
}
void off_(int rele){
  digitalWrite(rele, LOW);
}
void on_(int rele){
  digitalWrite(rele, HIGH);
}
