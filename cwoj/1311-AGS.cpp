/**
 * Cwoj Problem 1311
 * Author: AGStheDeveloper
 * Start DateTime: 20160930-01200000(GMT+800)
 * Finish DateTime: 20160930-19020000(GMT+800)
 */
 
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib>
 
using std::cin;
using std::cout;
using std::stable_sort;
using std::string;
 
namespace Cwoj1311 {
 
  using std::vector;
  using std::istream;
  using std::ostream;
  using std::exit;
 
  union KnightValue {
    int Cost;
    int Capability;
  };
 
  class Knight {
  public:
    Knight():_value(KnightValue()), _available(true) {}
    Knight(int UniValue, bool Available = true);
    inline KnightValue *GetValueR() {
      return &_value;
    }
    inline KnightValue GetValueL() const {
      return _value;
    }
    inline void Dispatch() {
      _available = false;
    }
    inline bool IsAvailable() {
      return _available;
    }
 
    inline static bool Comparator(const Knight &a, const Knight &b) {
      return a._value.Capability < b._value.Capability;
    }
        
  private:
    KnightValue _value;
    bool _available;
  };
  Knight::Knight(int UniValue, bool Available) {
    this->_available = Available;
    this->_value.Cost = UniValue;
  }
 
  class Dragon {
  public:
    Dragon():_difficulty(0), _killed(false) {}
    Dragon(int Difficulty, bool Killed = false);
 
    inline void Kill() {
      _killed = true;
    }
    inline bool IsKilled() const {
      return _killed;
    }
    inline bool operator<=(const Knight &KnightObj) const {
      return _difficulty <= KnightObj.GetValueL().Capability;
    }
 
    inline static bool Comparator(const Dragon &a, const Dragon &b) {
      return a._difficulty < b._difficulty;
    }
 
  private:
    int _difficulty;
    bool _killed;
  };
  Dragon::Dragon(int Difficulty, bool Killed) {
    this->_difficulty = Difficulty;
    this->_killed = Killed;
  }
 
  constexpr int SAFE_EXIT = 0;
  constexpr char *FAILURE_MSG = "Loowater is doomed!";
  class Massacre {
  public:
    Massacre():
      _knightContainer(new vector<Knight>()),
      _dragonContainer(new vector<Dragon>()),
      _failure(false),
      _totalCost(0) {}
    inline int GetResult() {
      return _totalCost;
    }
    inline bool IsFailed() {
      return _failure;
    }
    void SortData() const;
    void PerformGreedyAlgorithm();
 
    static Massacre *InitFromCliInput();
  private:
    vector<Knight> *_knightContainer;
    vector<Dragon> *_dragonContainer;
    bool _failure;
    int _totalCost;
  };
  void Massacre::SortData() const {
    stable_sort(_knightContainer->begin(), _knightContainer->end(), &Cwoj1311::Knight::Comparator);
    stable_sort(_dragonContainer->begin(), _dragonContainer->end(), &Cwoj1311::Dragon::Comparator);
  }
  void Massacre::PerformGreedyAlgorithm() {
    int knightRecorder = 0, dragonRecorder = 0;
    for (Knight &knight : *_knightContainer) {
      if (knightRecorder >= _knightContainer->size()) {
	_failure = true;
	break;
      }
 
      if ((*_dragonContainer)[dragonRecorder] <= (*_knightContainer)[knightRecorder] &&
	  !(*_dragonContainer)[dragonRecorder].IsKilled() &&
	  (*_knightContainer)[knightRecorder].IsAvailable()) {
	(*_knightContainer)[knightRecorder].Dispatch();
	(*_dragonContainer)[dragonRecorder].Kill();
	_totalCost += (*_knightContainer)[knightRecorder].GetValueL().Cost;
	dragonRecorder++;
      }
    }
  }
  Massacre* Massacre::InitFromCliInput() {
    int knightNumber, dragonNumber;
    cin >> dragonNumber >> knightNumber;
    if (dragonNumber == 0 && knightNumber == 0) {
      exit(SAFE_EXIT);
    }
 
    Massacre *mas = new Massacre();
    for (int dragonLooper = 0; dragonLooper < dragonNumber; dragonLooper++) {
      int _difficulty;
      cin >> _difficulty;
      mas->_dragonContainer->push_back(Cwoj1311::Dragon(_difficulty));
    }
    for (int knightLooper = 0; knightLooper < knightNumber; knightLooper++) {
      int _capability;
      cin >> _capability;
      mas->_knightContainer->push_back(Cwoj1311::Knight(_capability));
    }
 
    return mas;
  }
}
 
int main(int argc, char *argv[]) {
  while (true) {
    Cwoj1311::Massacre *mas = Cwoj1311::Massacre::InitFromCliInput();
    mas->InitFromCliInput();
    mas->SortData();
    mas->PerformGreedyAlgorithm();
 
    if (mas->IsFailed()) {
      cout << Cwoj1311::FAILURE_MSG;
      continue;
    }
 
    cout << mas->GetResult();
  }
}
