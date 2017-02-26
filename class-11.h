/*
 Drew Gilbertson
 * Section 7
 * April 24 2016
 * 
 * This program creates a templated linked list, and can perform a 
 * variety of operations 
 */


#ifndef RECEIPT_BAG
#define RECEIPT_BAG

#include<iostream>
using std::ostream;
#include<random>
using std::mt19937_64; using std::uniform_int_distribution;

// forward declaration
template<typename T>
class RBag;

/*
  Node struct has templated data_ field and an int receipt_ field
  The two-arg constructor fills in the data_ and receipt_ from its args
*/
template <typename T>
struct Node{
public:
  T data_;
  Node* next_;
  int receipt_;

  Node();
  Node (T, int);
  //simple output
  friend ostream& operator<<(ostream& out, Node& n){

		out<<"D: "<<n.data_<<" rec: "<<n.receipt_<<endl;
		return out;

  }
  friend class RBag<T>;
  

  
};
//constructors, setting defaults and dropping in arguments
  template<typename T>
  Node<T>::Node(T dat, int rec){
	  data_=dat;
	  receipt_=rec;
	  
  }
  template<typename T>
  Node<T>::Node(){
	  data_=0;
	  receipt_=0;
	  
  }


/*
  RBag class. Has only a head_ to the first Node. Empty list has head_ == nullptr
  Both the random engine and uniform distribution are provided. When a random
  number is required elsewhere in the RBag, call dist_(reng_)
*/

template<typename T>
class RBag{
private:
  Node<T>* head_;
  mt19937_64 reng_;
  uniform_int_distribution<int> dist_;


public:
  RBag():head_(nullptr){};

  // rule of three
  RBag(const RBag& b);
  RBag& operator=(RBag);
  ~RBag();

  // returns nullptr if not found, else returns pointer to the Node
  // and places the found Node at the front of the RBag linked list
  Node<T>* find(long receipt){
	  Node<T> *ptr;
		for(ptr=this->head_;ptr!=nullptr;ptr=ptr->next_){
			if(ptr->next_==nullptr)
				return nullptr;
			if(ptr->next_->receipt_==receipt){
				head_=ptr->next_;
				ptr->next_=ptr->next_->next_;
				head_->next_=ptr;
				return head_;
			}
        }
        return nullptr;
	  
  }

  // Make a new Node using dat and generating a random number receipt
  // then append to the front of the RBag linked list
  long append_front(T dat){
	  if(head_ != nullptr){
		int rec = dist_(reng_);
		Node<T>* node = new Node<T>(dat,rec);
		node->next_=head_;
		head_=node;
		return rec;
  }
	else{
		int rec = dist_(reng_);
	    Node<T>* node = new Node<T>(dat,rec);
	    head_=node;
	    return rec;

		}
	}
  
  // Node already exists, append to the front of the RBag linked list
  long append_front(Node<T>* n){
	  if(head_ != nullptr){
	  n->next_=head_;
	  head_=n;
	  return n->receipt_;
  }
	else{
	    head_=n;
	    return n->receipt_;
		}
  }
  // if Node is not found, return false, else delete the found Node
  // and return true
  bool remove(long receipt){
	  //two edge cases accounted for
	  if(this->head_->next_==nullptr){
		head_=nullptr;
		return true;
	}
	  if(this->head_->receipt_==receipt){
		  this->head_=this->head_->next_;
		  return true;
	  }
	  Node<T> *ptr;
	  for(ptr=this->head_;ptr!=nullptr;ptr=ptr->next_){
				if (ptr->next_->receipt_==receipt){
					ptr->next_=ptr->next_->next_;
					return true;
				}
	  
  }
  return false;
}
  
  friend ostream& operator<<(ostream& out, RBag& b){
    	Node<T> *ptr;
		for(ptr=b.head_;ptr!=nullptr;ptr=ptr->next_){
			out<<"d: "<<ptr->data_<<" rec: "<<ptr->receipt_<<endl;
		}
		return out;
  };
};
template<typename T>
RBag<T>::~RBag(){
    Node<T>* to_del = head_;
    while (to_del != nullptr){
	head_ = head_->next_;
	delete to_del;
	to_del = head_;
    }
    head_ = nullptr;
}

template<typename T>
RBag<T>::RBag(const RBag& r){
	//if there isn't anything in, no copying over
	if(r.head_==nullptr)
		this->head_=nullptr;
		
	else{
		this->head_ = new Node<T>(r.head_->data_,r.head_->receipt_);
		Node<T>* r_ptr = r.head_->next_;
		Node<T>* new_node;
		//tail copy allows the ability to chain on w/o changing head
	    Node<T>* tail;
	    tail=head_;
	    //while loop to check until end
	    while (r_ptr != nullptr){
			new_node = new Node<T>(r_ptr->data_,r_ptr->receipt_);
			tail->next_ = new_node;
			r_ptr = r_ptr->next_;
			tail = new_node;

}
}
}
//simple constructor using the above to make life easier
template<typename T>
RBag<T>& RBag<T>::operator=(RBag r){
    RBag<T> new_bag(r);
    return new_bag;
}
#endif
