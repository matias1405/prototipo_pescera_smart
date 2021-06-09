void configuraciones(){
    contador=3;
    while(true){
        contador = contadores(contador, 3, 1, 1); //funciona con logica inversa a la numeracion del menu
                                                  //variable: contador, lim_sup: 3, lim_inf: 1, variacion del contador con cada pulso: 1
        oled.clearDisplay();
        oled.drawRect(1,1,127,63,WHITE);
        oled.setTextSize(1);             // Normal 1:1 pixel scale
        oled.setTextColor(SSD1306_WHITE);        // Draw white text
        oled.setCursor(20,5);             // Columna, Fila
        oled.println(F("CONFIGURAIONES"));
        delay(5);
        oled.drawCircle(4,23,1,WHITE);
        oled.setCursor(7,20);
        seleccion(contador,3);
        oled.println(F("Temperatura"));
        delay(5);
        oled.drawCircle(4,33,1,WHITE);
        oled.setCursor(7,30);
        seleccion(contador,2);
        oled.println(F("NIvel de PH"));
        delay(5);
        oled.drawCircle(4,43,1,WHITE);
        oled.setCursor(7,40);
        seleccion(contador,1);
        oled.println(F("Horarios del"));
        delay(5);
        oled.setCursor(7,50);
        seleccion(contador,1);
        oled.println(F("Aireador"));
        delay(5);
        oled.display();
        if(contador == 3 && digitalRead(sw_aceptar) == 0){
            delay(700); //cambiar
            conf_temp();
        }
        if(contador == 2 && digitalRead(sw_aceptar) == 0){
            delay(700); //cambiar
            conf_ph();
        }
        if(contador == 1 && digitalRead(sw_aceptar) == 0){
            delay(700); //cambiar
            conf_horarios();
        }
        delay(100);
    }
}


void conf_temp(){
    contador = EEPROM.read(eeprom_temp);
    while(true){
        contador = contadores(contador, 40, 0, 1);       
        oled.clearDisplay();
        oled.drawRect(1,1,127,63,WHITE);
        oled.setCursor(2,5);
        oled.setTextColor(SSD1306_WHITE); 
        oled.println(F("Elija la temperatura:"));
        delay(5);
        oled.setCursor(45,25); 
        oled.println(contador);
        delay(5);
        oled.drawCircle(65,25,1,WHITE);
        oled.setCursor(68,25); 
        oled.println(F("C"));
        delay(5);
        oled.setCursor(40,50);
        oled.setTextColor(SSD1306_BLACK, SSD1306_WHITE); 
        oled.println(F("Aceptar"));
        delay(5);
        oled.display();
        if(digitalRead(sw_aceptar) == 0){
            EEPROM.write(eeprom_temp,contador);
            EEPROM.commit();
            delay(4);
            configuraciones();       
        }
        delay(100);
    }
}

void conf_ph(){
    contador = EEPROM.read(eeprom_ph);
    float contador_f;
    while(true){
        contador = contadores(contador, 140, 0, 1);
        contador_f = contador/10;       
        oled.clearDisplay();
        oled.drawRect(1,1,127,63,WHITE);
        oled.setCursor(2,5);
        oled.setTextColor(SSD1306_WHITE); 
        oled.println(F("Elija el nivel de ph:"));
        delay(5);
        oled.setCursor(45,25); 
        oled.println(contador_f);
        delay(5);
        oled.setCursor(40,50);
        oled.setTextColor(SSD1306_BLACK, SSD1306_WHITE); 
        oled.println(F("Aceptar"));
        delay(5);
        oled.display();
        if(digitalRead(sw_aceptar) == 0){
            EEPROM.write(eeprom_ph,contador);
            EEPROM.commit();
            delay(700);
            configuraciones();       
        }
        delay(100);
    }
}


