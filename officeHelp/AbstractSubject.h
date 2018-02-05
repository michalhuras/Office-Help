#ifndef ABSTRACTSUBJECT_H
#define ABSTRACTSUBJECT_H

#include <QVector>

class AbstractObservator;

class AbstractSubject
{
public:

	/**
	 * dodaje obserwatora o do listy obserwatorow
	 */
	void addObservator(AbstractObservator *aAbstractObservator) {
		ObservatorsContainer.push_back(aAbstractObservator);
	}

	/**
	 * powiadamia kazdego obserwatora o zmianie stanu
	 */
	void notify(){

		list<miernik*>::iterator it = mierniki.begin();
		for( ; it != mierniki.end(); it++){
		(*it)->update(this);
		}
	}

	/**
	 * abstrakcyjny destruktor
	 */
	virtual ~Obserwowany() {;}
	private:
	/**
	 * lista obserwatorow
	 */
	QVector<AbstractObservator*> ObservatorsContainer;
};

#endif // ABSTRACTSUBJECT_H
