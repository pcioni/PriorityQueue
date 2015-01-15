#ifndef priority_queue_h_
#define priority_queue_h_

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

template <class T>
class priority_queue {
private:
  std::vector<T> m_heap;

public:
	priority_queue() {}

	priority_queue( std::vector<T> const& values ) {
		for (int i=0; i < values.size(); ++i) {
			m_heap.push_back(values[i]);
			percolate_up(m_heap.size()-1);
		}
	}

	const T& top() const 
	{
		assert( !m_heap.empty() );
		return m_heap[0]; 
	}

	void push( const T& entry ) {
		m_heap.push_back(entry);
		percolate_up(m_heap.size()-1); //percolate up last element
	}
	
	void percolate_up(int position) {
		while(m_heap[(position - 1) / 2]) {
			if (m_heap[position] < m_heap[(position - 1) / 2]) {
				swap(m_heap, position, (position - 1) / 2);
				position = (position - 1) / 2;
			}
			else
				break;
		}
	}
	
	void percolate_down(int position) {
		while(position*2+1<m_heap.size()){
			int child;
			if (position*2+2 < m_heap.size() && m_heap[position*2+2] < m_heap[position*2+1])
				child = position*2+2;
			else 
				child = position*2+1;
			if (m_heap[child] < m_heap[position]) {
				swap(m_heap, child, position);
				position = child;
			}
			else
				break;
		}
	}
	
	void swap(vector<T>& heap, int pos_a, int pos_b) {
		T temp = heap[pos_a];
		heap[pos_a] = heap[pos_b];
		heap[pos_b] = temp;
	}


	void pop() {
		assert( !m_heap.empty() );
		m_heap[0] = m_heap.back();
		m_heap.pop_back();
		percolate_down(0);
	}
	


	int size() { return m_heap.size(); }
	bool empty() { return m_heap.empty(); }


	//  The following three functions are used for debugging.

	//  Check to see that internally the heap property is realized.
	bool check_heap( )
	{
		return this->check_heap( this->m_heap );
	}

	//  Check an external vector to see that the heap property is realized.
	bool check_heap( const std::vector<T>& heap ) {
		for (int i=0; 2*i+1 < heap.size();++i){
			if ( (heap[i] > heap[2*i+1]) || (2*i+2 < heap.size() && heap[i] > heap[2*i+2]) )
				return false;
		}
		return true;
	}

	//  A utility to print the contents of the heap.  Use it for debugging.
	void print_heap( std::ostream & ostr )
	{
		for ( unsigned int i=0; i<m_heap.size(); ++i )
			ostr << i << ": " << m_heap[i] << std::endl;
	}
  
};


template <class T> void heap_sort( vector<T> & v ) {
	if (v.size() == 0)
		return;
	priority_queue<T> pq(v);
	v.clear();
	int size = pq.size();
	while(size > 0) {
		v.push_back( pq.top() );
		pq.pop();
		--size;
	}
}

#endif
