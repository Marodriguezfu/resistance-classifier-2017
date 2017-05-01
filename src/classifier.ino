#include <Stepper.h>
#include <math.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd (0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

Stepper rodillo (32, 30, 32, 31, 33);
Stepper riel (32, 36, 38, 37, 39);

unsigned int pin1 = A0, pin2 = A1, pin3 = A2, raw1 = 0, raw10 = 0, raw100 = 0, cont = 0,  auR, cajaBase = 1, aux = 1;
double Vin = 4.98, Vout = 0, fija1 = 1019, fija2 = 10040, fija3 = 98000, auxR;

double resistor[13] = {0.1, 0.12, 0.15, 0.18, 0.22, 0.27, 0.33, 0.39, 0.47, 0.51, 0.56, 0.68, 0.82};
double valores[13][2];

boolean enRango, clasificable, adentro;

double inRange(int rango) {

  double R;

  switch (rango) {

    case 1:
      Vout = Vin - ((raw1 * Vin) / 1023);
      R = (Vout * fija1) / (Vin - Vout);
      Serial.println("\nPin 1");
      break;
    case 2:
      Vout = Vin - ((raw10 * Vin) / 1023);
      R = (Vout * fija2) / (Vin - Vout);
      Serial.println("\nPin 2");
      break;
    case 3:
      Vout = Vin - ((raw100 * Vin) / 1023);
      R = (Vout * fija3) / (Vin - Vout);
      Serial.println("\nPin 3");
      break;

  }

  Serial.print("Raw x Vin: ");
  Serial.println(1023 * (Vin - Vout));
  Serial.print("Vout: ");
  Serial.println(Vout);
  Serial.print("Resis: ");
  Serial.println(R);

  delay(1000);
  return R;

}

void girarRodillo(int grados) {

  //Lo ideal es que grados sea un múltiplo de 45, pero con cualquier número debería funcionar igual.

  Serial.print("Grados: ");
  Serial.println(grados);
  int giro = (int)((grados * 512) / 45); //2048/360
  Serial.print("Giro: ");
  Serial.println(giro);
  rodillo.step(giro);
}

void girarRiel(int cajaIni, int cajaFin) {

  int giro;

  if (cajaIni > cajaFin ) {
    if (cajaIni - cajaFin <= 8 ) {
      cajaBase = cajaFin;
      giro = (-1) * (cajaIni - cajaFin);
    } else {
      cajaBase = cajaFin;
      giro = (16 - (cajaIni - cajaFin));
    }
  } else if (cajaIni < cajaFin) {
    if (cajaFin - cajaIni <= 8) {
      cajaBase = cajaFin;
      giro = (cajaFin - cajaIni);
    } else {
      cajaBase = cajaFin;
      giro = ((-1) * (16 - (cajaFin - cajaIni)));
    }
  } else {
    cajaBase = cajaFin;
    giro = 0;
  }

  riel.step(giro * 128);
}

void rangos (int aux) {

  Serial.print("aux: ");
  Serial.println(aux);

  for (int x = 0; x < 13; x++) {
    for (int y = 0; y < 2 ; y++) {
      if (y == 0)
        valores[x][y] = (resistor[x] * aux - ((resistor[x] * aux) * 0.05));
      else
        valores[x][y] = (resistor[x] * aux + ((resistor[x] * aux) * 0.05));
    }
  }

  for (int x = 0; x < 13; x++) {
    for (int y = 0; y < 2 ; y++) {
      if (y == 0) {
        Serial.print("valores[");
        Serial.print(x);
        Serial.print("][");
        Serial.print(y);
        Serial.print("]: ");
        Serial.println(valores[x][y]);
      } else {
        Serial.print("valores[");
        Serial.print(x);
        Serial.print("][");
        Serial.print(y);
        Serial.print("]: ");
        Serial.println(valores[x][y]);
      }
    }
  }
}

boolean imprimidor(int mult, int pin) {

  boolean dentroRango = false;
  double Resis = 0;

  for (int x = 0; x < 13; x++) {
    if (auxR >= valores[x][0] && auxR <= valores[x][1]) {
      Serial.print("El valor de la resistencia es: ");
      Resis = resistor[x] * mult;
      Serial.println(Resis);

      girarRiel(cajaBase, x);

      delay(500);
      pin = 4 - pin;
      girarRodillo(pin * 45);
      dentroRango = true;
      break;
    }
  }
  return dentroRango;
}

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);

  lcd.clear();
  lcd.print("Iniciando...");

  rodillo.setSpeed(800);
  girarRodillo(360);

  riel.setSpeed(1200);
}

