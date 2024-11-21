#include <Servo.h>

Servo finger[5];  // Пример использования серво
int states[5];  // Массив для хранения полученных данных

void setup() {
  Serial.begin(9600);
  finger[0].attach(3);
  finger[1].attach(4);
  finger[2].attach(5);
  finger[3].attach(6);
  finger[4].attach(7);

}

void loop() {
  if (Serial.available()) {
    String data = Serial.readStringUntil('\n');  // Читаем строку до символа новой строки
    parseArray(data);  // Парсим строку в массив
  }

  for(int i=0;i<4; i++){
  if (states[i] == 1) {
    finger[i].write(180);  // Если первый элемент массива равен 1, движем серво
  } else {
    finger[i].write(0);
  }
  }
}

void parseArray(String input) {
  int index = 0;
  char *token = strtok((char *)input.c_str(), ",");  // Разделяем строку по запятым
  while (token != NULL && index < 5) {              // Ограничиваем размер массива
    states[index++] = atoi(token);                  // Конвертируем строку в число
    token = strtok(NULL, ",");
  }
}
