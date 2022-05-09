/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 18:24:58 by swquinc           #+#    #+#             */
/*   Updated: 2021/04/30 21:40:47 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
# define LIST_HPP
# include <iostream>

/*
**
**	Данный контейнер состоит из 4 конструкторов
**	1) Конструктор по умолчанию
**	2) Конструктор копирования
**	3) Конструктор заполнения - это конструктор, который принимает два параметра. Первый параметр - это количество выделяемой памяти. Второй параеметр - это значение, которым будет заполнена каждая ячейка выделенной памяти.
**	4) Конструктор диапaзона - конструктор который принимает диапозон значений в виде двух итераторов.
**
*/

/*
** ПЛАН:
** 1) объявить все типы членов, понять для чего -> для совмещение с STL algoritmh
** 2) объявить все функции, понять для чего они
** 3) Написать функции
** 4) Поиск ошибок
*/

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class list
	{
		private:
			/*********************************************************/
			/****************** list data structure ******************/
			/*********************************************************/
			 template<class N>
			class Node
			{
				public:
					Node	*next;
					Node	*prev;
					N		cont;

					explicit Node(N cont)
					{
						this->cont = cont;
						this->next = nullptr;
						this->prev = nullptr;
					};
					~Node() {};
				private:
					Node() {};
					Node(Node const &n) {};
					Node	&operator=(Node const &n) {};
			};

			/****************************************************/
			/****************** private fields ******************/
			/****************************************************/
			typedef Node<T> node;
			node	*_bilist;
			node	*_bilist_tail;
			size_t	_bilist_size;

			/****************************************************/
			/********************* iterator *********************/
			/****************************************************/
			template<class D, class Pointer = D*, class Reference = D&>
			struct Iterator
			{
				typedef 			D							value_type;
				typedef 			Pointer						pointer;
				typedef 			Reference					reference;

				Iterator() {this->ptr = nullptr;};
				explicit Iterator(node *ptr) {this->ptr = ptr;};
				Iterator(const Iterator<value_type> &i) {
					this->ptr = i.ptr;
				};
				~Iterator() {};

				Iterator	&operator=(const Iterator &i) {
					if (this == &i)
						return (*this);
					this->ptr = i.ptr;
					return (*this);
				};
				reference	operator*() const {return(ptr->cont);};
				bool 		operator==(const Iterator &l) const {return (l.ptr == ptr);};
				bool 		operator!=(const Iterator &l) const {return (l.ptr != ptr);};
				pointer 	operator->() const {return(ptr);};
				Iterator	&operator++() {
					ptr = ptr->next;
					return (*this);
				};
				Iterator	operator++(int) {
					iterator tmp(*this);
					ptr = ptr->next;
					return (tmp);
				};

				Iterator	&operator--() {
					ptr = ptr->prev;
					return (*this);
				};
				Iterator	operator--(int) {
					iterator tmp(*this);
					ptr = ptr->prev;
					return (tmp);
				};
			private:
				node	*ptr;
			};

		public: /* определение функций и перегрузка операторов */
			/****************************************************/
			/****************** public fields ******************/
			/****************************************************/
			typedef 			T 								value_type;
			typedef 			Alloc							allocator_type;
			typedef typename 	allocator_type::reference		reference;
			typedef typename 	allocator_type::const_reference	const_reference;
			typedef typename 	allocator_type::pointer			pointer;
			typedef typename 	allocator_type::const_pointer	const_pointer;
			typedef typename 	allocator_type::size_type		size_type;
		    typedef 			Iterator<value_type>			iterator;
		    typedef 			Iterator<const value_type>		const_iterator;

			/************************************************************/
			/********** Constructors, Destructor and operator= **********/
			/************************************************************/

			explicit list() /* Coplien's form 1 */
			{
				_bilist = nullptr;
				push_back(value_type());
				_bilist_size = 0;
				_bilist_tail = _bilist;
				_bilist_tail->prev = _bilist_tail;
				_bilist_tail->next = _bilist_tail;
			};

			list(list const &l) /* Coplien's form 2 */
			{
				_bilist = nullptr;
				node *tmp;
				push_back(value_type());
				_bilist_tail = _bilist;
				_bilist_tail->prev = _bilist_tail;
				_bilist_tail->next = _bilist_tail;

				tmp = l._bilist;
				while (tmp->next != l._bilist_tail) {
					push_back(tmp->cont);
					tmp = tmp->next;
				}
				push_back(tmp->cont);
				_bilist_size = l._bilist_size;
			};

			explicit list(size_type n, const value_type& val = value_type())
			{
				_bilist = nullptr;
				push_back(val);
				_bilist_size = 0;
				_bilist_tail = _bilist;
				_bilist_tail->prev = _bilist_tail;
				_bilist_tail->next = _bilist_tail;
				for (int i = 0; i != n; i++) {
					push_back(val);
				}
			};

			template<class InputIterator>
			list(InputIterator first, InputIterator second)
			{
				_bilist = nullptr;
				push_back(value_type());
				_bilist_size = 0;
				_bilist_tail = _bilist;
				_bilist_tail->prev = _bilist_tail;
				_bilist_tail->next = _bilist_tail;
				while (first != second) {
					push_back(*first);
					first++;
				}
			};

//			template<>
//			list<int>(int n, int val)
//			{
//				_bilist = nullptr;
//				push_back(val);
//				_bilist_size = 0;
//				_bilist_tail = _bilist;
//				_bilist_tail->prev = _bilist_tail;
//				_bilist_tail->next = _bilist_tail;
//				for (int i = 0; i != n; i++) {
//						push_back(val);
//					}
//			};
//
//			template<>
//			list<long>(long n, long val)
//			{
//				_bilist = nullptr;
//				push_back(val);
//				_bilist_size = 0;
//				_bilist_tail = _bilist;
//				_bilist_tail->prev = _bilist_tail;
//				_bilist_tail->next = _bilist_tail;
//				for (int i = 0; i != n; i++) {
//						push_back(val);
//					}
//			};
//
//			template<>
//			list<long long>(long long n, long long val)
//			{
//				_bilist = nullptr;
//				push_back(val);
//				_bilist_size = 0;
//				_bilist_tail = _bilist;
//				_bilist_tail->prev = _bilist_tail;
//				_bilist_tail->next = _bilist_tail;
//				for (int i = 0; i != n; i++) {
//						push_back(val);
//					}
//			};
//
//			template<>
//			list<short>(short n, short val)
//			{
//				_bilist = nullptr;
//				push_back(val);
//				_bilist_size = 0;
//				_bilist_tail = _bilist;
//				_bilist_tail->prev = _bilist_tail;
//				_bilist_tail->next = _bilist_tail;
//				for (int i = 0; i != n; i++) {
//						push_back(val);
//					}
//			};
//
//			template<>
//			list<unsigned long long>(unsigned long long n, unsigned long long val)
//			{
//				_bilist = nullptr;
//				push_back(val);
//				_bilist_size = 0;
//				_bilist_tail = _bilist;
//				_bilist_tail->prev = _bilist_tail;
//				_bilist_tail->next = _bilist_tail;
//				for (int i = 0; i != n; i++) {
//						push_back(val);
//					}
//			};
//
//			template<>
//			list<unsigned short int>(unsigned short int n, unsigned short int val)
//			{
//				_bilist = nullptr;
//				push_back(val);
//				_bilist_size = 0;
//				_bilist_tail = _bilist;
//				_bilist_tail->prev = _bilist_tail;
//				_bilist_tail->next = _bilist_tail;
//				for (int i = 0; i != n; i++) {
//						push_back(val);
//					}
//			};
//
//			template<>
//			list<unsigned int>(unsigned int n, unsigned int val)
//			{
//				_bilist = nullptr;
//				push_back(val);
//				_bilist_size = 0;
//				_bilist_tail = _bilist;
//				_bilist_tail->prev = _bilist_tail;
//				_bilist_tail->next = _bilist_tail;
//				for (int i = 0; i != n; i++) {
//						push_back(val);
//					}
//			};
//
//			template<>
//			list<unsigned int>(unsigned int n, unsigned int val)
//			{
//				_bilist = nullptr;
//				push_back(val);
//				_bilist_size = 0;
//				_bilist_tail = _bilist;
//				_bilist_tail->prev = _bilist_tail;
//				_bilist_tail->next = _bilist_tail;
//				for (int i = 0; i != n; i++) {
//						push_back(val);
//					}
//			};

			~list() /* Coplien's form 3 */
			{
			    node *tmp;

				while (_bilist != _bilist_tail)
                {
				    tmp = _bilist->next;
				    delete _bilist;
				    _bilist = tmp;
                }
				delete _bilist_tail;
			};

			list	&operator=(list const &l) /* Coplien's form 4 */
			{
				node *tmp;

				if (&l == this)
					return (*this);
				while (_bilist != nullptr)
				{
					tmp = _bilist->next;
					delete _bilist;
					_bilist = tmp;
				}
				_bilist = nullptr;
				_bilist_size = l._bilist_size;
				tmp = l._bilist;
				while (tmp->next != nullptr) {
					push_back(l._bilist->cont);
					tmp = tmp->next;
				}
				push_back(l._bilist->cont);
				_bilist_tail = tmp;
				return (*this);
			};

			/***********************************************/
			/****************** Iterators ******************/
			/***********************************************/

			iterator	begin()
			{
				_bilist_tail->cont = _bilist_size;
				iterator res(_bilist);
				return (res);
			};

			iterator	end()
            {
				_bilist_tail->cont = _bilist_size;
			    iterator	res1(_bilist_tail);
                return (res1);
            };

			/**********************************************/
			/****************** Capacity ******************/
			/**********************************************/

			size_type	size() const
			{
				node	*tmp;
				return (_bilist_size);
			};

			size_type	max_size() const {
				return (std::numeric_limits<size_type>::max() / sizeof(node));
			};

			bool	empty() {
				if (size() == 0)
					return (true);
				return  (false);
			};

			/**********************************************/
			/*************** Element access ***************/
			/**********************************************/

			reference	front()
			{
				return (_bilist->cont);
			};

			reference	back()
			{
				node	*res;
				if (_bilist->prev)
					res = _bilist_tail->prev;
				else
					res = _bilist;
				return (res->cont);
			};

			/***********************************************/
			/****************** Modifiers ******************/
			/***********************************************/

			template <class InputIterator>
			void 	assign(InputIterator first, InputIterator second)
			{
				clear();
				while (first != second)
				{
					push_back(*first);
					first++;
				}
			};

			template<>
			void	assign<long>(long n, long val)
			{
				clear();
				for (int i = 0; n != i; i++) {

					push_back(val);

				}
			};

			template<>
			void	assign<long long>(long long n, long long val)
			{
				clear();
				for (int i = 0; n != i; i++) {

					push_back(val);

				}
			};

			template<>
			void	assign<int>(int n, int val)
			{
				clear();
				for (int i = 0; n != i; i++) {
					push_back(val);
				}
			};

			template<>
			void	assign<short>(short n, short val)
			{
				clear();
				for (int i = 0; n != i; i++) {

					push_back(val);

				}
			};

			template<>
			void	assign<unsigned long long>(unsigned long long n, unsigned long long val)
			{
				clear();
				for (int i = 0; n != i; i++) {
					push_back(val);
				}
			};

			void	assign(size_type n, const value_type& val)
			{
				clear();
				for (int i = 0; n != i; i++) {
					push_back(val);
				}
			};

			void	push_front(const value_type &var) {
				node	*new_list = new node(var);
				if (_bilist)
				{
					if (_bilist != _bilist_tail) {
						new_list->next = _bilist_tail;
						new_list->prev = _bilist_tail->prev;
						_bilist_tail->prev = new_list;
					}
					else {
						_bilist = new_list;
						_bilist_tail->prev = _bilist;
						_bilist->prev = _bilist_tail;
						_bilist->next = _bilist_tail;
					}
					_bilist_tail->next = _bilist;
					_bilist->prev = _bilist_tail;
				}
				else {
					_bilist = new_list;
				}
				_bilist_size++;
			};

			void	push_back(const value_type &var) {
				node	*new_list = new node(var);
				node	*tmp;

				if (_bilist)
				{
					tmp = _bilist;
					_bilist = new_list;
					if (tmp != _bilist_tail) {
						tmp->prev = _bilist;
						_bilist->next = tmp;
					}
					else {
						_bilist_tail->prev = _bilist;
						_bilist->next = _bilist_tail;
					}
					_bilist_tail->next = _bilist;
					_bilist->prev = _bilist_tail;
				}
				else {
					_bilist = new_list;
				}
				_bilist_size++;
			};

			void	pop_back() {
				node *tmp;

				_bilist_size--;
				if (size() == 0)
					delete tmp;
				else if (size() == 1){
					delete _bilist_tail->prev;
					_bilist = _bilist_tail;
					_bilist->prev = nullptr;
					return ;
				}
				tmp = _bilist_tail->prev->prev;
				tmp->next = _bilist_tail;
				delete _bilist_tail->prev;
				_bilist_tail->prev = tmp;
			};

			void	pop_front() {
				node *tmp;

				_bilist_size--;
				if (size() == 0)
					delete tmp;
				else if (size() == 1) {
					tmp = _bilist;
					_bilist = _bilist_tail;
					delete tmp;
					_bilist->prev = nullptr;
					_bilist->next = nullptr;
					return ;
				}
				tmp = _bilist;
				_bilist = _bilist->next;
				_bilist->prev = nullptr;
				delete tmp;
			};

			iterator insert(iterator position, const value_type& val)
			{
				node *curr = position.operator->();
				node *newest = new node(val);

				curr->prev->next = newest;
			};

			void	insert(iterator position, size_type n, const value_type& val)
			{
				for (int i = 0; i != n; i++)
				{
					*position = val;
					position++;
				}
			};

			void clear() {
				node *tmp;

				while (_bilist != nullptr)
				{
					tmp = _bilist->next;
					delete _bilist;
					_bilist = tmp;
				}
				_bilist = nullptr;
				push_back(value_type());
				_bilist_tail = _bilist;
			};
			/************************************************/
			/****************** Operations ******************/
			/************************************************/
		
	};
}

#endif