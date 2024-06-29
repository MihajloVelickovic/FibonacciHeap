#include <cmath>
#include <algorithm>
#include "fibheap.h"

FibHeap::FibHeap()
	:m_Min(nullptr), m_Size(0), m_Roots(std::list<FibNode*>()){}

FibHeap::~FibHeap(){
	delete_heap();
}

void FibHeap::delete_heap(){
	while(m_Size > 0)
		extract_min();
}

void FibHeap::insert(int32_t element_to_insert)
{

    auto new_node = new FibNode(element_to_insert);
	
	m_Roots.push_back(new_node);

	if(!m_Min || new_node->get_key() < m_Min->get_key()){
		m_Min = new_node;
	}
		
	++m_Size;
}

void FibHeap::merge(FibHeap* heap_to_merge){
	
	m_Roots.insert(m_Roots.end(), heap_to_merge->m_Roots.begin(), heap_to_merge->m_Roots.end());

	if(!m_Min || (heap_to_merge->m_Min && heap_to_merge->m_Min->get_key() < m_Min->get_key()))
		m_Min = heap_to_merge->m_Min;

	m_Size += heap_to_merge->m_Size;

	heap_to_merge->m_Roots.clear();
	heap_to_merge->m_Min = nullptr;
	heap_to_merge->m_Size = 0;

}

int32_t FibHeap::extract_min(){

	if(m_Size == 0 || !m_Min)
		return std::numeric_limits<int32_t>::min();

	auto extracted_min = m_Min;
	
		
	for(auto child: extracted_min->get_child_list()){
		m_Roots.push_back(child);
		child->set_parent(nullptr);
	}

	m_Roots.remove(extracted_min);
		
	consolidate();
	
	--m_Size;
	auto key = extracted_min->get_key();
	delete extracted_min;
	return key;

}

uint32_t FibHeap::potential() const{
	return tree_count() + 2 * marked_node_count();
}

void FibHeap::decrese_key(int32_t value, int32_t new_value){
	auto node_to_decrease = find_node(value);
	if(!node_to_decrease)
		return;

	if(new_value > node_to_decrease->get_key())
		return;

	node_to_decrease->set_key(new_value);

	auto parent = node_to_decrease->get_parent();
	if(parent && node_to_decrease->get_key() < parent->get_key()){
		cut(node_to_decrease, parent);
		cascading_cut(parent);
	}

	if(node_to_decrease->get_key() < m_Min->get_key())
		m_Min = node_to_decrease;

}

void FibHeap::delete_key(int32_t value){

	decrese_key(value, std::numeric_limits<int32_t>::min());
	extract_min();

}

bool FibHeap::is_empty() const{
    return m_Size == 0 ? true : false;
}

int32_t FibHeap::find_min() const{
    return m_Min->get_key();
}

FibNode* FibHeap::find_node_rec(FibNode* node, uint32_t value) const{
	
	for(auto child: node->get_child_list()){
		
		if(node->get_key() == value)
			return node;	
		
		auto temp = child;
		do{
			auto found = find_node_rec(temp, value);
			if(found)
				return found;	
		
		}while(temp != child);
	
	}

	return nullptr;

}

FibNode* FibHeap::find_node(int32_t value) const{
	
	for(auto node: m_Roots){
		
		if(node->get_key() == value)
			return node;

		auto found = find_node_rec(node, value);
		if(found)
			return found;
	
	}

	return nullptr;

}

void FibHeap::consolidate(){

	int32_t max_degree = (std::log(m_Size)/std::log(2)) + 1;
	
	if(max_degree <= 0)
		return;

	FibNode* helper_array[max_degree];

	for(size_t i=0; i<max_degree; ++i)
		helper_array[i] = nullptr;

	auto helper_list = m_Roots;

	for(auto root: helper_list){

		auto root_deg = root->get_degree();
		
		while(helper_array[root_deg]){
			
			auto helper_node = helper_array[root_deg];
			if(root->get_key() > helper_node->get_key()){
				std::swap(root, helper_node);
			}
			
			link(helper_node, root);
			helper_array[root_deg++] = nullptr;
		
		}

		helper_array[root_deg] = root;

	}

	m_Min = nullptr;

	for(size_t i=0; i<max_degree; ++i){
		if(helper_array[i]){
			
			if(std::find(m_Roots.begin(), m_Roots.end(), helper_array[i]) == m_Roots.end())
				m_Roots.push_back(helper_array[i]);	
			
			if(!m_Min || helper_array[i]->get_key() < m_Min->get_key())
				m_Min = helper_array[i];
		
		}	
	}

}

void FibHeap::link(FibNode* first, FibNode* second){
	
	m_Roots.remove(first);

	second->add_child_to_list(first);
	second->set_child(first);	
	second->increase_degree(1);
	
	first->set_parent(second);
	first->set_mark(false);

}

uint32_t FibHeap::tree_count() const{
	return m_Roots.size();
}

uint32_t FibHeap::marked_node_count() const{
	
	uint32_t count = 0;
	
	for(auto root: m_Roots)
		count += root->marked_node_cout();
	
	return count;

}

void FibHeap::cut(FibNode* child, FibNode* parent){

	if(!parent || !child || child->get_parent() != parent)
		return;

	parent->get_child_list().remove(child);
	parent->increase_degree(-1);
	
	m_Roots.push_back(child);
	
	child->set_parent(nullptr);
	child->set_mark(false);

}

void FibHeap::cascading_cut(FibNode* node){
 	
	auto parent = node->get_parent();
	
	if(parent){
		if(node->get_mark()){
			cut(node, parent);
			cascading_cut(parent);
		}
		else
			node->set_mark(true);
	}

}

size_t FibHeap::get_size() const{
	return m_Size;
}
