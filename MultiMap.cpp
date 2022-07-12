#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>


using namespace std;
//FIRSTREE?

MultiMap::MultiMap() {
	this->sizee = 0;
	this->head = -1;
	this->tail = -1;
	this->firstFree = 0;
	this->cap = 10;
	this->nodes = new Node[this->cap];
}

//Theta(1)

void MultiMap::add(TKey c, TValue v) {


	if (this->sizee == this->cap)
	{
		//resize
		this->cap *= 2;


		Node* new_nodes = new Node[this->cap];
		for (int i = 0; i < this->sizee; i++)
		{
			new_nodes[i] = this->nodes[i];

		}

		delete[] this->nodes;

		this->nodes = new_nodes;
	}

	if (this->head == -1 and this->tail == -1) //add first element
	{
		this->head = 0;
		this->tail = 0;

		this->nodes[this->sizee].info.first = c;
		this->nodes[this->sizee].info.second = v;
		this->nodes[this->sizee].next = -1;
		this->nodes[this->sizee].previous = -1;
		this->sizee += 1;
	}
	else
	{

		int it = 0;
		bool verif = false;
		verif = false;

		for (int i = 0; i < this->sizee; i++) {
			if (this->nodes[i].info.first == c)
			{
				verif = true;
			}
		}
		

		if (verif == true) { //if we have this key already we add after it
			int index = 0;
			int index_prev = 0;
			Node current = this->nodes[this->tail];
			Node current_prev = this->nodes[this->head];
			while (current.info.first != c and current.previous != -1)
			{
				if (current.previous == -1)
					index = 0;
				else
					index = this->nodes[current.previous].next;
				current = this->nodes[current.previous];
				//index--;

			}
			if (current.previous == -1)
				index = 0;
			else
				index = this->nodes[current.previous].next;
			current_prev = current;
			while (current_prev.info.first == c and current_prev.next != -1)
			{
				if (current_prev.next == -1)
					index_prev = this->tail;
				else
					index_prev = this->nodes[current_prev.next].previous;
				current_prev = this->nodes[current_prev.next];
				//index_prev=this->nodes[current_prev.next].previous;

			}
			if (current_prev.next == -1)
				index_prev = this->tail;
			else
				index_prev = this->nodes[current_prev.next].previous;
			

			if (index == index_prev) //case where we need to add at the end and we already have the key
			{
				this->nodes[this->sizee].previous = this->tail;
				this->nodes[this->tail].next = this->sizee;
				this->nodes[this->sizee].info.first = c;
				this->nodes[this->sizee].info.second = v;
				this->nodes[this->sizee].next = -1;
				this->tail = this->sizee;
				this->sizee++;
			}
			else //case where we have the key but we need to add between 2 elements
			{
				this->nodes[this->sizee].previous = this->nodes[index_prev].previous;

				this->nodes[index_prev].previous = this->sizee;

				this->nodes[this->sizee].next = current.next;
				this->nodes[index].next = this->sizee;
				this->nodes[this->sizee].info.first = c;
				this->nodes[this->sizee].info.second = v;
				this->sizee++;
			}

		}
		else if (verif == false) {			//add to the end

			
			
			this->nodes[this->sizee].previous = this->tail;
			this->nodes[this->tail].next = this->sizee;
			this->nodes[this->sizee].info.first = c;
			this->nodes[this->sizee].info.second = v;
			this->nodes[this->sizee].next = -1;
			this->tail = this->sizee;
			this->sizee++;
		}


	}
}
//BC: Theta(1)
//WC: Theta(n)
//AC: O(n)
		


bool MultiMap::remove(TKey c, TValue v) {
	
	bool check=false;
	Node current;
	int pos_n=-1,pos_p=-1;
	current = this->nodes[this->head];
	int it = this->sizee - 1;
	Node l = this->nodes[this->sizee-1];
	for (int i = 0; i < this->sizee; i++)
	{
		if (this->nodes[i].info.first == c and this->nodes[i].info.second == v)
			check = true;
	}
	if (check == false)
		return false;


	
	//look for the index of the element we want to delete
	while (!(this->nodes[it].info.first == c and this->nodes[it].info.second == v))
	{
		it--;
	}
	
	//get the index of nodes that contains the element that will be removed on next and prev
	for (int i = 0; i < this->sizee; i++)
	{
			if (this->nodes[i].next == it)
			{
				pos_n = i;
			}
			if (this->nodes[i].previous == it)
				pos_p = i;
	}
		if (pos_n != -1)
		{
			this->nodes[pos_n].next = this->nodes[it].next;
		}
		if (pos_p != -1)
		{
			this->nodes[pos_p].previous = this->nodes[it].previous;
		}

		if (pos_p == -1 and pos_n != -1)//remove head
		{
			this->head = pos_n;
		}
		if (pos_p != -1 and pos_n == -1)
		{
			this->tail = pos_p; //DDDDD
		}


		Node* newelem=new Node[this->cap];
		//copy the list in a new one with correct indexis
		for (int i = 0; i < it; i++) {
			newelem[i] = this->nodes[i];
		}
		int i = it;
		while (i < this->sizee - 1) {
			newelem[i] = this->nodes[i + 1];
			i++;
		}
		for (i = 0; i < this->sizee - 1; i++)
		{
			if (newelem[i].next > it)
				newelem[i].next--;
			if (newelem[i].previous > it)
				newelem[i].previous--;
		}
		this->sizee--;
		if (this->sizee == 0)
		{
			this->head = -1;
			this->tail = -1;
		}
		delete[] this->nodes;
		this->nodes = newelem;
		return true;
	
}
//Theta(n)

vector<TValue> MultiMap::search(TKey c) const {
	
	Node current;
	vector<TValue> v;
	if (this->isEmpty() == true)
		return v;
	current = this->nodes[this->head];
	if (current.info.first == c and this->size()==1)
	{
		v.push_back(current.info.second);
		return v;
	}
	while (current.info.first != c and current.next!=-1)
	{
		current = this->nodes[current.next];
	}
	while (current.info.first == c  and current.next != -1)
	{
		v.push_back(current.info.second);
		current = this->nodes[current.next];
	}
	if( current.info.first == c )
		v.push_back(current.info.second);
	return v;
}
//BC: Theta(1)
//WC: Theta(n) (n  nr of values)
//AC: O(n)


int MultiMap::size() const {
	
	return this->sizee;
}
//Theta(1)

bool MultiMap::isEmpty() const {
	
	if (this->sizee != 0)
		return false;
	else
		return true;
}
//Theta(1)


MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}


MultiMap::~MultiMap() {
	delete[] this->nodes;
}
//Theta(1)

int MultiMap::updateValues(MultiMap& m)
{
	int k = 0;
	for (int i = 0; i < m.size(); i++)
	{
		for (int j = 0; j < this->size(); j++)
		{
			if (m.nodes[i].info.first == this->nodes[j].info.first)
			{
				

				this->nodes[j].info.second = m.nodes[i].info.second;
				k++;

			}

		}
	}
	return k;
}