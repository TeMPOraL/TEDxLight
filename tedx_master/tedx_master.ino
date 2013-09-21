/*
  Fade Example modified for TEDx Diode lights.
*/

int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by

int potValue = 0;
int realValue = 0;

int potPin = A0;

int syncInPin = A2;
int syncOutPin = A4;

int otherValue;

int range = 16777216;
int inPulseRange = 2000;

int R = 0;
int G = 0;
int B = 0;


void MAGICtoRGB(float h)
{
    int i;
    int s = 1;
    int v = 255;

    float f, p, q, t;

    if( s == 0 ) {
        // achromatic (grey)
        R = G = B = v;
        return;
    }

    h /= 60;			// sector 0 to 5
    i = floor( h );
    f = h - i;			// factorial part of h
    p = v * ( 1 - s );
    q = v * ( 1 - s * f );
    t = v * ( 1 - s * ( 1 - f ) );

    switch( i ) {
    case 0:
        R = v;
        G = t;
        B = p;
        break;
    case 1:
        R = q;
        G = v;
        B = p;
        break;
    case 2:
        R = p;
        G = v;
        B = t;
        break;
    case 3:
        R = p;
        G = q;
        B = v;
        break;
    case 4:
        R = t;
        G = p;
        B = v;
        break;
    default:		// case 5:
        R = v;
        G = p;
        B = q;
        break;
    }

}

void setup()  { 
  // declare pin 14 to be an output:
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  
  pinMode(syncInPin, INPUT);
  
  Serial.begin(9600);
} 

void loop()  {
  potValue = analogRead(potPin);
  
  analogWrite(syncOutPin, potValue / 16);
  otherValue = pulseIn(syncInPin, HIGH, 20000);
  
//  Serial.print(potValue / 16);
//  Serial.print("/");
//  Serial.print(otherValue);
//  Serial.print(" (");
//  Serial.print((otherValue * 360) / inPulseRange);
//  Serial.println(")");
  
  // set the brightness of pin 9:
//  analogWrite(RED_LED, potValue % 255);
//  analogWrite(GREEN_LED, ((potValue >> 4)*16) % 255);
//  analogWrite(BLUE_LED, ((realValue >> 8)*16) % 255);
  if(otherValue > 5) {
    MAGICtoRGB((((potValue * 360) / 4096) + ((otherValue * 360) / inPulseRange))/2);
  }
  else {
    MAGICtoRGB((potValue * 360) / 4096);
  }
  analogWrite(RED_LED, R);
  analogWrite(GREEN_LED, G);
  analogWrite(BLUE_LED, B);
  
//  Serial.print("R: ");
//  Serial.print(R);
  
//  Serial.print(" G: ");
//  Serial.print(G);
  
//  Serial.print(" B: ");
//  Serial.print(B);
  
//  Serial.println("");

//  Serial.println(potValue % 255);
//  Serial.println(((potValue >> 4)*16) % 255);
//  Serial.println(((potValue >> 8)*16) % 255);
 // delay(250);
}
