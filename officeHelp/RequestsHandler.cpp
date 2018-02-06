#include "RequestsHandler.h"

RequestsHandler::RequestsHandler() {

}

void RequestsHandler::catalogPathChangeSlot(QString newValue) {
qDebug() << "catalog path changed";
}

void RequestsHandler::wordToSearchChangeSlot(QString newValue) {
qDebug() << "word to search changed";
}



