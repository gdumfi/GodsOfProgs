#include "client.h"




SingletonClient::SingletonClient();
SingletonClient::~SingletonClientDestroyer(){//zakrt' soket};

bool SingletonClient::connectToServer(); // ecli socket ne pustoy
void SingletonClient::sendToServer(QString); // otpravit' soobschenie
slot SingletonClient::readyRead();
