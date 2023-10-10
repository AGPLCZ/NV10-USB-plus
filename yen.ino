volatile byte cashCount = 0;
volatile byte bored = 0;
 
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(1200);
  attachInterrupt(0, caChing, FALLING);
  delay(3000);          // Wait for the BA to boot
  cashCount = 0;        // clear any interrupts triggered by the BA booting
}
 
void caChing()
{
  cashCount++;    // for every bill pulse, add 1
}
 
void loop()
{
  // put your main code here, to run repeatedly:
  bored = cashCount;
 if (cashCount == 0){
   Serial.println("You have NO yen!");
   hanginAround();
 } else {
   Serial.print("You have ");
   Serial.print(cashCount*1000);
   Serial.println(" yen.");
 }
 hanginAround();
}
 
void hanginAround(){
  if (bored != cashCount){
    return;
  } else{
    hanginAround();
  }
}
 
