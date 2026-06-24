// KÖNYVTÁRAK
#include <Arduino.h>
#include <DHT.h>
#include <Servo.h>

// DEFINÍCIÓK
#define homeroBelsoPin A4
#define homeroBelsoTipus DHT11
#define homeroKulsoPin A5
#define homeroKulsoTipus DHT11

// DHT
DHT belsoHomero(homeroBelsoPin, homeroBelsoTipus);
DHT kulsoHomero(homeroKulsoPin, homeroKulsoTipus);

// SZERVÓ
Servo ablak;

// ESZKÖZÖK
const int vizszintSzenzor = A2;
const int vilagitas = 12;
const int szivattyu = 7;
const int wcGomb = A3;
const int mozgaserzekelo = 13;
const int klima = 4;
const int kandallo = 2;
const int fusterzekelo = 6;
const int fenyerzekelo = A1;
const int hangszoro = 5;
const int paraelszivoRele = 11;
const int demoMod = A0;
const int laser1 = 8;
const int laser2 = 9;
const int laser3 = 10;

// VÁLTOZÓK
// hőmérők
int homerokStep = 1;
unsigned long homerokElozoMillik = 0;
unsigned long homerokJelenlegiMillik = 0;
const long homerokIntervallum = 2000;

// hőmérséklet kezelés
int kezelesStep = 1;
int rendszerMod = 0;
boolean kezelesIf1Side = false; // kandalló
boolean kezelesIf2Side = false; // klíma
boolean kezelesIf3Side = false; // ablak

// WC gomb
int wcStep = 1;
boolean wcSide = false; // false = sideB

// vízszint
int vizszintStep = 1;
boolean vizszintSide = false; // false = sideB

// füstérzékelő
int fusterzekeloStep = 1;
boolean fusterzekeloSide = false; // false = sideB

// mozgásérzékelő
int mozgaserzekeloStep = 1;
boolean mozgaserzekeloSide = false; // false = sideB

// fényérzékelő
int fenyerzekeloStep = 1;
boolean fenyerzekeloSide = false; // false = sideB

// szivattyú
int szivattyuStep = 1;
boolean szivattyuSide = false; // false = sideB

// kandalló
int kandalloStep = 1;
boolean kandalloSide = false; // false = sideB

// ablak
int ablakStep = 1;
int ablakFor1Count = 1;
int ablakFor2Count = 1;
int poz = 0;
boolean ablakNyitva = false; // false = becsukva
boolean ablakSide = false; // false = sideB

// klíma
int klimaStep = 1;
boolean klimaSide = false; // false = sideB

// világítás
int vilagitasStep = 1;
boolean vilagitasSide = false; // false = sideB

// páraelszívó
int paraelszivoStep = 1;
boolean paraelszivoSide = false; // false = sideB

// laser
int laserStep = 1;
boolean laserSide1 = false; // false = sideB
boolean laserSide2 = false; // false = sideB
boolean laserSide3 = false; // false = sideB

// serial
unsigned long serialElozoMillik = 0;
unsigned long serialJelenlegiMillik = 0;
const long serialIntervallum = 3000;

// hangszóró riasztás
int hangszoroStep = 1;
unsigned long hangszoroElozoMillik = 0;
unsigned long hangszoroJelenlegiMillik = 0;
const long hangszoroIntervallum = 1000;

// demo mód
int demoModStep = 1;
int demoModAktivStep = 1; // 3 a maximum
boolean demoModSide = false; // false = sideB
unsigned long demoModElozoMillik = 0;
unsigned long demoModJelenlegiMillik = 0;
const long demoModIntervallum = 4000;

unsigned long mainElozoMillik = 0;
unsigned long mainJelenlegiMillik = 0;

float belsoHomerseklet = 0;
float belsoParatartalom = 0;
float kulsoHomerseklet = 0;
float kulsoParatartalom = 0;

boolean elegViz = false;
boolean kevesFeny = false;
boolean mozgas = false;
boolean wcGombLenyomva = false;
boolean vanFust = false;
boolean demoModAktiv = false;
boolean beriaszt = false;

const uint16_t dallam1[] = {
    392, 440, 494, 494,
    440, 440, 494, 392, 440,

    494, 494, 440, 440, 494, 
    392, 294,

    392, 440, 494, 494,
    440, 440, 494, 392, 370, 330,

    440, 440, 494, 392, 370,
    330, 330
};

