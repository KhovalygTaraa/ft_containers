#ifndef VECTOR_BOOL_HPP
# define VECTOR_BOOL_HPP
# include <iostream>
# include "type_traits.hpp"
# include "iterator.hpp"
#include <unistd.h>


namespace {

	template < typename Allocator >
	class vector < bool, Allocator >
	{
	public:
		typedef bool										T;
		typedef T											value_type;
		typedef size_t										size_type;
		typedef ptrdiff_t 									difference_type;

		typedef				Allocator						allocator_type;
		typedef typename	allocator_type::reference 		reference;
		typedef typename	allocator_type::const_reference const_reference;
		typedef typename	allocator_type::pointer 		pointer;
		typedef typename	allocator_type::const_pointer 	const_pointer;

	private:
		pointer			_array;
		size_type 		_capacity;
		size_type 		_size;
		allocator_type	_allocator;

		template<typename Type>
		class iterator_t: public ft::iterator<random_access_iterator_tag,
				typename ft::conditional<is_same<Type, const_pointer>::value, const T, T>::type,
				ptrdiff_t,
				typename ft::conditional<is_same<Type, const_pointer>::value, const T*, T*>::type,
				typename ft::conditional<is_same<Type, const_pointer>::value, const T&, T&>::type> {
		public:
			typedef typename ft::conditional<is_same<Type, const_pointer>::value, const T, T>::type		conditional_value;
			typedef typename ft::conditional<is_same<Type, const_pointer>::value, const T*, T*>::type	conditional_pointer;
			typedef typename ft::conditional<is_same<Type, const_pointer>::value, const T&, T&>::type	conditional_reference;
		private:
			conditional_pointer _ptr;
		public:
			iterator_t(): _ptr() {};
			iterator_t(conditional_pointer ptr): _ptr(ptr) {}
			virtual ~iterator_t(){};

			template<typename Iter>
			iterator_t(const iterator_t<Iter>& it) {
				_ptr = it.base();
			}

			iterator_t& operator=(const iterator_t& it){
				_ptr = it.base();
				return (*this);
			}

			conditional_pointer base() const { return (_ptr);}
			conditional_pointer operator->() const {return (_ptr);}
			conditional_reference operator*() const { return (*_ptr);}
			conditional_reference operator[](difference_type n) const {return (_ptr[n]);}

			iterator_t& operator++() {
				_ptr++;
				return (*this);
			}
			iterator_t operator++(int) {
				iterator_t tmp(*this);
				_ptr++;
				return (tmp);
			};
			iterator_t& operator--() {
				_ptr--;
				return (*this);
			}
			iterator_t operator--(int) {
				iterator_t tmp(*this);
				_ptr--;
				return (tmp);
			}

			iterator_t& operator+=(difference_type n) {
				_ptr = _ptr + n;
				return (*this);
			}

			iterator_t& operator-=(difference_type n) {
				_ptr = _ptr - n;
				return (*this);
			}

			iterator_t operator+(difference_type n) {
				iterator_t tmp(_ptr + n);
				return (tmp);
			}

			iterator_t operator-(difference_type n) {
				iterator_t tmp(_ptr - n);
				return (tmp);
			}

			difference_type operator-(const iterator_t& it) {
				return (_ptr - it.base());
			}

			bool operator==(const iterator_t& it) {return (_ptr == it.base());}
			bool operator!=(const iterator_t& it) {return (_ptr != it.base());}
			bool operator<(const iterator_t& it) {return (_ptr < it.base());}
			bool operator>(const iterator_t& it) {return (_ptr > it.base());}
			bool operator<=(const iterator_t& it) {return (!(_ptr > it.base()));}
			bool operator>=(const iterator_t& it) {return (!(_ptr < it.base()));}
			friend iterator_t operator+(difference_type n, const iterator_t& it) {
				iterator_t a(it);
				a+= n;
				return (a);
			}
		};

		template<typename I>
		void vector_helper(I first, I second, I)
		{
			_array = _allocator.allocate(first);
			for (int i = 0; i != first; i++)
				_allocator.construct(_array + i, second);
			_size = first;
			_capacity = first;
		}
		template<typename I>
		void vector_helper(I first, I second, input_iterator_tag,
						   typename ft::enable_if<is_same<typename iterator_traits<I>::iterator_category::input_iterator_tag,
						   input_iterator_tag>::value, void>::type* = NULL)
						   {
			_capacity = ft::distance(first, second);
			_size = capacity();
			_array = _allocator.allocate(_capacity);
			for(int i = 0; first != second; i++)
			{
				_allocator.construct(_array + i, *first);
				first++;
			}
						   }

