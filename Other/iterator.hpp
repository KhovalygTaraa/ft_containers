/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 18:40:33 by swquinc           #+#    #+#             */
/*   Updated: 2021/07/27 18:40:35 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP
# include <cstddef>
# include "type_traits.hpp"

namespace ft {

//// iterator inheritance
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag: public input_iterator_tag {};
	struct bidirectional_iterator_tag: public forward_iterator_tag {};
	struct random_access_iterator_tag: public bidirectional_iterator_tag {};

//// iterator_traits
	template<typename Iterator, typename = typename Iterator::pointer>
	class iterator_traits {
	public:
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};

	template<typename T>
	class iterator_traits<T*> {
	public:
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef random_access_iterator_tag iterator_category;
	};

	template<typename T>
	class iterator_traits<const T*> {
	public:
		typedef const ptrdiff_t difference_type;
		typedef const T value_type;
		typedef const T* pointer;
		typedef const T& reference;
		typedef const random_access_iterator_tag iterator_category;
	};


//// parent of all iterators
	template<typename Category, typename T, typename Distance, typename Pointer = T*, typename Reference = T&>
	class iterator {
	protected:
		virtual ~iterator(){};
	public:
		typedef Category	iterator_category;
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
	};

//// distance reimplementation

template<typename InputIterator>
static typename iterator_traits<InputIterator>::difference_type
my_distance_helper(InputIterator first,  InputIterator second, ft::random_access_iterator_tag) {
	return (second - first);
}

template<typename InputIterator>
static typename iterator_traits<InputIterator>::difference_type
my_distance_helper(InputIterator first, InputIterator second, InputIterator) {
	typename iterator_traits<InputIterator>::difference_type i;
	InputIterator it;

	it = first;
	for(i = 0; it != second; i++)
		it++;
	return (i);
}

template<typename InputIterator>
typename iterator_traits<InputIterator>::difference_type
distance(InputIterator first, InputIterator second,
		 typename enable_if<is_same<typename iterator_traits<InputIterator>::iterator_category::input_iterator_tag,
		 input_iterator_tag>::value, void>::type* = NULL) {

	return (my_distance_helper(first, second, typename iterator_traits<InputIterator>::iterator_category()));
}


//// reverse iterator
	template<typename Iterator>
	class reverse_iterator {
	private:
		Iterator iter;
	public:
		typedef 			Iterator 										iterator_type;
		typedef typename	iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename	iterator_traits<Iterator>::value_type			value_type;
		typedef typename	iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename	iterator_traits<Iterator>::pointer				pointer;
		typedef typename	iterator_traits<Iterator>::reference			reference;

		reverse_iterator(): iter()
		{
		};

		explicit reverse_iterator(Iterator it): iter(it)
		{
			iter--;
		};

		template<typename Iter>
		reverse_iterator(const reverse_iterator<Iter>& rev)
		{
			iter = rev.base();
		};

		reverse_iterator& operator=(const reverse_iterator& it) {
			iter = it.base();
			return (*this);
		}
		Iterator base() const
		{
			return (iter);
		};

		reference operator*() const {
			return (*iter);
		};

		reverse_iterator& operator++() {
			iter--;
			return (*this);
		};

		reverse_iterator operator++(int) {
			reverse_iterator tmp = *this;
			iter--;
			return (tmp);
		};

		reverse_iterator& operator--() {
			iter++;
			return (*this);
		};

		reverse_iterator operator--(int) {
			reverse_iterator tmp = *this;
			iter++;
			return (tmp);
		};

		reverse_iterator& operator+=(difference_type n) {
			iter -= n;
			return (*this);
		};

		reverse_iterator& operator-=(difference_type n) {
			iter += n;
			return (*this);
		};

		reverse_iterator operator+(difference_type n) const {
			reverse_iterator tmp = *this;
			tmp.iter -= n;
			return (tmp);
		};

		reverse_iterator operator-(difference_type n) const {
			reverse_iterator tmp = *this;
			tmp.iter += n;
			return (tmp);
		};

		pointer operator->() const {
			return (iter.operator->());
		};

		reference operator[](difference_type n) const {
			n *= -1;
			return (iter[n]);
		}
	};

	template<typename Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n,
			const reverse_iterator<Iterator>& rev_it) {
		return (rev_it.operator+(n));
	}

	template<typename Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(
			const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs) {
		return (ft::distance(lhs.base(), rhs.base()));
	}

	template<typename Iterator>
	bool operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template<typename Iterator>
	bool operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template<typename Iterator>
	bool operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template<typename Iterator>
	bool operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template<typename Iterator>
	bool operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template<typename Iterator>
	bool operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() <= rhs.base());
	}
}

#endif

