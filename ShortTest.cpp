#include "ShortTest.h"
#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <assert.h>
#include <vector>
#include<iostream>

void testAll() {



	MultiMap t1;
	MultiMap t2;

	t1.add(1, 2);
	t1.add(2, 3);
	t1.add(1, 4);
	t1.add(5, 6);

	t2.add(1, 5);
	t2.add(4, 3);
	//t2.add(5, 2);
	assert(t1.updateValues(t2)==2);
	t2.add(5, 2);
	assert(t1.updateValues(t2) == 3);




	MultiMap m;
	m.add(1, 100);
	m.add(2, 200);
	m.add(3, 300);
	m.add(1, 500);
	


	vector<TValue> vr;
	vr = m.search(6);
	assert(vr.size() == 0);

	m.add(2, 600);

	
	vr = m.search(6);
	assert(vr.size() == 0);

	m.add(4, 800);

	assert(m.size() == 6);

	assert(m.remove(5, 600) == false);
	assert(m.remove(1, 500) == true);

	assert(m.size() == 5);

    vector<TValue> v;
	v=m.search(6);
	assert(v.size()==0);

	v=m.search(1);
	assert(v.size()==1);

	assert(m.isEmpty() == false);

	MultiMapIterator im = m.iterator();
	assert(im.valid() == true);
	while (im.valid()) {
		im.getCurrent();
		im.next();
	}
	assert(im.valid() == false);
	im.first();
	assert(im.valid() == true);
}
