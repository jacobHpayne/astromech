
const float LATITUDE = 41.662013938945336;
const float LONGITUDE = -91.53219935314317;
const X_STEP = D2;
const Y_STEP = D3;
const X_DIR  = D5;
const Y_DIR  = D6;

double ha,dec,haMin;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available() > 0) {
    float ra = Serial.parseFloat();
    float dec = Serial.parseFloat();
  }
}