const int idohossz1[] = {
    4,4,4,4,
    4,8,8,4,4,

    8,2,4,8,8,
    2,2,

    4,4,8,2,
    4,8,8,8,8,4,

    8,4,8,4,4,
    2,2
};

const uint16_t dallam_rick[] = {
  349, 392, 466, 392, 587, 587, 523,       // Never gonna give you up,
  349, 392, 466, 392, 523, 523, 466, 440,  // Never gonna let you down,
  349, 392, 466, 392, 466, 523, 440, 392,  // Never gonna run around and
  349, 440, 466, 392                       // desert you.
};

const int idohossz_rick[] = {
  8, 8, 8, 8, 4, 4, 2,
  8, 8, 8, 8, 4, 4, 8, 4,
  8, 8, 8, 8, 4, 4, 4, 8, 4,
  4, 4, 4, 2
};

// FÜGGVÉNYEK
void zeneLejatszas(const uint16_t dallam[], const int idohossz[], int size, int tempoAlap, float huzas) {
    for (int i = 0; i < size; i++) {
        int hangHossz = tempoAlap / idohossz[i];
        tone(hangszoro, dallam[i], hangHossz);
        delay((int)(hangHossz * huzas));
        noTone(hangszoro);
    }
}

void homerokMain(){
    float temp;

    switch(homerokStep){
        case 1:
            temp = belsoHomero.readTemperature();
            if(!isnan(temp)) belsoHomerseklet = temp;

            break;
        case 2:
            temp = belsoHomero.readHumidity();
            if(!isnan(temp)) belsoParatartalom = temp;

            break;
        case 3:
            temp = kulsoHomero.readTemperature();
            if(!isnan(temp)) kulsoHomerseklet = temp;

            break;
        case 4:
            temp = kulsoHomero.readHumidity();
            if(!isnan(temp)) kulsoParatartalom = temp;

            break;
    }

    homerokStep++;
}

void homersekletKezelesMain(){
    switch(kezelesStep){
        case 1:
            if(vanFust){
                kezelesIf1Side = false;
                kezelesIf2Side = false;
                kezelesIf3Side = false;
            }else if(belsoHomerseklet < 22){
                kezelesIf1Side = true;
                kezelesIf2Side = false;
                kezelesIf3Side = false;
            }else if(belsoHomerseklet >= 26){
                kezelesIf1Side = false;
                kezelesIf2Side = true;
                kezelesIf3Side = false;
            }else if(belsoHomerseklet > 24 && kulsoHomerseklet < belsoHomerseklet){
                kezelesIf1Side = false;
                kezelesIf2Side = false;
                kezelesIf3Side = true;
            }else{
                kezelesIf1Side = false;
                kezelesIf2Side = false;
                kezelesIf3Side = false;
            }
          
            break;
        case 2:
            if(kezelesIf1Side) rendszerMod = 1; // kandalló
            else if(kezelesIf2Side) rendszerMod = 3; // klíma
            else if(kezelesIf3Side) rendszerMod = 2; // ablak
            else rendszerMod = 0;
            
            break;
    }

    kezelesStep++;
}

void wcMain(){
    switch(wcStep){
        case 1:
            wcSide = digitalRead(wcGomb) == LOW;
            break;
        case 2:
            wcGombLenyomva = wcSide;
            break;
    }

    wcStep++;
}

void vizszintMain(){
    switch(vizszintStep){
        case 1:
            vizszintSide = digitalRead(vizszintSzenzor);
            break;
        case 2:
            elegViz = vizszintSide;
            break;
    }

    vizszintStep++;
}

void fusterzekeloMain(){
    switch(fusterzekeloStep){
        case 1:
            fusterzekeloSide = digitalRead(fusterzekelo) == LOW;
            break;
        case 2:
            vanFust = fusterzekeloSide;
            break;
    }

    fusterzekeloStep++;
}

void mozgaserzekeloMain(){
    switch(mozgaserzekeloStep){
        case 1:
            mozgaserzekeloSide = digitalRead(mozgaserzekelo) == HIGH;
            break;
        case 2:
            mozgas = mozgaserzekeloSide;
            break;
    }

    mozgaserzekeloStep++;
}

