


char str1[] = "Ahmed";
char str2[] = "Nouira";
char str3[100];
byte two = 7;
float temp = 23.5;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("*************************************************************");
  Serial.print("Lenght of str1 :"); Serial.println(strlen(str1));
  Serial.print("Concatenate 2 char[]:"); Serial.println(strcat(str1, str2));
  Serial.print(size_t(two)); //!! 
  Serial.print(String(temp));

}

void loop() {
  // put your main code here, to run repeatedly:

}
