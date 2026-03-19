#include <Arduino.h>

const int rowPins[] = {4, 5};         // 2 Hàng
const int colPins[] = {7, 15, 16};    // 3 Cột
const int ledPins[] = {17, 18, 8, 3, 9}; // 5 Đèn (Tiến, Lùi, Trái, Phải, Dừng)

void setup() {
  Serial.begin(115200);

  // 1. Cài đặt 5 đèn LED
  for (int i = 0; i < 5; i++) pinMode(ledPins[i], OUTPUT);

  // 2. Cài đặt 2 Hàng là đầu ra (OUTPUT)
  for (int i = 0; i < 2; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], HIGH); // Mặc định để mức CAO
  }

  // 3. Cài đặt 3 Cột là đầu vào (INPUT_PULLUP)
  for (int i = 0; i < 3; i++) pinMode(colPins[i], INPUT_PULLUP);
}

void loop() {
  // QUY TRÌNH QUÉT:
  for (int r = 0; r < 2; r++) {      // Chạy qua từng Hàng
    digitalWrite(rowPins[r], LOW);   // "Hỏi" hàng này bằng cách cho nó xuống LOW

    for (int c = 0; c < 3; c++) {    // Trong hàng đó, kiểm tra từng Cột
      if (digitalRead(colPins[c]) == LOW) { // Nếu thấy Cột bị kéo xuống LOW
        
        int buttonID = (r * 3) + c + 1; // Tính số thứ tự nút (1 đến 6)
        Serial.print("Nút đã nhấn: "); Serial.println(buttonID);

        // ĐIỀU KHIỂN LED:
        for(int l=0; l<5; l++) digitalWrite(ledPins[l], LOW); // Tắt hết đèn cũ
        if (buttonID <= 5) digitalWrite(ledPins[buttonID - 1], HIGH); // Bật đèn tương ứng

        while(digitalRead(colPins[c]) == LOW); // Đợi buông tay
        delay(50);
      }
    }
    digitalWrite(rowPins[r], HIGH); // Trả hàng về mức CAO để quét hàng sau
  }
}
