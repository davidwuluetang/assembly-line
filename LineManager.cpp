// Name: David Tang
// Seneca Student ID: 150276228
// Seneca email: dtang30@myseneca.ca
// Date of completion: Ocotober 29, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include "Utilities.h"
#include "CustomerOrder.h"
#include "Workstation.h"
#include "LineManager.h"
using namespace std;

namespace sdds {
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
		ifstream inFile(file);
		if (inFile) {
			Utilities util;
			string line;

			struct Find_Match {
				string name;
				Find_Match(const string& str) { name = str; }
				bool operator()(const Workstation* it) {
					return it->getItemName() == name;
				}
			};

			while (!inFile.eof()) {
				getline(inFile, line);
				bool more = true;
				size_t pos = 0u;
				string str1, str2;

				str1 = util.extractToken(line, pos, more);
				if (more)
					str2 = util.extractToken(line, pos, more);


				auto station_1 = find_if(stations.begin(), stations.end(), Find_Match(str1));
				if (str2.empty())
					(*station_1)->setNextStation();
				else {
					auto station_2 = find_if(stations.begin(), stations.end(), Find_Match(str2));
					(*station_1)->setNextStation(*station_2);
				}
				m_activeLine.push_back(*station_1);
			}
			// find the station pointer not match any m_pNextStation.
			auto fisrtStation = find_if(stations.begin(), stations.end(), [this](Workstation* station) {
				return (none_of(m_activeLine.begin(), m_activeLine.end(), [station](Workstation* next_station) {
							if (next_station->getNextStation() != nullptr)
								return station == next_station->getNextStation();
							else
								return false;
						}));
			});

			m_firstStation = *fisrtStation;

			m_cntCustomerOrder = g_pending.size();
		}
		else {
			const string msg = "Cannot open [" + file + "].";
			throw msg;
		}
	}

	void LineManager::reorderStations() {
		m_activeLine.front() = m_firstStation;
		// from second element of m_activeLine, assign Workstation* from previous station m_pNextStation.
		for (auto current_it = m_activeLine.begin() + 1; current_it != m_activeLine.end(); current_it++) {
			Workstation* lastStation = *(--current_it);
			++current_it;
			*current_it = lastStation->getNextStation();
		}
	}

	bool LineManager::run(std::ostream& os) {
		static size_t count{ 1 };
		os << "Line Manager Iteration: " << count++ << endl;
		if (g_pending.size() > 0) {
			*m_firstStation += move(g_pending.front());
			g_pending.pop_front();
		}

		for (auto& station : m_activeLine)
			station->fill(cout);

		for (auto& station : m_activeLine)
			station->attemptToMoveOrder();

		if ((g_completed.size() + g_incomplete.size()) == m_cntCustomerOrder)
			return true;

		return false;
	}

	void LineManager::display(std::ostream& os) const {
		for (auto& station : m_activeLine)
			station->display(cout);
	}
}
