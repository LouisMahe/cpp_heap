#include "heap.hpp"
#include "heap.tpp"

#include <iostream>
#include <vector>
#include <algorithm>

class Plank
{
   private:
      size_t   _length;
   public:
      Plank(){_length = 0;}
      Plank(size_t x) {_length = x;}

      size_t   getLength() const
      {
         return (this->_length);
      }

      bool operator<(const Plank &rhs) const
      {
         return (this->_length < rhs._length);
      }

};

std::ostream   &operator<<(std::ostream &o, const Plank &inst)
{
   o << inst.getLength();
   return(o);
}

int   serial_int(const int& x)
{
   return (x);
}

int main()
{
  std::vector<int> w = {45, 3, 64, 101, 32, 9, 13, 415, 25, 0,44};
  Heap<int, int>  h = Heap(w.begin(), w.end(), &serial_int);

   h.printHeap();
   h.printIndexes();
   size_t   idx;
   if (h.getIndex(64, idx))
   {
      std::cout << "h contains 64 at index: " << idx; 
   }
}