void loop() {
  double caster = 0;

  lcd.clear();
  lcd.setCursor(0, 0);

  aux = 1;
  auxR = 0;
  cont = 0;
  enRango = false;
  clasificable = false;
  adentro = false;

  //------------------pin1-------------------------

  raw1 = analogRead(pin1);

  girarRodillo(45);

  auxR = inRange(1);

  caster = auxR;
  auR = 0;
  
  Serial.print("auR: ");
  Serial.println(auR);
  if (auxR >= 100.00 && auxR <= 5600.00) {

    while (caster / 10 >= 1 ) {
      caster /= 10;
      cont++;
    }

    if (auxR >= 9.5 * pow(10, cont)) {
      cont++;
    }
    cont++;
    enRango = true;

    Serial.print("Exponente: ");
    Serial.println(cont);
    aux = pow(10, cont);

    adentro = true;
    rangos(aux);

    clasificable = imprimidor(aux, 1);
  }
  //------------------pin2---------------------------


  if (!adentro) {
    girarRodillo(45);

    raw10 = analogRead(pin2);
    auxR = inRange(2);
    //auR = (int)auxR;
    caster = auxR;
    auR = 0;

    Serial.print("auR: ");
    Serial.println(auR);

    if (auxR > 5600.00 && auxR <= 82000.00) {
      while (caster / 10 >= 1) {
        caster /= 10;
        Serial.print("caster:");
        Serial.println(caster);
        cont++;
      }

      Serial.print("auR: ");
      Serial.println(auR);

      if (auxR >= 9.5 * pow(10, cont)) {
        cont++;
      }
      cont++;
      enRango = true;

      Serial.print("Exponente: ");
      Serial.println(cont);
      
      //aux = pow(10, cont);
      int contador = cont;
      while(contador - 1  > 0){
        
        aux *= 10;
        contador--;
        Serial.print("aux: ");
        Serial.println(aux);
        Serial.print("contador: ");
        Serial.println(contador);
        
      }
      Serial.print("FUERA DEL WHILE");

      
      adentro = true;
      rangos(aux);
      clasificable = imprimidor(aux, 2);
    }
  }
  //------------------pin3---------------------------

  if (!adentro) {
    girarRodillo(45);

    raw100 = analogRead(pin3);

    auxR = inRange(3);
    //auR = (int) auxR;
    
    caster = auxR;
    auR = 0;
    Serial.print("auR: ");
    Serial.println(auR);

    if (auxR > 82000.00 && auxR <= 820000.00) {
      while (caster / 10 >= 1) {
        caster /= 10;
        cont++;
      }

      if (auxR >= 9.5 * pow(10, cont)) {
        cont++;
      }
      enRango = true;
      cont++;
      Serial.print("Exponente: ");
      Serial.println(cont);
      aux = pow(10, cont);

      adentro = true;
      rangos(aux);
      clasificable = imprimidor(aux, 3);
    }
  }

  if (enRango && clasificable) {

    Serial.print("El valor de la resistencia es: ");
    Serial.println(auxR);

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Res:    ");
    lcd.print(auxR);

    Serial.print("La resistencia fue ubicada en la caja número: ");
    Serial.println(cajaBase);

    lcd.setCursor(0, 1);
    lcd.print("A caja: ");
    lcd.print(cajaBase);

  } else if (enRango && !clasificable) {

    Serial.print("\n-La resistencia es inclasificable, pero está en el rango de: ");
    Serial.print(valores[0][0]);
    Serial.print(" a ");
    Serial.print(valores[12][1]);
    Serial.print("-\n");

    lcd.clear();
    lcd.setCursor(0, 0);

    lcd.print("Inclasificable");
    lcd.setCursor(0, 1);
    lcd.print("Rango: ");
    lcd.print(valores[0][0]);
    lcd.setCursor(10, 1);
    lcd.print(valores[12][1]);

  } else if (!enRango) {

    Serial.println("\n\t-La resistencia está fuera de todo rango-\n");

  }
}

