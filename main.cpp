#include <chrono>
#include <limits>
#include <locale>

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;
using namespace chrono;

template <class TypeMultiply>
bool isSafeMultiply (TypeMultiply mult01, TypeMultiply mult02, TypeMultiply &multResult) {

  /*$$
  add code to check if mult01 or mult02 = 0
  if so, set multResult to 0 and leave with a true
  */
  if (mult02 == 0 || mult01 == 0) {
    multResult = 0;
    return true;
  }

  /*$$
  calculate the multResult from mult01 and mult02
  check if mult01 is equal to the multResult divided by mult02
  if it is equal then leave with a true
  if not then leave with a false (overflow)
  */
  multResult = mult01 * mult02;
  if (mult01 == multResult / mult02) {
    return true;
  } else {
    return false;
  }

}

template <class TypeMultiply>
void calculateTimeFactorialLoopFunc(void) {

  //$$ set  start time  
  auto timeStart = steady_clock::now();
  TypeMultiply multiplier      = 1,
               factorialResult = 1;

  /*$$ (inside while loop) invoke isSafeMultiply with multiplier and factorialResult*/
  while (isSafeMultiply(multiplier, factorialResult, factorialResult)) {
    //$$ display the multiplier and the factorial result using field widths of 3 and 27 respectively
    cout << setw(3) << multiplier << setw(27) << factorialResult << "\n";

    // increment the multiplier
    multiplier++;
  }

  // calculate timeElapsed as described in the assignment
  auto timeElapsed = duration_cast<nanoseconds>(steady_clock::now() - timeStart);

  //$$ display Unsigned overflow at : multiplier
  cout << "Unsigned overflow at: " << setw(15) << multiplier << "\n";

  //$$ display Time Elapsed (nano)  : timeElapsed.count()
  cout << "Time Elapsed (nano) : " << setw(15) << timeElapsed.count() << endl;
}//calculateTimeFactorialLoopFunc

 //------------------------------------------
template <class TypeMultiply>
void factorialRecursiveFunc(TypeMultiply &multiplier, TypeMultiply factorialResult) {

  if (/*$$ invoke isSafeMultiply <TypeMultiply> with multiplier and factorial result)*/
      isSafeMultiply<TypeMultiply>(multiplier, factorialResult, factorialResult)) {
    //$$ display the multiplier and the factorial result using field widths of 3 and 27 respectively
    cout << setw(3) << multiplier << setw(27) << factorialResult << "\n";

    //$$ invoke factorialRecursiveFunc with ++multiplier and factorialResult
    factorialRecursiveFunc(++multiplier, factorialResult);
  }

  return;

}//factorialRecursive

 //------------------------------------------  
template <class TypeMultiply>
void calculateTimeFactorialRecursiveFunc() {

  //$$ set start time
  auto timeStart = steady_clock::now();

  TypeMultiply mult01 = 1;
  factorialRecursiveFunc<TypeMultiply> (mult01, 1);

  //$$ set time elapsed 
  auto timeElapsed = duration_cast<nanoseconds>(steady_clock::now() - timeStart);

  //$$ display Unsigned overflow at : mult01
  //$$ display Time Elapsed (nano)  : timeElapsed.count()
  cout << "Unsigned overflow at: " << mult01 << "\n" 
       << "Time Elapsed (nano) : " << timeElapsed.count() << endl;
}//calculateTimeFactorialRecursiveFunc()

template <typename TYPESIZE> 
class FactorialCalculationClass {

private:
  unsigned typeSizeBits;

public:
  // Constructor
  FactorialCalculationClass(unsigned typeSize) {
    //$$ set typeSizeBits to typeSize;
    typeSizeBits = typeSize;
  }

  void executeFactorialForType() {

    cout << typeSizeBits <<
      " bit unsigned Factorial Loop" << endl <<
      "------------------------------" << endl;
    calculateTimeFactorialLoopFunc<TYPESIZE>();
    cout << endl << endl;

    cout << typeSizeBits <<
      " bit unsigned Factorial Recursion" << endl <<
      "-----------------------------------" << endl;
    calculateTimeFactorialRecursiveFunc<TYPESIZE>();
    cout << endl << endl;
  }

};// template <class TYPESIZE> class factorialCalculationClass

int main() {
  // condition cout set to local digit separation comas (USA)
  cout.imbue(locale(""));

  /*$$
  create an object of FactorialCalculationClass <uintnn_t> called factorialCalculateUintnnObj(nn)
  where nn is the size in bits for the tempalte type uintnn_t, the object name factorialCalculateUintnnObj
  and the nn for the argument (nn) to the constructor
  nn must equal nn = 16, 32 and 64 to make the 3 objects
  */
  FactorialCalculationClass<uint16_t> factorialCalculateUintnnObj(16);
  FactorialCalculationClass<uint32_t> factorialCalculateUint32Obj(32);
  FactorialCalculationClass<uint64_t> factorialCalculateUint64Obj(64);

  /*$$
  for each of the 3 nn objects factorialCalculateUintnnObj
  invoke the executeFactorialForType()
  */
  factorialCalculateUintnnObj.executeFactorialForType();
  factorialCalculateUint32Obj.executeFactorialForType();
  factorialCalculateUint64Obj.executeFactorialForType();

  // Hold the screen
  
  cout << "Press enter to end";
  cin.ignore();
  exit (EXIT_SUCCESS);
}
