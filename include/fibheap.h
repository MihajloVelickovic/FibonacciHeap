#ifndef FIB_HEAP_H
#define FIB_HEAP_H

#include <cstdint>
#include "fibnode.h"

class FibHeap{
private:
	FibNode* m_Min;
	size_t m_Size;
	std::list<FibNode*> m_Roots;

public:
	FibHeap();
	~FibHeap();
	void delete_heap();
	void insert(int32_t element_to_insert);
	void merge(FibHeap* heap_to_merge);
	int32_t extract_min();
	uint32_t potential() const;
	void decrese_key(int32_t value, int32_t new_value);
	void delete_key(int32_t value);
	bool is_empty() const;
	size_t get_size() const;
	int32_t find_min() const;
	FibNode* find_node(int32_t value) const;

private:
	void cut(FibNode* child, FibNode* parent);	
	void cascading_cut(FibNode* node);
	FibNode* find_node_rec(FibNode* node, uint32_t value) const;
	void consolidate();	
	void link(FibNode* first, FibNode* second);
	uint32_t tree_count() const;
	uint32_t marked_node_count() const;
};

#endif
