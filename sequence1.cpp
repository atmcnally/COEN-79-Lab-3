//Angelus McNally
//COEN 79

#include "sequence1.h"
#include <math.h>
#include <cassert>

using namespace std;
using namespace coen79_lab3;
	

	sequence::sequence() {
		//Postcondition: The sequence has been initialized as an empty sequence.
		iterator = 0;
		count = 0;
		
	}


	void sequence::start() {
		iterator = 0;
	}

	void sequence::end() {
		//if there is more than one element in the array, the end is one index back from the length
		if (size() > 0) {
			iterator = size() - 1;
		} else {
			//otherwise, there are no objects and the ned is the same as the start
			start();
		}
		
	}
//      Poscondition: The iterator points to the last item in the sequence;

	void sequence::last() {
		iterator = CAPACITY - 1;
	}

	void sequence::advance() {
		//current is item
		if (is_item()) {
			if (iterator + 1 < size()) {
				iterator++;
			}
		}
	}

	void sequence::retreat() {
		if (iterator > 0) {
			iterator--;
		}
	}

	sequence::value_type sequence::operator[](int index) const {
		//Precondition: index < used
		//Postcondition: The item returned is the item stored at "index"
		//check that the index is a valid index and then return the specified item.
		assert(index < size() && index >= 0);
		return arr[index];
	}


	void sequence::insert(const value_type& entry) {
		if (size() < CAPACITY) {

			//check whether there is a current item
			if (is_item()) {
				//only one object in sequence means able to attach to front
				if (iterator == 0) {
					insert_front(entry);
				} else {
					retreat();
					attach(entry);
				}

			} else {
				//if no current item, insert at front
				insert_front(entry);
			}
		}
	}
//      Postcondition: A new copy of entry has been inserted in the sequence before the current item. If there was no current item, 
//		the new entry has been inserted at the front. In either case, the new item is now the current item of the sequence.

	// iterator = 0 doesn't mean there's an entry at arr[0]
	//i feel like this may come to bite me se i just need to make sure to check for is_item wheneever i assume i'm at the start of a sequence


	void sequence::attach(const value_type& entry) {
		if (size() < CAPACITY) {
			//get current item and insert after it
			if (is_item()) {

				//i want to insert entry at the index after iterator
				//so move everything after iterator over one space
				for (int i = size() - 1; i > iterator; i--) {
					arr[i + 1] = arr[i];
				}
				//then insert entry
				advance();
				arr[iterator] = entry;
			} else {
				//if no current item, attach to end
				end();
				//this might mean no items in list or iterator got wonky
				//iterator is last used index at this point
				//add entry into the next space
				advance();
				arr[iterator] = entry;
			}
			
			count++;
		}
	}
//      Postcondition: A new copy of entry has been inserted in the sequence  after the current item. If there was no current item, 
//		the new entry has been attached to the end. In either case, the new item is now the current item of the sequence.

	void sequence::remove_current() {
		//Postcondition: The current item has been removed from the sequence, and the item after this (if there is one) is now the current item.
		if (is_item()) {
			for (int i = iterator + 1; i < size(); i++) {
				//move everything after current back one space
				arr[i] = arr[i + 1];
			}
			
			count--;
			//make next item the current item
			advance();
		}
	}


	void sequence::insert_front(const value_type& entry) {
		//Postcondition: A new copy of entry has been inserted in the sequence at the front. The new item is now the current item of the sequence.
		if (size() < CAPACITY) {
			start();
			attach(entry);
		}
	}


	void sequence::attach_back(const value_type& entry) {
		//Postcondition: A new copy of entry has been inserted in the sequence at the back. The new item is now the current item of the sequence.
		if (size() < CAPACITY) {
			end();
			attach(entry);
			advance();
		}
	}


	void sequence::remove_front() {
		//Postcondition: The item at the front of the sequence has been removed from the sequence, and the current item points at the front of the sequence.
		start();

		if (is_item()) {
			remove_current();
		}
	}


	sequence::size_type sequence::size() const {
		//Postcondition: The return value is the number of items in the sequence.
		return count;
	}

	
	bool sequence::is_item() const {
		//Postcondition: A true return value indicates there is a valid "current" item that may be retrieved with current(). A false return value means there is no valid current item.

		if (iterator > size()) {
			return true;
		}

		return false;
	}


	sequence::value_type sequence::current() const {
		//Postcondition: Returns the item in the sequence at the current position of the iterator.
		assert(is_item());
		return arr[iterator];
	}

	double sequence::mean() const {
		int sum = 0;
		for (int i = 0; i < size(); i++) {
			sum += arr[i];
		}
		return sum / size();
	}

	double sequence::standardDeviation() const {
		double mean1 = mean();
		double stdDev = 0;

		for (int i = 0; i < size(); i++) {
			stdDev += pow(arr[i] - mean1, 2);
		}

		stdDev = sqrt(stdDev / size());

		return stdDev;
	}


//Postcondition: The sequence that is returned contains all the numbers of the sequences of lsh and rhs.

//	operator + and operator += : These operators should have the precondition that 
//	the sum of the sizes of the two sequences being added is smaller than the CAPACITY of a sequence.


//change whatever sequence you're calling this method on
void sequence::operator +=(const sequence& rhs) {
	if((rhs.size() + size()) < CAPACITY) {
		for (int i = 0; i < rhs.size(); i++) {
			arr[size() + i] = rhs[i];
		}
	}
}


sequence operator +(sequence& lhs, sequence& rhs) {
	//sum of the sizes of the two sequences being added is smaller than the CAPACITY of a sequence.

	sequence added;

	if (lhs.size() + rhs.size() < added.CAPACITY) {
		added = lhs;
		
		for (int i = 0; i < rhs.size(); i++) {
			added.attach(rhs[i]);
		}

		return added;
	}

	return added;
}

sequence::value_type summation(const sequence &s) {
	sequence::value_type sum = 0;

	for (int i = 0; i < s.size(); i++) {
		sum += s[i];
	}

	return sum;
}