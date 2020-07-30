#pragma once
#include <QVector>

class Observer;
class Controller
{
public:
	Controller();
	~Controller();

public:
	void bindObserver(Observer* observer);
	void unboundObserver(Observer* observer);

	int getNumObservers();
	Observer* getObserver(int index);

private:
	bool isExist(Observer* observer);

private:
	QVector<Observer*> m_observers;
};
