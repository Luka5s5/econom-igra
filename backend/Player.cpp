#include "Player.h"


template<typename T>
void Player::show(std::string name, std::vector<T> v) {
    std::cout << name << ": ";
    for (auto t: v)
        std::cout << t << " ";
    std::cout << std::endl;
}

void Player::remove_treaty(int player_id, int type_of_treaty) {
    treaties[type_of_treaty].erase(player_id);
}

void Player::add_treaty(int player_id, int type_of_treaty) {
    treaties[type_of_treaty].insert(player_id);
}

bool Player::has_treaty(int player_id, int type_of_treaty) {
    return treaties[type_of_treaty].find(player_id) != treaties[type_of_treaty].end();
}

template<typename T>
void Player::change_vector(std::vector<T> &a, std::vector<T> b) {
    for (int i = 0; i < a.size(); i++) {
        a[i] += b[i];
    }
}

void Player::change_resources(std::vector<int> delta) {
    change_vector(resources, delta);
}

void Player::change_currencies(std::vector<double> delta) {
    change_vector(currencies, delta);
}

template<typename T>
bool Player::less_or_equal(std::vector<T> a, std::vector<T> b) {
    if (a.size() != b.size()) {
        return false;
    }
    for (int i = 0; i < a.size(); i++) {
        if (a[i] > b[i])
            return false;
    }
    return true;
}

bool Player::check_available_resources(std::vector<int> required) {
    return less_or_equal(required, resources);
}

bool Player::check_available_currencies(std::vector<double> required) {
    return less_or_equal(required, currencies);
}

void Player::change_army(std::vector<int> delta) {
    for (int i = 0; i < delta.size(); i++) {
        army[i] += delta[i];
    }
}

void Player::change_buildings(std::vector<int> delta) {
    for (int i = 0; i < delta.size(); i++) {
        building_levels[i] += delta[i];
    }
}

void Player::mine_resources() {
    resources[0] += building_levels[0] * 4;
    resources[1] += building_levels[1] * 8;
    resources[2] += building_levels[2] * 4;
    resources[3] += building_levels[3] * 8;
    resources[4] += building_levels[4] * 6;
    resources[5] += building_levels[5] * 4;
    resources[6] += building_levels[6] * building_levels[6];
    for (int i = 0; i <= 2; i++) {
        resources[i] += building_levels[7] * (building_levels[i] - 1);
    }
    for (int i = 3; i <= 5; i++) {
        resources[i] += building_levels[8] * (building_levels[i] - 1);
    }
    for (int i = 0; i < 7; i++) {
        resources[i] += building_levels[9] * 2;
    }
    resources[6] += building_levels[8] * (building_levels[6] + 1);
}

Player::Player(int id1) {
    id = id1;
    currencies = std::vector<double>(4);
    resources = std::vector<int>(11);
    building_levels = std::vector<int>(11);
    for (int i = 0; i < 7; i++) {
        building_levels[i] = 1;
    }
    treaties = std::vector<std::set<int>>(2);
    army = std::vector<int>(3);
    last_attack = 100;
    ban = 0;
    strategy = 3;
    city_used.resize(4);
    building_used.resize(11);
}

void Player::load(std::ifstream &file) {
    file >> id;
    std::cout << id << "\n";
    read(file, currencies);
    read(file, resources);
    read(file, building_levels);
    read(file, treaties[0]);
    read(file, treaties[1]);
    read(file, army);
    file >> last_attack;
    file >> ban;
    file >> strategy;
    read(file, city_used);
    read(file, building_used);
}

template<typename T>
void Player::read(std::ifstream &file, std::set<T> &v) {
    int size = 0;
    file >> size;
    for (int i = 0; i < size; i++) {
        T x;
        file >> x;
        v.insert(x);
    }
}

template<typename T>
void Player::read(std::ifstream &file, std::vector<T> &v) {
    int size = 0;
    file >> size;
    v.resize(size);
    for (auto& t: v)
        file >> t;
}

void Player::dumpload(std::ofstream &file) {
    file << id << std::endl;
    print(file, currencies);
    print(file, resources);
    print(file, building_levels);
    print(file, treaties[0]);
    print(file, treaties[1]);
    print(file, army);
    file << last_attack << std::endl;
    file << ban << std::endl;
    file << strategy << std::endl;
    print(file, city_used);
    print(file, building_used);
    file << std::endl;
}

template<typename T>
void Player::print(std::ofstream &file, std::set<T> v) {
    file << v.size() << " ";
    for (auto t: v)
        file << t << " ";
    file << std::endl;
}

void Player::show() {
    std::cout << id << std::endl;
    show("curr", currencies);
    show("res", resources);
    show("builds", building_levels);
    show("treaties0", treaties[0]);
    show("treaties1", treaties[1]);
    show("army", army);
    std::cout << "last_attack: " << last_attack << std::endl;
    std::cout << "ban: " << ban << std::endl;
    std::cout << "strategy: " << strategy << std::endl;
    show("city_used", city_used);
    show("building_used", building_used);
    std::cout << std::endl;
}

template<typename T>
void Player::print(std::ofstream &file, std::vector<T> v) {
    file << v.size() << " ";
    for (auto t: v)
        file << t << " ";
    file << std::endl;
}

template<typename T>
void Player::show(std::string name, std::set<T> v) {
    std::cout << name << ": ";
    for (auto t: v)
        std::cout << t << " ";
    std::cout << std::endl;
}
