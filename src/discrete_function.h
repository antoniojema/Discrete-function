#pragma once

#include <map>
#include <vector>
#include <utility>

using Tx = double;
using Ty = float;

//template <typename Tx, typename Ty>
class DiscreteFunction : private std::map<Tx, Ty> {
public:
    DiscreteFunction() = default;
    DiscreteFunction() = default;
    DiscreteFunction(const std::vector<Tx>&, const std::vector<Ty>&);
    DiscreteFunction(const std::vector<std::pair<Tx, Ty>>&);
    DiscreteFunction(const std::vector<std::pair<Tx, Ty>>&);
    
    void set(const std::vector<Tx>&, const std::vector<Ty>&);
    void set(const std::vector<std::pair<Tx, Ty>>&);

    void add(const Tx&, const Ty&);
    void add(const std::pair<Tx, Ty>&);
    void add(const std::vector<Tx>&, const std::vector<Ty>&);
    void add(const std::vector<std::pair<Tx, Ty>>&);

    void erase(const std::vector<Tx>&);
    void eraseAll();

    Ty operator() (Tx);

private:
    std::map<Tx, Ty>& getMap();
    const std::map<Tx, Ty>& getMap() const;

    std::map<Tx, Ty> x0;
    std::map<Tx, Ty> pond;
};

/*********************/
/*    Constructor    */
/*********************/
//template <typename Tx, typename Ty>
inline DiscreteFunction/*<Tx, Ty>*/::DiscreteFunction(const std::vector<Tx>& x, const std::vector<Ty>& y) {
    this->set(x, y);
}

//template <typename Tx, typename Ty>
inline DiscreteFunction/*<Tx, Ty>*/::DiscreteFunction(const std::vector<std::pair<Tx, Ty>>& xy) {
    this->set(xy);
}

/*************/
/*    Set    */
/*************/
//template <typename Tx, typename Ty>
inline void DiscreteFunction/*<Tx, Ty>*/::set(const std::vector<Tx>& x, const std::vector<Ty>& y){
    this->eraseAll();
    for (size_t i = 0; i < std::min(x.size(), y.size()); i++) {
        this->getMap()[x[i]] = y[i];
        if (i > 0) {
            this->x0[x[i]] = x[i-1];
            this->pond[x[i]] = (y[i]-y[i-1])/(x[i]-x[i-1]);
        } else {
            this->x0[x[i]] = 0;
        }
    }
}

//template <typename Tx, typename Ty>
inline void DiscreteFunction/*<Tx, Ty>*/::set(const std::vector<std::pair<Tx, Ty>>& xy){
    this->eraseAll();
    for (auto& p : xy)
        this->getMap()[p.first] = p.second;
}

/*************/
/*    Add    */
/*************/
//template <typename Tx, typename Ty>
inline void DiscreteFunction/*<Tx, Ty>*/::add(const Tx& x, const Ty& y){
    this->getMap()[x] = y;
}

//template <typename Tx, typename Ty>
inline void DiscreteFunction/*<Tx, Ty>*/::add(const std::pair<Tx, Ty>& xy){
    this->getMap()[xy.first] = xy.second;
}

//template <typename Tx, typename Ty>
inline void DiscreteFunction/*<Tx, Ty>*/::add(const std::vector<Tx>& x, const std::vector<Ty>& y){
    for (size_t i = 0; i < std::min(x.size(), y.size()); i++)
        this->getMap()[x[i]] = y[i];
}

//template <typename Tx, typename Ty>
inline void DiscreteFunction/*<Tx, Ty>*/::add(const std::vector<std::pair<Tx, Ty>>& xy){
    for (auto& p : xy)
        this->getMap()[p.first] = p.second;
}

/***************/
/*    Erase    */
/***************/
//template <typename Tx, typename Ty>
inline void DiscreteFunction/*<Tx, Ty>*/::erase(const std::vector<Tx>& x){
    for (auto& key : x)
        this->getMap().erase(key);
}

//template <typename Tx, typename Ty>
inline void DiscreteFunction/*<Tx, Ty>*/::eraseAll(){
    std::map<Tx, Ty>& map = this->getMap();
    map.erase(map.begin(), map.end());
}

/*****************/
/*    Evaluate   */
/*****************/
//template <typename Tx, typename Ty>
inline Ty DiscreteFunction/*<Tx, Ty>*/::operator() (Tx x) {
    std::map<Tx, Ty>& map = this->getMap();
    auto it = map.lower_bound(x);
    if (it == map.end()) {
        return map.end()->second;
    } else if (it == map.begin()) {
        return map.begin()->second;
    } else {
        return (x - this->x0[x])*this->pond[x];
    }
}

/****************/
/*    Get map   */
/****************/
//template <typename Tx, typename Ty>
inline std::map<Tx, Ty>& DiscreteFunction/*<Tx, Ty>*/::getMap() {
    return static_cast<std::map<Tx, Ty>&>(*this);
}

//template <typename Tx, typename Ty>
inline const std::map<Tx, Ty>& DiscreteFunction/*<Tx, Ty>*/::getMap() const {
    return static_cast<const std::map<Tx, Ty>&>(*this);
}
