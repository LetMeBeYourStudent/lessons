#include <cassert>
#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <vector>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses,
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream& operator>>(istream& is, Query& q) {
    // Реализуйте эту функцию
    return is;
}

struct BusesForStopResponse {
    // Наполните полями эту структуру
    vector<string> buses;
};

ostream& operator<<(ostream& os, const BusesForStopResponse& r) {
    // Реализуйте эту функцию
    if (!r.buses.empty())
        for (const string& bus : r.buses)
            os << bus << " ";
    else {
        os << "No stop";
    }
    os << endl;
    return os;
}

struct StopsForBusResponse {
    // Наполните полями эту структуру
    vector<string> stops;
};

ostream& operator<<(ostream& os, const StopsForBusResponse& r) {
    // Реализуйте эту функцию
    return os;
}

struct AllBusesResponse {
    map<string, vector<string>> lines;
};

ostream& operator<<(ostream& os, const AllBusesResponse& r) {
    // Реализуйте эту функцию
    return os;
}

class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        lines_[bus] = stops;
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        // Реализуйте этот метод
        BusesForStopResponse result;
        for (const auto& [bus, stops] : lines_)
            if (count(stops.begin(), stops.end(), stop)) result.buses.push_back(bus);
        return result;
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        // Реализуйте этот метод
        StopsForBusResponse result;
        if (lines_.count(bus))
            result.stops = lines_.at(bus);
        return result;
    }

    AllBusesResponse GetAllBuses() const {
        // Реализуйте этот метод
        AllBusesResponse result;
        result.lines = lines_;
        return result;
    }
private:
    map<string, vector<string>> lines_;
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;

    }
//}
//int main() {
//    int query_count;
//    Query q;
//
//    cin >> query_count;
//
//    BusManager bm;
//    for (int i = 0; i < query_count; ++i) {
//        cin >> q;
//        switch (q.type) {
//            case QueryType::NewBus:
//                bm.AddBus(q.bus, q.stops);
//                break;
//            case QueryType::BusesForStop:
//                cout << bm.GetBusesForStop(q.stop) << endl;
//                break;
//            case QueryType::StopsForBus:
//                cout << bm.GetStopsForBus(q.bus) << endl;
//                break;
//            case QueryType::AllBuses:
//                cout << bm.GetAllBuses() << endl;
//                break;
//        }
//    }
//}