/*
#       _\|/_   A ver..., ¿que tenemos por aqui?
#       (O-O)        
# ---oOO-(_)-OOo---------------------------------
 
 
#################################################
# ********************************************* #
# *       ANIMACION BATERIA CARGANDO          * #
# *      Autor: Eulogio López Cayuela         * #
# *                                           * #
# *    Versión 1.0    Fecha: 04/09/2015       * #
# ********************************************* #
#################################################
*/


//------------------------------------------------------
//algunas definiciones personales para mi comodidad al escribir codigo
//------------------------------------------------------
#define AND &&
#define OR ||

//------------------------------------------------------
//Otras definiciones para pines y variables
//------------------------------------------------------
#define LCD_AZUL_ADDR    0x27  // Direccion I2C de nuestro LCD color azul
#define LCD_VERDE_ADDR   0x3F  // Direccion I2C de nuestro LCD color verde

//------------------------------------------------------
//Importamos las librerias necesariasç
//------------------------------------------------------
#include <Wire.h>               //libreria para comunicaciones I2C
#include <LiquidCrystal_I2C.h>  // LiquidCrystal library

//------------------------------------------------------
// Creamos las instancia de los objetos:
//------------------------------------------------------

//Creamos el objeto 'lcd' como una instancia del tipo "LiquidCrystal_I2C"
//                        addr,     en,rw,rs,d4,d5,d6,d7,bl, blpol
LiquidCrystal_I2C lcd(LCD_AZUL_ADDR, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 

//------------------------------------------------------
//DECLARACION DE CONSTANTES GLOBALES
//------------------------------------------------------

// defino el nuevo caracter

//bateria estrecha
byte bateria_0[6][8] = {{B0110, B1111, B1001, B1001, B1001, B1001, B1001, B1111},
                        {B0110, B1111, B1001, B1001, B1001, B1001, B1111, B1111},
                        {B0110, B1111, B1001, B1001, B1001, B1111, B1111, B1111},
                        {B0110, B1111, B1001, B1001, B1111, B1111, B1111, B1111},
                        {B0110, B1111, B1001, B1111, B1111, B1111, B1111, B1111},
                        {B0110, B1111, B1111, B1111, B1111, B1111, B1111, B1111}};

//bateria algo mas ancha
byte bateria_1[6][8] = {{B01110, B11111, B10001, B10001, B10001, B10001, B10001, B11111},
                        {B01110, B11111, B10001, B10001, B10001, B10001, B11111, B11111},
                        {B01110, B11111, B10001, B10001, B10001, B11111, B11111, B11111},
                        {B01110, B11111, B10001, B10001, B11111, B11111, B11111, B11111},
                        {B01110, B11111, B10001, B11111, B11111, B11111, B11111, B11111},
                        {B01110, B11111, B11111, B11111, B11111, B11111, B11111, B11111}};


//*******************************************************
//         FUNCION DE CONFIGURACION
//*******************************************************
void setup()  
{
  randomSeed(analogRead(0));
  Serial.begin(9600);  //Se inicia el puerto serie para depuracion
  lcd.begin (16,2);    //Inicializar lcd 
  
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  
  
  //Mensaje inicial para demostrar que el LCD esta bien conectado y comunicado
  lcd.clear();         //Reset del display 
  lcd.backlight();     //Activamos la retroiluminacion
 
  lcd.setCursor(0, 0);
  Serial.println("SISTEMA EN ESPERA...\n");   // ---> DEBUB
  delay(1500);
  lcd.clear();
}


//*******************************************************
//   BUCLE PRINCIPAL DEL PROGRAMA (Sistema vegetativo)
//*******************************************************


void loop()
{
  /*
   * enviamos tres parametros posicion del caracter (o-15)
   * linea donde escribir (0 o 1)
   * Tipo de bateria a mostrar (o escrecha, 1 algo masancha)
   */
   
  bateriaCargando(15, 0, 1);  // (byte pos, byte linea, byte tipo)
  delay(700);                 // pausa antes de reiniciar la animacion
}


//*******************************************************
//   Funcion para crear la animacion de la bateria
//*******************************************************

void bateriaCargando(byte pos, byte linea, byte tipo)
{
 /*
  * Recibe tres parametros de tipo byte
  * -pos:   posicion del caracter (o-15)
  * -linea: renglon donde escribir (0 superior,  1 inferior)
  * .tipo:  Tipo de bateria a mostrar (o escrecha, 1 algo masancha)
  */
  for (int i=0; i<=5; i++){
    if (tipo == 0){
      lcd.createChar(3, bateria_0[i]);    //creamos el caracter con la informacion de la lista
      lcd.setCursor(pos, linea);          //posicion donde mostras la animacion
      lcd.write(3);
    }
    
    if (tipo == 1){
      lcd.createChar(3, bateria_1[i]);    //creamos el caracter con la informacion de la lista
      lcd.setCursor(pos, linea);          //posicion donde mostras la animacion
      lcd.write(3);
    }
    delay (300);                          //pausa para dar realismo
  }
}



//*******************************************************
//                    FIN DE PROGRAMA
//*******************************************************

