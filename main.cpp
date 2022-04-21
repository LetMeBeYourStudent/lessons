#include <cassert>
#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <vector>
#include <sstream>

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

istream &operator>>(istream &is, Query &q) {
    // Реализуйте эту функцию
    string operation_code;
    is >> operation_code;
    if (operation_code == "NEW_BUS"s) {
        q.type = QueryType::NewBus;
        is >> q.bus;
        int stop_count;
        is >> stop_count;
        q.stops.resize(stop_count);
        for (string &stop: q.stops) {
            is >> stop;
        }
    } else if (operation_code == "BUSES_FOR_STOP"s) {
        q.type = QueryType::BusesForStop;
        is >> q.stop;
    } else if (operation_code == "STOPS_FOR_BUS"s) {
        q.type = QueryType::StopsForBus;
        is >> q.bus;
    } else if (operation_code == "ALL_BUSES"s) {
        q.type = QueryType::AllBuses;
    }
    return is;
}

struct BusesForStopResponse {
    // Наполните полями эту структуру
    vector<string> buses;
};

ostream &operator<<(ostream &os, const BusesForStopResponse &r) {
    // Реализуйте эту функцию
    if (r.buses.empty())
        os << "No stop";
    else
        for (const string &bus: r.buses)
            os << bus << " ";
    return os;
}

struct StopsForBusResponse {
    // Наполните полями эту структуру
    vector<string> stops;
    map<string, vector<string>> stops_to_bus;
};

ostream &operator<<(ostream &os, const StopsForBusResponse &r) {
    // Реализуйте эту функцию
    if (r.stops.empty())
        os << "No bus";
    else {
        for (const string &stop: r.stops) {
            os << "Stop " << stop << ": ";
            if (r.stops_to_bus.at(stop).empty())
                os << "no interchange";
            else
                for (const string &bus: r.stops_to_bus.at(stop))
                    os << bus << " ";
            os << endl;
        }
    }
    return os;
}

struct AllBusesResponse {
    map<string, vector<string>> lines;
};

ostream &operator<<(ostream &os, const AllBusesResponse &r) {
    // Реализуйте эту функцию
    if (r.lines.empty())
        os << "No buses";
    else
        for (const auto& [bus, stops] : r.lines)
        {
            os << "Bus " << bus << ": ";
            for (const string& stop : stops)
                os << stop << " ";
            os << endl;
        }
    return os;
}

class BusManager {
public:
    void AddBus(const string &bus, const vector<string> &stops) {
        lines_[bus] = stops;
    }

    BusesForStopResponse GetBusesForStop(const string &stop) const {
        // Реализуйте этот метод
        BusesForStopResponse result;
        for (const auto &[bus, stops]: lines_)
            if (count(stops.begin(), stops.end(), stop)) result.buses.push_back(bus);
        return result;
    }

    StopsForBusResponse GetStopsForBus(const string &bus) const {
        // Реализуйте этот метод
        StopsForBusResponse result;
        if (lines_.count(bus))
            result.stops = lines_.at(bus);
        for (const string &stop: result.stops)
        {
            vector<string> r;
            for (const string& cur_bus : GetBusesForStop(stop).buses)
                if (cur_bus != bus) r.push_back(cur_bus);
            result.stops_to_bus[stop] = r;
        }
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

void TestAddNewBusInput() {
    istringstream input;
    input.str("NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo"s);

    Query q;
    input >> q;
    assert(q.type == QueryType::NewBus);
    assert(q.bus == "32");
    assert(q.stops.size() == 3);
}

int main() {
    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
            case QueryType::NewBus:
                bm.AddBus(q.bus, q.stops);
                break;
            case QueryType::BusesForStop:
                cout << bm.GetBusesForStop(q.stop) << endl;
                break;
            case QueryType::StopsForBus:
                cout << bm.GetStopsForBus(q.bus) << endl;
                break;
            case QueryType::AllBuses:
                cout << bm.GetAllBuses() << endl;
                break;
        }
    }
}