/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 10:17:19 by swquinc           #+#    #+#             */
/*   Updated: 2021/07/27 10:17:20 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

namespace ft {
//// enable_if
	 template<bool B, typename T = void>
	 struct enable_if {
	 };

	 template<typename T>
	 struct enable_if<true, T> {
	 	typedef T type;
	 };

//// is_same
	 template<typename A, typename B>
	 struct is_same {
	 	static const bool value = false;
	 };

	 template<typename A>
	 struct is_same<A, A> {
	 	static const bool value = true;
	 };

//// is_integral


	template<typename T, T val>
	struct integral_const {
		static const T value = val;
	};

	struct true_type:	public integral_const<bool, true>{};
	struct false_type:	public integral_const<bool, false> {};

	template<typename T>
	struct is_integral: public false_type {};

	template<> struct is_integral<int>:					public true_type {};
	template<> struct is_integral<short>:				public true_type {};
	template<> struct is_integral<char>:				public true_type {};
	template<> struct is_integral<long>:				public true_type {};
	template<> struct is_integral<long long>:			public true_type {};
	template<> struct is_integral<bool>:				public true_type {};
	template<> struct is_integral<wchar_t>:				public true_type {};
	template<> struct is_integral<unsigned int>:		public true_type {};
	template<> struct is_integral<unsigned short>:		public true_type {};
	template<> struct is_integral<unsigned char>:		public true_type {};
	template<> struct is_integral<unsigned long>:		public true_type {};
	template<> struct is_integral<unsigned long long>:	public true_type {};

//// conditional
	template<bool Cond, typename T, typename F>
	struct conditional {
		typedef F type;
	};
	template<typename T, typename F>
	struct conditional<true, T, F> {
		typedef T type;
	};

}

#endif