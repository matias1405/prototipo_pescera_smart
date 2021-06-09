#include <WiFi.h>
#include <RTClib.h>
#include <EEPROM.h>
#include <SPI.h>
#include <Wire.h>     // libreria para bus I2C
#include <Adafruit_GFX.h>   // libreria para pantallas graficas
#include <Adafruit_SSD1306.h>   // libreria para controlador SSD1306


#define ANCHO 128     // reemplaza ocurrencia de ANCHO por 128
#define ALTO 64       // reemplaza ocurrencia de ALTO por 64

#define OLED_RESET 4      // necesario por la libreria pero no usado
#define EEPROM_SIZE 10

Adafruit_SSD1306 oled(ANCHO, ALTO, &Wire, OLED_RESET);  // crea objeto
RTC_DS1307 rtc;

#define sw_subir 8 //Botón Subir
#define sw_aceptar 9 //Botón Seleccionar Opción
#define sw_bajar 10 //Botón Bajar
//direcciones de memoria de la eeprom
#define eeprom_temp 0
#define eeprom_ph 1
#define eeprom_horario_1_h 2
#define eeprom_horario_1_m 3
#define Nivel 7
#define valor A0
#define SensorPin 5
#define bomba 16
#define resist 17
#define dosificador 18
#define aireador 19

int contador = 1;

//--------------¡¡¡IMPORTANTE!!!---------------------------------
//Cambiar ssid y password por los valores de la red que se usara
//---------------------------------------------------------------

const char* ssid = "ESP32-Access-Point";
const char* password = "123456789";

//---------------------------------------------------------------

void setup() {
    Serial.begin(115200);
    EEPROM.begin(EEPROM_SIZE);
    
    WiFi.begin(ssid, password);
    Serial.println("Connecting");
    while(WiFi.status() != WL_CONNECTED) { 
        delay(500);
        Serial.print(".");
    }
    Wire.begin();         // inicializa bus I2C

    if(!oled.begin(SSD1306_SWITCHCAPVCC, 0x3D)) { // Address 0x3D for 128x64
        Serial.println(F("Modulo SSD1306 no encontrada"));
        for(;;); // Don't proceed, loop forever
    }
    if(!rtc.begin()) { // Address 0x3D for 128x64
        Serial.println(F("Modulo RTC no encontrado"));
        for(;;); // Don't proceed, loop forever
    }

    pinMode(sw_subir, INPUT_PULLUP);
    pinMode(sw_aceptar, INPUT_PULLUP);
    pinMode(sw_bajar, INPUT_PULLUP);
    pinMode(Nivel,INPUT);
    pinMode(valor,INPUT);
    pinMode(SensorPin,INPUT);
    pinMode(bomba,OUTPUT);
    pinMode(aireador,OUTPUT);
    pinMode(resist,OUTPUT);
    delay(100);

    //oled.stopscroll();
    oled.clearDisplay();
    oled.drawBitmap(0, 0, logo_Eg, 128, 64, SSD1306_WHITE);
    oled.display();
    delay(1000);
//    for(int k = 0; k < 10; k++){
//        if(digitalRead(aceptar)==0){
//            delay(700); //cambiar
//            config_wifi();
//        }
//        delay(100);
//    }
    menu_principal(); //funcion A
}

void loop() {
  // ** //
}
/*
====== Menu Principal =======

*/
void menu_principal(){
    contador=2;
    while(true){
        contador = contadores(contador, 2, 1, 1); //funciona con logica inversa a la numeracion del menu
                                                  //variable: contador, lim_sup: 3, lim_inf: 1, variacion del contador con cada pulso: 1
        oled.clearDisplay();
        oled.drawRect(1,1,127,63,WHITE);
        oled.setTextSize(1);             // Normal 1:1 pixel scale
        oled.setTextColor(SSD1306_WHITE);        // Draw white text
        oled.setCursor(20,5);             // Columna, Fila
        oled.println(F("MENU PRINCIPAL"));
        delay(5);
        oled.drawCircle(4,23,1,WHITE);
        oled.setCursor(7,20);
        seleccion(contador,2);
        oled.println(F("Configuraciones"));
        delay(5);
        oled.drawCircle(4,33,1,WHITE);
        oled.setCursor(7,30);
        seleccion(contador,1);
        oled.println(F("Ver Estado"));
        delay(5);
        oled.display();
        if(contador == 2 && digitalRead(sw_aceptar) == 0){
            delay(700); //cambiar
            configuraciones();
        }
         if(contador == 1 && digitalRead(sw_aceptar) == 0){
            delay(700); //cambiar
            ver_estado();
        }
        delay(100);
    }
}

/*
======  Seleccion =======
Esta funcion es llamada por varias funciones de pantalla donde se muestre un menu.
Se utiliza para saber cual es la opcion actual en donde se encuentra el usuario,
destacandola cambiando el color de fondo y el color de texto.
*/
void seleccion(int cont,int cont_comparacion){
    if(cont == cont_comparacion)(oled.setTextColor(SSD1306_BLACK, SSD1306_WHITE));
    else(oled.setTextColor(SSD1306_WHITE));
}

int contadores(int n, int lim_sup, int lim_inf, int variacion){
    if(digitalRead(sw_bajar) == 0){
        if(n < (lim_inf + variacion))(n = lim_sup);
        else(n = n - variacion);
    }
    if(digitalRead(sw_subir) == 0){
        if(n > (lim_sup - variacion))(n = lim_inf);
        else(n = n + variacion);
    }
    return n;
}