						   void expand_array() {
							int m;
							size_type n;

							m = 2;
							n = _capacity;
							if (_capacity == 0)
							{
								n = 1;
								m = 1;
							}
							reserve(n * m);

							//			pointer tmp;
							//			int m;
							//
							//			m = 2;
							//			if (_capacity == 0) {
							//				_capacity = 1;
							//				m = 1;
							//			}
							//			tmp = _allocator.allocate(_capacity * m);
							//			for(int i = 0; i != _size; i++) {
							//				_allocator.construct(tmp + i, _array[i]);
							//				_allocator.destroy(_array + i);
							//			}
							//			_allocator.deallocate(_array, _capacity);
							//			_array = tmp;
							//			_capacity = _capacity * m;
						   }
	public:
		typedef iterator_t<const_pointer>					const_iterator;
		typedef iterator_t<pointer>							iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

		explicit vector(const allocator_type& alloc = allocator_type()):
		_array(), _capacity(), _size(), _allocator(alloc){};

		explicit vector(size_type n, const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type()): _allocator(alloc)
						{
			_array = _allocator.allocate(n);
			for (size_type i = 0; i != n; i++) {
				_allocator.construct(_array + i, val);
			}

			_size = n;
			_capacity = n;
						};

		template<typename InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()): _allocator(alloc)
		{
			_size = 0;
			_capacity = 0;
			vector_helper(first, last,
						  typename ft::conditional<is_integral<InputIterator>::value, InputIterator, input_iterator_tag>::type());
		};

		vector(const vector& x): _allocator(x.get_allocator())
		{
			_size = x.size();
			_capacity = x.capacity();
			_array = _allocator.allocate(_capacity);

			for(int i = 0; i != _size; i++)
				_allocator.construct(_array + i, x[i]);
		}
		~vector(){
			for (int i = 0; i != _size; i++)
				_allocator.destroy(_array + i);
			_allocator.deallocate(_array, _capacity);
		};
		//// Iterators
		iterator begin() {
			return(_array);
		};

		const_iterator begin() const {
			return (_array);
		};

		iterator end() {
			return(_array + _size);
		};

		const_iterator end() const {
			return (_array + _size);
		};

		reverse_iterator rbegin() {
			iterator it(_array + _size);
			reverse_iterator rit(it);
			return (rit);
		}

		const_reverse_iterator rbegin() const {
			const_iterator it(_array + _size);
			const_reverse_iterator rit(it);
			return (rit);
		}

		reverse_iterator rend() {
			iterator it(_array);
			reverse_iterator rit(it);
			return (rit);
		}
		const_reverse_iterator rend() const {
			const_iterator it(_array);
			const_reverse_iterator rit(it);
			return (rit);
		}


		//// Capacity
		size_type size() const {
			return (_size);
		}

		size_type max_size() const {
			size_type a;

			a = sizeof(value_type);
			if (a == 1)
				a = 2;
			return (std::numeric_limits<size_type>::max() / a);
		}


		void resize(size_type n, value_type val = value_type()) {
			iterator it;
			pointer tmp;
			size_type push;

			push = n - _size;
			if (n < _size)
			{
				it = begin();
				for(int i = 0; i != n; i++) {
					it++;
				}
				erase(it, end());
			}
			else if (n > _size)
			{
				if (n > _capacity * 2)
					reserve(n);
				for(size_type i = 0; i != push; i++)
					push_back(val);
			}
		}

		size_type capacity() const {
			return(_capacity);
		};

		bool empty() const {
			return (!_size);
		}

		void reserve(size_type n) {
			pointer tmp;
			size_type size;

			if (n > _capacity) {
				tmp = _allocator.allocate(n);
				for (int i = 0; i != _size; ++i) {
					_allocator.construct(tmp + i, _array[i]);
				}
				size = _size;
				clear();
				_size = size;
				_allocator.deallocate(_array, _capacity);
				_array = tmp;
				_capacity = n;
			}
		}

		//// Element_access
		reference operator[](size_type n) {
			return(_array[n]);
		}

		const_reference operator[](size_type n) const {
			return (_array[n]);
		}

