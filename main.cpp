#include "heap.hpp"
#include "heap.tpp"

#include <iostream>
#include <vector>
#include <algorithm>
int main()
{
   std::vector<int> w = {23, 53, 5, 22, 3, 100, 66, 13, 11, 47, 0, 79};

   Heap<int>   h(w.begin(), w.end());
   h.printHeap();
   h.insert(2);
   h.printHeap();
   std::cout << h.peekHead() << " " << h[7] << std::endl;
   int   x = h.popHead();
   h.printHeap();
   std::cout << "x = " << x << std::endl;
   int y = 500;
   h.modify(5, y);
   h.printHeap();

}