#define GREEN 6
#define RED 9
#define BLUE 5
#define sound A4

void setup() {
  //Set up Pins
  Serial.begin(9600);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(sound, INPUT);
}

void loop() {

    float long_max = 0;
   //Start Mega Loop - to find Long term maximum
    for(int i = 0; i < 10000; i++){
      
   //declare new STM variable
    int short_max = 0;
    float average = 0;
    
   //Find short term maximum - Loop 100 times
    for(int j = 0; j < 400; j++){
      average = average + analogRead(sound);
      if(analogRead(sound) > short_max){
        short_max = analogRead(sound);
        }
    }
   float loudness = abs(short_max - average/400);

   if(loudness > long_max){
      long_max = loudness;
    }
   
   //Calc the RGB values and Vol variables based on formula
    
   float factor = long_max/20;

   float rA = 10*sq(1/factor);
   float gA = 15*sq(1/factor);
   float bA = 8*sq(1/factor);
   float rB = 15*factor;
   float gB = 4*factor;
   float bB = 9*factor;
   
   float red = -rA*sq(loudness - rB) + 255;
   float green = -gA*sq(loudness - gB) + 255;
   float blue = -bA*sq(loudness - bB) + 255;

   
   //if Logic for below 0
   if(red < 0){
    red = 0;
    }
   if(green < 0){
    green = 0;
    }
   if(blue < 0){
    blue = 0;
    }

    if(red < 50 && blue < 50 && green < 150){
      green = 150;
      }

    if(long_max < 1){
      red = 0;
      blue = 0;
      green = 0;
      }
    Serial.print(long_max);
    Serial.print(' ');
    Serial.print(loudness);
    Serial.print(' ');
    Serial.print(red);
    Serial.print(' ');
    Serial.print(green);
    Serial.print(' ');
    Serial.println(blue);
   
   //Send RGB vals to Lights
   analogWrite(RED, red);
   analogWrite(GREEN, green);
   analogWrite(BLUE, blue);
    
   
    }

}
