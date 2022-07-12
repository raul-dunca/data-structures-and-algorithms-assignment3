#include "MultiMapIterator.h"
#include "MultiMap.h"


MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
	this->index = c.head;
}

TElem MultiMapIterator::getCurrent() const{
	
	if (this->valid())
		return this->col.nodes[this->index].info;
}

bool MultiMapIterator::valid() const {
	if (this->col.head!=-1  &&  this->index < this->col.sizee && this->index >= 0)
		return true;
	else
		return false;
}

void MultiMapIterator::next() {
	if (!this->valid())
		throw exception();
	else
	this->index = this->col.nodes[this->index].next;
}

void MultiMapIterator::first() {
	this->index = this->col.head;
}

