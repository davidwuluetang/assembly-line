// Name: David Tang
// Seneca Student ID: 150276228
// Seneca email: dtang30@myseneca.ca
// Date of completion: Ocotober 29, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include "Workstation.h"
using namespace std;

namespace sdds {
	deque<CustomerOrder> g_pending;
	deque<CustomerOrder> g_completed;
	deque<CustomerOrder> g_incomplete;

	Workstation::Workstation(const string& inputStr) : Station(inputStr) {}

	void Workstation::fill(std::ostream& os) {
		if (!m_orders.empty())
			m_orders.front().fillItem(*this, cout);
	}

	bool Workstation::attemptToMoveOrder() {
		bool moved{ false };

		if (!m_orders.empty()) {
			if (m_orders.front().isItemFilled(getItemName()) || getQuantity() == 0) {
				if (m_pNextStation) {
					m_pNextStation->m_orders.push_back(move(m_orders.front()));
					m_orders.pop_front();
					moved = true;
				}
				else {
					if (m_orders.front().isOrderFilled()) {
						g_completed.push_back(move(m_orders.front()));
						m_orders.pop_front();
						moved = true;
					}
					else {
						g_incomplete.push_back(move(m_orders.front()));
						m_orders.pop_front();
						moved = true;
					}
				}
			}
		}
		return moved;
	}

	void Workstation::setNextStation(Workstation* station) {
		m_pNextStation = station;
	}

	Workstation* Workstation::getNextStation() const {
		return m_pNextStation;
	}

	void Workstation::display(ostream& os) const {
		os << getItemName() << " --> " <<
			(m_pNextStation ? m_pNextStation->getItemName() : "End of Line");
		os << '\n';
	}

	Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
		m_orders.push_back(move(newOrder));
		return *this;
	}
}
