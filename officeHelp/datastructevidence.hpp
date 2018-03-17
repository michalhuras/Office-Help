#ifndef DATASTRUCTEVIDENCE_HPP
#define DATASTRUCTEVIDENCE_HPP

#include <QStringList>
#include <QVector>
#include <QDir>
#include <QString>

namespace CUS{
//common used structures

enum searchMode {
	error = -2,
	undefined = -1,
	inThisFile = 0,
	inThisCatalog = 1,
	inThisCatalogRecursevely = 2 };

struct searchReult
{
	QDir fileDirectory;
	QString fileName;
	QVector<QVector<QPair<int , QString > > > results;
	int numberOfResults;
};
}

#endif // DATASTRUCTEVIDENCE_HPP
