#ifndef ABSTRACTOBSERVER_H
#define ABSTRACTOBSERVER_H


class AbstractObserver
{
public:
	AbstractObserver();
	/**
	 * powiadamia obserwatora o zajsciu zmiany stanu w obiekcie obserwowanym
	 */
	virtual void odswiez() = 0;
	/**
	 * abstrakcyjny destruktor
	 */
	virtual ~Obserwator() {;}
};

#endif // ABSTRACTOBSERVER_H
