#include "RequestsHandler.h"

RequestsHandler::RequestsHandler() {
	sig.connect(hello);
}

RequestsHandler::createFileList() {

}

RequestsHandler::catalogPathChangeSlot() {
qDebug() << "catalog path changed";
}

RequestsHandler::wordToSearchChangeSlot() {
qDebug() << "word to search changed";
}

RequestsHandler::setCatalogPath() {

}

RequestsHandler::setWordToSearch() {

}