void conf_horarios(){
    contador=4;
    while(true){
        contador = contadores(contador, 4, 0, 1); //funciona con logica inversa a la numeracion del menu
                                                  //variable: contador, lim_sup: 3, lim_inf: 1, variacion del contador con cada pulso: 1
        oled.clearDisplay();
        oled.drawRect(1,1,127,63,WHITE);
        oled.setTextSize(1);             // Normal 1:1 pixel scale
        oled.drawCircle(4,13,1,WHITE);
        oled.setCursor(7,10);
        seleccion(contador,4);
        oled.println(F("ENCENDIDO 1"));
        delay(5);
        oled.drawCircle(4,23,1,WHITE);
        oled.setCursor(7,20);
        seleccion(contador,3);
        oled.println(F("APAGADO 1"));
        delay(5);
        oled.drawCircle(4,33,1,WHITE);
        oled.setCursor(7,30);
        seleccion(contador,2);
        oled.println(F("ENCENDIDO 2"));
        delay(5);
        oled.drawCircle(4,43,1,WHITE);
        oled.setCursor(7,40);
        seleccion(contador,1);
        oled.println(F("APAGADO 2"));
        delay(5);
        oled.drawCircle(4,53,1,WHITE);
        oled.setCursor(7,50);
        seleccion(contador,0);
        oled.println(F("Volver"));
        delay(5);
        oled.display();
        if(contador == 4 && digitalRead(sw_aceptar) == 0){
            delay(700); //cambiar
            introducir_horarios(0);
        }
        if(contador == 3 && digitalRead(sw_aceptar) == 0){
            delay(700); //cambiar
            introducir_horarios(1);
        }
        if(contador == 2 && digitalRead(sw_aceptar) == 0){
            delay(700); //cambiar
            introducir_horarios(2);
        }
        if(contador == 1 && digitalRead(sw_aceptar) == 0){
            delay(700); //cambiar
            introducir_horarios(3);
        }
        if(contador == 0 && digitalRead(sw_aceptar) == 0){
            delay(700); //cambiar
            configuraciones();
        }
        delay(100);
    }   
}

void introducir_horarios(int k){   
    int addr = eeprom_horario_1_h + 2*k;
    contador = EEPROM.read(addr);   
    while(true){
        contador = contadores(contador, 23, 0, 1);
        oled.clearDisplay();
        oled.drawRect(1,1,127,63,WHITE);
        oled.setTextColor(SSD1306_WHITE);
        if(k == 0){
            oled.setCursor(15,5);
            oled.println(F("ENCENDIDO 1"));
            delay(5); 
        }
        else if(k == 1){
            oled.setCursor(15,5);
            oled.println(F("APAGADO 1"));
            delay(5); 
        }
        else if(k == 2){
            oled.setCursor(15,5);
            oled.println(F("ENCENDIDO 2"));
            delay(5); 
        }
        else{
            oled.setCursor(15,5);
            oled.println(F("APAGADO 2"));
            delay(5); 
        }
        oled.setCursor(8,15);
        oled.println(F("Introduzca la hora:"));
        delay(5);
        oled.setCursor(55,35); 
        oled.println(contador);
        delay(5);
        oled.setCursor(40,50);
        oled.setTextColor(SSD1306_BLACK, SSD1306_WHITE); 
        oled.println(F("ACEPTAR"));
        delay(5);
        oled.display();
        if(digitalRead(sw_aceptar) == 0){
            EEPROM.write(addr,contador);
            EEPROM.commit();
            delay(4);
            addr = eeprom_horario_1_m + 2*k;
            contador = EEPROM.read(addr);
            while(true){
                contador = contadores(contador, 59, 0, 1);
                oled.clearDisplay();
                oled.drawRect(1,1,127,63,WHITE);
                oled.setTextColor(SSD1306_WHITE);
                if(k == 0){
                    oled.setCursor(15,5);
                    oled.println(F("ENCENDIDO 1"));
                    delay(5); 
                }
                else if(k == 1){
                    oled.setCursor(15,5);
                    oled.println(F("APAGAD0 1"));
                    delay(5); 
                }
                else if(k == 3){
                    oled.setCursor(15,5);
                    oled.println(F("ENCENDIDO 2"));
                    delay(5); 
                }
                else{
                    oled.setCursor(15,5);
                    oled.println(F("APAGAD0 2"));
                    delay(5); 
                }
                oled.setCursor(8,15);
                oled.println(F("Introduzca los"));
                delay(5);
                oled.setCursor(2,25);
                oled.println(F("minutos:"));
                delay(5);
                oled.setCursor(55,35); 
                oled.println(contador);
                delay(5);
                oled.setCursor(40,50);
                oled.setTextColor(SSD1306_BLACK, SSD1306_WHITE); 
                oled.println(F("ACEPTAR"));
                delay(5);
                oled.display();
               if(digitalRead(sw_aceptar) == 0){
                    EEPROM.write(addr, contador);
                    EEPROM.commit();
                    delay(700);
                    conf_horarios();
                }
                delay(100);
            }            
        }
        delay(100);
    }    
} 
