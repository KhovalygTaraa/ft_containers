/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 19:47:16 by swquinc           #+#    #+#             */
/*   Updated: 2021/08/14 19:47:17 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP
# include <iostream>
# include "../../Other/type_traits.hpp"
# include "../../Other/iterator.hpp"
# include "../../Other/algorithm.hpp"
# include "../../Other/utility.hpp"
# include <functional>
# define RED true
# define BLACK false
# include <unistd.h>

namespace ft {
	template <typename Key, typename Compare = std::less<Key>, typename Alloc = std::allocator<Key> >
	class set {
	public:
		typedef Key											key_type;
		typedef Key											value_type;
		typedef Compare										key_compare;
		typedef Alloc										allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer 			pointer;
		typedef typename allocator_type::const_pointer 		const_pointer;
		typedef ptrdiff_t 									difference_type;
		typedef size_t 										size_type;

		class value_compare: public std::binary_function<value_type, value_type, bool> {
		protected:
			key_compare comp;
			value_compare(key_compare c): comp(c) {};
		public:
			bool operator()(const value_type &x, const value_type &y) const {
				return(comp(x, y));
			}
		};

	private:
		class Comparator: public value_compare {
		public:
			Comparator(key_compare c): value_compare(c) {
				this->comp = c;
			};

		};
		allocator_type	_allocator;
		size_type 		_size;
		Comparator		_comparator;
		class Node {
		private:
			allocator_type _alloc;
		public:
			Node		*parent;
			Node		*left;
			Node		*right;
			bool 		color;
			value_type	*data;

			explicit Node(allocator_type a = allocator_type()): _alloc(a), parent(NULL), left(NULL), right(NULL), color(BLACK), data(NULL) {
				data = _alloc.allocate(1);
			};
			Node(value_type data, Node *nil, allocator_type alloc, bool color = RED) {
				parent = nil;
				left = nil;
				right = nil;
				_alloc = alloc;
				this->color = color;
				this->data = _alloc.allocate(1);
				_alloc.construct(this->data, data);
			}
			~Node() {
				_alloc.destroy(data);
				_alloc.deallocate(data, 1);
			}
		};
	private:

		/// Pointers

		Node			*_root;
		Node			*_end;
		Node			*_nil;
		Node			*_bnil;

		/// Map Iterator

		template<typename Type>
		class _map_iterator: public iterator<bidirectional_iterator_tag,
				typename ft::conditional<is_same<Type, const_pointer>::value, const value_type , value_type>::type,
				difference_type,
				typename ft::conditional<is_same<Type, const_pointer>::value, const value_type*, value_type*>::type,
				typename ft::conditional<is_same<Type, const_pointer>::value, const value_type&, value_type&>::type> {
		private:
			typedef typename ft::conditional<is_same<Type, const_pointer>::value, const value_type, value_type>::type	conditional_value;
			typedef typename ft::conditional<is_same<Type, const_pointer>::value, const value_type*, value_type*>::type	conditional_pointer;
			typedef typename ft::conditional<is_same<Type, const_pointer>::value, const value_type&, value_type&>::type	conditional_reference;
			int iterator;
			Node *ptr;
			Node *nil;
			Node *bnil;
			Node* 	base() const {return (ptr);}
		public:
			_map_iterator(): ptr(), nil(), bnil() {
			};
			explicit _map_iterator(Node* node, Node *n, Node *bn): ptr(node), nil(n), bnil(bn) {
			};
			template<typename Iter>
			_map_iterator(const _map_iterator<Iter>& it): ptr(it.ptr), nil(it.nil), bnil(it.bn) {
			};

			virtual ~_map_iterator() {
			};
			_map_iterator& operator=(const _map_iterator& it){
				ptr = it.base();
				nil = it.nil;
				bnil = it.bnil;
				return *this;
			};

			conditional_reference	operator*() const {return(*ptr->data);}
			conditional_pointer		operator->() const {return (ptr->data);}
			bool					operator==(const _map_iterator& it) const {
				return (ptr == it.ptr);
			}
			bool					operator!=(const _map_iterator& it) const {
				return (ptr != it.ptr);
			}
			_map_iterator& 			operator++() {
				if (ptr->right != nil) {
					ptr = ptr->right;
					while (ptr->left != nil)
						ptr = ptr->left;
				} else {
					while (ptr->parent != nil) {
						if (ptr->parent->right != ptr) {
							ptr = ptr->parent;
							return *this;
						}
						ptr = ptr->parent;
					}
					if (ptr->parent == nil)
						ptr = nil;
				}
				return *this;
			}
			_map_iterator 			operator++(int) {
				_map_iterator tmp(*this);
				++(*this);
				return tmp;
			}
			_map_iterator& 			operator--() {
				if (ptr->left != nil && ptr->left != NULL) {
					ptr = ptr->left;
					while (ptr->right != nil)
						ptr = ptr->right;
				} else {
					while (ptr->parent != nil) {
						if (ptr->parent->left != ptr || ptr->parent->right == ptr) {
							ptr = ptr->parent;
							return *this;
						}
						ptr = ptr->parent;
					}
					ptr = bnil;
				}
				return *this;
			}
			_map_iterator 			operator--(int) {
				_map_iterator tmp(*this);
				--(*this);
				return tmp;
			}
		};

		bool isNil(Node *node) {
			return (!node || node == _nil || node == _bnil);
		}

		bool isNil(Node *node) const {
			return (!node || node == _nil || node == _bnil);
		}

		void setNilParent() {
			Node *tmp;

			tmp = _root;
			while (!isNil(tmp->right)) {
				tmp = tmp->right;
			}
			_nil->parent = tmp;
		}
		void setBnilParent() {
			Node *tmp;

			tmp = _root;
			while (!isNil(tmp->left))
				tmp = tmp->left;
			_bnil->parent = tmp;
		}
		/// Algorithms

		Node * elderRecolor(Node *grandpa) {
			grandpa->right->color = BLACK;
			grandpa->left->color = BLACK;
			grandpa->color = RED;
			return grandpa;
		}

		void leftRotate(Node *x_node) {

			Node *p_node = x_node->parent;
			Node *y_node = x_node->right;
			Node *b_node = x_node->right->left;

			x_node->right = b_node;

			if (!isNil(b_node)) {
				b_node->parent = x_node;
			}
			if (isNil(p_node)) {
				y_node->parent = _nil;
				_root = y_node;
			}
			else if (p_node->left == x_node) {
				p_node->left = y_node;
				y_node->parent = p_node;
			}
			else {
				p_node->right = y_node;
				y_node->parent = p_node;
			}
			y_node->left = x_node;
			x_node->parent = y_node;
		}

		void rightRotate(Node *y_node) {
			Node *p_node = y_node->parent;
			Node *x_node = y_node->left;
			Node *b_node = x_node->right;

			y_node->left = b_node;
			if (!isNil(b_node)) {
				b_node->parent = y_node;
			}

			if (isNil(p_node)) {
				x_node->parent = _nil;
				_root = x_node;
			}
			else if (p_node->right == y_node) {
				p_node->right = x_node;
				x_node->parent = p_node;
			}
			else {
				p_node->left = x_node;
				x_node->parent = p_node;
			}
			x_node->right = y_node;
			y_node->parent = x_node;
		}

		void rebalance_insert(Node *newNode) {
			Node *pa;
			Node *grandpa;

			while (newNode->parent->color == RED) {
				pa = newNode->parent;
				grandpa = pa->parent;
				if (grandpa->left == pa) {
					if (grandpa->right->color == RED) {
						newNode = elderRecolor(grandpa);
					}
					else {
						if (pa->right == newNode) {
							newNode = pa;
							leftRotate(newNode);
						}
						pa->color = BLACK;
						grandpa->color = RED;
						rightRotate(grandpa);
					}
				}
				else {
					if (grandpa->left->color == RED) {
						newNode = elderRecolor(grandpa);
					}
					else {
						if (newNode == pa->left) {
							newNode = pa;
							rightRotate(newNode);
						}
						pa->color = BLACK;
						grandpa->color = RED;
						leftRotate(grandpa);
					}
				}
				_root->color = BLACK;
			}
		}

		void rebalance_erase(Node *x_node, Node *x_parent) {
			Node *w_node;

			while (true) {
				if (x_parent->left == x_node) {
					w_node = x_parent->right;
					if (x_node->color == RED) {
						x_node->color = BLACK;
						break;
					}
					if (x_node->color == BLACK && w_node->color == RED) {
						w_node->color = BLACK;
						x_parent->color = RED;
						leftRotate(x_parent);
						w_node = x_parent->right;
					}
					if (x_node->color == BLACK && w_node->color == BLACK) {
						if (isNil(w_node)){
							w_node->color = RED;
							x_node = x_parent;
							if (x_node->color == RED) {
								x_node->color = BLACK;
								break ;
							}
							break;
						}
						if (w_node->left->color == RED && w_node->right->color == BLACK) {

							w_node->left->color = BLACK;
							w_node->color = RED;
							rightRotate(w_node);
							w_node = x_parent->right;
						}
						else if (w_node->left->color == BLACK && w_node->right->color == BLACK) {
							w_node->color = RED;
							x_node = x_parent;
							if (x_node->color == RED) {
								x_node->color = BLACK;
								break ;
							}
							if (x_node->color == BLACK && x_node->parent == _nil)
								break;
						}
						if (w_node->right->color == RED) {
							w_node->color = x_parent->color;
							x_parent->color = BLACK;
							w_node->right->color = BLACK;
							leftRotate(x_parent);
							break;
						}
					}
				}
				else if (x_parent->right == x_node) {
					w_node = x_parent->left;
					if (x_node->color == RED) {
						x_node->color = BLACK;
						break;
					}
					if (x_node->color == BLACK && w_node->color == RED) {
						w_node->color = BLACK;
						x_parent->color = RED;
						rightRotate(x_parent);
						w_node = x_parent->left;
					}
					if (x_node->color == BLACK && w_node->color == BLACK) {
						if (isNil(w_node))
						{
							w_node->color = RED;
							x_node = x_parent;
							if (x_node->color == RED) {
								x_node->color = BLACK;
								break ;
							}
							break;
						}
						if (w_node->right->color == RED && w_node->left->color == BLACK) {
							w_node->right->color = BLACK;
							w_node->color = RED;
							leftRotate(w_node);
							w_node = x_parent->left;
						}
						else if (w_node->left->color == BLACK && w_node->right->color == BLACK) {
							w_node->color = RED;
							x_node = x_parent;
							if (x_node->color == RED) {
								x_node->color = BLACK;
								break ;
							}
							if (x_node->color == BLACK && x_node->parent == _nil)
								break;
						}
						if (w_node->left->color == RED) {
							w_node->color = x_parent->color;
							x_parent->color = BLACK;
							w_node->left->color = BLACK;
							rightRotate(x_parent);
							break ;
						}
					}
				}
				else {
					break;
				}
			}
			x_node->color = BLACK;
		}

		void transplant(Node *dst, Node *src) {
			if (isNil(src))
				return;
			if (isNil(dst->parent)){
				_root = src;
			}
			else if (dst->parent->left == dst) {
				dst->parent->left = src;
			}
			else {
				dst->parent->right = src;
			}
			if (!isNil(src))
				src->parent = dst->parent;
		}

		void fullTransplant(Node *dst, Node *src) {
			if (isNil(dst->parent)) {
				_root = src;
			}
			else if (dst->parent->left == dst) {
				dst->parent->left = src;
			}
			else {
				dst->parent->right = src;
			}
			if (!isNil(src)) {
				src->parent = dst->parent;
				if (dst->right != src && dst->left != src)
				{
					src->left = dst->left;
					src->right = dst->right;
				}
				else if (dst->right == src){
					dst->left->parent = src;
					src->left = dst->left;
				}
				else if (dst->left == src) {
					dst->right->parent = src;
					src->right = dst->right;
				}
			}
		}

		Node *rcopy(Node *node, Node *parent) {
			Node *new_node;

			if (node->left == NULL && node->right == NULL)
				return _nil;
			new_node = new Node(*node->data, _nil, _allocator, node->color);
			new_node->parent = parent;
			new_node->right = rcopy(node->right, new_node);
			new_node->left= rcopy(node->left, new_node);
			return new_node;
		}

		void rclear(Node *node) {

			if (node->left == NULL && node->right == NULL)
				return;
			rclear(node->left);
			rclear(node->right);
			delete node;
		}

	public:
		typedef _map_iterator<pointer>					iterator;
		typedef _map_iterator<const_pointer>			const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		//// Constructors
		/// empty
		explicit set(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		: _allocator(alloc), _size(), _comparator(comp), _root(), _end(), _nil(new Node(alloc)), _bnil(new Node(alloc)) {
			_root = _nil;
			_end = _nil;
		}
		/// range
		template<typename InputIterator>
		set(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(),
			typename enable_if<is_same<typename iterator_traits<InputIterator>::iterator_category::input_iterator_tag, input_iterator_tag>::value, void>::type* = NULL)
			: _root(), _end(), _nil(new Node(alloc)), _bnil(new Node(alloc)), _allocator(alloc), _size(), _comparator(comp) {
			_root = _nil;
			_end = _nil;

			insert(first, last);
		}
		/// copy
		set(const set& x)
		:_allocator(x.get_allocator()), _nil(new Node(x.get_allocator())), _bnil(new Node(x.get_allocator())), _size(x.size()),
		_comparator(x.key_comp()) {
			_root = rcopy(x._root, _nil);
		}

		//// Destructor
		virtual ~set(){
			clear();
			delete _nil;
			delete _bnil;
		};

		//// Assigment operator=
		set& operator=(const set& m) {
			clear();
			_root = rcopy(m._root, _nil);
		}

		//// Iterators
		iterator begin() {
			Node *ptr = _root;
			while (!isNil(ptr->left))
				ptr = ptr->left;
			return iterator(ptr, _nil, _bnil);
		}
		const_iterator begin() const {
			Node *ptr = _root;

			while (!isNil(ptr->left))
				ptr = ptr->left;
			return const_iterator(ptr, _nil, _bnil);
		}

		iterator end() {
			return iterator(_nil, _nil, _bnil);
		}
		const_iterator end() const {
			return const_iterator(_nil, _nil, _bnil);
		}

		reverse_iterator rbegin() {
			Node *ptr = _root;
			while (!isNil(ptr->left))
				ptr = ptr->left;
			return reverse_iterator(iterator(ptr, _nil, _bnil));
		}
		const_reverse_iterator rbegin() const {
			Node *ptr = _root;
			while (!isNil(ptr->left))
				ptr = ptr->left;
			return const_reverse_iterator(const_iterator(ptr, _nil, _bnil));
		}

		reverse_iterator rend() {
			Node *ptr = _root;
			while (!isNil(ptr->left))
				ptr = ptr->left;
			return reverse_iterator(iterator(ptr, _nil, _bnil));
		}
		const_reverse_iterator rend() const {
			const_iterator tmp(_end);
			const_reverse_iterator rit(tmp);
			return rit;
		}

		//// Capacity
		bool empty() const {
			return !_size;
		}
		size_type size() const {
			return _size;
		}
		size_type max_size() const {
			return (std::numeric_limits<size_type>::max() / sizeof(Node));
		}

		//// Element_access
		value_type& operator[](const key_type &k) {
			return find(k)->second;
		}

		//// Modifiers
		///insert
		pair<iterator, bool> insert(const value_type& val) {
			Node *node = new Node(val, _nil, _allocator);
			Node *tmp;
			Node *tmp_parent;

			tmp = _root;
			tmp_parent = _nil;
			while (!isNil(tmp)) {
				tmp_parent = tmp;
				if (_comparator(*node->data, *tmp->data)) {
					tmp = tmp->left;
				}
				else if (_comparator(*tmp->data, *node->data)) {
					tmp = tmp->right;
				}
				else {
					delete node;
					return make_pair(iterator(tmp, _nil, _bnil), false);
				}
			}
			node->parent = tmp_parent;
			if (isNil(tmp_parent)) {
				_root = node;
				_root->color = BLACK;
			}
			else if (_comparator(*node->data, *tmp_parent->data)) {
				tmp_parent->left = node;
			}
			else {
				tmp_parent->right = node;
			}
			_size++;
			rebalance_insert(node);
			setNilParent();
			setBnilParent();
			return make_pair(iterator(node, _nil, _bnil), true);
		}

		iterator insert(iterator position, const value_type& val) {
			(void)position;
			return insert(val).first;
		}

		template<typename InputIterator>
		void insert(InputIterator first, InputIterator last) {
			iterator tmp;
			while (first != last) {
				tmp = first++;
				this->insert(ft::make_pair(tmp->first, tmp->second));
			}
		}

		///erase
		void erase(iterator position) {
			Node *nodeToBeDeleted;
			Node *x_node;
			Node *nodeForReplace;
			Node *x_node_parent;
			value_type *pair;
			bool or_color;

			pair = position.operator->();
			nodeToBeDeleted = _root;
			x_node_parent = _nil;
			x_node = _nil;

			while (!isNil(nodeToBeDeleted)) {
				if (_comparator(*nodeToBeDeleted->data, *pair)) {
					nodeToBeDeleted = nodeToBeDeleted->right;
				}
				else if (_comparator(*pair, *nodeToBeDeleted->data)) {
					nodeToBeDeleted = nodeToBeDeleted->left;
				}
				else {
					break ;
				}
			}
			if (!isNil(nodeToBeDeleted)) {
				/// delete node
				or_color = nodeToBeDeleted->color;
				if (isNil(nodeToBeDeleted->left)) {
					nodeForReplace = nodeToBeDeleted->right;
					x_node = nodeToBeDeleted->right;
					x_node_parent = nodeToBeDeleted->parent;
				}
				else if (isNil(nodeToBeDeleted->right)) {
					nodeForReplace = nodeToBeDeleted->left;
					x_node = nodeToBeDeleted->left;
					x_node_parent = nodeToBeDeleted->parent;
				}
				else {
					nodeForReplace = nodeToBeDeleted->right;
					while(!isNil(nodeForReplace->left)) {
						nodeForReplace = nodeForReplace->left;
					}
					x_node = nodeForReplace->right;
					x_node_parent = nodeForReplace->parent;
					transplant(nodeForReplace, x_node);
				}
				fullTransplant(nodeToBeDeleted, nodeForReplace);
				///pre-balancing
				if (or_color == BLACK && nodeForReplace->color == RED) {
					nodeForReplace->color = BLACK;
					x_node->color = BLACK;
					or_color = RED;
				}
				else if (or_color == RED && nodeForReplace->color == BLACK && !isNil(nodeForReplace) && !isNil(x_node)) {
					nodeForReplace->color = RED;
					x_node->color = RED;
					or_color = BLACK;
				}
				delete nodeToBeDeleted;
				_size--;
				if (or_color == BLACK)
					rebalance_erase(x_node, x_node_parent);
				setBnilParent();
				setNilParent();
			}
		}

		size_type erase(const key_type& k) {
			iterator it = find(k);
			if (it != end()) {
				erase(it);
				return 1;
			}
			return 0;
		}

		void erase(iterator first, iterator last) {
			while (first != last) {
				erase(first++);
			}
		}

		void swap(set &x) {
			Node			*root;
			Node			*end;
			allocator_type	allocator;
			Comparator		comparator;
			size_type		size;

			root = _root;
			end = _end;
			allocator = _allocator;
			comparator = _comparator;
			size = _size;

			_root = x._root;
			_end = x._end;
			_allocator = x._allocator;
			_comparator = x._comparator;
			_size = x._size;

			x._root = root;
			x._end = end;
			x._allocator = allocator;
			x._comparator = comparator;
			x._size = size;
		}

		void clear() {
			rclear(_root);
			_size = 0;
			_root = _nil;
			//			erase(begin(), end());
			//			_root = _nil;
		}

		//// Observers

		key_compare key_comp() const {
			return key_compare();
		}

		value_compare value_comp() const {
			return _comparator;
		}

		//// Operations

		iterator find(const key_type& k) {
			Node *to_find(_root);
			key_compare comp;

			while (!isNil(to_find)) {
				if (comp(k, *to_find->data)) {
					to_find = to_find->left;
				}
				else if (comp(*to_find->data, k)) {
					to_find = to_find->right;
				}
				else {
					return iterator(to_find, _nil, _bnil);
				}
			}
			return iterator(_nil, _nil, _bnil);
		}

		const_iterator find(const key_type& k) const {
			Node *to_find(_root);
			key_compare comp;

			while (!isNil(to_find)) {
				if (comp(k, *to_find->data)) {
					to_find = to_find->left;
				}
				else if (comp(*to_find->data, k)) {
					to_find = to_find->right;
				}
				else {
					return const_iterator(to_find, _nil, _bnil);
				}
			}
			return const_iterator(_nil, _nil, _bnil);
		}

		size_type count(const key_type& k) const {
			if (find(k) != end())
				return 1;
			return 0;
		}

		iterator lower_bound(const key_type& k) {
			Node *ptr = _root;
			key_compare comp;

			while (*ptr->data != k) {
				if (comp(*ptr->data, k)) {
					if (isNil(ptr->right))
						break;
					ptr = ptr->right;
				}
				else {
					if (isNil(ptr->left))
						break;
					ptr = ptr->left;
				}
			}

			iterator it(ptr, _nil, _bnil);
			if (comp(*ptr->data, k)) {
				++it;
			}
			return it;
		}

		const_iterator lower_bound(const key_type& k) const {
			Node *ptr = _root;
			key_compare comp;

			while (ptr->data != k) {
				if (comp(ptr->data, k)) {
					if (isNil(ptr->right))
						break;
					ptr = ptr->right;
				}
				else {
					if (isNil(ptr->left))
						break;
					ptr = ptr->left;
				}
			}

			const_iterator it(ptr, _nil, _bnil);
			if (comp(ptr->data->first, k)) {
				++it;
			}
			return it;
		}

		iterator upper_bound(const key_type& k) {
			Node *ptr = _root;
			key_compare comp;

			while (*ptr->data != k) {
				if (comp(*ptr->data, k)) {
					if (isNil(ptr->right))
						break;
					ptr = ptr->right;
				}
				else {
					if (isNil(ptr->left))
						break;
					ptr = ptr->left;
				}
			}
			iterator it(ptr, _nil, _bnil);
			if (!comp(*ptr->data, k)) {
				++it;
			}
			return it;
		}

		const_iterator upper_bound(const key_type& k) const{
			Node *ptr = _root;
			key_compare comp;

			while (ptr->data->first != k) {
				if (!comp(ptr->data->first, k)) {
					if (isNil(ptr->right))
						break;
					ptr = ptr->right;
				}
				else {
					if (isNil(ptr->left))
						break;
					ptr = ptr->left;
				}
			}

			const_iterator it(ptr, _nil, _bnil);
			if (!comp(ptr->data->first, k)) {
				--it;
			}
			return it;
		}

		pair<const_iterator, const_iterator> equal_range(const key_type& k) const {
			return make_pair(lower_bound(k), upper_bound(k));
		}

		pair<iterator, iterator> equal_range(const key_type& k) {
			return make_pair(lower_bound(k), upper_bound(k));
		}

		//// Allocator
		allocator_type get_allocator() const {
			return _allocator;
		}
	};
}

#endif
