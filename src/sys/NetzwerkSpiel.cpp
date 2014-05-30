
#include "../h/sys/NetzwerkSpiel.h"
#include "../h/net/tcpclient.h"
#include "boost/bind.hpp"
#include "iostream"

NetzwerkSpiel::NetzwerkSpiel(unsigned short zeilen, unsigned short spalten) : Spiel(zeilen,spalten)
{
    this->tcpServer = new TcpServer();
    tcpServer->LoginRequestSignal.connect(boost::bind(&NetzwerkSpiel::on_loginRequest, this,_1));
    tcpServer->LoginReplySignal.connect(boost::bind(&NetzwerkSpiel::on_loginReply, this,_1));
    tcpServer->RemoteMoveSignal.connect(boost::bind(&NetzwerkSpiel::on_remoteMove, this,_1));
    tcpServer->start();

    this->tcpClient = new TcpClient();
}

NetzwerkSpiel::~NetzwerkSpiel()
{
    std::cout << "schließe Netzwerkspiel!!!" << endl;
    if(tcpServer->getIsActive())
        tcpServer->stop();

    delete tcpServer;
    delete tcpClient;
    std::cout << "Netzwerkspiel geschlossen!!!" << endl;

}

void NetzwerkSpiel::starteNetzwerkSpiel(string spielerName)
{
    cout << "starte Netzwerkspiel..."<< endl;
    this->sp1 = new Spieler(spielerName);
}

void NetzwerkSpiel::anmeldenNetzwerk(string nameSpieler2)
{
    this->sp2 = new Spieler(nameSpieler2);
    tcpClient->sendLoginRequest("SEND_REQUEST");

     //anmeldung erfolgreich sende eigene Daten zurueck...
    cout << "Anmelden erfolgreich!"<< endl;
}

void NetzwerkSpiel::rueckgabeSpielerInfo(Spieler spieler)
{
    //zuweisungsoperator ueberschreiben
    this->sp1 = new Spieler(spieler.getName());
    sp1->setIstAmZug(spieler.getIstAmZug());
    sp1->setFarbe(spieler.getFarbe());

    if(sp1->getFarbe() == ROT)
    {
        sp2->setFarbe(GELB);
    }
    else{
        sp2->setFarbe(ROT);
    }

    //finde heraus wer anfaengt!
    if(sp1->getIstAmZug())
    {
        sp2->setIstAmZug(false);
        aktuellerSpieler = sp1;
    }
    else
    {
        sp2->setIstAmZug(true);
        aktuellerSpieler = sp2;
    }

    std::cout << "System ready!!!" << endl;
    std::cout << *sp1 << endl;
    std::cout << *sp2 << endl;

    cout << "sende Reply..." << endl;
    tcpClient->sendLoginReply(sp1);
    cout << "Daten zurueckgesendet"<< endl;
}

void NetzwerkSpiel::abmeldenNetzwerk()
{
    //Blaa Blaa Blubb....
}

void NetzwerkSpiel::on_loginRequest(string loginPlayerName)
{
    cout << "Incoming to on_loginRequest() VALUE: " << loginPlayerName << endl;
}

void NetzwerkSpiel::on_loginReply(Spieler spieler)
{
    cout << "Incoming to on_loginReply() VALUE: " << spieler << endl;
    rueckgabeSpielerInfo(spieler);
}

void NetzwerkSpiel::on_remoteMove(unsigned short column)
{
    cout << "Incoming to on_remoteMove() VALUE: " << column << endl;
}
