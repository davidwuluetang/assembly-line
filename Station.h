// Name: David Tang
// Seneca Student ID: 150276228
// Seneca email: dtang30@myseneca.ca
// Date of completion: Ocotober 26, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_STATION_H
#define SDDS_STATION_H

namespace sdds {
	class Station {
		int m_id{};
		std::string m_itemName;
		std::string m_description;
		size_t m_serialNum{};
		size_t m_stockQty{};
		static size_t m_widthField;
		static size_t id_generator;
	public:
		Station(const std::string& inputStr);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
}

#endif // !SDDS_STATION_H
