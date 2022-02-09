template<class T>
struct trivial_container
{
	typedef T 					value_type;

	typedef value_type*			pointer;
	typedef const value_type*	const_pointer;
	typedef value_type&			reference;
	typedef const value_type&	const_reference;

	typedef value_type*			iterator;
	typedef const value_type*	const_iterator;
	typedef ptrdiff_t			difference_type;
	typedef size_t				size_type;

	const_iterator begin() const { return 0; }
	const_iterator end() const { return 0; }

	iterator begin() { return 0; }
	iterator end() { return 0; }

	size_type size() const { return 0; }
	bool empty() const { return true; }
	size_type max_size() const { return 0; }

	void swap(trivial_container&) {}
};