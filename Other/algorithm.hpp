/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 13:08:08 by swquinc           #+#    #+#             */
/*   Updated: 2021/08/10 13:08:09 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP
# include "iterator.hpp"
# include "type_traits.hpp"

namespace ft {
	template <typename InputIterator1, typename InputIterator2>
	typename ft::enable_if<(ft::is_same<typename ft::iterator_traits<InputIterator1>::iterator_category::input_iterator_tag, ft::input_iterator_tag>::value)
	&& (ft::is_same<typename ft::iterator_traits<InputIterator2>::iterator_category::input_iterator_tag, ft::input_iterator_tag>::value),bool>::type
	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
		while (first1 != last1) {
			if (*first1 != *first2)
				return (false);
			++first1;
			++first2;
		}
		return (true);
	}

	template <typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
	typename ft::enable_if<(ft::is_same<typename ft::iterator_traits<InputIterator1>::iterator_category::input_iterator_tag, ft::input_iterator_tag>::value)
	&& (ft::is_same<typename ft::iterator_traits<InputIterator2>::iterator_category::input_iterator_tag, ft::input_iterator_tag>::value),bool>::type
	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred) {
		while (first1 != last1) {
			if (!pred(*first1, *first2))
				return (false);
			++first1;
			++first2;
		}
		return (true);
	}

	template<typename InputIterator1, typename InputIterator2>
	typename ft::enable_if<(ft::is_same<typename ft::iterator_traits<InputIterator1>::iterator_category::input_iterator_tag, ft::input_iterator_tag>::value)
	&& (ft::is_same<typename ft::iterator_traits<InputIterator2>::iterator_category::input_iterator_tag, ft::input_iterator_tag>::value),bool>::type
	lexicographical_compare(InputIterator1 first1, InputIterator2 last1, InputIterator2 first2, InputIterator2 last2) {
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return (false);
			else if (*first1 > *first2)
				return (true);
			first1++;
			first2++;
		}
		return(first2 != last2);
	}

	template<typename InputIterator1, typename InputIterator2, typename Compare>
	typename ft::enable_if<(ft::is_same<typename ft::iterator_traits<InputIterator1>::iterator_category::input_iterator_tag, ft::input_iterator_tag>::value)
	&& (ft::is_same<typename ft::iterator_traits<InputIterator2>::iterator_category::input_iterator_tag, ft::input_iterator_tag>::value),bool>::type
	lexicographical_compare(InputIterator1 first1, InputIterator2 last1, InputIterator2 first2, InputIterator2 last2, Compare comp) {
		while (first1 != last1)
		{
			if (first2 == last2 || comp(*first1, *first2))
				return (false);
			else if (comp(*first2, *first1))
				return (true);
			first1++;
			first2++;
		}
		return(first2 != last2);
	}
}
#endif

