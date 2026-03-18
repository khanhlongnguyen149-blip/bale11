#include <Arduino.h>

// --- PHẦN KHAI BÁO ---

// 1. Chân GPIO cho 5 đèn LED. Nên dùng các chân an toàn 7,8,9,10,11
const int ledTienPin = 17;
const int ledLuiPin  = 18;
const int ledTraiPin = 8;
const int ledPhaiPin = 3;
const int ledDungPin = 9;

// 2. Chân GPIO cho ma trận nút 3x3. Chừa chân 0,3,1. Nên dùng 2,4,5 (Hàng) và 6,15,16 (Cột)
// Chú ý: Cột 1 cắm chân 6, Cột 2 chân 15, Cột 3 chân 16
const int rowPins[] = {4 ,5, 6};   // 3 chân Hàng (Outputs)
const int colPins[] = {7, 15, 16};  // 3 chân Cột (Inputs với Pullup)

const int NUM_ROWS = sizeof(rowPins) / sizeof(rowPins[0]);
const int NUM_COLS = sizeof(colPins) / sizeof(colPins[0]);

// Ánh xạ từ (Hàng, Cột) ra số nút tương ứng trên hình
const int buttonMap[3][3] = {
  {3, 2, 1}, // Hàng 1 (Nút 3, 2, 1)
  {6, 5, 4}, // Hàng 2 (Nút 6, 5, 4)
  {9, 8, 7}  // Hàng 3 (Nút 9, 8, 7)
};

// --- CÁC HÀM HỖ TRỢ ---

// Hàm tắt tất cả 5 đèn LED
void turnOffAllLeds() {
  digitalWrite(ledTienPin, LOW);
  digitalWrite(ledLuiPin,  LOW);
  digitalWrite(ledTraiPin, LOW);
  digitalWrite(ledPhaiPin, LOW);
  digitalWrite(ledDungPin, LOW);
}

// Yêu cầu của đề bài: Viết HÀM để quét ma trận nút nhấn
// Hàm trả về số nút được nhấn (1-9), hoặc trả về 0 nếu không nhấn
int readButtonMatrix() {
  for (int i = 0; i < NUM_ROWS; i++) {
    // 1. Bật hàng hiện tại lên (cho xuống LOW)
    digitalWrite(rowPins[i], LOW);

    // 2. Kiểm tra xem các cột có ai bị kéo xuống LOW không
    for (int j = 0; j < NUM_COLS; j++) {
      if (digitalRead(colPins[j]) == LOW) {
        // Nút tại (Hàng i, Cột j) đang được nhấn
        int pressedButton = buttonMap[i][j];

        // Đợi cho đến khi buông tay ra mới làm tiếp (chống dội nút nhấn)
        while(digitalRead(colPins[j]) == LOW);
        delay(50); // Nghỉ một chút trước khi quét tiếp
        
        // Trả hàng về lại HIGH trước khi thoát hàm
        digitalWrite(rowPins[i], HIGH);
        return pressedButton; // Trả về số nút
      }
    }

    // 3. Tắt hàng hiện tại đi (cho lên lại HIGH) trước khi chuyển sang hàng tiếp theo
    digitalWrite(rowPins[i], HIGH);
  }
  return 0; // Không nút nào được nhấn
}

// --- HÀM SETUP VÀ LOOP CHÍNH ---

void setup() {
  Serial.begin(115200);
  Serial.println("--- Ma tran nut nhan 3x3 dieu khien 5 LED ---");

  // Thiết lập 5 đèn LED là đầu ra
  pinMode(ledTienPin, OUTPUT);
  pinMode(ledLuiPin,  OUTPUT);
  pinMode(ledTraiPin, OUTPUT);
  pinMode(ledPhaiPin, OUTPUT);
  pinMode(ledDungPin, OUTPUT);
  turnOffAllLeds(); // Mặc định tắt hết

  // Thiết lập chân Hàng là OUTPUT, mặc định để HIGH
  for (int i = 0; i < NUM_ROWS; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], HIGH);
  }

  // Thiết lập chân Cột là INPUT_PULLUP
  // Chú ý: Lệnh này rất quan trọng để nút không bị 'trôi nổi' (Floating).
  for (int j = 0; j < NUM_COLS; j++) {
    pinMode(colPins[j], INPUT_PULLUP);
  }
}

void loop() {
  int buttonPressed = readButtonMatrix(); // Quét lấy nút được nhấn

  if (buttonPressed > 0) {
    Serial.print("Da nhan nut so: ");
    Serial.println(buttonPressed);
    
    // Yêu cầu đề bài: "VD: Ấn nút tiến đèn tiến sẽ sáng, ..."
    // Chúng ta sẽ ánh xạ 5 nút đầu tiên (1-5) vào 5 đèn (Tiến-Dừng)
    turnOffAllLeds(); // Tắt hết đèn cũ trước khi bật đèn mới
    
    switch (buttonPressed) {
      case 1: // Nút 1 -> Đèn Tiến sáng
        digitalWrite(ledTienPin, HIGH);
        Serial.println("-> Bat den TIEN");
        break;
      case 2: // Nút 2 -> Đèn Lùi sáng
        digitalWrite(ledLuiPin, HIGH);
        Serial.println("-> Bat den LUI");
        break;
      case 3: // Nút 3 -> Đèn Trái sáng
        digitalWrite(ledTraiPin, HIGH);
        Serial.println("-> Bat den TRAI");
        break;
      case 4: // Nút 4 -> Đèn Phải sáng
        digitalWrite(ledPhaiPin, HIGH);
        Serial.println("-> Bat den PHAI");
        break;
      case 5: // Nút 5 -> Đèn Dừng sáng
        digitalWrite(ledDungPin, HIGH);
        Serial.println("-> Bat den DUNG");
        break;
      default:
        Serial.println("-> Nut nay khong co chuc nang");
        break;
    }
  }
}