		reference at(size_type n) {
			if (n > _size)
				throw std::out_of_range("out of range");
			else
				return (_array[n]);
		}

		const_reference at(size_type n) const {
			if (n > _size)
				throw std::out_of_range("out of range");
			else
				return (_array[n]);
		}

		reference front() {
			return (*_array);
		}

		const_reference front() const {
			return (*_array);
		}

		reference back() {
			return (*(_array + _size));
		}

		const_reference back() const {
			return (*(_array + _size));
		}

		//// Modifiers
		template<typename InputIterator>
		void assign(InputIterator first, InputIterator second,
					typename enable_if<is_same<typename iterator_traits<InputIterator>::iterator_category::input_iterator_tag,
					input_iterator_tag>::value, void>::type* = NULL) {
			size_type n;

			n = ft::distance(first, second);
			clear();
			if (n <= _capacity) {
				for (size_type i = 0; first != second; i++)
				{
					_allocator.construct(_array + i, *first);
					first++;
				}
			}
			else {
				_allocator.deallocate(_array, _capacity);
				_array = _allocator.allocate(n);
				for (size_type i = 0; first != second; i++)
				{
					_allocator.construct(_array + i, *first);
					first++;
				}
				_capacity = n;
			}
			_size = n;
		}

		void assign(size_type n, const value_type& val) {
			clear();
			if (n <= _capacity)
			{
				for (size_type i = 0; i != n; i++) {
					_allocator.construct(_array + i, val);
				}
			}
			else
			{
				_allocator.deallocate(_array, _capacity);
				_array = _allocator.allocate(n);
				for (size_type i = 0; i != n; i++) {
					_allocator.construct(_array + i, val);
				}
				_capacity = n;
			}
			_size = n;
		}

		void push_back (const value_type& val) {
			if (_size < _capacity)
			{
				_array[_size] = val;
			}
			else
			{
				expand_array();
				_array[_size] = val;
			}
			_size++;
		}

		void pop_back() {
			erase(--end(), end());
			_size--;
		}

		iterator insert(iterator position, const value_type& val) {
			iterator pos;
			size_type d;

			d = ft::distance(begin(), position);
			if (_size >= _capacity)
				expand_array();
			pos = begin() + d;

			for (iterator it = end(); it != pos; it--)
				it[0] = it[-1];
			*pos = val;
			_size++;
			return (pos);
		}

		void insert(iterator position, size_type n, const value_type& val) {
			iterator tmp;
			size_type d;

			d = ft::distance(begin(), position);
			if (n + _size > _capacity * 2)
				reserve(n);
			tmp = begin() + d;
			for (size_type i = 0; i != n; i++)
				tmp = insert(tmp, val);
		}

		template<typename InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last,
					typename enable_if<is_same<typename iterator_traits<InputIterator>::iterator_category::input_iterator_tag,
					input_iterator_tag>::value, void>::type* = NULL) {
			iterator tmp;
			iterator tmp_first;
			iterator tmp_last;
			size_type insert_pos = 0;
			size_type first_pos = 0;
			size_type last_pos = 0;
			size_type n;
			insert_pos = ft::distance(begin(), position);
			n = ft::distance(first, last);
			if (last >= position) {
				first_pos = ft::distance(begin(), first);
				last_pos = ft::distance(begin(), last);
			}
			if (n + _size > _capacity * 2)
				reserve(n);
			tmp = begin() + insert_pos;
			tmp_first = begin() + first_pos;
			tmp_last = begin() + last_pos - 1;
			if (tmp_last >= tmp) {
				for(InputIterator it = tmp_last; it >= tmp_first; it--)
					tmp = insert(tmp, *it);
			}
			else {
				for(InputIterator it = last - 1; it >= first; it--)
					tmp = insert(tmp, *it);
			}
		}

		iterator erase(iterator position) {
			erase(position, position + 1);
			return (position);
		}

		iterator erase(iterator first, iterator last) {
			iterator tmp(first);
			iterator tmp_for_end(end());

			while (first != last)
			{
				_allocator.destroy(first.base());
				_size--;
				first++;
			}
			if (_size)
				for(iterator f = first; f != tmp_for_end; f++) {
					*tmp = *f;
					tmp++;
				}
			if (last == tmp_for_end)
				return (end());
			return (last);
		}

		void clear() {
			erase(begin(), end());
		}

		//// Allocator
		allocator_type get_allocator() const {
			return (_allocator);
		}
	};
}

#endif