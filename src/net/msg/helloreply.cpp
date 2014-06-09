#include "../h/net/msg/helloreply.h"

HelloReply::HelloReply()
{
    //Do Nothing...
}

HelloReply::HelloReply(string ipAdress, string name, unsigned int rows, unsigned int columns)
{
    this->ipAdress = ipAdress;
    this->name = name;
    this->rows = rows;
    this->columns = columns;
}

HelloReply::~HelloReply()
{
    //kein new...
}

string HelloReply::getIpAdress() const
{
    return ipAdress;
}

void HelloReply::setIpAdress(const string &value)
{
    ipAdress = value;
}
string HelloReply::getName() const
{
    return name;
}

void HelloReply::setName(const string &value)
{
    name = value;
}
unsigned int HelloReply::getRows() const
{
    return rows;
}

void HelloReply::setRows(unsigned int value)
{
    rows = value;
}
unsigned int HelloReply::getColumns() const
{
    return columns;
}

void HelloReply::setColumns(unsigned int value)
{
    columns = value;
}

void HelloReply::fromCsvString(string csv)
{
    char * buffer = new char[csv.length()];
    strcpy(buffer,csv.c_str());

    char delimiter[] = ";";
    char *ptr;

    ptr = strtok(buffer, delimiter);
    this->ipAdress = ptr;

    ptr = strtok(NULL, delimiter);
    this->name = ptr;

    ptr = strtok(NULL, delimiter);
    this->rows = atoi(ptr);

    ptr = strtok(NULL, delimiter);
    this->columns = atoi(ptr);
}

ostream &operator<<(ostream& out, HelloReply& object){

    out << object.ipAdress << ";";
    out << object.name     << ";";
    out << object.rows     << ";";
    out << object.columns;
    return out;
}

istream &operator>>(istream& in, HelloReply& object){

    in >> object.ipAdress;
    in >> object.name;
    in >> object.rows;
    in >> object.columns;
    return in;
}

string HelloReply::toString()
{
    ostringstream o;
    o << "IpAddress: " << ipAdress << endl;
    o << "Name     : " << name << endl;
    o << "Rows     : " << rows << endl;
    o << "Columns  : " << columns << endl;
    return o.str();
}