void fenyerzekeloMain(){
    switch(fenyerzekeloStep){
        case 1:
            fenyerzekeloSide = digitalRead(fenyerzekelo);
            break;
        case 2:
            kevesFeny = fenyerzekeloSide;
            break;
    }

    fenyerzekeloStep++;
}

void szivattyuMain(){
    switch(szivattyuStep){
        case 1:
            szivattyuSide = elegViz && wcGombLenyomva;
            break;
        case 2:
            digitalWrite(szivattyu, szivattyuSide ? LOW : HIGH);
            break;
    }

    szivattyuStep++;
}

void kandalloMain(){
    switch(kandalloStep){
        case 1:
            kandalloSide = rendszerMod == 1;
            break;
        case 2:
            digitalWrite(kandallo, kandalloSide ? HIGH : LOW);
            break;
    }

    kandalloStep++;
}

void ablakMain(){
    switch(ablakStep){
        case 1:
            if(rendszerMod == 2 && !ablakNyitva){
                ablakSide = true;
            }else if(rendszerMod != 2 && ablakNyitva){
                ablakSide = false;
            }else{
                ablakStep--;
            }
          
            break;
        case 2:
            if(ablakSide){
                if(ablakFor1Count <= 12){
                    poz += 7;
                    ablakFor1Count++;
                    ablakStep--;
                }else{
                    ablakNyitva = true;
                    ablakFor1Count = 1;
                }
                ablak.write(poz);
            }else{
                if(ablakFor2Count <= 12){
                    poz -= 7;
                    ablakFor2Count++;
                    ablakStep--;
                }else{
                    ablakNyitva = false;
                    ablakFor2Count = 1;
                }
                ablak.write(poz);
            }
          
            break;
    }

    ablakStep++;
}

void klimaMain(){
    switch(klimaStep){
        case 1:
            klimaSide = rendszerMod == 3;
            break;
        case 2:
            digitalWrite(klima, klimaSide ? LOW : HIGH);
            break;
    }

    klimaStep++;
}

void vilagitasMain(){
    switch(vilagitasStep){
        case 1:
            vilagitasSide = kevesFeny && mozgas;
            break;
        case 2:
            digitalWrite(vilagitas, vilagitasSide ? HIGH : LOW);
            break;
    }

    vilagitasStep++;
}

void paraelszivoMain(){
    switch(paraelszivoStep){
        case 1:
            paraelszivoSide = belsoParatartalom > 30;
            break;
        case 2:
            digitalWrite(paraelszivoRele, paraelszivoSide ? LOW : HIGH);
            break;
    }

    paraelszivoStep++;
}

void laserMain(){
    switch(laserStep){
        case 1:
            laserSide1 = digitalRead(laser1) == HIGH;
            break;
        case 2:
            if(!beriaszt) beriaszt = laserSide1;
            break;
        case 3:
            laserSide2 = digitalRead(laser2) == HIGH;
            break;
        case 4:
            if(!beriaszt) beriaszt = laserSide2;
            break;
        case 5:
            laserSide3 = digitalRead(laser3) == HIGH;
            break;
        case 6:
            if(!beriaszt) beriaszt = laserSide3;
            break;
    }

    laserStep++;
}

void serialMain(){
    Serial.println("a");
    Serial.println(belsoHomerseklet);
    Serial.println(belsoParatartalom);
    Serial.println(kulsoHomerseklet);
    Serial.println(kulsoParatartalom);
    Serial.println(vanFust);
    Serial.println(beriaszt);
}

void demoModMain(){
    switch(demoModStep){
        case 1:
            demoModSide = digitalRead(demoMod) == HIGH;
            break;
        case 2:
            demoModAktiv = demoModSide;
            break;
    }

    demoModStep++;
}

void riasztasMain(){
    rendszerMod = 1;

    belsoHomerseklet = 0;
    belsoParatartalom = 0;
    kulsoHomerseklet = 0;
    kulsoParatartalom = 0;

    elegViz = false;
    kevesFeny = false;
    mozgas = false;
    wcGombLenyomva = false;
    vanFust = false;
    demoModAktiv = false;
    beriaszt = true;
}

