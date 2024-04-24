// Name: David Tang
// Seneca Student ID: 150276228
// Seneca email: dtang30@myseneca.ca
// Date of completion: Ocotober 26, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include <string>
#include <iomanip>
#include "Utilities.h"
#include "Station.h"
using namespace std;

namespace sdds {
	size_t Station::m_widthField = 0;
	size_t Station::id_generator = 0;

	Station::Station(const string& inputStr) {
		Utilities util;
		bool more = true;
		size_t pos = 0u;

		m_id = static_cast<int>(++id_generator);
		m_itemName = util.extractToken(inputStr, pos, more);
		m_serialNum = stoull(util.extractToken(inputStr, pos, more));
		m_stockQty = stoull(util.extractToken(inputStr, pos, more));
		if (m_widthField < util.getFieldWidth())
			m_widthField = util.getFieldWidth();
		m_description = util.extractToken(inputStr, pos, more);
	}

	const string& Station::getItemName() const {
		return m_itemName;
	}

	size_t Station::getNextSerialNumber() {
		return m_serialNum++;
	}

	size_t Station::getQuantity() const {
		return m_stockQty;
	}

	void Station::updateQuantity() {
		--m_stockQty;
	}

	void Station::display(ostream& os, bool full) const {
		os << setw(3) << setfill('0') << m_id << " | "
			<< left << setfill(' ') << setw(m_widthField) << m_itemName << " | "
			<< right << setw(6) << setfill('0') << m_serialNum << " | ";
		if (full) {
			os << setfill(' ') << setw(4) << m_stockQty << " | " << m_description;
		}
		os << endl;
	}
}
