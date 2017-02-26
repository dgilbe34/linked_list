#include<iostream>
using std::cout; using std::endl;

#include "class-11.h"


int main (){
  RBag<long> b;
  b.append_front(10);
  b.append_front(20);
  RBag<long> c(b);
  cout<<c<<endl;
  long rcpt = b.append_front(30);
  cout<<b<<endl;

  Node<long>* n = new Node<long>(40,100);
  b.append_front(n);
  cout << b << endl;
  
  auto ptr = b.find(rcpt);

  cout << *ptr << endl;
  
  cout << b << endl;

  ptr = b.find(1);
  if (ptr == nullptr)
    cout << "Not found" << endl;
  else
    cout << *ptr << endl;

  b.remove(1526154843);
  cout << b << endl;
}
  