void setup(){
    // serial indítása
    Serial.begin(9600);

    // dht
    belsoHomero.begin();
    kulsoHomero.begin();

    // szervó
    ablak.attach(3);
    ablak.write(0);

    // pinMode-ok
    pinMode(klima, OUTPUT);
    pinMode(kandallo, OUTPUT);
    pinMode(vilagitas, OUTPUT);
    pinMode(szivattyu, OUTPUT);
    pinMode(hangszoro, OUTPUT);

    pinMode(vizszintSzenzor, INPUT);
    pinMode(wcGomb, INPUT_PULLUP);
    pinMode(mozgaserzekelo, INPUT);
    pinMode(fusterzekelo, INPUT);
    pinMode(fenyerzekelo, INPUT);

    // szenzorok végig futtatása
    for (int i = 0; i < 4; i++) {homerokMain();}            // 1. hőmérők
    for (int i = 0; i < 2; i++) {homersekletKezelesMain();} // 2. hőmérséklet kezelés
    for (int i = 0; i < 2; i++) {wcMain();}                 // 3. WC gomb
    for (int i = 0; i < 2; i++) {vizszintMain();}           // 4. vízszint
    for (int i = 0; i < 2; i++) {fusterzekeloMain();}       // 5. füstérzékelő
    for (int i = 0; i < 2; i++) {mozgaserzekeloMain();}     // 6. mozgásérzékelő
    for (int i = 0; i < 2; i++) {fenyerzekeloMain();}       // 7. fényérzékelő
    serialMain();                                           // 8. SERIAL

    // eszközök beállítása
    digitalWrite(klima, HIGH);
    digitalWrite(szivattyu, HIGH);
    digitalWrite(paraelszivoRele, HIGH);

    // változók
    homerokStep = 1; // hőmérők

    kezelesStep = 1; // hőmérséklet kezelés
    kezelesIf1Side = false;
    kezelesIf2Side = false;
    kezelesIf3Side = false;
    
    wcStep = 1; // WC gomb
    wcSide = false;

    vizszintStep = 1; // vízszint
    vizszintSide = false;

    fusterzekeloStep = 1; // füstérzékelő
    fusterzekeloSide = false;

    mozgaserzekeloStep = 1; // mozgásérzékelő
    mozgaserzekeloSide = false;

    fenyerzekeloStep = 1; // fényérzékelő
    fenyerzekeloSide = false;

    szivattyuStep = 1; // szivattyú
    szivattyuSide = false;

    kandalloStep = 1; // kandalló
    kandalloSide = false;

    ablakStep = 1; // ablak
    ablakFor1Count = 1;
    ablakFor2Count = 1;
    poz = 0;
    ablakNyitva = false;
    ablakSide = false;

    klimaStep = 1; // klíma
    klimaSide = false;

    vilagitasStep = 1; // világítás
    vilagitasSide = false;

    paraelszivoStep = 1; // páraelszívó
    paraelszivoSide = false;

    laserStep = 1; // laser
    laserSide1 = false;
    laserSide2 = false;
    laserSide3 = false;

    demoModStep = 1; // demo mód
    demoModAktivStep = 1;
    demoModSide = false;
    demoModAktiv = false;

    // bekapcsoló zene
    if(digitalRead(demoMod) == HIGH){
        zeneLejatszas(
            dallam_rick,
            idohossz_rick,
            sizeof(dallam_rick) / sizeof(dallam_rick[0]),
            1000,
            1.30
        );
    }else{
        zeneLejatszas(
            dallam1,
            idohossz1,
            sizeof(dallam1) / sizeof(dallam1[0]),
            1000,
            1.30
        );
    }
}

