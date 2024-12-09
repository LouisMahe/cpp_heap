#include "heap.hpp"
#include "heap.tpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>

class Plank
{
   private:
      size_t   _length;
      size_t   _serial_num;
   public:
      Plank(){_length = 0;}
      Plank(size_t x, size_t num) {_length = x; _serial_num = num;}

      size_t   getLength() const
      {
         return (this->_length);
      }

      size_t getSerial() const
      {
         return (this->_serial_num);
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

using p_ptr = Plank*;
bool  comp_ptr(const p_ptr &p, const p_ptr &q)
{
   return (*p < *q);
}


std::ostream   &operator<<(std::ostream &o, const Plank *inst)
{
   o << "||Plank length: " << inst->getLength() << " Plank serial: " << inst->getSerial() << "\n";
   return(o);
}
size_t   serial_plank(const p_ptr &p)
{
   return (p->getSerial());
}

void  cleanPt(p_ptr &p)
{
   if (p != nullptr)
   {
      delete p;
      p = nullptr;
   }
}

int main()
{
  srand(time(0));
  std::vector<Plank*> w;
  for ( size_t i = 0; i < 15; i++)
  {
   w.push_back(new Plank(i+1, i));
  }
  Heap<Plank*, size_t>  h = Heap<Plank*, size_t>(w.begin(), w.end(), &serial_plank, &comp_ptr);
  h.printHeap();
  h.printIndexes();
  p_ptr  new_plank = new Plank(0, 9);
  Plank  *res = h.modify(9, new_plank);
  delete res;
  std::cout << "removed and modified " << *res << std::endl;
  h.printHeap();
  h.deleteVec(&cleanPt);
}
