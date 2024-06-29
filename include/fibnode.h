#ifndef FIB_NODE_H
#define FIB_NODE_H

#include <cstddef>
#include <cstdint>
#include <list>

class FibNode{
private:
	int32_t m_Key;
	bool m_Mark;
	size_t m_Degree;
	FibNode* m_Parent, *m_Child;
	std::list<FibNode*> m_ChildList;
public:
	FibNode(int32_t key);
	~FibNode();
	void add_child_to_list(FibNode* node);
	size_t get_degree() const;
	int32_t get_key() const;
	std::list<FibNode*>& get_child_list();
	FibNode* get_parent() const;
	FibNode* get_child() const;
	uint32_t marked_node_cout() const;
	bool get_mark() const;
	void set_parent(FibNode* node);
	void set_child(FibNode* node);
	void set_mark(bool mark);
	void set_key(int32_t value);
	void increase_degree(int32_t deg);
};

#endif
