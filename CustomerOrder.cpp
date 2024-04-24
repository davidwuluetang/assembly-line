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
#include <vector>
#include <utility> 
#include "Utilities.h"
#include "CustomerOrder.h"
using namespace std;

namespace sdds {
	size_t CustomerOrder::m_widthField = 0;


	CustomerOrder::CustomerOrder(const string& inputStr) {
		Utilities util;
		bool more = true;
		size_t pos = 0u;

		m_name = util.extractToken(inputStr, pos, more);
		m_product = util.extractToken(inputStr, pos, more);

		vector<string> itemList;
		while (more)
			itemList.push_back(util.extractToken(inputStr, pos, more));

		m_cntItem = itemList.size();
		m_lstItem = new Item * [m_cntItem];
		for (size_t i = 0; i < m_cntItem; i++)
			m_lstItem[i] = new Item(itemList[i]);

		if (m_widthField < util.getFieldWidth())
			m_widthField = util.getFieldWidth();
	}

	CustomerOrder::CustomerOrder(const CustomerOrder& src) {
		throw "ERROR: Cannot make copies.";
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept {
		*this = move(src);
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept {
		if (this != &src) {
			for (size_t i = 0; i < m_cntItem; i++)
				delete m_lstItem[i];
			delete[] m_lstItem;

			m_name = src.m_name;
			m_product = src.m_product;
			m_cntItem = src.m_cntItem;
			m_lstItem = src.m_lstItem;

			src.m_lstItem = nullptr;
			src.m_cntItem = 0;
		}
		return *this;
	}

	CustomerOrder::~CustomerOrder() {
		for (size_t i = 0; i < m_cntItem; i++)
			delete m_lstItem[i];
		delete[] m_lstItem;
	}

	bool CustomerOrder::isOrderFilled() const {
		bool allFilled{ true };
		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_isFilled == false) {
				allFilled = false;
				i = m_cntItem;
			}
		}
		return allFilled;
	}

	bool CustomerOrder::isItemFilled(const string& itemName) const {
		bool allFilled{ true };
		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == itemName && m_lstItem[i]->m_isFilled == false) {
				allFilled = false;
				i = m_cntItem;
			}
		}
		return allFilled;
	}

	void CustomerOrder::fillItem(Station& station, ostream& os) {
		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == station.getItemName() && m_lstItem[i]->m_isFilled == false) {
				if (station.getQuantity() > 0) {
					m_lstItem[i]->m_isFilled = true;
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					station.updateQuantity();
					os << "    Filled " << m_name << ", " << m_product
						<< " [" << m_lstItem[i]->m_itemName << ']' << endl;
					i = m_cntItem;
				}
				else {
					os << "    Unable to fill " << m_name << ", " << m_product
						<< " [" << m_lstItem[i]->m_itemName << ']' << endl;
				}
			}
		}
	}

	void CustomerOrder::display(ostream& os) const {
		os << m_name << " - " << m_product << endl;
		for (size_t i = 0; i < m_cntItem; i++) {
			os << '[' << setw(6) << setfill('0') << m_lstItem[i]->m_serialNumber << ']'
				<< ' ' << left << setw(m_widthField) << setfill(' ') << m_lstItem[i]->m_itemName
				<< right << " - " << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED");
			os << endl;
		}
	}
}