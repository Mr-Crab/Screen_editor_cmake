#include "Controller.h"
#include "Observer.h"

Controller::Controller()
{
}

Controller::~Controller()
{
}

void Controller::bindObserver(Observer* observer)
{
	if (isExist(observer))
		return;

	m_observers.push_back(observer);
}

void Controller::unboundObserver(Observer* observer)
{
	for (int i = 0; i < m_observers.size(); i++)
	{
		if (observer == m_observers[i])
		{
			m_observers.remove(i);
			return;
		}
	}
}

int Controller::getNumObservers()
{
	return m_observers.size();
}

Observer* Controller::getObserver(int index)
{
	return m_observers[index];
}

bool Controller::isExist(Observer* observer)
{
	for (int i = 0; i < m_observers.size(); i++)
	{
		if (observer == m_observers[i])
			return true;
	}
	return false;
}

