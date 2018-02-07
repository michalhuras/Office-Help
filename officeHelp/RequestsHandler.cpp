#include "RequestsHandler.h"

RequestsHandler::RequestsHandler() {

}

void RequestsHandler::catalogPathChangeSlot(QString newValue) {
qDebug() << "catalog path changed:  " << newValue;
}

void RequestsHandler::wordToSearchChangeSlot(QString newValue) {
qDebug() << "word to search changed:  " << newValue;
}



