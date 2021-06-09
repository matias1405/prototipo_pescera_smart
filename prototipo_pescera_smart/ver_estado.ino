void ver_estado(){
    contador = 0;
    while(true){
        int Sens = Leer_Nivel_Agua();
        float temp = Leer_Temp();
        float T = EEPROM.read(eeprom_temp);
        T = T - 2;
        if(temp < T)(digitalWrite(resist, HIGH));
        else(digitalWrite(resist, LOW));      
        float ph = Leer_Ph();
        int p = EEPROM.read(eeprom_ph);
        int p_f = (p/10) + 1;
        if(ph > p_f)(digitalWrite(dosificador, HIGH));
        else(digitalWrite(dosificador, LOW)); 
        oled.clearDisplay();
        oled.drawRect(1,1,127,63,WHITE);
        oled.setTextSize(1);
        oled.setTextColor(SSD1306_WHITE);
        oled.setCursor(15,5);             // Columna, Fila
        oled.println(F("ESTADO ACTUAL"));
        delay(5);
        oled.setCursor(4,15);             // Columna, Fila
        oled.println(F("Temp:"));
        delay(5);
        oled.setCursor(70,15);             // Columna, Fila
        oled.println(temp);
        delay(5);
        oled.setCursor(4,25);             // Columna, Fila
        oled.println(F("N. de PH:"));
        delay(5);
        oled.setCursor(70,25);             // Columna, Fila
        oled.println(ph);
        delay(5);
        if(Sens == 0){
            digitalWrite(bomba, HIGH);
            oled.setCursor(4,35);             // Columna, Fila
            oled.println(F("B. de Agua ON"));
            delay(5);
        } 
        else{
            digitalWrite(bomba, LOW);
            oled.setCursor(4,35);             // Columna, Fila
            oled.println(F("B. de Agua OFF"));
            delay(5);
        }
        int hora_1 = EEPROM.read(2);
        int min_1 = EEPROM.read(3);
        int hora_2 = EEPROM.read(4);
        int min_2 = EEPROM.read(5);
        int hora_3 = EEPROM.read(6);
        int min_3 = EEPROM.read(7);
        int hora_4 = EEPROM.read(8);
        int min_4 = EEPROM.read(9);
        DateTime h_actual = rtc.now();
        int hora_actual = h_actual.hour();
        int min_actual = h_actual.minute();
        if((hora_actual == hora_1 && min_actual == min_1)||(hora_actual == hora_3 && min_actual == min_3)){
            digitalWrite(aireador, HIGH);
            contador = 1;                     
        }
        else if((hora_actual == hora_2 && min_actual == min_2)||(hora_actual == hora_4 && min_actual == min_4)){
            digitalWrite(aireador, LOW);
            contador = 0;                     
        }
        if(contador == 1){
            oled.setCursor(4,45);             // Columna, Fila
            oled.println(F("Aireador ON"));
            delay(5);
        }
        if(contador == 0){
            oled.setCursor(4,45);             // Columna, Fila
            oled.println(F("Aireador OFF"));
            delay(5);
        }
        oled.setCursor(4,55);             // Columna, Fila
        oled.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
        oled.println(F("VOLVER"));
        delay(5);
        oled.display();
        if(digitalRead(sw_aceptar) == 0){
            menu_principal();
        }                
    }
}    

         
  
int Leer_Nivel_Agua(){
    int SensorNivel = digitalRead(Nivel); 
    return SensorNivel; 
}        
float Leer_Temp(){
       int Vo;
       float R1 = 100000;              // resistencia fija del divisor de tension 
       float logR2, R2, temperatura;
       float c1 = 2.114990448e-03, c2 = 0.3832381228e-04, c3 = 5.228061052e-07;
       Vo = analogRead(valor);      // lectura de A0
       R2 = R1 * (1023.0 / (float)Vo - 1.0); // conversion de tension a resistencia
       logR2 = log(R2);      // logaritmo de R2 necesario para ecuacion
       temperatura = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));   // ecuacion S-H
       temperatura = temperatura - 273.15;   // Kelvin a Centigrados (Celsius)
       return temperatura;  
}  
      
float Leer_Ph(){
    float Offset=0.00; //deviation compensate
    unsigned long int avgValue; //Store the average value of the sensor feedback
    int buf[10]; //buffer for read analog
    for(int i=0;i<10;i++){ //Get 10 sample value from the sensor for smooth the value
        buf[i]=analogRead(SensorPin);
        delay(10);
    }
    for(int i=0;i<9;i++){ //sort the analog from small to large
       for(int j=i+1;j<10;j++){
           if(buf[i]>buf[j]){
              int temp=buf[i];
              buf[i]=buf[j];
              buf[j]=temp;
           }
       }
    }
    avgValue=0;
    for(int i=2;i<8;i++){ //take the average value of 6 center sample
          avgValue+=buf[i];
    }
    float phValue=(float)avgValue*5.0/1024/6; //convert the analog into millivolt
    phValue=3.5*phValue+Offset; //convert the millivolt into pH value
    return phValue;
}
  
