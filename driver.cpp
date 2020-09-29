#include <iostream>
#include "hash.h"
#include "donut.h"


// Prototype for 16 bit cyclic hash function; implementation is after
// main().
unsigned cyclic_hash16(string key);

int main() {

  // Create a vector of donuts to insert in the hash table
  vector<Donut> donuts;
  donuts.push_back(Donut("glazed", 5, "super donut"));
  donuts.push_back(Donut("glazed", 12, "mega donut"));
  donuts.push_back(Donut("glazed", 4, "shack of donuts"));
  donuts.push_back(Donut("boston cream", 10, "mega donut"));
  donuts.push_back(Donut("boston cream", 5, "donut world"));
  donuts.push_back(Donut("sprinkle", 7, "donut world"));
  donuts.push_back(Donut("sprinkle", 15, "super donut"));
  donuts.push_back(Donut("sprinkle", 8, "shack of donuts"));
  donuts.push_back(Donut("boston cream", 3, "donut joint"));
  donuts.push_back(Donut("cinnamon", 3, "shack of donuts"));
  donuts.push_back(Donut("bavarian cream", 28, "mega donut"));
  donuts.push_back(Donut("cinnamon", 11, "super donut"));

  Donut p;
  vector<Donut> P;
  P.push_back(Donut("KK", 5, "super donut"));
  P.push_back(Donut("KK", 12, "mega donut"));
  P.push_back(Donut("KK", 4, "shack of donuts"));
  P.push_back(Donut("Jk", 10, "mega donut"));
  P.push_back(Donut("Jk", 5, "donut world"));
  P.push_back(Donut("L+", 7, "donut world"));
  P.push_back(Donut("L+", 15, "super donut"));
  P.push_back(Donut("L+", 8, "shack of donuts"));
  P.push_back(Donut("Jk", 3, "donut joint"));
  P.push_back(Donut("A,*", 3, "shack of donuts"));
  P.push_back(Donut("P«", 28, "mega donut"));
  P.push_back(Donut("A,*", 11, "super donut"));
  HashTable<Donut> ht4(10, cyclic_hash16);
  for (auto d : P) {
	  ht4.insert(d);
  }

  // Create the hash table of length 10 using cyclic_hash function
  HashTable<Donut> ht(10, cyclic_hash16);

  // Insert the donut orders
  for (auto d : donuts) {
    ht.insert(d);
  }
  HashTable<Donut> ht3 = ht;

  cout << "\nDump of ht:\n";
  ht.dump();

  // Extract some orders
  
  Donut d;
  vector<string> orders;

  orders.push_back("boston cream");
  orders.push_back("bavarian cream");
  orders.push_back("cinnamon");
  orders.push_back("cinnamon");
  orders.push_back("cinnamon");

  for ( auto ord : orders ) {
    cout << "\nGet next '" << ord << "' order...\n";
    if ( ht.getNext(ord, d) ) {
      cout << "  " << d << endl;
    } else {
      cout << "  No " << ord << " orders!\n";
    }
  }

  cout << endl;

  cout << "\nDump of ht:\n";
  ht.dump();

  // Simple test of copy constructor; also need to test assignment
  // operator!
  cout << "\nCreate copy of hash table, remove two 'sprinkle' orders, dump both tables...\n";

  HashTable<Donut> ht2(ht);

  ht2.getNext("sprinkle", d);
  ht2.getNext("sprinkle", d);

  cout << "\nDump of ht:\n";
  ht.dump();

  cout << "\nDump of ht2:\n";
  ht2.dump();

  cout << "\n!Create copy of hash table, remove all 'sprinkle' orders, dump both tables...\n";
  //HashTable<Donut> ht3 = ht;
  //ht3.getNext("sprinkle", d);
  //ht3.getNext("sprinkle", d);
  //ht3.getNext("sprinkle", d);
  cout << "\nDump of ht3:\n";
  ht3.dump();
  cout << "\nDump of ht:\n";
  ht.dump();

  cout << endl;
  ht4.dump();
  ht4.getNext("L+", p);
  ht4.getNext("L+", p);
  ht4.getNext("L+", p);
  ht4.insert(Donut("Q‹", 27, "Bega donut"));
  cout << endl;
  ht4.dump();
  
  return 0;
}

unsigned cyclic_hash16(string key) {
  unsigned usize = 16;
  unsigned s = 5; // shift by 5
  unsigned h = 0;
  for (auto c : key) {
    h = (( h << s ) | ( h >> (usize - s) ));
    h += c;
    h = h & 0xffff;
  }
  return h;
}