void loop(){
    mainJelenlegiMillik = millis();

    // 1. HŐMÉRŐK
    if(!beriaszt){
        if(homerokStep == 5) homerokStep = 1;

        homerokJelenlegiMillik = millis();
        if((homerokJelenlegiMillik - homerokElozoMillik >= homerokIntervallum) && homerokStep == 1){
            homerokElozoMillik = homerokJelenlegiMillik;

            homerokMain();
        }else if(homerokStep > 1){
            homerokMain();
        }
    }

    // 2. HŐMÉRSÉKLET KEZELÉS
    if(kezelesStep == 4) kezelesStep = 1;
    if(!demoModAktiv && !beriaszt) homersekletKezelesMain();

    // 3. WC GOMB
    if(wcStep == 3) wcStep = 1;
    if(!beriaszt) wcMain();

    // 4. VÍZSZINT
    if(vizszintStep == 3) vizszintStep = 1;
    if(!beriaszt) vizszintMain();

    // 5. FÜSTÉRZÉKELŐ
    if(fusterzekeloStep == 3) fusterzekeloStep = 1;
    if(!beriaszt) fusterzekeloMain();

    // 6. MOZGÁSÉRZÉKELŐ
    if(mozgaserzekeloStep == 3) mozgaserzekeloStep = 1;
    if(!beriaszt) mozgaserzekeloMain();

    // 7. FÉNYÉRZÉKELŐ
    if(fenyerzekeloStep == 3) fenyerzekeloStep = 1;
    if(!beriaszt) fenyerzekeloMain();

    // 8. SZIVATTYÚ
    if(szivattyuStep == 3) szivattyuStep = 1;
    szivattyuMain();

    // 9. KANDALLÓ
    if(kandalloStep == 3) kandalloStep = 1;
    kandalloMain();

    // 10. ABLAK
    if(ablakStep == 3) ablakStep = 1;
    ablakMain();

    // 11. KLÍMA
    if(klimaStep == 3) klimaStep = 1;
    klimaMain();

    // 12. VILÁGÍTÁS
    if(vilagitasStep == 3) vilagitasStep = 1;
    vilagitasMain();

    // 13. PÁRAELSZÍVÓ
    if(paraelszivoStep == 3) paraelszivoStep = 1;
    paraelszivoMain();

    // 14. LASER
    if(laserStep == 7) laserStep = 1;
    if(!beriaszt) laserMain();

    // 15. SERIAL
    serialJelenlegiMillik = millis();
    if((serialJelenlegiMillik - serialElozoMillik >= serialIntervallum)){
        serialElozoMillik = serialJelenlegiMillik;

        serialMain();
    }

    // 16. HANGSZÓRÓ
    if(beriaszt){
        hangszoroJelenlegiMillik = millis();

        if(hangszoroStep == 1 && (hangszoroJelenlegiMillik - hangszoroElozoMillik >= hangszoroIntervallum)){
            hangszoroElozoMillik = hangszoroJelenlegiMillik;
            hangszoroStep++;
            
            noTone(hangszoro);
            tone(hangszoro, 700);
        }else if(hangszoroStep == 2 && (hangszoroJelenlegiMillik - hangszoroElozoMillik >= hangszoroIntervallum)){
            hangszoroElozoMillik = hangszoroJelenlegiMillik;
            hangszoroStep = 1;

            noTone(hangszoro);
            tone(hangszoro, 900);
        }
    }

    // 17. DEMO MÓD
    if(!beriaszt){
        if(!demoModAktiv){
            if(demoModStep == 3) demoModStep = 1;
            demoModMain();
        }else{
            demoModJelenlegiMillik = millis();
            
            if(demoModAktivStep == 1){
                demoModAktivStep++;
                demoModElozoMillik = demoModJelenlegiMillik;
                rendszerMod = 1;
            }else if(demoModAktivStep == 2 && (demoModJelenlegiMillik - demoModElozoMillik >= demoModIntervallum)){
                demoModAktivStep++;
                demoModElozoMillik = demoModJelenlegiMillik;
                rendszerMod = 2;
            }else if(demoModAktivStep == 3 && (demoModJelenlegiMillik - demoModElozoMillik >= demoModIntervallum)){
                demoModAktivStep++;
                demoModElozoMillik = demoModJelenlegiMillik;
                rendszerMod = 3;
            }else if(demoModAktivStep == 4 && (demoModJelenlegiMillik - demoModElozoMillik >= demoModIntervallum)){
                demoModAktivStep = 1;
                demoModAktiv = false;
                rendszerMod = 0;
            }
        }
    }

    // 18. RIASZTÁS
    if(beriaszt) riasztasMain();

    // csak tesztelésre
    //Serial.println("Futasi ido: ");
    //Serial.print(mainJelenlegiMillik - mainElozoMillik);

    mainElozoMillik = mainJelenlegiMillik;
}