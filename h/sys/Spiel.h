/*
 * Spiel.h
 *
 *  Created on: 19.04.2014
 *      Author: K
 */

#ifndef SPIEL_H_
#define SPIEL_H_
#include <string>
#include "../h/sys/Konstanten.h"
#include "../h/sys/Spielfeld.h"
#include "../h/sys/Historie.h"
#include <iostream>

class Spiel {

public:
    Spiel(unsigned short zeilen=Y, unsigned short spalten=X);
    virtual ~Spiel();

    void starteSpiel(string nameSpieler1, string nameSpieler2);
    virtual int naechsterZug(Spieler* spieler, unsigned short spalte);
    void aufgeben();
    HisEintrag* getLetztenHisEintrag();
    void erstelleNeuenHisEintrag(Spieler* spieler,
                                 unsigned short zeile,
                                 unsigned short spalte,
                                 unsigned short runde);


    int getAktuelleZeile(int spalte);
    int getId() const
    {
        return id;
    }

    void setId(int value)
    {
        id = value;
    }

    Spieler* getAktuellerSpieler() const {
        return aktuellerSpieler;
    }
    Spieler* getVerherigerSpieler() const {
        return vorherigerSpieler;
    }

    Spieler* getSp1() const{
        return sp1;
    }

    void setSp1(Spieler* value){
        sp1 = value;
    }

    Spieler* getSp2() const{
        return sp2;
    }

    void setSp2(Spieler* value){
        sp2 = value;
    }

    unsigned short getRunde() const{
        return runde;
    }

    void setRunde(unsigned short value){
        runde = value;
    }

    Historie *getHistorie() const
    {
        return historie;
    }

    void setHistorie(Historie *value)
    {
        historie = value;
    }

    friend ostream& operator<<(ostream& out, Spiel& sp);
    string toString() const;



protected:
    int id;
    Spielfeld *spielfeld;
    Historie *historie;
    Spieler *sp1;
    Spieler *sp2;
    Spieler *aktuellerSpieler;
    Spieler *vorherigerSpieler;
    unsigned short runde;
    void wechselSpieler();
};

#endif /* SPIEL_H_ */
