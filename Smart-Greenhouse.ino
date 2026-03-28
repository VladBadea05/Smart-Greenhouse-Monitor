#include <LiquidCrystal.h>

const int rs = 11, en = 12, d4 = 3, d5 = 4, d6 = 5, d7 = 6;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int SoilSenzor = A5;
const int TempS = A0;
float voltaj = 0;
float temperaturaC = 0; 
unsigned long time=0;
bool  ErrorTemp = 0;
bool  ErrorSoil = 0;
#define VerificationState 1
#define ActionState 2
#define ErrorState 3
const int ValUmed = 300;
const int ValUscat = 800;
int soilMoisturePercentage=0;
int temp=0;

int StartState = 1 ;
void setup(){
  Serial.begin(9600);
  lcd.begin(16,2);
  
}
void loop(){
  switch(StartState){
    case VerificationState:
    soilMoisturePercentage=0;
      for(int i=0;i<10;i++){
        	soilMoisturePercentage+=map(analogRead(SoilSenzor),ValUmed,ValUscat,0,150);	
      }
     soilMoisturePercentage/=10;
  	soilMoisturePercentage=constrain(soilMoisturePercentage,0,150);
   	temp=analogRead(TempS);
     voltaj = temp * (5.0 / 1024.0);
     temperaturaC = (voltaj - 0.5) * 100.0;
    if(temperaturaC<=-1 || temperaturaC>=40){
      ErrorTemp=1;
       time=millis();
      StartState=ErrorState;
    }
    	lcd.setCursor(0, 0);
      lcd.print("Umid: "); lcd.print(soilMoisturePercentage); lcd.print(" %   ");
      lcd.setCursor(0, 1);
      lcd.print("Temp: "); lcd.print(temperaturaC); lcd.print(" C   ");
    //delay(50);
    lcd.clear();
      if(soilMoisturePercentage >= 80 && soilMoisturePercentage < 130){
        if(millis()-time>=1000){
           time=millis();
          StartState=ActionState;
        }
      }
        if(soilMoisturePercentage <= 10 || soilMoisturePercentage >= 130){
            ErrorSoil=1;
           	time=millis();
          	StartState=ErrorState;
        }
      
    break;
    case ActionState:
  		lcd.print("Se uda solul... ");
      soilMoisturePercentage = map(analogRead(SoilSenzor), ValUmed, ValUscat, 0, 150);
      lcd.setCursor(0, 1);
      lcd.print("Umid: ");
      lcd.print(soilMoisturePercentage);
      if(soilMoisturePercentage <= 40 ){ 
        StartState = VerificationState; 
        lcd.clear(); 
      }
    if(soilMoisturePercentage <= 5 || soilMoisturePercentage >= 140 ){ 
        StartState = ErrorState; 
        lcd.clear(); 
      }
    break;
    case ErrorState:
    if(ErrorTemp==1){
      lcd.setCursor(0,1);
      	lcd.print("Error:CheckTemp");
      Serial.println(temperaturaC);
    }
  
    if(ErrorSoil==1){
      lcd.setCursor(0,0);
      	lcd.print("Error:CheckSoil");
      Serial.println(soilMoisturePercentage);
    }
    if(millis()-time>=2000){
    ErrorTemp = 0;
    ErrorSoil = 0; 
    lcd.clear();
    StartState=VerificationState;
    }
    break;
    
  }
  

}