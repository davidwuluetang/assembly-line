// Name: David Tang
// Seneca Student ID: 150276228
// Seneca email: dtang30@myseneca.ca
// Date of completion: Ocotober 29, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_LINE_MANAGER_H
#define SDDS_LINE_MANAGER_H

namespace sdds {
	class LineManager {
		std::vector<Workstation*> m_activeLine;
		size_t m_cntCustomerOrder{};
		Workstation* m_firstStation{};
	public:
		LineManager(const std::string& file, const std::vector<Workstation*>& stations);
		void reorderStations();
		bool run(std::ostream& os);
		void display(std::ostream& os) const;
	};
}

#endif // !SDDS_LINE_MANAGER_H

